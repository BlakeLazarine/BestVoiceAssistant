# -*- coding: utf-8 -*-

import numpy as np
from scipy.signal import find_peaks

#Filled in at beginning of commands
commandLine = []
#An array of arrays which are the sequences that make commands
commands = [[0, 2], [1, 2], [0, 1, 0, 1]]

def frequency_analyzer(data):    
    freq = np.arange(len(data))
    fourier = np.fft.fft(data)
    return fourier
    
#returns which level of frequency we are detecting
def findTone(data):
    peakFreqs, values = find_peaks(np.abs(data), height = 14000, distance = 500)
    bigPeak = 0.0
    peakHeights = values['peak_heights']
    for i in range (len(peakHeights)):
        if (peakHeights[i] == max(peakHeights)):
            bigPeak = peakFreqs[i]
    print(bigPeak)
    if (bigPeak < 1200):
        return 0
    elif (bigPeak > 2300):
        return 2
    else:
        return 1

#for creating commands
def commands(data):
    if (findTone(data) == -1):
        return
    dataNum = findTone(data)
    whichCommand = 0
    commandLine.append(dataNum)
    for x in range(len(commandList)):
        tempList = commandList[x]
        if (len(commandLine) >= len(tempList)):
            executeCommand = True
            for i in range(len(tempList)):
                if (commandLine[i] != tempList[i]):
                    executeCommand = False
            if (executeCommand):
                whichCommand = x
                for i in range(len(tempList)):
                    del commandLine[0]
    if (whichCommand == 1):
        print("Command 1")
        #command 1
    elif (whichCommand == 2):
        print("Command 2")
        #command 2
    elif (whichCommand == 3):
        print("Command 3")
        #command 3
        
#A different variant of commands
def alternateCommands(data):
    commandLine.append(data)                
    if (len(commandLine) > 3):
        if (commandLine[0] == 0 && commandLine[1] == 1 && commandLine[2] == 0 && commandLine[3] == 1):
            print("Command 3") #replace with call to whatever function
            commandLine.remove(0)
            commandLine.remove(0)
            commandLine.remove(0)
            commandLine.remove(0)
    if (len(commandLine) > 1)
        if (commandLine[0] == 0 && commandLine[1] == 2):
            print("Command 1") # replace with call to whatever function
            commandLine.remove(0)
            commandLine.remove(0)
        elif (commandLine[0] == 1 && commandLine[2] == 2):
            print("Command 2") # replace with call to whatever function
            commandLine.remove(0)
            commandLine.remove(0)
    
data = #put data here

changed = false

#continously run

if (changed):
    changed = false
    commands(findTone(data)
