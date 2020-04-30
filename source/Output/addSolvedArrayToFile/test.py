import os
import numpy as np
import shutil

GENERATE = False
MAX_COMPONENTS = 10
TYPES = ['R', 'V', 'I', 'L', 'C']
TESTS = 20


class Components:
    def __init__(self, length):
        self.array = []
        self.nodes = []

        def createRandomNode():
            n = np.random.randint(length)
            while n in self.nodes:
                n = np.random.randint(length)
            self.nodes.append(n)
            return n

        temp = createRandomNode()
        c = Component(temp, temp)
        self.array.append(c)
        i = 1
        while i < length:
            paralel = np.random.randint(2) * (i - 1) # pasti seri kalau i = 1
            if paralel:
                c = Component(c.node1, c.node2)
            else:
                temp = c.node2
                c.node2 = createRandomNode()
                c = Component(c.node2, temp)
            self.array.append(c)
            i += 1

        self.ground = self.nodes[np.random.randint(len(self.nodes))]

        randomValue = lambda: np.random.randint(100) * pow(10, np.random.randint(12) - 6)

        nodes = []
        def unique (node):
            if node == self.ground:
                return 0
            if node in nodes:
                return 0
            else:
                nodes.append(node)
                return 1
        self.raw_solved = {}
        self.raw_solved["e"] = []
        self.raw_solved["v"] = []
        self.raw_solved["i"] = []
        for c in self.array:
            self.raw_solved["v"].append((c.type, randomValue()))
            self.raw_solved["i"].append((c.type, randomValue()))
            if unique(c.node1):
                self.raw_solved['e'].append((1, randomValue()))
            if c.type == 'C':
                # add series resistor
                self.raw_solved["e"].append((0, randomValue()))
                self.raw_solved["v"].append((0, randomValue()))
                self.raw_solved["i"].append((0, randomValue()))
            elif c.type == 'L':
                # add paralel resistor
                self.raw_solved["v"].append((0, randomValue()))
                self.raw_solved["i"].append((0, randomValue()))
            if unique(c.node2):
                self.raw_solved['e'].append((1, randomValue()))



        # self.solved = self.raw_solved
        # i = 0
        # while i < len(self.array):
        #     if self.array[i].type == 'C':


    def __str__(self):
        str = ''
        for i in range(len(self.array)):
            c = self.array[i]
            str += f'{c.type} {c.node1} {c.node2} {c.value:02.6f}'
            if i < len(self.array) - 1:
                str += '\n'
        return str

    def printNodes(self):
        for n in self.nodes:
            print(n)

    def save(self, dir):
        # print("saving", dir)

        path = os.path.join(dir, "infile_components.txt")
        f = open(path,"w")
        for c in self.array:
            f.write(f'{c.type}\n{c.value:02.6f}\n{c.node1}\n{c.node2}\n\n')
        f.close()

        path = os.path.join(dir, "ground.txt")
        f = open(path, "w")
        f.write( str(self.ground) )
        f.close()

        path = os.path.join(dir, "infile_solved.txt")
        f = open(path,"w")
        for x, val in self.raw_solved["e"]:
            f.write(f'{val:02.6f} ')
        for x, val in self.raw_solved["v"]:
            f.write(f'{val:02.6f} ')
        for x, val in self.raw_solved["i"]:
            f.write(f'{val:02.6f} ')
        f.close()

        path = os.path.join(dir, "outfile_reference.txt")
        f = open(path,"w")
        f.write("1,")
        for type, val in self.raw_solved["e"]:
            if type:
                f.write(f'{val:02.6f},')
        i = 0
        while i < len(self.raw_solved['v']):
            type, val = self.raw_solved['v'][i]
            out = val
            if type == 'C':
                a, b = self.raw_solved['v'][i+1]
                out += b
            if type:
                f.write(f'{out:02.6f},')
            i += 1
        i = 0
        while i < len(self.raw_solved['i']):
            type, val = self.raw_solved['i'][i]
            out = val
            if type == 'L':
                a, b = self.raw_solved['i'][i+1]
                out += b
            if type:
                f.write(f'{out:02.6f},')
            i += 1
        f.close()

class Component:
    def __init__(self, node1, node2):
        self.type = TYPES[np.random.randint(len(TYPES))]
        self.value = (np.random.randint(99)+1) * pow(10, np.random.randint(12) - 6)
        self.node1 = node1
        self.node2 = node2

class Solved:
    def __init__(self, length):
        self.components = Components(length)

def generateTests(n):
    for dir in os.listdir():
        if 'testcase' in dir:
            shutil.rmtree(dir)
    for i in range(n):
        dir = f'testcase{i+1}'
        os.mkdir(dir)
        a = Components(np.random.randint(MAX_COMPONENTS-1)+2)
        a.save(dir)

if GENERATE:
    generateTests(TESTS)

length = len(list(filter(lambda f: "testcase" in f, os.listdir())))
for i in range(length):
    dir = f'testcase{i+1}'
    f = open(os.path.join(dir, "ground.txt"))
    ground = f.read()
    inpath_components = os.path.join(dir, "infile_components.txt")
    inpath_solved = os.path.join(dir, "infile_solved.txt")
    outpath = os.path.join(dir, "outfile.txt")
    t = 1
    os.system(f'./a {inpath_components} {inpath_solved} {outpath} {ground} {t}')

    print(dir, ":", end=' ')
    reference = open(os.path.join(dir, "outfile_reference.txt")).read().split(',')[:-1]
    out = open(outpath).read().split(',')[:-1]
    passed = True
    if len(reference) != len(out):
        print(f"length umatched (result={len(out)}, reference={length})")
        continue
    else:
        for i in range(len(reference)):
            fr = float(reference[i])
            fo = float(out[i])
            if fr != fo:
                print(f"unmatched {i} (result={fo}, reference={fr})")
                passed = False
                continue
    if passed:
        print("passed")
