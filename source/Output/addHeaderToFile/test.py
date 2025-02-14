import os
import numpy as np
import shutil

MAX_COMPONENTS = 30
TYPES = ['R', 'V', 'I', 'C', 'L']
TESTS = 5

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
        for i in range(1, length):
            paralel = np.random.randint(2) * (i - 1) # false kalau i = 1
            if paralel:
                c = Component(c.node1, c.node2)
            else:
                temp = c.node2
                c.node2 = createRandomNode()
                c = Component(c.node2, temp)
            self.array.append(c)

        self.ground = self.nodes[np.random.randint(len(self.nodes))]

    def printComponents(self):
        for c in self.array:
            # print(c.type, c.node1, c.node2, c.value)
            print(f'{c.type} {c.node1} {c.node2} {c.value:02.6f}')

    def printNodes(self):
        for n in self.nodes:
            print(n)

    def save(self, dir):
        # print("saving", dir)
        path = os.path.join(dir, "test_infile.txt")
        f = open(path,"w")
        for c in self.array:
            f.write(f'{c.type}\n{c.value:02.6f}\n{c.node1}\n{c.node2}\n\n')
        f.close()
        path = os.path.join(dir, "ground.txt")
        f = open(path, "w")
        f.write( str(self.ground) )
        f.close

        path = os.path.join(dir, "test_outfile_reference.txt")
        f = open(path, "w")
        f.write('t,')
        for n in self.nodes:
            if n != self.ground:
                f.write(f'node {n} (Volt),')

        count = {}
        for c in self.array:
            if not c.type in count.keys():
                count[c.type] = 1
            else:
                count[c.type] += 1
            f.write(f'V({c.type}{count[c.type]}) (Volt),')

        count = {}
        for c in self.array:
            if not c.type in count.keys():
                count[c.type] = 1
            else:
                count[c.type] += 1
            f.write(f'I({c.type}{count[c.type]}) (Amp),')
        f.write("\n")
        f.close()

class Component:
    def __init__(self, node1, node2):
        self.type = TYPES[np.random.randint(5)]
        self.value = (np.random.randint(99)+1) * pow(10, np.random.randint(12) - 6)
        self.node1 = node1
        self.node2 = node2

def generateTests(n):
    for dir in os.listdir():
        if 'testcase' in dir:
            shutil.rmtree(dir)
    for i in range(n):
        dir = f'testcase{i+1}'
        os.mkdir(dir)
        a = Components(np.random.randint(MAX_COMPONENTS)+1)
        a.save(dir)

generateTests(TESTS)

length = len(list(filter(lambda f: "testcase" in f, os.listdir())))
for i in range(length):
    dir = f'testcase{i+1}'
    f = open(os.path.join(dir, "ground.txt"))
    ground = f.read()
    inpath = os.path.join(dir, "test_infile.txt")
    outpath = os.path.join(dir, "test_outfile.txt")
    os.system(f'./a {inpath} {outpath} {ground}')

    reference = open(os.path.join(dir, "test_outfile_reference.txt")).read().split(',')
    out = open(outpath).read().split(',')
    if (reference == out):
        print(dir, "passed")
    else:
        print(dir, "failed: ", end="")
        length = len(reference)
        if length != len(out):
            print(f"length umatched (result={len(out)}, reference={length})")
            continue
        else:
            for i in range(length):
                if reference[i] != out[i]:
                    print(f"unmatched {i} (result={out[i]}, reference={reference[i]})")
                    continue
