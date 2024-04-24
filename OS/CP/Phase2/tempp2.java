package OS.CP.Phase2;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;
public class tempp2 {
    static CPU cpu = CPU.getObject();
    static PCB pcb;
    static char[][] M = new char[300][4];
    static char[] BUFF = new char[40];
    static int SI = 3;
    static int TI = 0;
    static int PI = 0;
    static int EM;
    static int[] VA = new int[2];
    static int RA;
    static int page_fault;
    static int abTerminate;
    static BufferedReader input;
    static FileWriter output;

    static {
        try {
            input = new BufferedReader(new FileReader("/home/aniket-u22/SY2/OS/CP/Phase2/input1.txt"));
            output = new FileWriter("output.txt");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    static void init() {
        for (int i = 0; i < 4; i++) {
            cpu.R[i] = '-';
            cpu.IR[i] = '-';
            cpu.PTR[i] = '-';
            if (i < 2)
                cpu.IC[i] = '-';
        }
        cpu.C = false;

        for (int i = 0; i < 300; i++) {
            for (int j = 0; j < 4; j++) {
                M[i][j] = '-';
            }
        }

        SI = 3;
        TI = 0;
        PI = 0;

        abTerminate = 0;
    }

    static void clearbuff() {
        for (int i = 0; i < 40; i++) {
            BUFF[i] = '-';
        }
    }

    static int allocate() {
        Random rand = new Random();
        int allNum;

while (true) {
    allNum = rand.nextInt(29);

    if (cpu.PTR[3] == '-') {
        return allNum;
    } else if ((Character.getNumericValue(cpu.PTR[0]) * 1000 + Character.getNumericValue(cpu.PTR[1]) * 100
            + Character.getNumericValue(cpu.PTR[2]) * 10 + Character.getNumericValue(cpu.PTR[3])) == allNum * 10) {
        continue;
    } else {
        int j = (Character.getNumericValue(cpu.PTR[0]) * 1000 + Character.getNumericValue(cpu.PTR[1]) * 100
                + Character.getNumericValue(cpu.PTR[2]) * 10 + Character.getNumericValue(cpu.PTR[3]));
        for (int i = j; i < j + 10; i++) {
            int m = (Character.getNumericValue(M[i][0]) * 1000 + Character.getNumericValue(M[i][1]) * 100
                    + Character.getNumericValue(M[i][2]) * 10 + Character.getNumericValue(M[i][3]));
            if (m == allNum)
                continue;
        }
    }
k            return allNum;
        }
    }

    static void loadtoMemory(int word_no) {
        int k = 0, j = 0;
        while (k != 40) {
            M[word_no][j] = BUFF[k];
            if (BUFF[k] == 'H' && SI != 1) {
                j += 3;
            }
            k++;
            j++;
            if (j == 4) {
                j = 0;
                word_no++;
            }
        }
        clearbuff();
    }

    static void LOAD() throws IOException {
        String line;
        int jobNo = 1;

        while ((line = input.readLine()) != null) {
            for (int i = 0; i < line.length() && i < 40; i++) {
                BUFF[i] = line.charAt(i);
            }

            if (BUFF[0] == '$' && BUFF[1] == 'A' && BUFF[2] == 'M' && BUFF[3] == 'J') {
                System.out.println("------------------------ Job No." + jobNo++ + " ------------------------");
                init();
                pcb = new PCB();
                pcb.JOB_ID = String.valueOf(BUFF, 4, 4);
                pcb.TTL = (BUFF[8] - '0') * 1000 + (BUFF[9] - '0') * 100 + (BUFF[10] - '0') * 10 + (BUFF[11] - '0');
                pcb.TLL = (BUFF[12] - '0') * 1000 + (BUFF[13] - '0') * 100 + (BUFF[14] - '0') * 10 + (BUFF[15] - '0');
                clearbuff();

                int ptr_no = allocate() * 10;

                for (int i = ptr_no; i < ptr_no + 10; i++) {
                    for (int j = 0; j < 4; j++) {
                        M[i][j] = '*';
                    }
                }

                for (int j = 3; j >= 0; j--) {
                    cpu.PTR[j] = ptr_no % 10;
                    ptr_no /= 10;
                }

                int i = cpu.PTR[0] * 1000 + cpu.PTR[1] * 100 + cpu.PTR[2] * 10 + cpu.PTR[3];
                while ((line = input.readLine()) != null) {
                    for (int j = 0; j < line.length() && j < 40; j++) {
                        BUFF[j] = line.charAt(j);
                    }

                    if (!(BUFF[0] == '$' && BUFF[1] == 'D' && BUFF[2] == 'T' && BUFF[3] == 'A')) {
                        int frame_no = allocate();
                        loadtoMemory(frame_no * 10);

                        for (int j = 3; j >= 0; j--) {
                            M[i][j] = (char) (frame_no % 10 + 48);
                            frame_no /= 10;
                        }
                        i++;
                    } else {
                        break;
                    }
                }
            }

            if (BUFF[0] == '$' && BUFF[1] == 'D' && BUFF[2] == 'T' && BUFF[3] == 'A') {
                clearbuff();
                startExecution();
            }

            if (BUFF[0] == '$' && BUFF[1] == 'E' && BUFF[2] == 'N' && BUFF[3] == 'D') {
                System.out.println("           -----------------");
                for (int i = 0; i < 300; i++) {
                    System.out.print("    ");
                    if (i < 10)
                        System.out.print("00");
                    else if (i < 100)
                        System.out.print("0");

                    System.out.print(i + "    | ");
                    for (int j = 0; j < 4; j++) {
                        System.out.print(M[i][j] + " | ");
                    }
                    System.out.println();
                    if (i % 10 == 9)
                        System.out.println("           -----------------");
                }
                System.out.println("\n\n\n");
            }
        }
    }

    static void startExecution() throws IOException {
        cpu.IC[0] = 0;
        cpu.IC[1] = 0;
        executeUserProgram();
    }

    static void executeUserProgram() throws IOException {
        while (abTerminate == 0) {
            VA[0] = cpu.IC[0];
            VA[1] = cpu.IC[1];
            addressMap();

            if (PI != 0)
                break;

            for (int i = 0; i < 4; i++) {
                cpu.IR[i] = M[RA][i];
            }

            cpu.IC[1] += 1;
            if (cpu.IC[1] == 10) {
                cpu.IC[1] = 0;
                cpu.IC[0] += 1;
            }

            System.out.println(cpu.IR[0] + "" + cpu.IR[1] + "" + cpu.IR[2] + "" + cpu.IR[3]);

            if (cpu.IR[0] == 'G' && cpu.IR[1] == 'D') {
                if ('0' <= cpu.IR[3] && cpu.IR[3] <= '9')
                    cpu.IR[3] = '0';
                VA[0] = cpu.IR[2] - '0';
                VA[1] = cpu.IR[3] - '0';
                addressMap();

                if (PI == 3)
                    page_fault = 1;

                SI = 1;

                MOS();
            } else if (cpu.IR[0] == 'P' && cpu.IR[1] == 'D') {
                if ('0' <= cpu.IR[3] && cpu.IR[3] <= '9')
                    cpu.IR[3] = '0';
                VA[0] = cpu.IR[2] - '0';
                VA[1] = cpu.IR[3] - '0';
                addressMap();

                SI = 2;
                MOS();
            } else if (cpu.IR[0] == 'L' && cpu.IR[1] == 'R') {
                VA[0] = cpu.IR[2] - '0';
                VA[1] = cpu.IR[3] - '0';
                addressMap();

                if (PI != 0 || TI != 0) {
                    MOS();
                } else {
                    for (int i = 0; i < 4; i++) {
                        cpu.R[i] = M[RA][i];
                    }

                    simulation();
                }
            } else if (cpu.IR[0] == 'S' && cpu.IR[1] == 'R') {
                VA[0] = cpu.IR[2] - '0';
                VA[1] = cpu.IR[3] - '0';
                addressMap();

                if (PI == 3) {
                    page_fault = 1;
                    MOS();
                } else if (TI != 0 || PI == 2) {
                    MOS();
                } else {
                    for (int i = 0; i < 4; i++) {
                        M[RA][i] = cpu.R[i];
                    }

                    simulation();
                }
            } else if (cpu.IR[0] == 'C' && cpu.IR[1] == 'R') {
                VA[0] = cpu.IR[2] - '0';
                VA[1] = cpu.IR[3] - '0';
                addressMap();

                if (PI != 0 || TI != 0) {
                    MOS();
                } else {
                    cpu.C = true;
                    for (int i = 0; i < 4; i++) {
                        if (M[RA][i] != cpu.R[i]) {
                            cpu.C = false;
                            break;
                        }
                    }
                    simulation();
                }
            } else if (cpu.IR[0] == 'B' && cpu.IR[1] == 'T') {
                VA[0] = cpu.IR[2] - '0';
                VA[1] = cpu.IR[3] - '0';
                addressMap();

                if (PI != 0 || TI != 0) {
                    MOS();
                } else if (cpu.C) {
                    cpu.IC[0] = cpu.IR[2] - '0';
                    cpu.IC[1] = cpu.IR[3] - '0';

                    simulation();
                }
            } else if (cpu.IR[0] == 'H') {
                SI = 3;

                MOS();
                break;
            } else {
                PI = 1;
                MOS();
                break;
            }
        }
    }

    static void addressMap() {
        if (0 <= VA[0] && VA[0] <= 9 && 0 <= VA[1] && VA[1] <= 9) {
            int va = VA[0] * 10 + VA[1];
            int PTE = (cpu.PTR[0] * 1000 + cpu.PTR[1] * 100 + cpu.PTR[2] * 10 + cpu.PTR[3]) + (va / 10);
            if (M[PTE][0] == '-' && M[PTE][1] == '-' && M[PTE][2] == '-' && M[PTE][3] == '-') {
                PI = 3;
                page_fault = 0;
            } else {
                RA = ((M[PTE][0] - '0') * 1000 + (M[PTE][1] - '0') * 100 + (M[PTE][2] - '0') * 10
                        + (M[PTE][3] - '0')) * 10 + (va % 10);
            }
        } else {
            PI = 2;
        }
    }

    static void Terminate() throws IOException {
        if (EM == 0)
            output.write("Normal Termination");
        else {
            output.write("Abnormal Termination: ");
            switch (EM) {
                case (1):
                    output.write("Out Of Data");
                    break;
                case (2):
                    output.write("Line Limit Exceeded");
                    break;
                case (3):
                    output.write("Time Limit Exceeded");
                    break;
                case (4):
                    output.write("Operation Code Error");
                    break;
                case (5):
                    output.write("Operand Error");
                    break;
                case (6):
                    output.write("Invalid Page Fault");
                    break;
            }
            abTerminate = 1;
        }
        output.write("\nIC: " + cpu.IC[0] + cpu.IC[1] + ", IR: " + cpu.IR[0] + cpu.IR[1] + cpu.IR[2] + cpu.IR[3]
                + ", TTL: " + pcb.TTL + ", TTC: " + pcb.TTC + ", TLL: " + pcb.TLL + ", LLC: " + pcb.LLC + ", SI: "
                + SI + ", TI: " + TI + ", PI: " + PI + "\n\n\n");
    }

    static void simulation() {
        pcb.TTC += 1;
        if (pcb.TTC == pcb.TTL)
            TI = 2;
    }

    static void MOS() throws IOException {
        if (TI == 0) {
            if (PI == 1) {
                EM = 4;
                Terminate();
            } else if (PI == 2) {
                EM = 5;
                Terminate();
            } else if (PI == 3) {
                if (page_fault == 1) {
                    int frame_no = allocate();
                    int PTE = (cpu.PTR[0] * 1000 + cpu.PTR[1] * 100 + cpu.PTR[2] * 10 + cpu.PTR[3]) + VA[0];
                    for (int j = 3; j >= 0; j--) {
                        M[PTE][j] = (char) (frame_no % 10 + 48);
                        frame_no /= 10;
                    }
                    cpu.IC[1] -= 1;
                    if (cpu.IC[1] == -1) {
                        cpu.IC[1] = 9;
                        cpu.IC[0] -= 1;
                    }
                    page_fault = 0;
                    PI = 0;
                    simulation();
                } else {
                    EM = 6;
                    Terminate();
                }
            } else if (SI == 1) {
                String line = input.readLine();
                if (line != null) {
                    for (int i = 0; i < line.length() && i < 40; i++) {
                        BUFF[i] = line.charAt(i);
                    }
                    if (BUFF[0] == '$' && BUFF[1] == 'E' && BUFF[2] == 'N' && BUFF[3] == 'D') {
                        EM = 1;
                        Terminate();
                        input.reset();
                    } else {
                        loadtoMemory(RA);
                        SI = 0;
                        simulation();
                    }
                }
            } else if (SI == 2) {
                pcb.LLC += 1;
                if (pcb.LLC > pcb.TLL) {
                    EM = 2;
                    Terminate();
                } else {
                    for (int i = RA; i < RA + 10; i++) {
                        for (int j = 0; j < 4; j++) {
                            output.write(M[i][j]);
                        }
                    }
                    output.write("\n");
                    SI = 0;
                    simulation();
                }
            } else if (SI == 3) {
                simulation();
                SI = 0;
                EM = 0;
                Terminate();
            }
        } else if (TI == 2) {
            if (PI == 1) {
                EM = 3;
                Terminate();
                input.reset();
                EM = 4;
                Terminate();
            } else if (PI == 2) {
                EM = 3;
                Terminate();
                input.reset();
                EM = 5;
                Terminate();
            } else if (PI == 3) {
                EM = 3;
                Terminate();
            } else if (SI == 1) {
                EM = 3;
                Terminate();
            } else if (SI == 2) {
                pcb.LLC += 1;
                if (pcb.LLC > pcb.TLL) {
                    EM = 2;
                    Terminate();
                    output.flush();
                } else {
                    for (int i = RA; i < RA + 10; i++) {
                        for (int j = 0; j < 4; j++) {
                            output.write(M[i][j]);
                        }
                    }
                    output.write("\n");
                    simulation();
                }
                EM = 3;
                Terminate();
            } else {
                EM = 3;
                Terminate();
            }
        }
    }

    public static void main(String[] args) {
        try {
            init();
            LOAD();
            input.close();
            output.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }    
}

class CPU {
    char[] R = new char[4];
    char[] IR = new char[4];
    int[] IC = new int[2];
    int[] PTR = new int[4];
    boolean C;

    private static CPU object = new CPU();

    private CPU() {
    }

    static CPU getObject() {
        return object;
    }
}

class PCB {
    String JOB_ID;
    int TTL, TLL, TTC, LLC;

    PCB() {
        this.JOB_ID = "";
        this.TTL = 0;
        this.TLL = 0;
        this.TTC = 0;
        this.LLC = 0;
    }
}

