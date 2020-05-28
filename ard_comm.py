import serial
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import FinalProjectFourierAnalyzer as an


fig = plt.figure()
ax1 = fig.add_subplot(1,1,1)
comm_port = "COM15"
sampleInput = serial.Serial(comm_port, 115200, timeout=5)
buffSize = 255
ready = True

def read_one_sample(inBuf, start):
    data = sampleInput.read()
    i = start
    while(i < start + buffSize):

        inBuf[i] = ((ord(data) << 8)) | ord(sampleInput.read())
        data = sampleInput.read()
        i += 1
        # print(i)
    # print("done")


def read_n_samples(n):
    inBuff = np.array([0] * n * buffSize)
    sampleInput.write(("1" + str(n)).encode('utf-8'))
    for i in range(n):
        read_one_sample(inBuff, i * buffSize)
    inBuff -= 43500
    return inBuff
    fft = np.fft.fft(inBuff)
    x = np.arange(len(inBuff)) * 32500 / len(inBuff)
    t = np.arange(len(inBuff)) / 32500
    plt.plot(x, abs(fft))
    plt.title("Whistly bois")
    # plt.plot(t, inBuff)
    plt.xlim(0, 3000)
    plt.show()

def testInput():
    sampleInput.write("1".encode('utf-8'))
    print(sampleInput.readline())

def animate(i):
    global ready
    if not ready:
        return
    ready = False
    ax1.clear()
    inBuff = read_n_samples(5)
    fft = np.fft.fft(inBuff)
    x = np.arange(len(inBuff)) * 32500 / len(inBuff)
    ax1.plot(x, abs(fft))
    plt.xlim(0, 5000)
    an.commands(fft, sampleInput)
    ready = True;

while not sampleInput.read():
    pass;

ani = animation.FuncAnimation(fig, animate, interval=1000)
plt.show()

while True:
    inp = input()
    if(inp == 'blue'):
        print("wowza")
        sampleInput.write("3".encode('utf-8'))
    if (inp == 'red'):
        sampleInput.write("2".encode('utf-8'))
    if inp == "Owo":
        testInput()
    if inp == "UwU":
        read_n_samples(5)

