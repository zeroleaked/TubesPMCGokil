import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
try :
    import subprocess
except:
    print("install subprocess")
    exit(0)

try :
    import subprocess
except:
    print("install subprocess")
    exit(0)
try :
    import Tkinter as Tk
    from Tkinter import ttk
except ImportError :
    import Tkinter as Tk
    import ttk

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


class showComponentClass(Tk.Toplevel):
    def __init__(self, original):
        self.original_frame = original
        Tk.Toplevel.__init__(self)
        self.Row = 0
        canvas = Tk.Canvas(self)
        scroll_y = Tk.Scrollbar(self, orient = "vertical", command = canvas.yview)

        self.frame = Tk.Frame(canvas)

        self.geometry("600x300")
        self.title("addComponentClass")
        self.file = open(original.inputFile, "r")

        self.r_list = []
        self.l_list = []
        self.c_list = []
        self.v_list = []
        self.i_list = []
        self.w_list = []
        self.j_list = []

        self.readInputFile()
        # print self.r_list
        # Tk.Label(frame, text = "Daftar R", bg = "#00ffff").grid(row = self.getRow())
        self.row = ["Name", "Value", "Node 1", "Node 2", "Initial", "Amplitude", "Frequency", "Time Shift"]
        self.writeRow()

        for i in range (len(self.r_list)):
            self.row[0] = 'R' + str(i+1)
            self.row[1] = str(self.r_list[i][0]) + ' Ohm'
            self.row[2] = str(self.r_list[i][1])
            self.row[3] = str(self.r_list[i][2])
            self.row[4] = '-'
            self.row[5] = '-'
            self.row[6] = '-'
            self.row[7] = '-'
            self.writeRow()

        for i in range (len(self.l_list)):
            self.row[0] = 'L' + str(i+1)
            self.row[1] = str(self.l_list[i][0]) + ' H'
            self.row[2] = str(self.l_list[i][1])
            self.row[3] = str(self.l_list[i][2])
            self.row[4] = str(self.l_list[i][3]) + ' A'
            self.row[5] = '-'
            self.row[6] = '-'
            self.row[7] = '-'
            self.writeRow()

        for i in range (len(self.c_list)):
            self.row[0] = 'C' + str(i+1)
            self.row[1] = str(self.c_list[i][0]) + ' F'
            self.row[2] = str(self.c_list[i][1])
            self.row[3] = str(self.c_list[i][2])
            self.row[4] = str(self.c_list[i][3]) + ' V'
            self.row[5] = '-'
            self.row[6] = '-'
            self.row[7] = '-'
            self.writeRow()

        for i in range (len(self.v_list)):
            self.row[0] = 'V' + str(i+1)
            self.row[1] = str(self.v_list[i][0]) + ' V'
            self.row[2] = str(self.v_list[i][1])
            self.row[3] = str(self.v_list[i][2])
            self.row[4] = '-'
            self.row[5] = '-'
            self.row[6] = '-'
            self.row[7] = '-'
            self.writeRow()

        type = ['Sine', 'Square']
        for i in range (len(self.w_list)):
            self.row[0] = 'V' + str(len(self.v_list)+i+1)
            self.row[1] = type[int(self.w_list[i][3])]
            self.row[2] = str(self.w_list[i][1])
            self.row[3] = str(self.w_list[i][2])
            self.row[4] = '-'
            self.row[5] = str(self.w_list[i][0]) + ' V'
            self.row[6] = str(self.w_list[i][4]) + ' Hz'
            self.row[7] = str(self.w_list[i][5]) + ' s'
            self.writeRow()

        for i in range (len(self.i_list)):
            self.row[0] = 'I' + str(i+1)
            self.row[1] = str(self.i_list[i][0]) + ' A'
            self.row[2] = str(self.i_list[i][1])
            self.row[3] = str(self.i_list[i][2])
            self.row[4] = '-'
            self.row[5] = '-'
            self.row[6] = '-'
            self.row[7] = '-'
            self.writeRow()

        for i in range (len(self.j_list)):
            self.row[0] = 'V' + str(len(self.i_list)+i+1)
            self.row[1] = type[int(self.j_list[i][3])]
            self.row[2] = str(self.j_list[i][1])
            self.row[3] = str(self.j_list[i][2])
            self.row[4] = '-'
            self.row[5] = str(self.j_list[i][0]) + ' A'
            self.row[6] = str(self.j_list[i][4]) + ' Hz'
            self.row[7] = str(self.j_list[i][5]) + ' s'
            self.writeRow()

        btn = Tk.Button(self.frame, text="Close", command=self.onClose)
        btn.grid(row = self.getRow(), column=4, padx=5, pady=5)

        canvas.create_window(0,0,anchor='nw',window = self.frame)
        canvas.update_idletasks()

        canvas.configure(scrollregion=canvas.bbox('all'),
        yscrollcommand = scroll_y.set)

        canvas.pack(fill='both', expand=True, side='left')
        scroll_y.pack(fill='y', side='right')

    def hide(self):
        self.withdraw()
    def show(self):
        """"""
        self.update()
        self.deiconify()

    def onClose(self):
        self.file.close()
        self.destroy()
        self.original_frame.show()

    def getRow(self):
        self.Row += 1
        return (self.Row - 1)

    def readN(self,list,k, n) :
        temp_list = []
        for i in range (n):
            s = list[k+i+1]
            # print("momo = "+s)
            temp_list.append(s)
        return temp_list


    def readInputFile(self):
        list = self.file.read().splitlines()
        for k in range (len (list)):
            ch = list[k]

            if ch == "R":
                self.r_list.append(self.readN(list,k,3))
            elif ch == 'L':
                self.l_list.append(self.readN(list,k,4))
            elif ch == 'C':
                self.c_list.append(self.readN(list,k,4))
            elif ch == 'V':
                self.v_list.append(self.readN(list,k,3))
            elif ch == 'I':
                self.i_list.append(self.readN(list,k,3))
            elif ch == 'J':
                self.j_list.append(self.readN(list,k,6))
            elif ch == 'W':
                self.w_list.append(self.readN(list,k,6))
            elif ch == '':
                break

    def writeRow(self):
        row_now = self.getRow()
        for i in range (8):
            Tk.Label(self.frame, text = self.row[i]).grid(row = row_now, column = i, padx=5, pady=5)
