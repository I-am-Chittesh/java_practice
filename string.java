import java.util.Scanner;

public class string{
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter a string:");
        StringBuilder str = new StringBuilder();
        String s = sc.nextLine();
        String st[] = s.split(" ");
        for(int i=st.length-1;i>=0;i--){
            str.append(st[i]+" ");
        }
        System.out.println("The reve string is:"+str.toString().trim());
        sc.close();
    }
}
