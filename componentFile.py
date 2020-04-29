import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg

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

class addComponentClass(Tk.Toplevel):
    def __init__(self, original, inputFile):
        self.original_frame = original
        self.Row = 0
        Tk.Toplevel.__init__(self)
        self.geometry("800x600")
        self.title("addComponentClass")        
        self.file = open(original.inputFile, "w+")

        btnres =Tk.Button(self, text="Add Resistance", command=self.addResistance)
        btnres.grid(row = self.getRow()) 

        btncap =Tk.Button(self, text="Add Capacitance", command=self.addCapacitance)
        btncap.grid(row = self.getRow())

        btnind =Tk.Button(self, text="Add Inductance", command=self.addInductance)
        btnind.grid(row = self.getRow())                           

        btnvolt =Tk.Button(self, text="Add Constant Voltage Source", command=self.addVoltageSource)
        btnvolt.grid(row = self.getRow())                                   

        btncurr =Tk.Button(self, text="Add Constant Current Source", command=self.addCurrentSource)
        btncurr.grid(row = self.getRow())         

        # btnvoltAc =Tk.Button(self, text="Add AC Voltage Source", command=self.addACVoltageSource)
        # btnvoltAc.grid(row = self.getRow())        

        btncurrAc =Tk.Button(self, text="Add AC Current Source", command=self.addACCurrentSource)
        btncurrAc.grid(row = self.getRow())                 

        btnvoltAc =Tk.Button(self, text="Add AC Voltage Source", command=self.addACVoltageSource)
        btnvoltAc.grid(row = self.getRow())           
                                 
       
        btn = Tk.Button(self, text="Save", command=self.onClose)
        btn.grid(row = self.getRow())          

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

    #Add resistance Component
    def addResistance(self):
        self.hide()
        otherFrame = addFrame(self, "addResistance")
        resValueEntry = Tk.Entry(otherFrame)
        
        resNode1Entry = Tk.Entry(otherFrame)
        
        resNode2Entry = Tk.Entry(otherFrame)

        rowStart = otherFrame.getRow()
        resValueLabel=Tk.Label(otherFrame,text = "Nilai resistor(Ohm):")        
        resNode1Label=Tk.Label(otherFrame,text = "Nilai Node 1:")
        resNode2Label=Tk.Label(otherFrame,text = "Nilai Node 2:")

        resValueLabel.grid(row=rowStart, column = 1)
        resNode1Label.grid(row=rowStart+1, column = 1)        
        resNode2Label.grid(row=rowStart+2, column = 1)

        resNode1Entry.grid(row=rowStart+1, column = 2)        
        resValueEntry.grid(row=rowStart, column = 2)
        resNode2Entry.grid(row=rowStart+2, column = 2)    

        submit = Tk.Button(otherFrame, text = "Submit")
        cancel = Tk.Button(otherFrame, text = "Cancel")
        submit['command'] =lambda binst =submit, binst2 = cancel:self.putResistance(1,resValueEntry,
                resNode1Entry,resNode2Entry, resValueLabel, resNode1Label, resNode2Label, binst, binst2, otherFrame)
        cancel['command'] = lambda binst = cancel,  binst2 = submit:self.putResistance(0,resValueEntry,
                resNode1Entry,resNode2Entry, resValueLabel, resNode1Label, resNode2Label, binst, binst2, otherFrame)
        cancel.grid(row = rowStart+4, column = 4)
        submit.grid(row = rowStart+4, column = 5)

    def putResistance(self, state ,resValueEntry, resNode1Entry, resNode2Entry, resValueLabel, resNode1Label, resNode2Label,binst, binst2, otherFrame):
        if state == 1:
            self.file.write("R")
            self.file.write("\n")
            self.file.write(str(resValueEntry.get()))
            self.file.write("\n")       
            self.file.write(str(resNode1Entry.get()))
            self.file.write("\n")       
            self.file.write(str(resNode2Entry.get()))
            self.file.write("\n")
   
        otherFrame.onClose()
        

    #Add Capacitor Component
    def addCapacitance(self):
        self.hide()
        otherFrame = addFrame(self, "addResistance")

        capValueEntry = Tk.Entry(otherFrame)
        
        capNode1Entry = Tk.Entry(otherFrame)
        
        capNode2Entry = Tk.Entry(otherFrame)

        capVoltEntry = Tk.Entry(otherFrame)


        rowStart = otherFrame.getRow()
        capValueLabel=Tk.Label(otherFrame,text = "Nilai capacitor:")        
        capNode1Label=Tk.Label(otherFrame,text = "Nilai Node 1:")
        capNode2Label=Tk.Label(otherFrame,text = "Nilai Node 2:")
        capVoltLabel=Tk.Label(otherFrame,text = "Tegangan awal kapasitor:")

        capValueLabel.grid(row=rowStart, column = 1)
        capNode1Label.grid(row=rowStart+1, column = 1)        
        capNode2Label.grid(row=rowStart+2, column = 1)
        capVoltLabel.grid(row = rowStart+3, column = 1)

        capNode1Entry.grid(row=rowStart+1, column = 2)        
        capValueEntry.grid(row=rowStart, column = 2)
        capNode2Entry.grid(row=rowStart+2, column = 2)    
        capVoltEntry.grid(row=rowStart+3, column = 2)

        submit = Tk.Button(otherFrame, text = "Submit")
        cancel = Tk.Button(otherFrame, text = "Cancel")
        submit['command'] =lambda binst =submit, binst2 = cancel:self.putCapacitance(1,capValueEntry,
                capNode1Entry,capNode2Entry, capValueLabel, capNode1Label, capNode2Label,capVoltEntry ,binst, binst2, otherFrame)
        cancel['command'] = lambda binst = cancel,  binst2 = submit:self.putCapacitance(0,capValueEntry,
                capNode1Entry,capNode2Entry, capValueLabel, capNode1Label, capNode2Label,capVoltEntry ,binst, binst2, otherFrame)
        cancel.grid(row = rowStart+4, column = 4)
        submit.grid(row = rowStart+4, column = 5)

    def putCapacitance(self, state ,capValueEntry, capNode1Entry, capNode2Entry, capValueLabel, capNode1Label, capNode2Label,capVoltEntry,binst, binst2, otherFrame):
        if state == 1:
            self.file.write("C")
            self.file.write("\n")
            self.file.write(str(capValueEntry.get()))
            self.file.write("\n")       
            self.file.write(str(capNode1Entry.get()))
            self.file.write("\n")       
            self.file.write(str(capNode2Entry.get()))
            self.file.write("\n")
            self.file.write(str(capVoltEntry.get()))
            self.file.write("\n")

        capValueEntry.destroy()
        capNode1Entry.destroy()     
        capNode2Entry.destroy()  
        capValueLabel.destroy()
        capNode1Label.destroy()     
        capNode2Label.destroy()          

        binst.destroy()   
        binst2.destroy() 
        otherFrame.onClose()
        
    def addInductance(self):
        self.hide()
        otherFrame = addFrame(self, "Add Inductance")

        indValueEntry = Tk.Entry(otherFrame)
        indNode1Entry = Tk.Entry(otherFrame)
        indNode2Entry = Tk.Entry(otherFrame)
        indCurrEntry  = Tk.Entry(otherFrame)

        rowStart = otherFrame.getRow()
        indValueLabel=Tk.Label(otherFrame,text = "Nilai induktor(H):")        
        indNode1Label=Tk.Label(otherFrame,text = "Nilai Node 1:")
        indNode2Label=Tk.Label(otherFrame,text = "Nilai Node 2:")
        indCurrLabel=Tk.Label(otherFrame,text = "Nilai Arus Awal(A):")

        indValueLabel.grid(row=rowStart, column = 1)
        indNode1Label.grid(row=rowStart+1, column = 1)        
        indNode2Label.grid(row=rowStart+2, column = 1)
        indCurrLabel.grid(row=rowStart+3, column = 1)

        indNode1Entry.grid(row=rowStart+1, column = 2)        
        indValueEntry.grid(row=rowStart, column = 2)
        indNode2Entry.grid(row=rowStart+2, column = 2)    
        indCurrEntry.grid(row=rowStart+3, column = 2)    

        submit = Tk.Button(otherFrame, text = "Submit")
        cancel = Tk.Button(otherFrame, text = "Cancel")
        submit['command'] =lambda binst =submit, binst2 = cancel:self.putInductance(1,indValueEntry,
                indNode1Entry,indNode2Entry, indValueLabel, indNode1Label, indNode2Label,indCurrEntry ,binst, binst2, otherFrame)
        cancel['command'] = lambda binst = cancel,  binst2 = submit:self.putInductance(0,indValueEntry,
                indNode1Entry,indNode2Entry, indValueLabel, indNode1Label, indNode2Label,indCurrEntry ,binst, binst2, otherFrame)
        cancel.grid(row = rowStart+4, column = 4)
        submit.grid(row = rowStart+4, column = 5)


    def putInductance(self, state ,indValueEntry, indNode1Entry, indNode2Entry, indValueLabel, indNode1Label, indNode2Label,indCurrEntry,binst, binst2, otherFrame):
        if state == 1:
            self.file.write("L")
            self.file.write("\n")
            self.file.write(str(indValueEntry.get()))
            self.file.write("\n")       
            self.file.write(str(indNode1Entry.get()))
            self.file.write("\n")       
            self.file.write(str(indNode2Entry.get()))
            self.file.write("\n")
            self.file.write(str(indCurrEntry.get()))
            self.file.write("\n")

        indValueEntry.destroy()
        indNode1Entry.destroy()     
        indNode2Entry.destroy()  
        indValueLabel.destroy()
        indNode1Label.destroy()     
        indNode2Label.destroy()          

        binst.destroy()   
        binst2.destroy()  
        otherFrame.onClose()

    def addVoltageSource(self):
        self.hide()
        otherFrame = addFrame(self, "Add Constant Voltage Source")
        voltValueEntry = Tk.Entry(otherFrame)
        
        voltNode1Entry = Tk.Entry(otherFrame)
        
        voltNode2Entry = Tk.Entry(otherFrame)

        rowStart = otherFrame.getRow()
        voltValueLabel=Tk.Label(otherFrame,text = "Nilai Sumber Tegangan:")        
        voltNode1Label=Tk.Label(otherFrame,text = "Nilai Node 1:")
        voltNode2Label=Tk.Label(otherFrame,text = "Nilai Node 2:")

        voltValueLabel.grid(row=rowStart, column = 1)
        voltNode1Label.grid(row=rowStart+1, column = 1)        
        voltNode2Label.grid(row=rowStart+2, column = 1)

        voltNode1Entry.grid(row=rowStart+1, column = 2)        
        voltValueEntry.grid(row=rowStart, column = 2)
        voltNode2Entry.grid(row=rowStart+2, column = 2)    

        submit = Tk.Button(otherFrame, text = "Submit")
        cancel = Tk.Button(otherFrame, text = "Cancel")
        submit['command'] =lambda binst =submit, binst2 = cancel:self.putVoltageSource(1,voltValueEntry,
                voltNode1Entry,voltNode2Entry, voltValueLabel, voltNode1Label, voltNode2Label, binst, binst2, otherFrame)
        cancel['command'] = lambda binst = cancel,  binst2 = submit:self.putVoltageSource(0,voltValueEntry,
                voltNode1Entry,voltNode2Entry, voltValueLabel, voltNode1Label, voltNode2Label, binst, binst2, otherFrame)
        cancel.grid(row = rowStart+4, column = 4)
        submit.grid(row = rowStart+4, column = 5)

    def putVoltageSource(self, state ,voltValueEntry, voltNode1Entry, voltNode2Entry, voltValueLabel, voltNode1Label, voltNode2Label,binst, binst2, otherFrame):
        if state == 1:
            self.file.write("V")
            self.file.write("\n")
            self.file.write(str(voltValueEntry.get()))
            self.file.write("\n")       
            self.file.write(str(voltNode1Entry.get()))
            self.file.write("\n")       
            self.file.write(str(voltNode2Entry.get()))
            self.file.write("\n")

        otherFrame.onClose()

    def addCurrentSource(self):
        self.hide()
        otherFrame = addFrame(self, "Add Current Source")
        currValueEntry = Tk.Entry(otherFrame)
        
        currNode1Entry = Tk.Entry(otherFrame)
        
        currNode2Entry = Tk.Entry(otherFrame)

        rowStart = otherFrame.getRow()
        currValueLabel=Tk.Label(otherFrame,text = "Nilai Sumber Arus:")        
        currNode1Label=Tk.Label(otherFrame,text = "Nilai Node 1:")
        currNode2Label=Tk.Label(otherFrame,text = "Nilai Node 2:")

        currValueLabel.grid(row=rowStart, column = 1)
        currNode1Label.grid(row=rowStart+1, column = 1)        
        currNode2Label.grid(row=rowStart+2, column = 1)

        currNode1Entry.grid(row=rowStart+1, column = 2)        
        currValueEntry.grid(row=rowStart, column = 2)
        currNode2Entry.grid(row=rowStart+2, column = 2)    

        submit = Tk.Button(otherFrame, text = "Submit")
        cancel = Tk.Button(otherFrame, text = "Cancel")
        submit['command'] =lambda binst =submit, binst2 = cancel:self.putCurrentSource(1,currValueEntry,
                currNode1Entry,currNode2Entry, currValueLabel, currNode1Label, currNode2Label, binst, binst2, otherFrame)
        cancel['command'] = lambda binst = cancel,  binst2 = submit:self.putCurrentSource(0,currValueEntry,
                currNode1Entry,currNode2Entry, currValueLabel, currNode1Label, currNode2Label, binst, binst2, otherFrame)
        cancel.grid(row = rowStart+4, column = 4)
        submit.grid(row = rowStart+4, column = 5)

    def putCurrentSource(self, state ,currValueEntry, currNode1Entry, currNode2Entry, currValueLabel, currNode1Label, currNode2Label,binst, binst2, otherFrame):
        if state == 1:
            self.file.write("I")
            self.file.write("\n")
            self.file.write(str(currValueEntry.get()))
            self.file.write("\n")       
            self.file.write(str(currNode1Entry.get()))
            self.file.write("\n")       
            self.file.write(str(currNode2Entry.get()))
            self.file.write("\n")

        otherFrame.onClose()

    def addACCurrentSource(self):
        self.hide()
        otherFrame = addFrame(self, "Add AC Current Source")
        currValueEntry = Tk.Entry(otherFrame)
        currFreqEntry = Tk.Entry(otherFrame)        
        currShiftEntry = Tk.Entry(otherFrame)
        currNode1Entry = Tk.Entry(otherFrame)        
        currNode2Entry = Tk.Entry(otherFrame)

        rowStart = otherFrame.getRow()
        currValueLabel=Tk.Label(otherFrame,text = "Nilai Amplitude Sumber Arus(A):")        
        currFreqLabel=Tk.Label(otherFrame,text = "Nilai Frekuensi (Hz):")        
        currShiftLabel=Tk.Label(otherFrame,text = "Nilai Shifting (s):")        
        currNode1Label=Tk.Label(otherFrame,text = "Nilai Node 1:")
        currNode2Label=Tk.Label(otherFrame,text = "Nilai Node 2:")
        currTypeLabel = Tk.Label(otherFrame,text = "Tipe Sumber:")

        currValueLabel.grid(row=rowStart, column = 1)
        currFreqLabel.grid(row = rowStart + 1, column = 1)
        currNode1Label.grid(row=rowStart+2, column = 1)        
        currNode2Label.grid(row=rowStart+3, column = 1)
        currShiftLabel.grid(row=rowStart+4, column = 1)

        currValueEntry.grid(row=rowStart, column = 2)
        currFreqEntry.grid(row = rowStart + 1, column = 2)
        currNode1Entry.grid(row=rowStart+2, column = 2)                
        currNode2Entry.grid(row=rowStart+3, column = 2)    
        currShiftEntry.grid(row=rowStart+4, column = 2)

        typeAC = ["Sinus", "Kotak"]
        variable = Tk.StringVar(otherFrame)
        variable.set(typeAC[0])

        typeOptions = apply(Tk.OptionMenu, (otherFrame, variable)+tuple(typeAC))
        currTypeLabel.grid(row = rowStart+5, column = 1)
        typeOptions.grid(row = rowStart+5, column = 2)

        submit = Tk.Button(otherFrame, text = "Submit")
        cancel = Tk.Button(otherFrame, text = "Cancel")
        submit['command'] =lambda binst =submit, binst2 = cancel:self.putCurrentACSource(1,currValueEntry,
                currNode1Entry,currNode2Entry,currFreqEntry,currShiftEntry,variable, binst, binst2, otherFrame)
        cancel['command'] = lambda binst = cancel,  binst2 = submit:self.putCurrentACSource(0,currValueEntry,
                currNode1Entry,currNode2Entry,currFreqEntry,currShiftEntry,variable, binst, binst2, otherFrame)
        cancel.grid(row = rowStart+6, column = 4)
        submit.grid(row = rowStart+6, column = 5)

    def putCurrentACSource(self, state ,currValueEntry, currNode1Entry, currNode2Entry,currFreqEntry,currShiftEntry,variable,binst, binst2, otherFrame):
        if state == 1:
            self.file.write("J")
            self.file.write("\n")
            self.file.write(str(currValueEntry.get())) #A
            self.file.write("\n")       
            self.file.write(str(currNode1Entry.get()))#1
            self.file.write("\n")       
            self.file.write(str(currNode2Entry.get()))#2
            self.file.write("\n")
            if variable.get() == "Sinus":
                self.file.write("0")
            else :
                self.file.write("1")
            self.file.write("\n")
            self.file.write(str(currFreqEntry.get()))
            self.file.write("\n")            
            self.file.write(str(currShiftEntry.get()))
            self.file.write("\n")            

        otherFrame.onClose()        

    def addACVoltageSource(self):
        self.hide()
        otherFrame = addFrame(self, "Add AC Voltage Source")
        voltValueEntry = Tk.Entry(otherFrame)
        voltFreqEntry = Tk.Entry(otherFrame)        
        voltShiftEntry = Tk.Entry(otherFrame)
        voltNode1Entry = Tk.Entry(otherFrame)        
        voltNode2Entry = Tk.Entry(otherFrame)

        rowStart = otherFrame.getRow()
        voltValueLabel=Tk.Label(otherFrame,text = "Nilai Amplitude Sumber Tegangan(V):")        
        voltFreqLabel=Tk.Label(otherFrame,text = "Nilai Frekuensi (Hz):")        
        voltShiftLabel=Tk.Label(otherFrame,text = "Nilai Shifting (s):")        
        voltNode1Label=Tk.Label(otherFrame,text = "Nilai Node 1:")
        voltNode2Label=Tk.Label(otherFrame,text = "Nilai Node 2:")
        voltTypeLabel = Tk.Label(otherFrame,text = "Tipe Sumber:")

        voltValueLabel.grid(row=rowStart, column = 1)
        voltFreqLabel.grid(row = rowStart + 1, column = 1)
        voltNode1Label.grid(row=rowStart+2, column = 1)        
        voltNode2Label.grid(row=rowStart+3, column = 1)
        voltShiftLabel.grid(row=rowStart+4, column = 1)

        voltValueEntry.grid(row=rowStart, column = 2)
        voltFreqEntry.grid(row = rowStart + 1, column = 2)
        voltNode1Entry.grid(row=rowStart+2, column = 2)                
        voltNode2Entry.grid(row=rowStart+3, column = 2)    
        voltShiftEntry.grid(row=rowStart+4, column = 2)

        typeAC = ["Sinus", "Kotak"]
        variable = Tk.StringVar(otherFrame)
        variable.set(typeAC[0])

        typeOptions = apply(Tk.OptionMenu, (otherFrame, variable)+tuple(typeAC))
        voltTypeLabel.grid(row = rowStart+5, column = 1)
        typeOptions.grid(row = rowStart+5, column = 2)

        submit = Tk.Button(otherFrame, text = "Submit")
        cancel = Tk.Button(otherFrame, text = "Cancel")
        submit['command'] =lambda binst =submit, binst2 = cancel:self.putACVoltageSource(1,voltValueEntry,
                voltNode1Entry,voltNode2Entry,voltFreqEntry,voltShiftEntry,variable, binst, binst2, otherFrame)
        cancel['command'] = lambda binst = cancel,  binst2 = submit:self.putACVoltageSource(0,voltValueEntry,
                voltNode1Entry,voltNode2Entry,voltFreqEntry,voltShiftEntry,variable, binst, binst2, otherFrame)
        cancel.grid(row = rowStart+6, column = 4)
        submit.grid(row = rowStart+6, column = 5)

    def putACVoltageSource(self, state ,voltValueEntry, voltNode1Entry, voltNode2Entry,voltFreqEntry,voltShiftEntry,variable,binst, binst2, otherFrame):
        if state == 1:
            self.file.write("W")
            self.file.write("\n")
            self.file.write(str(voltValueEntry.get())) #A
            self.file.write("\n")       
            self.file.write(str(voltNode1Entry.get()))#1
            self.file.write("\n")       
            self.file.write(str(voltNode2Entry.get()))#2
            self.file.write("\n")
            if variable.get() == "Sinus":
                self.file.write("0")
            else :
                self.file.write("1")
            self.file.write("\n")
            self.file.write(str(voltFreqEntry.get()))
            self.file.write("\n")            
            self.file.write(str(voltShiftEntry.get()))
            self.file.write("\n")            

        otherFrame.onClose()  