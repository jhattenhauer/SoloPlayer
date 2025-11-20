import guitarpro
import logging
import os


tab_file = input("Select GP3 file")
song = guitarpro.parse(tab_file)

log_file = "track_output.log"
if os.path.exists(log_file):
    os.remove(log_file)

logging.basicConfig(filename='track_output.log', level=logging.DEBUG)

#track selection
track_index = 0
for i in song.tracks:
    print(f"Track index {track_index}: {i.name}")
    track_index += 1
selected_track_index = int(input("Select input track: "))

selected_track = song.tracks[selected_track_index]
print(selected_track.name)

