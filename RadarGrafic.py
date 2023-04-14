import matplotlib.pyplot as plt
import math
import serial
import numpy as np
from IPython import get_ipython

get_ipython().run_line_magic('matplotlib', 'qt')

arduino_ports = "COM4"
ser = serial.Serial(arduino_ports,baudrate=115200)
ser.flush()

DIST_MAX = 100
OUT_RANGE = 8000
ax = plt.subplot(111, polar=True)

lista = np.full((180,), OUT_RANGE)
i = 0


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
        
                        
        
        if dist < DIST_MAX:
            lista[i] == dist
        
        else:
            lista[i] == OUT_RANGE
            
        i = i + 1

            







        ax.plot(*fila[i], linewidth=10, marker="o", color="black", linestyle='')
            
        plt.pause(0.0001)
        plt.ion()
        plt.show(block=False)
    
    
    
    except KeyboardInterrupt:
        print('Keyboard Interrupt')
        break
