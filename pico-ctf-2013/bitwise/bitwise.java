import java.util.*;

public class Bit {
  public static void main(String[] args) {
    System.out.print("Enter Password: ");
    Scanner s = new Scanner(System.in);
    String user_key = s.next();
    if (user_key.length() != 10) {
      System.out.println("Wrong");
      return;
    }

    char[] verify_arr = {193, 35, 9, 33, 1, 9, 3, 33, 9, 225};

    ArrayList<Character> user_arr = new ArrayList<Character>();
    char[] user_submitted_arr = user_key.toCharArray();

    for (char ch : user_submitted_arr) {
      user_arr.add((char)((((ch << 5) | (ch >> 3)) ^ 111) & 255));
    }

    int i;
    for(i = 0; i < 10; i++) {
      if (!user_arr.get(i).equals((char)verify_arr[i])) {
        System.out.println("Wrong");
        return;
      }
    }
    System.out.println("Success");
  }
}
