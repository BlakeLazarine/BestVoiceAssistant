# -*- coding: utf-8 -*-

import numpy as np
from scipy.signal import find_peaks
import serial
import SendSongBytes
import weatherTest
import time


# Filled in at beginning of commands
commandLine = []
# An array of arrays which are the sequences that make commands

commandList = [[0,0],[0,1],[0,2],[1,0],[1,1],[1,2],[2,0],[2,1],[2,2]]
songSelect = False

def frequency_analyzer(data):
    freq = np.arange(len(data))
    fourier = np.fft.fft(data)
    return fourier


# returns which level of frequency we are detecting
def findTone(data):
    peakFreqs, values = find_peaks(np.abs(data), height=14000, distance=500)
    x = np.arange(len(data)) * 32500 / len(data)
    bigPeak = 0
    peakHeights = values['peak_heights']
    for i in range(len(peakHeights)):
        if (peakHeights[i] == max(peakHeights) and 0 < x[peakFreqs[i]] < 5000):
            bigPeak = peakFreqs[i]
    # print("here",x[bigPeak])
    if (x[bigPeak] < 800):
        return -1
    elif (x[bigPeak] < 1200):
        return 0
    elif (x[bigPeak] > 2300):
        return 2
    else:
        return 1

# sends text
def sendText(ser, text):
    ser.write("3 ".encode('utf-8'))
    time.sleep(0.05)
    if (len(text) > 64):
        ser.write(text[0:64].encode('utf-8'))
        time.sleep(0.1)
        ser.write(text[64].encode('utf-8'))
    else:
        ser.write(text.encode('utf-8'))
    mes = ser.readline()
    while not mes:
        mes = ser.readline()
    print(mes)
    
def getTime():
    currentTime = time.localtime()
    timeString = str(currentTime.tm_hour) + ":" + str(currentTime.tm_min)
    return timeString

# for creating commands
def commands(data, ser):
    global commandLine
    global songSelect
    dataNum = findTone(data)
    if (dataNum == -1):
        return
    print(dataNum)
    whichCommand = -1
    commandLine.append(dataNum)
    for i in range(len(commandList)):
        c = commandList[i]
        if len(c) > len(commandLine):
            continue
        if commandLine[-len(c):] == c:
            whichCommand = i
    print("whichcommand", whichCommand)
    if whichCommand != -1:
        #send arduino command
        commandLine = []

        if not songSelect:
            if whichCommand == 0:
                ser.write("1 ".encode('utf-8'))
                #blue
            elif whichCommand == 1:
                ser.write("2 ".encode('utf-8'))
                #red
            elif whichCommand == 2:
                sendText(ser, getTime())
                # time()
            elif whichCommand == 3:
                sendText(ser, weatherTest.getTempFahrenheit())
                #weather()
            elif whichCommand == 4:
                ser.write("5 ".encode('utf-8'))
                #joke
            elif whichCommand == 5:
                songSelect = True
                #song
            elif whichCommand == 6:
                ser.write("7 ".encode('utf-8'))
                # lightShow()
        else:
            songSelect = False
            SendSongBytes.playSong(ser, SendSongBytes.songArray[whichCommand])