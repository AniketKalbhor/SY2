import random

M, Buff, R, IR = [], [], [], []
IC, SI, PI, TI, TTC, LLC, EM, flag = 0, 0, 0, 0, 0, 0, 0, -1
C = False
PTR, VA, RA = -1, -1, -1
valid_bit = False
page_flag = [False] * 30
file = ""


class PCB:
    def init(self):
        self.job_id = 0
        self.TTL = 0
        self.TLL = 0
        self.TTC = 0
        self.TLC = 0

    def update(self, id, linel, time, lcount, tcount):
        self.job_id = id
        self.TTL = linel
        self.TLL = time
        self.TLC = lcount
        self.TTC = tcount


pcb = PCB()

def initialize():
    global M, Buff
    M = ["*" for _ in range(300)]
    # Buff = [[0, 0, 0, 0] for _ in range(40)]


def mos():
    global SI, PI, TI, TTC, RA, VA, valid_bit, IR, Buff, line, file, pcb
    
    if pcb.TTC > pcb.TTL:
        TI = 2

    if TI == 0:
        if SI == 1:
            SI = 0
            i = 0
            count = 0
            # print(Buff)
            # i = len(Buff[0])

            temp = IR[0]
            # print(temp)
            VA = int(temp[2:])
            # print("VA FOR ;",VA)
            RA = addressMap()
            # print("BUUFFE", Buff)
            line = file.readline()
            i = len(line)
            for k in range(0, i, 4):
                M[RA * 10 + count] = line[k:k + 4]
                count += 1
            # Buff.pop(0)
            IR.pop(0)

        elif SI == 2:
            VA = int(IR[0][2:])
            print("VA", VA)
            RA = addressMap()
            Buff.append(M[RA * 10 + VA % 10])
            print("M[RA] = ", M[RA * 10 + VA % 10])
            # pcb.TLC += 1

            try:
                with open("/home/aniket-u22/SY2(linux)/OS/ref/rPhase 2/output.txt", 'a') as out:
                    out.write("".join(map(str, Buff[0])))
                    out.write("\n")
            except Exception as e:
                print(e)
            Buff.pop(0)
            IR.pop(0)

            if pcb.TLC > pcb.TLL:
                terminate(2)

        elif SI == 3:
            try:
                with open("/home/aniket-u22/SY2(linux)/OS/ref/rPhase 2/output.txt", 'a') as out:
                    out.write("\n\n")
            except Exception as e:
                print(e)
            IR.pop(0)

        elif PI == 1:
            with open("/home/aniket-u22/SY2(linux)/OS/ref/rPhase 2/log.txt", 'a+') as file:
                file.write("Error")
            PI = 0
            terminate(4)

        elif PI == 2:
            terminate(5)

        elif PI == 3:
            if not valid_bit:
                print("valid")
                b = allocate()
                print(b)
                M[PTR * 10 + VA // 10] = b
            else:
                # print("invaid")
                terminate(6)


    elif TI == 2:
        TI = 0
        if SI == 1:
            terminate(3)

        elif SI == 2:
            VA = int(IR[0][2:])
            RA = addressMap()
            Buff.append(M[RA])
            pcb.TLC += 1

            try:
                with open("/home/aniket-u22/SY2(linux)/OS/ref/rPhase 2/output.txt", 'a') as out:
                    out.write("".join(map(str, Buff[0])))
                    out.write("\n")
            except Exception as e:
                print(e)
            Buff.pop(0)
            IR.pop(0)

            if pcb.TLC > pcb.TLL:
                terminate(2, 3)
            else:
                terminate(3)

        elif SI == 3:
            terminate(0)

        elif PI == 1:
            # with open("C:/Users/harsh/OneDrive/Desktop/SEM4/OS/log.txt", 'a+') as file:
            #     file.write("Error")
            terminate(3, 4)

        elif PI == 2:
            terminate(3, 5)
            PI = 0

        elif PI == 3:
            terminate(3)


def terminate(*args):
    global PI, TI

    out = open("/home/aniket-u22/SY2(linux)/OS/ref/rPhase 2/output.txt", 'a')

    for arg in args:
        if arg == 1:
            out.write("OUT OF DATA ERROR OCCURRED!!")
        elif arg == 2:
            out.write("LINE LIMIT EXCEEDED!!")
        elif arg == 3:
            TI = 0
            out.write("TIME LIMIT EXCEEDED!!")
        elif arg == 4:
            PI = 0
            out.write("OPCODE ERROR OCCURRED!!")
        elif arg == 5:
            out.write("OPERAND ERROR OCCURRED!!")
        elif arg == 6:
            out.write("INVALID PAGE FAULT!!")

    out.write("\nJob Id:")
    out.write(str(pcb.job_id))
    out.write("\nTTC:")
    out.write(str(pcb.TTC))
    out.write("\nTLC:")
    out.write(str(pcb.TLC))
    out.write("\nTTL:")
    out.write(str(pcb.TTL))
    out.write("\nTLL:")
    out.write(str(pcb.TLL))
    out.write("\n\n")
    out.close()


def addressMap():
    global RA, PI, VA
    PTE = PTR * 10 + VA // 10
    # print("PTE: ",PTE)

    if (M[PTE] != "*"):
        # print(M[PTE])
        RA = int(M[PTE])
        return RA
    else:
        PI = 3
        mos()
        PI = 0
        return addressMap()


def executeUserPgm():
    global IC
    global SI, PI, TI, RA, VA
    global R
    global C
    global pcb
    global valid_bit
    while True:
        # print(IC)
        VA = IC
        # print("VA for addresss map",VA)
        print("IC : ", IC)
        RA = addressMap()
        # print(RA)
        print("IR TO BE FOUND", M[RA * 10 + VA % 10])

        IR.append(M[RA * 10 + VA % 10])

        # print(,IR[0][:2])
        # print(type("GD"))

        if IR[0][:2] == "GD":
            print("GD found", IR)
            SI = 1
            # valid_bit = True
            pcb.TTC += 2
            mos()
            # IC += 1
        elif IR[0][:2] == "PD":
            print("PD found", IR)
            SI = 2
            valid_bit = True
            pcb.TTC += 1
            mos()
            # IC += 1
        elif IR[0][:1] == "H":
            print("H found")
            SI = 3
            pcb.TTC += 1
            mos()
            break
            # IC += 1
        elif IR[0][:2] == "LR":
            R.append(M[int(IR[0][2:])])
            pcb.TTC += 1
            IR.pop(0)
        elif IR[0][:2] == "SR":
            M[int(IR[2:])] = R
            # valid_bit = True
            pcb.TTC += 2
            IR.pop(0)
        elif IR[0][:2] == "CR":
            if R[0] == int(M[int(IR[0][2:])]):
                C = True
            # print(C)
            pcb.TTC += 1
            IR.pop(0)
        elif IR[0][:2] == "BT":
            if C:
                IC = int(IR[0][2:])
            pcb.TTC += 1
            IR.pop(0)
        else:
            PI = 1
            pcb.TTC += 1
            mos()
            IR.pop()
        IC += 1

def allocate():
    a = random.randint(0, 28)
    print("a = ", a)
    if not page_flag[a]:
        page_flag[a] = True
        return a
    else:
        return allocate()


def init():
    print("This is init function")


def load():
    global IC
    global flag
    global pcb
    global PTR, VA, RA, filename, line, pcb

    try:
        while line:
            if line[:4] == "$AMJ":
                flag = 0
                init()
                pcb.update(int(line[4:8]), int(line[8:12]), int(line[12:16]), 0, 0)
                print(pcb.job_id, pcb.TLL, pcb.TTL, pcb.TLC, pcb.TTC)
                PTR = allocate()
                print(PTR, page_flag)
                IC = 0
                VA = IC
                RA = addressMap()
                M[PTR * 10 + VA // 10] = RA
            elif line[:4] == "$DTA":
                IC = 00
                try:
                    executeUserPgm()
                except:
                    print("FAILED")
                # while True:
                    # next_line = file.readline()
                    #
                    #     try:
                    #         with open("./output.txt", 'a') as out:
                    #             out.write("\n\n")
                    #     except Exception as e:
                    #         print(e)
                    #     break
                    # Buff.append(next_line)
                    # executeUserPgm()
                    # IC += 1
                    # print(IC)
            elif line[:4] == "$END":
                pass
                # x = ''
                # while x != 'H':
                #     executeUserPgm()
                #     # print(M[RA])
                #     x = M[RA][0]
                #     IC += 1
                # IC = 0
            else:
                length = len(line)
                VA = 0
                RA = addressMap()
                print("RA IN GD PD ", RA)
                j = 0
                for i in range(0, length, 4):
                    M[RA * 10 + j] = line[i:i + 4]
                    j += 1
            line = file.readline()
        for i in range(300):
            print("M[" + str(i) + "] = " + str(M[i]))

    except FileNotFoundError:
        print("File not found.")


filename = "/home/aniket-u22/SY2(linux)/OS/ref/rPhase 2/input.txt"
file = open(filename, "r+")
line = file.readline()
initialize()
load()