
public class Shape {                            //superclass of 2D and 3D
	static final String CLASS_NAME = "Shape";
	private String name;


public Shape(String name) {   // constructor
	this.name=name;
}	
	
public String getClassName() {
	return CLASS_NAME;
}

public String getName() {
	return name;
}


}
