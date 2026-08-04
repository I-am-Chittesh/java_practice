import java.util.Scanner;

public class array{
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        int n,k;
        System.out.println("Enter the no. of rows:");
        n = sc.nextInt();
        int jag[][] = new int[n][];
        for(int i=0;i<n;i++){
            System.out.print("Enter the no. of colums on row "+(i+1)+": ");
            k = sc.nextInt();
            jag[i] = new int[k];
        } 
        for(int i=0;i<n;i++){
            int max = 0;
            for(int j=0;j<jag[i].length;j++){
                System.out.print("Enter the element at "+(i+1)+" "+(j+1)+": ");
                jag[i][j] = sc.nextInt();
                if(jag[i][j]>max){
                    max = jag[i][j];
                }
            }
            System.out.println("The max element in row "+(i+1)+" is: "+max);
        }
        sc.close();
    }
}