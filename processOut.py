import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from simulateFile import simulateCircuit
from componentFile import addComponentClass
from plotFile import showPlotClass
try :
    import subprocess
except:
    print("install subprocess")
    exit(0)
import Tkinter as Tk


import os

class addFrame(Tk.Toplevel):
    def __init__(self, original, frameName):
        self.original_frame = original
        Tk.Toplevel.__init__(self)
        self.geometry("400x300")
        self.title(frameName)
        self.Row = 0

    def onClose(self):
        self.destroy()
        self.original_frame.show()

    def getRow(self):
        self.Row += 1
        return (self.Row - 1)

class MyApp(object):

    def __init__(self, parent, fileName):
        self.inputFile = "infile.txt"
        self.simulateexecute = "program.exe"
        self.root = parent
        self.root.title("Main Menu")
        self.frame = Tk.Frame(parent)
        self.frame.pack()

        self.data = pd.read_csv(fileName)
        self.Dict = {}


        btnShowPlot = Tk.Button(self.frame, text="Show Plot", command=self.showPlotInMenu)
        btnShowPlot.pack()
        btnAddComponent = Tk.Button(self.frame, text="Add Component", command=self.insertComponentInMenu)
        btnAddComponent.pack()
        btnSimulate = Tk.Button(self.frame, text="Simulate", command=self.simulate)
        btnSimulate.pack()

        btnExit = Tk.Button(self.frame, text = "Exit", command = self.root.destroy)
        btnExit.pack()

    def hide(self):
        self.root.withdraw()

    def onCloseOtherFrame(self, otherFrame):
        otherFrame.destroy()
        self.show()

    def show(self):
        """"""
        self.root.update()
        self.root.deiconify()
    #showplot
    def showPlotInMenu(self):
        self.hide()
        subFrame = showPlotClass(self)

    # insert component
    def insertComponentInMenu(self)   :
        self.hide()
        subFrame = addComponentClass(self, self.inputFile)

    def simulate(self):
        self.hide()
        subFrame = simulateCircuit(self)




#----------------------------------------------------------------------
if __name__ == "__main__":
    root = Tk.Tk()
    root.geometry("800x600")
    root.configure(bg='white')
    app = MyApp(root, "outfile.csv")
    root.mainloop()
