import os
import numpy as np
import shutil

GENERATE = True
MAX_COMPONENTS = 20
TYPES = ['R', 'R', 'R', 'V', 'I', 'v', 'i']
TESTS = 10


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

        path1 = os.path.join(dir, 'outfile_coef_reference.txt')
        path2 = os.path.join(dir, 'outfile_const_reference.txt')
        e_length = len(self.nodes) - 1
        comp_length = len(self.array)
        A = np.zeros((e_length, comp_length))
        groundPassed = 0
        i = 0
        while i < len(self.nodes):
            node = self.nodes[i]
            if node != self.ground:
                for j in range(comp_length):
                    c = self.array[j]
                    if c.node1 == node:
                        A[i - groundPassed][j] = -1
                    elif c.node2 == node:
                        A[i - groundPassed][j] = 1
            else:
                groundPassed = 1
            i += 1
        M = np.zeros((comp_length, comp_length))
        N = np.zeros((comp_length, comp_length))
        u = np.zeros((comp_length,1))
        for i in range(comp_length):
            type = self.array[i].type
            value = self.array[i].value
            if type == 'R':
                M[i][i] = 1
                N[i][i] = -value
            elif type in ['V', 'v']:
                M[i][i] = 1
                u[i] = value
            elif type in ['I', 'i']:
                N[i][i] = 1
                u[i] = value
        one = np.zeros((e_length, comp_length + e_length))
        one = np.concatenate((one, A), axis=1)
        # print(one)
        two = np.zeros((comp_length, comp_length))
        two = np.concatenate((np.transpose(A), np.identity(comp_length), two), axis=1)
        # print(two)
        three = np.zeros((comp_length, e_length))
        three = np.concatenate((three, M, N), axis=1)
        # print(three)
        coef = np.concatenate((one, two, three))
        try:
            inversed = np.linalg.inv(coef)
        except np.linalg.LinAlgError:
            return False
        inversed = np.around(inversed, decimals=6)
        np.savetxt(path1, inversed, delimiter=',')
        four = np.zeros((e_length + comp_length, 1))
        u = np.around(u, decimals=6)
        u = np.concatenate((four, u))
        np.savetxt(path2, u, delimiter=',')

        path = os.path.join(dir, "infile_components.txt")
        f = open(path,"w")
        for c in self.array:
            f.write(f'{c.type}\n{c.value:02.6f}\n{c.node1}\n{c.node2}\n\n')
        f.close()

        path = os.path.join(dir, "ground.txt")
        f = open(path, "w")
        f.write( str(self.ground) )
        f.close()

        return True

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
        # print(a)
        while not a.save(dir):
            # print("inversed not found")
            a = Components(np.random.randint(MAX_COMPONENTS-1)+2)
            # print(a)


if GENERATE:
    generateTests(TESTS)

length = len(list(filter(lambda f: "testcase" in f, os.listdir())))
for i in range(length):
    dir = f'testcase{i+1}'
    f = open(os.path.join(dir, "ground.txt"))
    ground = f.read()
    inpath_components = os.path.join(dir, "infile_components.txt")
    outpath_coef = os.path.join(dir, "outfile_coef.txt")
    outpath_const = os.path.join(dir, "outfile_const.txt")
    os.system(f'./a {inpath_components} {outpath_coef} {outpath_const} {ground}')

    print(dir, ":", end=' ')
    # print()
    reference = np.genfromtxt(os.path.join(dir, "outfile_coef_reference.txt"), delimiter=',')
    # print(reference)
    out = np.genfromtxt(outpath_coef, delimiter=',')
    # print(out)
    # out = open(outpath).read().split(',')[:-1]
    passed = True
    if len(reference) != len(out) or len(reference[0]) != len(out[0]):
        print(f"length unmatched coef (result={len(out)}, reference={length})")
        continue
    else:
        for i in range(len(reference)):
            for j in range(len(reference)):
                fr = reference[i][j]
                fo = out[i][j]
                # print(fo, fr)
                if fr != fo:
                    print(f"unmatched coef [{i}][{j}] (result={fo}, reference={fr})")
                    passed = False
                    break
            if not passed:
                break
        if not passed:
            continue

    reference = np.genfromtxt(os.path.join(dir, "outfile_const_reference.txt"), delimiter=',')
    out = np.genfromtxt(outpath_const, delimiter=',')
    if len(reference) != len(out):
        print(f"length unmatched const (result={len(out)}, reference={length})")
        continue
    else:
        for i in range(len(reference)):
            fr = reference[i]
            fo = out[i]
            # print(fo, fr)
            if fr != fo:
                print(f"unmatched const [{i}] (result={fo}, reference={fr})")
                passed = False
                break


    if passed:
        print("passed")
