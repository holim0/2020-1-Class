
public class ShapeTester {

	public static void main(String[] args) {
		Circle cir1 = new Circle("Cir one", 2.0);
		
		System.out.println("1. "+ cir1);
		System.out.printf("%s's area is %.2f, radius is %.2f\n", 
				cir1.getName(), cir1.getArea(), cir1.getRadius());
		
		Rectangle Rec1= new Rectangle("Rec one", 3.0, 4.0);
		
		System.out.println("2. "+ Rec1);
		System.out.printf("%s's area is %.2f, width is %.2f, height is %.2f\n",
				Rec1.getName(), Rec1.getArea(), Rec1.getWidth(), Rec1.getheight());
		
		Square Square1= new Square("Square one", 5.0);
		System.out.println("3. "+ Square1);
		System.out.printf("%s's area is %.2f, side is %.2f\n",
				Square1.getName(), Square1.getArea(), Square1.getSide());
		
		Cube cube1=new Cube("Cube one", 6.0);
		System.out.println("4. "+ cube1);
		System.out.printf("%s's volume is %.2f, side is %.2f\n",
				cube1.getName(), cube1.getVolume(), cube1.getside());
		
		RectangularPrism Rectang1= new RectangularPrism("RectanglePrism one", 7.0, 8.0, 9.0);
		System.out.println("5. "+ Rectang1);
		System.out.printf("%s's volume is %.2f, height is %.2f, length is %.2f, width is %.2f\n",
				Rectang1.getClassName(), Rectang1.getVolume(),Rectang1.geth(),Rectang1.getl(),Rectang1.getw());
		
		Cylinder cylin1 = new Cylinder("Cylinder one", 10.0, 11.0);
		System.out.println("6. "+ cylin1);
		System.out.printf("%s's volume is %.2f, radius is %.2f, height is %.2f\n", 
				cylin1.getClassName(), cylin1.getVolume(), cylin1.getRadius(), cylin1.getheight());
		
		
		Cone cone1= new Cone("Cone one", 12.0, 13.0);
		System.out.println("7. "+ cone1);
		System.out.printf("%s's volume is %.2f, radius is %.2f, height is %.2f\n",
				cone1.getClassName(), cone1.getVolume(), cone1.getRadius(), cone1.getheight());
		
		Sphere sphere1= new Sphere("Sphere one", 14.0);
		System.out.println("8. "+sphere1);
		System.out.printf("%s's volume is %.2f, radius is %.2f\n", 
				sphere1.getClassName(), sphere1.getVolume(), sphere1.getRadius());
		
	}

}
