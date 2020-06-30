
public class TwoDimensionalShape extends Shape {
	private static String CLASS_NAME = "2D Shape";
	private double dimension1;
	private double dimension2;



public TwoDimensionalShape(String name, double d1, double d2) {        //constructor
	super(name);
	this.dimension1 = d1;
	this.dimension2 = d2;
	}

public String getClassName() {
	return CLASS_NAME;
	}

public String getName() {
	return super.getName();
	}

public double getDimension1() {
	return dimension1;
}

public double getDimension2() {
	return dimension2;
}

public void setDimension1(double d1) {
	this.dimension1 = d1;
}

public void setDimension2(double d2) {
	this.dimension2 = d2;
}

public double getArea() {
	return 0;
}

}



class Circle extends TwoDimensionalShape{     
	private static String CLASS_NAME="Circle";
	
	public Circle(String name, double r) {
		super(name, r, r);
		
	}
	public String getClassName() {
		return CLASS_NAME;
	}
	public double getRadius() {            /// getRadius from super just one Dimension
		return super.getDimension1();
	}
	public void setRadius(double r) {     ///Set the Radius
		super.setDimension1(r);
		super.setDimension2(r);
	}
	public double getArea() {            // get the circle area
		return Math.PI * super.getDimension1() * super.getDimension1();
	}
	
	public String toString() {                 
		return String.format("%s is a [%s], and is a [%s]", 
			super.getName(), getClassName(), super.getClassName());
	}
	
}

class Rectangle extends TwoDimensionalShape{
	private static String CLASS_NAME="Rectangle";
	public Rectangle(String name, double d1, double d2) {      //constructor
		super(name, d1, d2);
	}
	
	public String getClassName() {
		return CLASS_NAME;              
	}
	public double getWidth() {         //get the rectangle Width
		return super.getDimension1();
	}
	public double getheight() {       // get the rectangle height
		return super.getDimension2();
	}
	public void setWidth_height(double d1, double d2) {  // set the width and height
		super.setDimension1(d1);
		super.setDimension2(d2);

	}
	public double getArea() {                   // get the rectangle area
		return super.getDimension1()*super.getDimension2();    
	}
	public String toString() {
		return String.format("%s is a [%s], and is a [%s]", 
			super.getName(), getClassName(), super.getClassName());
	}
	

}



class Square extends Rectangle{          
	private static String CLASS_NAME="Square";
	public Square(String name, double side) {
		super(name, side, side);
		
	}
	public String getClassName() {
		return CLASS_NAME;
	}
	
	public double getSide() {           // get square side
		return super.getDimension1();
	}
	
	public void setSide(double side) {  // set the side
		super.getheight();
	}
	
	public double getArea() {         // get square area by using Rectangle object
		return super.getheight()* super.getWidth();
	}
	
	
	public String toString() {
		return String.format("%s is a [%s], and is a [%s]", 
			super.getName(), getClassName(), super.getClassName());
	}
	
}

	
	





