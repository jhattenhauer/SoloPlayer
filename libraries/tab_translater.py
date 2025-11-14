import guitarpro
import logging

file_path = "/home/ubuntu/projects/SoloPlayer/libraries/creed-one_last_breath.gp3"
song = guitarpro.parse(file_path)

logging.basicConfig(filename='track_output.log', level=logging.DEBUG)

for track in song.tracks:
    logging.debug(f"{track.name}")
    for measure in track.measures:
        for voice in measure.voices:
            for beat in voice.beats:
                for note in beat.notes:
                    logging.debug(f"String: {note.string}, Fret: {note.value}")  # value = fret
