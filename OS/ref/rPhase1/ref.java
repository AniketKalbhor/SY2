package OS.ref.rPhase1;

import java.io.*;
import java.util.*;

public class ref {

    static List<String[]> M = new ArrayList<>();
    static List<String> Buff = new ArrayList<>();
    static List<String> R = new ArrayList<>();
    static String IR;
    static int IC = 0;
    static boolean C = false;
    static int SI = 0;

    public static void initialize() {
        for (int i = 0; i < 100; i++) {
            M.add(new String[]{"ඞ", "ඞ", "ඞ", "ඞ"});
        }
    }

    public static void mos() {
        if (SI == 1) {
            int i = 0;
            int count = 0;
            while (!Buff.get(0).equals("\n")) {
                i += 1;
            }

            for (int k = 0; k < i; k += 4) {
                M.set(Integer.parseInt(IR.substring(2)) + count, Buff.get(0).substring(k, k + 4).split(""));
                count += 1;
            }
            Buff.remove(0);
        } else if (SI == 2) {
            Buff.add(String.join("", M.get(Integer.parseInt(IR.substring(2)))));
            try (FileWriter out = new FileWriter("output.txt", true)) {
                out.write(Buff.get(0));
                out.write("\n");
            } catch (IOException e) {
                e.printStackTrace();
            }
            Buff.remove(0);
        } else if (SI == 3) {
            System.out.println("\n");
        }
    }

    public static void executeUserPgm() {
        IR = String.join("", M.get(IC));

        if (IR.substring(0, 2).equals("GD")) {
            SI = 1;
            mos();
        } else if (IR.substring(0, 2).equals("PD")) {
            SI = 2;
            mos();
        } else if (IR.substring(0, 2).equals("H")) {
            SI = 3;
            mos();
        } else if (IR.substring(0, 2).equals("LR")) {
            R.add(String.join("", M.get(Integer.parseInt(IR.substring(2)))));
        } else if (IR.substring(0, 2).equals("SR")) {
            M.set(Integer.parseInt(IR.substring(2)), R.toArray(new String[0]));
        } else if (IR.substring(0, 2).equals("CR")) {
            if (R.get(0).equals(String.join("", M.get(Integer.parseInt(IR.substring(2)))))) {
                C = true;
            }
        } else if (IR.substring(0, 2).equals("BT")) {
            if (C) {
                IC = Integer.parseInt(IR.substring(2));
            }
        }
        IC++;
    }

    public static void init() {
        System.out.println("This is init function");
    }

    public static void start_exec() {
        executeUserPgm();
    }

    public static void load() {
        String filename = "input.txt";
        try (BufferedReader file = new BufferedReader(new FileReader(filename))) {
            String line;
            while ((line = file.readLine()) != null) {
                if (line.startsWith("$AMJ")) {
                    init();
                } else if (line.startsWith("$DTA")) {
                    while (true) {
                        String next_line = file.readLine();
                        if (next_line.startsWith("$END")) {
                            break;
                        }
                        Buff.add(next_line);
                        executeUserPgm();
                        IC++;
                    }
                    String x;
                    do {
                        executeUserPgm();
                        x = String.valueOf(M.get(IC)[0]);
                        IC++;
                    } while (!x.equals("H"));
                } else {
                    int length = line.length();
                    int index = 0;
                    for (int i = 0; i < length; i += 4) {
                        M.set(index, line.substring(i, i + 4).split(""));
                        index++;
                    }
                }
            }
            for (int i = 0; i < 100; i++) {
                System.out.println("M[" + i + "] = " + String.join("", M.get(i)));
            }
        } catch (IOException e) {
            System.out.println("File not found.");
        }
    }

    public static void main(String[] args) {
        initialize();
        load();
    }
}
