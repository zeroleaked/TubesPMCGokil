import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from simulateFile import simulateCircuit
from componentFile import addComponentClass
from plotFile import showPlotClass
from showComponentFile import showComponentClass
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
        self.fileOutputName = fileName;
        self.inputFile = "infile.txt"
        # self.simulateexecute = "program.exe"
        self.simulateexecute = "./program.o"
        self.root = parent
        self.root.title("Main Menu")
        self.frame = Tk.Frame(parent)
        self.frame.grid(padx=10, pady=10)


        title = Tk.Label(self.frame, text="Main Menu")
        title.grid(row=0, padx=5, pady=5, sticky="NESW")

        btnShowPlot = Tk.Button(self.frame, text="Show Plot", command=self.showPlotInMenu)
        btnShowPlot.grid(row=1, padx=5, pady=5, sticky="NESW")
        btnAddComponent = Tk.Button(self.frame, text="Add Component", command=self.insertComponentInMenu)
        btnAddComponent.grid(row=2, padx=5, pady=5, sticky="NESW")
        btnSimulate = Tk.Button(self.frame, text="Simulate", command=self.simulate)
        btnSimulate.grid(row=3, padx=5, pady=5, sticky="NESW")

        btnShowComponent = Tk.Button(self.frame, text="Show Component", command=self.showComponent)
        btnShowComponent.grid(row=4, padx=5, pady=5, sticky="NESW")

        btnExit = Tk.Button(self.frame, text = "Exit", command = self.root.destroy)
        btnExit.grid(row=5, padx=5, pady=5)

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

    def showComponent(self):
        self.hide()
        subFrame = showComponentClass(self)




#----------------------------------------------------------------------
if __name__ == "__main__":
    root = Tk.Tk()
    # root.geometry("800x600")
    app = MyApp(root, "outfile.csv")
    root.mainloop()
