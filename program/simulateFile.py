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
        # self.geometry("800x600")
        self.title("Simulate")

        rowStart = self.getRow()
        print rowStart

        timestartEntry = Tk.Entry(self)
        timendEntry = Tk.Entry(self)

        timestartLabel=Tk.Label(self,text = "Start Time (s):")
        timeendLabel=Tk.Label(self,text = "End Time (s):")

        timestartEntry.grid(row = rowStart, column = 1, columnspan=2, padx=5, pady=5)
        timestartLabel.grid(row=rowStart, column = 0, padx=5, pady=5, sticky="E")

        timendEntry.grid(row=rowStart+1, column = 1, columnspan=2, padx=5, pady=5)
        timeendLabel.grid(row=rowStart+1, column = 0, padx=5, pady=5, sticky="E")
        self.getRow()

        button_row = self.getRow()

        btngrou =Tk.Button(self, text="Add Ground", command=self.addGround)
        btngrou.grid(row = button_row, column = 1, padx=5, pady=5)

        btnsim = Tk.Button(self, text="Simulate", command=lambda :self.simulateNow(timestartEntry, timendEntry))
        btnsim.grid(row = button_row, column = 2, padx=5, pady=5)

        btn = Tk.Button(self, text="Cancel", command=self.onClose)
        btn.grid(row = button_row, column = 0, padx=5, pady=5)
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
        grouValueLabel=Tk.Label(otherFrame,text = "Ground Node:")

        grouValueLabel.grid(row=rowStart, column = 1, padx=5, pady=5)

        grouValueEntry.grid(row=rowStart, column = 2, columnspan=2, padx=5, pady=5)

        submit = Tk.Button(otherFrame, text = "Submit")
        cancel = Tk.Button(otherFrame, text = "Cancel")
        submit['command'] =lambda binst =submit, binst2 = cancel:self.putGround(1,grouValueEntry,otherFrame)
        cancel['command'] = lambda binst = cancel,  binst2 = submit:self.putGround(0,grouValueEntry,otherFrame)
        cancel.grid(row = rowStart+4, column = 2, padx=5, pady=5)
        submit.grid(row = rowStart+4, column = 3, padx=5, pady=5)

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
        self.file.close()

        os.chdir(self.cwd)

        process = subprocess.Popen(self.original_frame.simulateexecute, stdout=subprocess.PIPE)
        print process
        process.wait()

        self.onClose()
