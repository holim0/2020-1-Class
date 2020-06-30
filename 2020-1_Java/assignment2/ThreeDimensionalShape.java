
public class ThreeDimensionalShape extends Shape{
	private static String CLASS_NAME = "3D Shape";
	private double dimension1;
	private double dimension2;
	private double dimension3;

public ThreeDimensionalShape(String name, double d1, double d2, double d3) {  //constructor
		super(name);                   // from superclass Shape
		this.dimension1 = d1;
		this.dimension2 = d2;
		this.dimension3 = d3;
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
public double getDimension3() {
	return dimension3;
}

public void setDimension1(double d1) {
	this.dimension1 = d1;
}

public void setDimension2(double d2) {
	this.dimension2 = d2;
}
public void setDimension3(double d3) {
	this.dimension3 = d3;
}

public double getVolume() {
	return 0;
}


}


class Cube extends ThreeDimensionalShape{  
	private static String CLASS_NAME="Cube";
	public Cube(String name, double s1) {         // constructor
		super(name, s1, s1, s1);
		
	}
	
	public String getClassName() {
		return CLASS_NAME;
	}
	
	public double getside() {
		return super.getDimension1();
	}
	public void setside(double r1) {     // set the all dimension by r1
		super.setDimension1(r1);
		super.setDimension2(r1);
		super.setDimension3(r1);
	}
	Square squa= new Square("", super.getDimension1()); // set Square object
	
	public double getVolume() {
		return super.getDimension1() * squa.getArea(); // and use Square object
	}
	
	public String toString() {
		return String.format("%s is a [%s], [%s]", 
			super.getName(), getClassName(), super.getClassName());
	}
	
	
}

class RectangularPrism extends ThreeDimensionalShape{
	private static String CLASS_NAME="RectangularPrism";
	public RectangularPrism(String name, double h, double l, double w) {
		super(name, h, l, w);
		
	}
	public String getClassName() {
		return CLASS_NAME;
	}
	
	public double geth() {
		return super.getDimension1();
	}
	public double getl() {
		return super.getDimension2();
	}
	public double getw() {
		return super.getDimension3();
	}
	public void setHLW(double h, double l, double w) {
		super.setDimension1(h);
		super.setDimension2(l);
		super.setDimension3(w);
	}
	
	Rectangle Rec= new Rectangle("", super.getDimension2(), super.getDimension3()); // set Rectangle object
	
	public double getVolume() {    // get volume using Rectangle object
		return super.getDimension1()* Rec.getArea();
	}
	
	
	public String toString() {
		return String.format("%s is a [%s], [%s]", 
			super.getName(), getClassName(), super.getClassName());
	}
		
}


class Cylinder extends ThreeDimensionalShape{
	private static String CLASS_NAME="Cylinder";
	public Cylinder(String name, double r, double h) {
		super(name, r, r, h);
		
	}
	public String getClassName() {
		return CLASS_NAME;
	}
	
	public double getRadius() {
		return super.getDimension1();
	}
	public double getheight() {
		return super.getDimension3();     
	}
	
	public void setRH(double r, double h) {
		super.setDimension1(r);
		super.setDimension2(r);
		super.setDimension3(h);
	}
	
	Circle Cir= new Circle("", super.getDimension1()); // get Circle object
	
	public double getVolume() {        //get the volume using Circle object
		return super.getDimension3() * Cir.getArea();
	}
	
	
	public String toString() {
		return String.format("%s is a [%s], [%s]", 
			super.getName(), getClassName(), super.getClassName());
	}
		
}

class Cone extends ThreeDimensionalShape{
	private static String CLASS_NAME="Cone";
	public Cone(String name, double r, double h) {
		super(name, r, r, h);
		
	}
	public String getClassName() {
		return CLASS_NAME;
	}
	
	public double getRadius() {
		return super.getDimension1();
	}
	public double getheight() {
		return super.getDimension3();
	}
	
	public void setRH(double r, double h) {
		super.setDimension1(r);
		super.setDimension2(r);
		super.setDimension3(h);
	}
	
	Circle Cir= new Circle("", super.getDimension1()); // get Circle object
	
	public double getVolume() {      //get the volume using Circle object
		return (super.getDimension3() * Cir.getArea())/3;
	}
	
	
	public String toString() {
		return String.format("%s is a [%s], [%s]", 
			super.getName(), getClassName(), super.getClassName());
	}
		
}

class Sphere extends ThreeDimensionalShape{
	private static String CLASS_NAME="Sphere";
	public Sphere(String name, double r) {
		super(name, r, r, r);
		
	}
	public String getClassName() {
		return CLASS_NAME;
	}
	
	public double getRadius() {
		return super.getDimension1();
	}
	
	
	public void setRH(double r, double h) {
		super.setDimension1(r);
		super.setDimension2(r);
		super.setDimension3(h);
	}
	
	Circle Cir= new Circle("", super.getDimension1()); // get Circle object
	
	public double getVolume() {       //get the volume by using Circle object
		return ((super.getDimension3() * Cir.getArea())*4)/3;
	}
	
	
	public String toString() {
		return String.format("%s is a [%s], [%s]", 
			super.getName(), getClassName(), super.getClassName());
	}
		
}





