import guitarpro
import logging
import os


tab_file = "/home/ubuntu/projects/SoloPlayer/libraries/tabs/creed-one_last_breath.gp3"
song = guitarpro.parse(tab_file)

log_file = "/home/ubuntu/projects/SoloPlayer/libraries/track_output.log"
if os.path.exists(log_file):
    os.remove(log_file)

logging.basicConfig(filename='/home/ubuntu/projects/SoloPlayer/libraries/track_output.log', level=logging.DEBUG)

for track in song.tracks:
    logging.debug(f"{track.name}")
    for measure in track.measures:
        for voice in measure.voices:
            for beat in voice.beats:
                for note in beat.notes:
                    logging.debug(f"String: {note.string}, Fret: {note.value}")  # value = fret
