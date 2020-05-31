# -*- coding: utf-8 -*-

import numpy as np
from scipy.signal import find_peaks
import serial
import SendSongBytes


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
                # blue()
                pass
            elif whichCommand == 1:
                pass
                # red()
            elif whichCommand == 2:
                pass
                # time()
            elif whichCommand == 3:
                pass
                # weather()
            elif whichCommand == 4:
                pass
                # joke()
            elif whichCommand == 5:
                songSelect = True
            elif whichCommand == 6:
                pass
                # lightShow()
        else:
            songSelect = False
            SendSongBytes.playSong(ser, SendSongBytes.songArray[whichCommand])

    '''
    for x in range(len(commandList)):
        tempList = commandList[x]
        if (len(commandLine) >= len(tempList)):
            executeCommand = True
            for i in range(len(tempList)):
                if (commandLine[len(commandLine) - i] != tempList[len(tempList(i))]):
                    executeCommand = False
                if (executeCommand):
                    whichCommand = x
                for i in range(len(tempList)):
                    del commandLine[0]
                if (whichCommand == 1):
                    print("Command 1")
                # command 1
                elif (whichCommand == 2):
                    print("Command 2")
                # command 2
                elif (whichCommand == 3):
                    print("Command 3")
                # command 3
    '''