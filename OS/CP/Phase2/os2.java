import java.io.*;
import java.util.*;

class FileReaderHelper{
    public static final String filename = "/home/aniket/Desktop/SY2/OS/CP/Phase2/input1.txt";
    public static BufferedReader br;
    static {
        try {
            br = new BufferedReader(new FileReader(filename));
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
    }
    public static String readLine() throws IOException{
        return br.readLine();
    }
}

class PCB {
    StringBuilder jobId;
    int ttl, tll, ttc, llc;

    public PCB() {
        jobId = new StringBuilder();
        ttl = 0;
        tll = 0;
        ttc = 0;
        llc = 0;
    }

    public void PCBinit() {
        jobId.setLength(0);
        ttl = 0;
        tll = 0;
        ttc = 0;
        llc = 0;
    }
}

public class os2 extends PCB {

    Random rand = new Random();
    public static final int MAX_MEMORY = 300;
    char[][] M = new char[MAX_MEMORY][4];
    char[] IR = new char[4];
    char[] R = new char[4];
    int IC[] = new int[2];
    boolean C;
    int SI;

    //added for phase 2
    int PTR[] = new int[4];
    int TI=0;   //time interrupt
    int PI=0;   //programming interrupt
    int EM;
    int RA;
    int VA[] = new int[2];
    int pageFault; //0: Invalid, 1: Valid
    int abnormalTerminate; // 0:Normal Termination, 1:Abnormal Termination

    StringBuilder buffer = new StringBuilder(40);
    
    public void printMemory(){
        System.out.println("Memory:");    
        for(int i=0;i<MAX_MEMORY;i++){
            for(int j=0;j<4;j++)
                System.out.print(M[i][j]);
            System.out.println();
        }
    }

    public void init(){
        System.out.println("Initialising memory and registers.....");
        for(int i=0;i<MAX_MEMORY;i++){
            for(int j=0;j<4;j++){
                M[i][j] = 'ඞ';
            }
        }
        for(int i=0;i<4;i++){
            IR[i] = 'ඞ';
            R[i] = 'ඞ';
            PTR[i] = 'ඞ';
        }
        SI=3;
        TI=0;
        PI=0;
        abnormalTerminate=0;
        
        System.out.println("Memory and registers initialised");
    }
    
    int allocate(){
        int allocNum;
        label:
        while(true){
            allocNum = rand.nextInt(30);
            if(PTR[3] == 'ඞ')
                return allocNum;
            else if(PTR[0]*1000 + PTR[1]*100 + PTR[2]*10 + PTR[3] == allocNum*10)
                continue label;
            else{
                int j = PTR[0]*1000 + PTR[1]*100 + PTR[2]*10 + PTR[3];
                for(int i=0;i<j+10;i++){
                    int m = (M[i][0] - 48)*1000 + (M[i][1] - 48)*100 + (M[i][2] - 48)*10 + (M[i][3] - 48);
                    if(m == allocNum)
                    continue label;
                }
            }
            return allocNum;
        }
    }
        
    void addressMap() {
        if (0<=VA[0] && VA[0]<=9 && 0<=VA[1] && VA[1]<=9) {
            int virtualAddress = VA[0]*10 + VA[1];
            int PTE = PTR[0]*1000 + PTR[1]*100 + PTR[2]*10 + PTR[3] + (virtualAddress/10);
            if (M[PTE][0] == 'ඞ' && M[PTE][1] == 'ඞ' && M[PTE][2] == 'ඞ' && M[PTE][3] == 'ඞ') {
                PI = 3;
                pageFault = 0;
            }
            else {
                RA = (M[PTE][2] - 48)*1000 + (M[PTE][3] - 48)*100 + VA[0]*10 + virtualAddress%10;                   
            }
            RA = PTR[0]*1000 + PTR[1]*100 + PTR[2]*10 + VA[0];
            pageFault = 1;
        }
        else
            PI = 2;
    }

    void simulation() {
        ttc++;
        if (ttc == ttl) {
            TI = 2;
            System.out.println("Time Limit Exceeded");
        }
    }

    public void start_exe(){
        IC[0] = 0;
        IC[1] = 0;
        executeUserProgram();
    }
    

