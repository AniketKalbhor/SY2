'''OS CP'''

M, Buff, R, IR = [],[],[],[]
IC = 0
C = False
SI = 0

def initialize():
    for i in range(100):
        M.append([0,0,0,0])

def mos():
    global Buff
    global IR
    global M
    if SI == 1:
        i = 0
        count = 0
        while Buff[0][i] != '\n':
            i += 1

        for k in range(0,i,4):
            M[int(IR[0][2:])+count] = Buff[0][k:k+4]
            count += 1
        Buff.pop()

    elif SI == 2:
        Buff.append(M[int(IR[0][2:])])
        try:
            with open("/home/aniket/Desktop/SY2/OS/ref/rPhase1/output.txt", 'a') as out:
                out.write(Buff[0])
                out.write("\n")
            out.close()
        except Exception as e:
            print(e)
        Buff.pop()

    elif SI == 3:
        print()
        print()
    IR.pop()

def executeUserPgm():
    global IC
    global SI
    global IR
    global R
    global C
    global M

    IR.append(M[IC])

    if IR[0][:2] == "GD":
        SI = 1
        mos()
    elif IR[0][:2] == "PD":
        SI = 2
        mos()
    elif IR[0][:2] == "H":
        SI = 3
        mos()
    elif IR[0][:2] == "LR":
        R.append(M[int(IR[0][2:])])
        IR.pop()
    elif IR[0][:2] == "SR":
        M[int(IR[2:])] = R
        IR.pop()
    elif IR[0][:2] == "CR":
        if R[0] == M[int(IR[0][2:])]:
            C = True
        IR.pop()
    elif IR[0][:2] == "BT":
        if C is True:
            IC = int(IR[0][2:])
        IR.pop()

def init():
    print("This is init function")

def start_exec():
    executeUserPgm()

def load():
    global Buff
    global IC
    filename = "input.txt"
    try:
        with open(filename, 'r') as file:
            length = 0
            for line in file:
                if line[:4] == "$AMJ":
                    init()
                elif line[:4] == "$DTA":
                    while True:
                        next_line = file.readline()
                        if next_line[:4] == "$END":
                            print()
                            break
                        Buff.append(next_line)
                        executeUserPgm()
                        IC += 1

                    x = ''
                    while x != 'H':
                        executeUserPgm()
                        IC = int(IC) + 1
                        x = M[IC][0]

                else:
                    length = len(line)
                    index = 0

                    for i in range(0,length,4):
                        M[index] = line[i:i+4]
                        index += 1

            for i in range(100):
                print("M["+str(i)+"] = "+str(M[i]))

    except FileNotFoundError:
        print("File not found.")

initialize()