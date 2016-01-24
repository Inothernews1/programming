import java.util.Scanner;

public class DailyProgrammer001i {
	static Scanner input = new Scanner(System.in);

  static int curState = 0;
  static int curMonth = 0;
  static int curDay = 1;
  static String [] month = {"January", "Februrary", "March", "April",
    "May", "June", "July", "August",
    "September", "October", "November", "December"};
  static String command;
  static String dataEdit;                            21, 22, 23, 24};
  static String [] [] [] data = new String [12] [31] [24];

	public static void main(String[] args) {
    while (true) {
      draw();
      input();
    }
	}

  public static void draw() {
    if (curState == 0) {
      System.out.print("\nWelcome to the Sussman cmd planner!" +
        "\nTo change the time period, type switch." +
        "\nThen type what you want to switch it to. (ex. swtich 12 24)"+
        "\nTo change an hour's activity, type edit");
        curState = 1;
    }
    if (curState == 1) {
      System.out.print("\n\n\nThe date is: " + month[curMonth] + " " + Integer.toString(curDay) + ".");
      for (int h = 0; h < 24; h++) {
        System.out.print("\n" + Integer.toString(h) + "00: " + data [curMonth] [curDay] [h]);
      }
    }
  }

  public static void input() {
    System.out.print("\n:");
    command = input.nextLine();
    if (command.equals("edit")) {
      System.out.print("\nWhich hour do you want to edit?");
      System.out.print("\n:");
      command = input.nextLine();
      System.out.print("\nChange to what?");
      System.out.print("\n:");
      dataEdit = input.nextLine();
      data [curMonth] [curDay] [Integer.parseInt(command)] = dataEdit;
    }
  }
}