    public void executeUserProgram() {
    while (abnormalTerminate == 0) {
        VA[0] = IC[0];
        VA[1] = IC[1];
        addressMap();
        if (PI!=0)
            break;
            
            for (int i = 0; i < 4; i++)
            IR[i] = M[RA][i];
            IC[1]++;
            
            if(IC[1] == 10){
                IC[0]++;
                IC[1] = 0;
            }
            
            System.out.println("IR: " + IR[0] + IR[1] + IR[2] + IR[3]);
            
        if(IR[0] == 'G' && IR[1] == 'D'){
            if('0'<=IR[3] && IR[3]<='9')
                IR[3] = '0';
            VA[0] = IR[2]-'0';
            VA[1] = IR[3]-'0';
            addressMap();
            
            if(PI == 3){
                System.out.println("Page Fault");
                pageFault = 1;
            }
            SI = 1;
            System.out.println();
            MOS();
        }
        else if(IR[0] == 'P' && IR[1] == 'D'){
            if('0'<=IR[3] && IR[3]<='9')
            IR[3] = '0';
            VA[0] = IR[2]-'0';
            VA[1] = IR[3]-'0';
            addressMap();
            
            SI = 2;
            System.out.println();
            MOS();
        }
        else if(IR[0] == 'L' && IR[1] == 'R'){
            VA[0] = IR[2]-'0';
            VA[1] = IR[3]-'0';
            addressMap();

            if(PI!=0 || TI!=0)
                MOS();
            else{
                for(int j=0;j<4;j++)
                    R[j] = M[RA][j];
                System.out.println("LR, load register");
                simulation();
            }
        }
        else if(IR[0] == 'S' && IR[1] == 'R'){
            VA[0] = IR[2]-'0';
            VA[1] = IR[3]-'0';
            addressMap();
            
            if (PI==3) {
                pageFault = 1;
                System.out.println("Page Fault");
                MOS();                    
            }
            else if(PI==2 || TI!=0)
            MOS();
            else{
                for(int j=0;j<4;j++)
                M[RA][j] = R[j];
                System.out.println("SR, store register");
                simulation();
            }
        }
        else if(IR[0] == 'C' && IR[1] == 'R'){
            VA[0] = IR[2]-'0';
            VA[1] = IR[3]-'0';
            addressMap();
            
            if(PI!=0 || TI!=0)
            MOS();
            else{
                for(int i=0;i<4;i++){
                    if(M[RA][i]==R[i])
                    C=true;
                    else{
                        C=false;
                        break;
                    }
                }
                System.out.println("CR, compare register");
                simulation();
            }
        }
        else if(IR[0] == 'B' && IR[1] == 'T'){
            VA[0] = IR[2]-'0';
            VA[1] = IR[3]-'0';
            addressMap();

            if (PI!=0 || TI!=0)
                MOS();
            else if (C) {
                IC[0] = IR[2]-'0';
                IC[1] = IR[3]-'0';
                System.out.println("BT, branched-true");
                simulation();
            }
            else if(IR[0] == 'H'){
                SI = 3;
                System.out.println("H, halt");
                MOS();
                break;
            }
            else{
                System.out.println("Invalid instruction");
                PI = 1;
                MOS();
                break;
            } 
        }
    }
    }

    void Termination(){
        if(EM==0){
            System.out.println("Normal Termination");
            abnormalTerminate = 0;
        }
        else{
            System.out.println("Abnormal Termination");
            switch (EM) {
                case 1:
                    System.out.println("Out of Data");
                    break;
                case 2:
                    System.out.println("Line Limit Exceeded");
                    break;
                case 3:
                    System.out.println("Time Limit Exceeded");
                    break;
                case 4:
                    System.out.println("Operation Code Error");
                    break;
                case 5:
                    System.out.println("Operand Error");
                    break;
                case 6:
                    System.out.println("Invalid Page Fault");
                    break;
            }
            abnormalTerminate = 1;
        }
        System.out.println("Execution ended");
        System.out.println("IC: " + IC[0] + " " + IC[1]);
        System.out.println("IR: " + IR[0] + IR[1] + IR[2] + IR[3]);
        System.out.println("TTL: " + ttl);
        System.out.println("TTC: " + ttc);
        System.out.println("LLC: " + llc);
        System.out.println("TLL: " + tll);
        System.out.println("SI: " + SI + " PI: " + PI + " TI: " + TI);
    }

