import java.util.ArrayList;
import java.util.Scanner;

public class Main{
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        ArrayList<String> loadout = new ArrayList<>();

        loadout.add("repulsors");
        loadout.add("unibeam");
        loadout.add("missiles");

        System.out.println("The current loadout is: "+ loadout);

        loadout.add(1, "lasers");

        System.out.println("The updated loadout is: "+ loadout);

        String primaryindex = loadout.get(0);

        System.out.println("The primary weapon is: "+ primaryindex);

        loadout.set(2, "micromissles");

        System.out.println("The updated loadout is: "+ loadout);

        loadout.remove(3);
        
        System.out.println("The updated loadout is: "+ loadout);

        int length = loadout.size();

        System.out.println("The loadout has "+ length + " weapons.");
        
        sc.close();
    }
}