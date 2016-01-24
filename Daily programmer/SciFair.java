import java.util.Random;
import java.io.PrintWriter;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class SciFair {
  static int[] diceRolls = new int[1000];
  static Random random = new Random();
  static double avg = 0;

  public static void main(String[] args) {
    PrintWriter diceRollsLog = null;
    try {
      diceRollsLog = new PrintWriter("logBook10.txt");
    } catch (FileNotFoundException e) {
      e.printStackTrace();
    }
    for (int i = 0; i < 1000; i++) {
      diceRolls[i] = random.nextInt(10) + 1;
      System.out.println(diceRolls[i]);
      diceRollsLog.println(diceRolls[i]);
      avg += diceRolls[i];
    }
    avg = avg/1000;
    System.out.println("avg: " + avg);
    diceRollsLog.println("avg: " + avg);
    diceRollsLog.close();
	}
}