    public void MOS() {
        buffer.setLength(0);
        if (TI==0) {
            if (PI == 1) {
                EM = 4;
                Termination();
            }
            else if (PI == 2) {
                EM = 5;
                Termination();
            }
            else if (PI == 3){
                if (pageFault == 1) {
                    int frame = allocate();
                    int PTE = PTR[0]*1000 + PTR[1]*100 + PTR[2]*10 + PTR[3] + VA[0];
                    for (int j = 3; j>=0; j--){
                        M[PTE][j] = (char)(frame/10 + 48);
                        frame = frame%10;
                    }
                    IC[1]--;
                    if (IC[1] == -1){
                        IC[0]--;
                        IC[1] = 9;
                    }
                    pageFault = 0;
                    PI = 0;
                    simulation();
                }
                else {
                    EM = 6;
                    Termination();
                }
            }
        }
        else if (SI == 1){
            System.out.println("GD, Read from input device");
            try {
                String data = FileReaderHelper.readLine();
                System.out.println("**********Data:"+data);
                buffer.append(data);
                if (buffer.substring(0,4).equals("$END")) {
                    EM = 1;
                    Termination();
                    //
                }
                else{
                    loadToMem(RA);
                    SI = 0;
                    simulation();
                }}catch (IOException e) {
                    e.printStackTrace();
                }
            }
        else if(SI == 2){
            llc++;
            System.out.println("PD, Write to output device: ");
            if(llc>tll){
                EM = 2;
                Termination();
            }
            else{
                for(int i = RA; i<RA+10; i++)
                    for(int j=0;j<4;j++)
                        System.out.println(M[i][j]);
                SI = 0;
                simulation();
            }

            // String output = "";
            // for (int j = 0; j < 10; j++) {
            //     for (int k = 0; k < 4; k++){
            //         if (M[i][k] == 'ඞ') {
            //             break;
            //         }
            //         output += M[i][k];
            //     }
            //     i++;
            // }
            // try {
            //     FileWriter myWriter = new FileWriter("/home/aniket/Desktop/SY2/OS/CP/Phase1/output.txt");
            //     myWriter.write(output);
            //     myWriter.close();
            //     System.out.println("Successfully wrote to the file.");
            //     } catch (IOException e) {
            //     System.out.println("An error occurred.");
            //     e.printStackTrace();
            //     }
            // System.out.println(output);
        }
        else{
            EM = 3;
            Termination();
        }
    }

    public void loadToMem(int wordNum){
        int k = 0;
        for (int i = wordNum; k < buffer.length(); i++)
            for (int j = 0; j < 4; j++)
            {
                if(buffer.charAt(k) == 'H')
                {
                    M[i][j] = buffer.charAt(k++);
                    break;
                }
                else
                M[i][j] = buffer.charAt(k++);
            }
            buffer.setLength(0);
    }
    
    public void  load(){
        int block_index = 0;
        try{
            String line;
            while ((line = FileReaderHelper.readLine()) != null) {
                System.out.println();
                System.out.println("Line: " + line);
                
                buffer.append(line);
                System.out.println("Buffer:"+ buffer);
                if (buffer.substring(0, 4).equals("$AMJ")) {
                    SI = 1;
                    jobId = new StringBuilder(buffer.substring(4, 8));
                    ttl = (buffer.charAt(8) - 48) * 1000 + (buffer.charAt(9)- 48) * 100 + (buffer.charAt(10) - 48) * 10 + (buffer.charAt(11) - 48);
                    tll = (buffer.charAt(12) - 48) * 1000 + (buffer.charAt(13)- 48) * 100 + (buffer.charAt(14) - 48) * 10 + (buffer.charAt(15) - 48);
                    System.out.println("AMJ, job id: " + jobId + " ttl: " + ttl + " tll: " + tll);
                    buffer.setLength(0);
                    init();
                    System.out.println("AMJ, initialised memory and registers");
                } else if (buffer.substring(0, 4).equals("$DTA")) {
                    System.out.println("DTA, started execution");
                    buffer.setLength(0);
                    start_exe();
                } else if (buffer.substring(0, 4).equals("$END")) {
                    PCBinit();
                    // SI = 3;
                    buffer.setLength(0);
                    printMemory();
                    try {
                        FileWriter myWriter = new FileWriter("output.txt");
                        myWriter.write("");
                        myWriter.write("");
                        myWriter.close();
                        System.out.println("Successfully wrote to the file.");
                        } catch (IOException e) {
                        System.out.println("An error occurred.");
                        e.printStackTrace();
                        }
                    System.out.println("END, ended execution");
                } else {
                    if (block_index > MAX_MEMORY){
                        System.out.println("Memory full");
                        break;
                    }
                    loadToMem(0);
                }
            }
        } catch (FileNotFoundException e) {
            System.out.println("File not found");
            e.printStackTrace();
        } catch (IOException e) {
            System.out.println("Error reading file");
            e.printStackTrace();
        }
        finally{
            System.out.println("Memory loaded");
            printMemory();
        }
    }
    
    public static void main(String[] args) {
        os2 job = new os2();
        job.load();
    }
}