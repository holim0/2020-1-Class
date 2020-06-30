package HEE_JE;

import java.util.Scanner;
import java.text.DecimalFormat;

public class question1 {

	public static void main(String[] args) {
		Scanner input = new Scanner (System.in); 
		DecimalFormat form = new DecimalFormat("#.00");
		double tmoney=0;
		while(true) {
			int hour; double money=2;
			System.out.printf("Enter number of hours (a negative to quit):");
			hour=input.nextInt();
			if(hour<0) {
				System.exit(0);
			}
			if(hour<=3) {
				String val=form.format(money);
				tmoney+=money;
				String val2=form.format(tmoney);
				System.out.printf("Current charge: $"+val+",");
				System.out.printf(" Total receipts: $"+val2);
				System.out.printf("\n");
			
			}else {
				double over=(hour-3)*(0.5)+2;
				if(over>10) {
					over=10;
				}
				String val2=form.format(over);
				tmoney+=over;
				String val3=form.format(tmoney);
				System.out.printf("Current charge: $"+val2+",");
				System.out.printf(" Total receipts: $"+val3);
				System.out.printf("\n");
			}
			
		}

	}

}
