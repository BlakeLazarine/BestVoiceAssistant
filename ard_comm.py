import serial
import numpy as np
import matplotlib.pyplot as plt

comm_port = "COM15"
sampleInput = serial.Serial(comm_port, 115200, timeout=5)
buffSize = 255

def read_one_sample(inBuf, start):
    sampleInput.write("1".encode('utf-8'))
    data = sampleInput.read()
    i = start
    while(i < start + buffSize):

        inBuf[i] = ((ord(data) << 8)) | ord(sampleInput.read())
        data = sampleInput.read()
        i += 1
        print(i)
    print("done")


def read_n_samples(n):
    inBuff = np.array([0] * n * buffSize)
    for i in range(n):
        read_one_sample(inBuff, i * buffSize)
    inBuff -= 43500
    fft = np.fft.fft(inBuff)
    x = np.arange(len(inBuff)) * 32500 / len(inBuff)
    t = np.arange(len(inBuff)) / 32500
    plt.plot(x, abs(fft))
    # plt.plot(t, inBuff)
    plt.xlim(0, 1000)
    plt.show()

def testInput():
    sampleInput.write("4".encode('utf-8'))
    print(sampleInput.readline())

while True:
    inp = input()
    if(inp == 'blue'):
        sampleInput.write("3".encode('utf-8'))
    if (inp == 'red'):
        sampleInput.write("2".encode('utf-8'))
    if inp == "Owo":
        testInput()
    if inp == "UwU":
        read_n_samples(5)