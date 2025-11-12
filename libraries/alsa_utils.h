#include <alsa/asoundlib.h>
#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <chrono>
#include <thread>

snd_pcm_t* _soundDevice = nullptr;

bool InitCapture(const char* name) { //setup alsa device
    int err;
    snd_pcm_hw_params_t* hw_params;
    err = snd_pcm_open(&_soundDevice, name ? name : "hw:3,0", SND_PCM_STREAM_CAPTURE, 0); //magic number 'hw:3,0' is just alsa endpoint
    if (err < 0) {
        std::cerr << "Cannot open audio device for capture (" << snd_strerror(err) << ")" << std::endl;
        return false;
    }

    snd_pcm_hw_params_malloc(&hw_params);
    snd_pcm_hw_params_any(_soundDevice, hw_params);

    snd_pcm_hw_params_set_access(_soundDevice, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED);
    snd_pcm_hw_params_set_format(_soundDevice, hw_params, SND_PCM_FORMAT_S32_LE);
    snd_pcm_hw_params_set_channels(_soundDevice, hw_params, 4);

    unsigned int sample_rate = 44100;
    snd_pcm_hw_params_set_rate_near(_soundDevice, hw_params, &sample_rate, 0);

    snd_pcm_hw_params(_soundDevice, hw_params);
    snd_pcm_hw_params_free(hw_params);

    snd_pcm_prepare(_soundDevice);
    return true;
}

std::vector<float> Int_to_Float(const std::vector<int32_t>& intBuffer) {
    std::vector<float> floatBuffer(intBuffer.size());
    const float scale = 1.0f / static_cast<float>(INT32_MAX);
    for (size_t i = 0; i < intBuffer.size(); ++i)
        floatBuffer[i] = static_cast<float>(intBuffer[i]) * scale;
    return floatBuffer;
}

std::vector<int32_t> Float_to_Int(const std::vector<float>& floatBuffer) {
    std::vector<int32_t> intBuffer(floatBuffer.size());
    for (size_t i = 0; i < floatBuffer.size(); ++i) {
        float clamped = std::max(-1.0f, std::min(1.0f, floatBuffer[i])); // avoid overflow
        intBuffer[i] = static_cast<int32_t>(clamped * INT32_MAX);
    }
    return intBuffer;
}

std::vector<int32_t> CaptureSample() {
    const int framesPerChunk = 1024;
    const int channels = 4;
    std::vector<int32_t> intBuffer(framesPerChunk * channels);

    int err = snd_pcm_readi(_soundDevice, intBuffer.data(), framesPerChunk);
    if (err == -EPIPE) {
        std::cerr << "Overrun occurred!" << std::endl;
        snd_pcm_prepare(_soundDevice);
    } else if (err < 0) {
        std::cerr << "Read error: " << snd_strerror(err) << std::endl;
        snd_pcm_prepare(_soundDevice);
    } else if (err != framesPerChunk) {
        std::cerr << "Short read, got " << err << " frames" << std::endl;
    }

    return intBuffer;
}

void UnInit() {
    if (_soundDevice) {
        snd_pcm_close(_soundDevice);
        _soundDevice = nullptr;
        std::cout << "Capture device closed." << std::endl;
    }
}