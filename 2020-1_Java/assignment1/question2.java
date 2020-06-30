package HEE_JE;
import java.util.Scanner;
public class question2 {

	public static void main(String[] args) {
		int a, b;
		Scanner sc = new Scanner(System.in);
		while(true) {
			a=(int)(Math.random()*10);
			b=(int)(Math.random()*10);
			System.out.printf("Howm much is "+a+" times "+b+"?\n");
			System.out.printf("Enter you answer (-1 to exit):");
			int val=sc.nextInt();
			if(val==-1) {
				System.exit(0);
			}
			
			if(val==a*b) {
				System.out.printf("Very Good!\n");
			}
			else {
				while(true) {
					System.out.printf("No. Please try again.\n");
					System.out.printf("Enter you answer (-1 to exit):");
					val=sc.nextInt();
					if(val==a*b) {System.out.printf("Very Good!\n"); break;}
				}
			}
			
		}

	}

}
