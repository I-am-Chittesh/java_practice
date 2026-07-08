import java.util.Scanner;

public class practice1{
    public static void main(String[] args){
         Scanner input = new Scanner(System.in);
        
         System.out.println("Enter the number accordingly to the number:");
         System.out.println("1. Rectangle\n2.Triangle");

         int shapenum = input.nextInt();
         if (shapenum==1){
            System.out.println("Enter rectangle dimensions");
            double a= input.nextDouble();
            double b= input.nextDouble();

            double c= a*b;
            System.out.println("The area of the rectangle:" + c);
         }

         else if (shapenum==2){
            System.out.println("Enter triangle dimensions");
            double a=input.nextDouble();
            double b= input.nextDouble();

            double c=a*b;
            System.out.println("The area of the triangle:" + c);
         }
         else{
            System.out.println("Enter a valid choice");
         }
         input.close();
    }
}
