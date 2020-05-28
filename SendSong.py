import serial
import time

NOTE_B0  = 31
NOTE_C1  = 33
NOTE_CS1 = 35
NOTE_D1  = 37
NOTE_DS1 = 39
NOTE_E1  = 41
NOTE_F1  = 44
NOTE_FS1 = 46
NOTE_G1  = 49
NOTE_GS1 = 52
NOTE_A1  = 55
NOTE_AS1 = 58
NOTE_B1  = 62
NOTE_C2  = 65
NOTE_CS2 = 69
NOTE_D2  = 73
NOTE_DS2 = 78
NOTE_E2  = 82
NOTE_F2  = 87
NOTE_FS2 = 93
NOTE_G2  = 98
NOTE_GS2 = 104
NOTE_A2  = 110
NOTE_AS2 = 117
NOTE_B2  = 123
NOTE_C3  = 131
NOTE_CS3 = 139
NOTE_D3  = 147
NOTE_DS3 = 156
NOTE_E3  = 165
NOTE_F3  = 175
NOTE_FS3 = 185
NOTE_G3  = 196
NOTE_GS3 = 208
NOTE_A3  = 220
NOTE_AS3 = 233
NOTE_B3  = 247
NOTE_C4  = 262
NOTE_CS4 = 277
NOTE_D4  = 294
NOTE_DS4 = 311
NOTE_E4  = 330
NOTE_F4  = 349
NOTE_FS4 = 370
NOTE_G4  = 392
NOTE_GS4 = 415
NOTE_A4  = 440
NOTE_AS4 = 466
NOTE_B4  = 494
NOTE_C5  = 523
NOTE_CS5 = 554
NOTE_D5  = 587
NOTE_DS5 = 622
NOTE_E5  = 659
NOTE_F5  = 698
NOTE_FS5 = 740
NOTE_G5  = 784
NOTE_GS5 = 831
NOTE_A5  = 880
NOTE_AS5 = 932
NOTE_B5  = 988
NOTE_C6  = 1047
NOTE_CS6 = 1109
NOTE_D6  = 1175
NOTE_DS6 = 1245
NOTE_E6  = 1319
NOTE_F6  = 1397
NOTE_FS6 = 1480
NOTE_G6  = 1568
NOTE_GS6 = 1661
NOTE_A6  = 1760
NOTE_AS6 = 1865
NOTE_B6  = 1976
NOTE_C7  = 2093
NOTE_CS7 = 2217
NOTE_D7  = 2349
NOTE_DS7 = 2489
NOTE_E7  = 2637
NOTE_F7  = 2794
NOTE_FS7 = 2960
NOTE_G7  = 3136
NOTE_GS7 = 3322
NOTE_A7  = 3520
NOTE_AS7 = 3729
NOTE_B7  = 3951
NOTE_C8  = 4186
NOTE_CS8 = 4435
NOTE_D8  = 4699
NOTE_DS8 = 4978
REST     =  255

