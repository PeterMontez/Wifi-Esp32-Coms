import matplotlib.pyplot as plt
import math
import serial
from IPython import get_ipython

get_ipython().run_line_magic('matplotlib', 'qt')

arduino_ports = "COM4"
ser = serial.Serial(arduino_ports,baudrate=115200)
ser.flush()

DIST_MAX = 100
ax = plt.subplot(111, polar=True)

pilha_hor = []
pilha_ant = []
aux = 1


while True:
    try:
        ser_bytes = ser.readline() 
        decoded_bytes = ser_bytes.decode('utf-8') 
        data = ((decoded_bytes.replace('\r','')).replace('\n','')).split(" ")
        dist = int(data[0])
        angulo = int(data[1])
     
        ax.clear()
        ax.set_thetamax(180)
        ax.plot(math.pi, DIST_MAX, linewidth=10, linestyle='solid')
        
        if angulo == 0:
            aux = 1
        if angulo == 180:
            aux = 0
            
        if aux == 1:
            pilha_hor.append((angulo*math.pi/180, dist))
            if len(pilha_ant) != 0:
                pilha_ant.pop()
        else:
            pilha_ant.append((angulo*math.pi/180, dist))
            if len(pilha_hor) != 0:
                pilha_hor.pop()
        
        for i in range(len(pilha_hor)):
            if pilha_hor[i][1] < DIST_MAX:
                ax.plot(*pilha_hor[i], linewidth=10, marker="o", color="black", linestyle='')
        for i in range(len(pilha_ant)):
            if pilha_ant[i][1] < DIST_MAX:
                ax.plot(*pilha_ant[i], linewidth=10, marker="o", color="black", linestyle='')
            
        plt.pause(0.0001)
        plt.ion()
        plt.show(block=False)
    
    
    
    except KeyboardInterrupt:
        print('Keyboard Interrupt')
        break
