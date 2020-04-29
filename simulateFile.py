import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import os

try :
    import subprocess
except:
    print("install subprocess")
    exit(0)
try :
    import Tkinter as Tk
except ImportError :
    import tkinter as Tk

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

class simulateCircuit(Tk.Toplevel):
    def __init__(self, original):
        self.cwd = os.getcwd()
        """Constructor"""
        self.original_frame = original
        self.file = open("timefile.txt", "w+")
        self.nameFileGrou = "groundfile.txt"

        self.Row = 0
        Tk.Toplevel.__init__(self)
        self.geometry("800x600")
        self.title("Simulate")

        rowStart = self.getRow()

        timestartEntry = Tk.Entry(self)
        timendEntry = Tk.Entry(self)

        timestartLabel=Tk.Label(self,text = "Time Start :")
        timeendLabel=Tk.Label(self,text = "Time End :")

        timestartEntry.grid(row = rowStart, column = 2)
        timestartLabel.grid(row=rowStart, column = 1)

        timendEntry.grid(row=rowStart+1, column = 2)
        timeendLabel.grid(row=rowStart+1, column = 1)
        self.getRow()

        btngrou =Tk.Button(self, text="Add Ground", command=self.addGround)
        btngrou.grid(row = self.getRow())

        btnsim = Tk.Button(self, text="Simulate", command=lambda :self.simulateNow(timestartEntry, timendEntry))
        btnsim.grid(row = self.getRow(), column = 0)

        btn = Tk.Button(self, text="Close", command=self.onClose)
        btn.grid(row = self.getRow(), column = 0)
    def hide(self):
        self.withdraw()

    def show(self):
        """"""
        self.update()
        self.deiconify()

    def onClose(self):
        self.destroy()
        self.original_frame.show()

    def getRow(self):
        self.Row += 1
        return (self.Row - 1)

    def addGround(self):
        self.hide()
        otherFrame = addFrame(self, "Add Ground")
        grouValueEntry = Tk.Entry(otherFrame)

        rowStart = otherFrame.getRow()
        grouValueLabel=Tk.Label(otherFrame,text = "Nilai Node Ground:")

        grouValueLabel.grid(row=rowStart, column = 1)

        grouValueEntry.grid(row=rowStart, column = 2)

        submit = Tk.Button(otherFrame, text = "Submit")
        cancel = Tk.Button(otherFrame, text = "Cancel")
        submit['command'] =lambda binst =submit, binst2 = cancel:self.putGround(1,grouValueEntry,otherFrame)
        cancel['command'] = lambda binst = cancel,  binst2 = submit:self.putGround(0,grouValueEntry,otherFrame)
        cancel.grid(row = rowStart+4, column = 4)
        submit.grid(row = rowStart+4, column = 5)

    def putGround(self, state ,grouValueEntry, otherFrame):
        if state == 1:
            self.fileGrou = open("groundfile.txt", "w+")
            self.fileGrou.write(str(grouValueEntry.get()))
            self.file.write("\n")
            self.fileGrou.close()

        otherFrame.onClose()

    def simulateNow(self, timestartEntry, timendEntry):
        self.file.write(str(timestartEntry.get()))
        self.file.write("\n")
        self.file.write(str(timendEntry.get()))
        self.file.write("\n")

        os.chdir(self.cwd)

        process = subprocess.Popen(self.original_frame.simulateexecute, stdout=subprocess.PIPE)
        print process
        process.wait()

        self.onClose()