take_on_me = [

NOTE_FS5, 8, NOTE_FS5, 8, NOTE_D5, 8, NOTE_B4, 8, REST, 8, NOTE_B4, 8, REST, 8, NOTE_E5, 8,
REST, 8, NOTE_E5, 8, REST, 8, NOTE_E5, 8, NOTE_GS5, 8, NOTE_GS5, 8, NOTE_A5, 8, NOTE_B5, 8,
NOTE_A5, 8, NOTE_A5, 8, NOTE_A5, 8, NOTE_E5, 8, REST, 8, NOTE_D5, 8, REST, 8, NOTE_FS5, 8,
REST, 8, NOTE_FS5, 8, REST, 8, NOTE_FS5, 8, NOTE_E5, 8, NOTE_E5, 8, NOTE_FS5, 8, NOTE_E5, 8,
NOTE_FS5, 8, NOTE_FS5, 8, NOTE_D5, 8, NOTE_B4, 8, REST, 8, NOTE_B4, 8, REST, 8, NOTE_E5, 8,

REST, 8, NOTE_E5, 8, REST, 8, NOTE_E5, 8, NOTE_GS5, 8, NOTE_GS5, 8, NOTE_A5, 8, NOTE_B5, 8,
NOTE_A5, 8, NOTE_A5, 8, NOTE_A5, 8, NOTE_E5, 8, REST, 8, NOTE_D5, 8, REST, 8, NOTE_FS5, 8,
REST, 8, NOTE_FS5, 8, REST, 8, NOTE_FS5, 8, NOTE_E5, 8, NOTE_E5, 8, NOTE_FS5, 8, NOTE_E5, 8,
NOTE_FS5, 8, NOTE_FS5, 8, NOTE_D5, 8, NOTE_B4, 8, REST, 8, NOTE_B4, 8, REST, 8, NOTE_E5, 8,
REST, 8, NOTE_E5, 8, REST, 8, NOTE_E5, 8, NOTE_GS5, 8, NOTE_GS5, 8, NOTE_A5, 8, NOTE_B5, 8,

NOTE_A5, 8, NOTE_A5, 8, NOTE_A5, 8, NOTE_E5, 8, REST, 8, NOTE_D5, 8, REST, 8, NOTE_FS5, 8,
REST, 8, NOTE_FS5, 8, REST, 8, NOTE_FS5, 8, NOTE_E5, 8, NOTE_E5, 8, NOTE_FS5, 8, NOTE_E5, 8

]
cantina = [440, 4, 587, 8, 255, 8, 440, 8, 255, 8, 587, 8, 255, 8, 440, 8, 587, 8, 255, 8, 440, 4, 415, 8, 440, 8, 255, 8, 440, 8, 415, 8, 440, 8, 392, 2, 392, 8, 255, 8, 349, 2, 294, 2, 440, 8, 255, 8, 587, 8, 255, 8, 440, 8, 255, 8, 587, 8, 255, 8, 440, 8, 587, 8, 255, 8, 440, 4, 415, 8, 440, 4, 392, 8, 255, 8, 392, 2, 370, 8, 392, 4, 523, 8, 466, 8, 255, 8, 440, 8, 255, 8, 392, 4, 415, 8, 440, 8, 255, 8, 587, 8, 255, 8, 440, 8, 255, 8, 587, 8, 255, 8, 440, 8, 587, 8, 255, 8, 440, 4, 415, 8, 440, 4, 523, 8, 255, 8, 523, 2, 440, 8, 392, 4, 349, 2, 294, 8, 255, 2, 294, 2, 349, 2, 392, 8, 415, 8, 440, 4, 523, 2, 554, 16, 587, 16, 622, 16, 255, 16, 587, 8, 255, 8, 415, 8, 440, 8, 255, 8, 349, 4]
megalovania = [294, 18, 255, 285, 294, 17, 255, 285, 587, 16, 255, 16, 440, 5, 255, 105, 415, 16, 255, 16, 392, 16, 255, 16, 349, 8, 255, 153, 294, 17, 255, 285, 349, 17, 255, 285, 392, 17, 255, 285, 262, 18, 255, 285, 262, 17, 255, 285, 587, 16, 255, 16, 440, 5, 255, 105, 415, 16, 255, 16, 392, 16, 255, 16, 349, 8, 255, 153, 294, 17, 255, 285, 349, 17, 255, 285, 392, 17, 255, 285, 247, 18, 255, 285, 247, 17, 255, 285, 587, 16, 255, 16, 440, 5, 255, 105, 415, 16, 255, 16, 392, 16, 255, 16, 349, 8, 255, 153, 294, 17, 255, 285, 349, 17, 255, 285, 392, 17, 255, 285, 233, 18, 255, 285, 233, 17, 255, 285, 587, 16, 255, 16, 440, 5, 255, 105, 262, 17, 255, 16, 262, 16, 255, 16, 262, 8, 255, 153, 294, 17, 255, 285, 349, 17, 255, 285, 392, 17, 255, 285, 294, 17, 255, 285, 294, 17, 255, 285, 587, 16, 255, 16, 440, 5, 255, 105, 415, 16, 255, 16, 392, 16, 255, 16, 349, 8, 255, 153, 294, 17, 255, 285, 349, 17, 255, 285, 392, 17, 255, 285, 262, 17, 255, 285, 262, 17, 255, 285, 587, 16, 255, 16]
despacito = [255, 10, 277, 3, 255, 10, 247, 2, 255, 5, 247, 10, 277, 10, 255, 6, 330, 6, 294, 10, 277, 6, 255, 6, 220, 10, 196, 3, 294, 3, 294, 1, 255, 2, 294, 5, 220, 5, 294, 5, 220, 5, 294, 5, 220, 5, 294, 5, 330, 10, 277, 2, 255, 0, 247, 2, 255, 10, 185, 10, 247, 10, 277, 10, 294, 6, 330, 6, 255, 10, 277, 6, 247, 6, 255, 10, 196, 3, 294, 3, 330, 5, 294, 2, 255, 2, 294, 5, 255, 5, 294, 5, 220, 5, 294, 5, 220, 5, 294, 5, 330, 10, 277, 2, 255, 2, 294, 4, 255, 10, 277, 3, 255, 10, 247, 2, 247, 10, 247, 10, 247, 10, 277, 10, 255, 10, 277, 10, 294, 6]
def playSong(ser, song):
    ser.write((str(len(song) / 2) + " ").encode('utf-8'))
    for i in range(len(song)):
        print(song[i])
        # rin = ser.read()
        # while (not rin):
        #     rin = ser.read()
        # time.sleep(0.1)
        # print('rin', rin)
        ser.write((str(song[i]) + " ").encode('utf-8'))
        time.sleep(0.07)
        # time.sleep(0.1)



    print('here')
    mes = ser.readline()
    while not mes:
        mes = ser.readline()
    print(mes)

if __name__ == '__main__':
    comm_port = "COM15"
    sampleInput = serial.Serial(comm_port, 115200, timeout=5)
    while(not sampleInput.read()):
        pass
    # sampleInput.write("1".encode('utf-8'));
    playSong(sampleInput, cantina)