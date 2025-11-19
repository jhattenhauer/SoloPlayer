import guitarpro
import logging
import os


tab_file = "tabs/creed-one_last_breath.gp3"
song = guitarpro.parse(tab_file)

log_file = "track_output.log"
if os.path.exists(log_file):
    os.remove(log_file)

logging.basicConfig(filename='track_output.log', level=logging.DEBUG)


lead_guitar = song.tracks[0]
beat_count = 0

logging.debug(f"{song.title}")
logging.debug(f"{song.tempo}")

for track in song.tracks:
    logging.debug(f"{track.name}")
    for measure in track.measures:
        for voice in measure.voices:
            for beat in voice.beats:
                logging.debug(f"\nbreak note\n")
                for note in beat.notes:
                    logging.debug(f"String: {note.string}, Fret: {note.value}")            
                    pass
