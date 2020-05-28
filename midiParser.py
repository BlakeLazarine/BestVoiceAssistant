import mido

# Credit to Jacob Dorny for gathering all midi files used in this

file = 'songs/Despacito3.mid'
raw_midi = mido.MidiFile(file)
track = mido.merge_tracks(raw_midi.tracks)
note_vals = [31
,33
,35
,37
,39
,41
,44
,46
,49
,52
,55
,58
,62
,65
,69
,73
,78
,82
,87
,93
,98
,104
,110
,117
,123
,131
,139
,147
,156
,165
,175
,185
,196
,208
,220
,233
,247
,262
,277
,294
,311
,330
,349
,370
,392
,415
,440
,466
,494
,523
,554
,587
,622
,659
,698
,740
,784
,831
,880
,932
,988
,1047
,1109
,1175
,1245
,1319
,1397
,1480
,1568
,1661
,1760
,1865
,1976
,2093
,2217
,2349
,2489
,2637
,2794
,2960
,3136
,3322
,3520
,3729
,3951
,4186
,4435
,4699
,4978]
notes = []
t = 0
for msg in track:
    tempo = 0
    # if t > 10000:
    #     break
    if msg.type == "set_tempo":
        tempo = msg.tempo
    elif msg.type == "note_on":
        # if(msg.time > 1500):
        #     print("on", msg.note, msg)
        #     break
        if(msg.time > 1):
            notes.append(255)
            notes.append(int(2000/msg.time))
            t+=msg.time

    elif msg.type == "note_off":
        # print("off", msg.note, msg)
        if (msg.time > 1):
            notes.append(note_vals[msg.note-23])
            notes.append(int(2000/msg.time))
            t += msg.time

print(notes)
print(len(notes))