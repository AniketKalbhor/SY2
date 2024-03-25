import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
public class buff {
    public static void main(String[] args) {
        try (BufferedReader reader = new BufferedReader(new FileReader("/home/aniket/Desktop/SY2/OS/CP/Phase1/input2.txt"))) {
            // Read the first line
            String line1 = reader.readLine();
            System.out.println("Line 1: " + line1);

            // Mark the current position
            reader.mark(100);

            // Read the second line
            String line2 = reader.readLine();
            System.out.println("Line 2: " + line2);

            // Reset the reader to the previously marked position
            reader.reset();

            // Read the second line again
            String line2Again = reader.readLine();
            System.out.println("Line 2 Again: " + line2Again);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
