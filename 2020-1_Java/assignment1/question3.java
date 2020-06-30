package HEE_JE;
import java.util.Scanner;
import java.util.Random;
public class question3 {

	public static void main(String[] args) {
		int a, b, c;
		Scanner sc = new Scanner(System.in);
		String[] array1 = {"Very good!\n", "Excellent!\n", "Nice work!\n","Keep up the good work!\n"};
		String[] array2 = {"No. Please try again.\n", "Wrong. Try once more.\n","Don't give up!\n",
				"No. Keep trying.\n"};
		
		while(true) {
			a=(int)(Math.random()*10);
			b=(int)(Math.random()*10);
			c=(int)(Math.random()*10)%4;
			System.out.printf("Howm much is "+a+" times "+b+"?\n");
			System.out.printf("Enter you answer (-1 to exit):");
			int val=sc.nextInt();
			if(val==-1) {
				System.exit(0);
			}
			
			if(val==a*b) {
				System.out.printf(array1[c]);
			}
			else {
				while(true) {
					System.out.printf(array2[c]);
					System.out.printf("Enter you answer (-1 to exit):");
					val=sc.nextInt();
					c=(int)(Math.random()*10)%4;
					if(val==a*b) {System.out.printf(array1[c]); break;}
				}
			}
			
		}

	}

}
