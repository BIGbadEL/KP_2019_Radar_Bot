import serial
import matplotlib.pyplot as plt
import math
import numpy
import time

def polar_to_point( angle, radius):
    return [radius * math.cos(angle), radius * math.sin(angle)]

def distance_from_three_points(p1, p2, p3):
    tab_of_len = (math.fabs(p1 - p2), math.fabs(p1 - p3), math.fabs(p3 - p2))
    min_val = min(tab_of_len)
    index = tab_of_len.index(min_val)
    if index == 0:
        return (p1 + p2) / 2.0
    if index == 1:
        return (p1 + p3) / 2.0
    return (p2 + p3) / 2.0

import matplotlib.pyplot as plt
plt.ion()
class DynamicUpdate():
    min_x = -10
    max_x = 10

    def on_launch(self):
        self.figure, self.ax = plt.subplots()
        self.lines, = self.ax.plot([],[], 'o')
        self.ax.set_autoscaley_on(True)
        self.ax.grid()

    def on_running(self, xdata, ydata):

        self.lines.set_xdata(xdata)
        self.lines.set_ydata(ydata)
        self.ax.relim()
        self.ax.autoscale_view()
        self.figure.canvas.draw()
        self.figure.canvas.flush_events()

    def __call__(self):
        self.on_launch()
        xdata = []
        ydata = []
        ser = serial.Serial('/dev/ttyACM0',9600)
        readOut = 0
        while True:
            readDistance = ser.readline().decode('ascii')[:-2]
            floatDistance = float(readDistance)
            readDistance1 = ser.readline().decode('ascii')[:-2]
            floatDistance1 = float(readDistance1)
            readDistance2 = ser.readline().decode('ascii')[:-2]
            floatDistance2 = float(readDistance2)
            readAngle = ser.readline().decode('ascii')[:-2]
            floatAngle = float(readAngle)
            point = polar_to_point(2.0 * math.pi * floatAngle / 360.0 , distance_from_three_points(floatDistance, floatDistance1, floatDistance2))
            print(point)
            print(floatAngle)
            xdata.append(point[0])
            ydata.append(point[1])
            self.on_running(xdata, ydata)
        return xdata, ydata

d = DynamicUpdate()
d()