import java.util.*;
import java.io.*;

public class temp{
    char[][] M = new char[100][4];
    char[] IR = new char[4];
    char[] R = new char[40];
    int IC;
    boolean C;
    int SI;
    char[] buffer = new char[40];

    public void start_exe() {

        while (true) {
            for (int i = 0; i < 4; i++) {
                IR[i] = M[IC][i];
                IC++;

                if (IR[0] == 'G' && IR[1] == 'D') {
                    SI = 1;
                    System.out.println("GD, read from input device");
                    MOS();
                }
                if (IR[0] == 'P' && IR[1] == 'D') {
                    SI = 2;
                    System.out.println("PD, write to output device");
                    MOS();
                }
                if (IR[0] == 'H') {
                    SI = 3;
                    System.out.println("H, halt");
                    MOS();
                    break;
                } else {
                    System.out.println("Invalid instruction");
                }
            }
        }
    }

    public void MOS() {
        if(SI == 1){
             //for(int i=0;i<4;i++)
                //buffer[i] = '\0';
            System.out.println("Read from input device");
            for(int i=0;i<40;i++){
                R[i] = buffer[i];
            }
            int i = IR[2] - 48;
            i = i * 10;
            System.out.println("Data read: " + new String(R));
            while (true) {
                for (int j = 0; j < 4; j++) {
                    System.out.print(buffer[j]);
                    M[i][j] = buffer[j];
                    i++;
                }
            }
           // i++;
        }
        else if(SI == 2){
            System.out.println("Write to output device");
            System.out.println("Data written: " + new String(R));
        }
        else if(SI == 3){
            System.out.println("Halt");
            System.out.println("Execution ended");
        }
        else{
            System.out.println("Invalid interrupt");
        }
    }

    public void init(){
        System.out.println("Initialising memory and registers.....");
        for(int i=0;i<100;i++){
            for(int j=0;j<4;j++){
                M[i][j] = 'ඞ';
            }
        }
        for(int i=0;i<4;i++){
            IR[i] = 'ඞ';
            R[i] = 'ඞ';
        }
        IC = 0;
        C = false;
        SI = 0;
        System.out.println("Memory and registers initialised");
        // System.out.println("Memory:");
        // for(int i=0;i<100;i++){
        //     for(int j=0;j<4;j++){
        //         System.out.print(M[i][j]);
        //     }
        //     System.out.println();
        // }
    }

    public void load(){
        File f = new File("C:\\Users\\karan\\Documents\\college\\SY\\OS\\CP\\input.txt");
        int row = 0;
        try (Scanner sc = new Scanner(f)) {
            while(sc.hasNextLine()){
                int count = 0;
                String s = sc.nextLine();
                outer:
                while(true){
                    for(int j=0;j<4;j++){
                        buffer[j] = s.charAt(count);
                        System.out.println("Buffer: " + buffer[j]);
                        if (buffer[j]=='H') {
                            break;
                        }
                        count++;
                    }
                    System.out.println("We got buffer: " + new String(buffer));
                    if (buffer[0]=='$' && buffer[1]=='A' && buffer[2]=='M' && buffer[3]=='J'){
                       // SI = 1;
                        init();
                        System.out.println(buffer);
                        System.out.println("AMJ, initialised memory and registers");
                        break;
                    }
                    else if (buffer[0]=='$' && buffer[1]=='D' && buffer[2]=='T' && buffer[3]=='A'){
                       // SI = 2;
                        count = 0;
                        s = sc.nextLine();
                        for(int j=0;j<40;j++){
                            buffer[j] = s.charAt(count);
                            System.out.println("Buffer: " + buffer[j]);
                            count++;
                        }
                        System.out.println("DTA, started execution");
                        //start_exe();
                        break;
                    }
                    else if (buffer[0]=='$' && buffer[1]=='E' && buffer[2]=='N' && buffer[3]=='D'){
                        //SI = 3;
                        sc.close();
                        System.out.println("END, ended execution");
                        return;
                    }
                    else{
                        for(int j=0;j<4;j++){
                            System.out.print(buffer[j]);
                            M[row][j] = buffer[j];
                            if (buffer[j]=='H') {
                                break outer;
                                //    break;
                            }
                        }
                        row++;
                        System.out.println();
                    }
                }
            }
        }
        catch(Exception e){
            System.out.println("File not found");
            System.out.println(e);
        }
        System.out.println("\nMemory loaded");
        for(int i=0;i<100;i++){
            for(int j=0;j<4;j++){
                System.out.print(M[i][j]);
            }
            System.out.println();
        }
    }

    public static void main(String[] args) {
        temp job = new temp();
        job.load();
        job.start_exe();
    }
}