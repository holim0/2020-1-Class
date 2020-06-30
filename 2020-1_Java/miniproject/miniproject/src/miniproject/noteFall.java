package miniproject;

import java.awt.Graphics2D;
import java.awt.Image;

import javax.swing.ImageIcon;

public class noteFall extends Thread {
	
	public static int MissCnt=0;

	private Image gameblockImg=new ImageIcon(Main.class.getResource("../images/gameblock.png")).getImage();
	
	private int x; 
	private int y=(300-1000/Main.SLEEP_TIME*Main.NOTE_SPEED)*Main.REACH_TIME;
	private String noteType;
	private boolean proceeded=true;
	
	public static int GameScore=0;
	
	public String getNoteType() {
			return noteType;
	}
	
	public boolean isProceeded() {
		return proceeded;
	}
	
	public void close() {
		proceeded=false;
	}
	
	public noteFall(String noteType) {
		if(noteType.equals("S")) {
			x=216;
		}else if(noteType.equals("D")) {
			x=320;
		}else if(noteType.equals("F")) {
			x=434;
		}else if(noteType.equals("Space")) {
			x=543;
		}else if(noteType.equals("J")) {
			x=754;
		}else if(noteType.equals("K")) {
			x=868;
		}else if(noteType.equals("L")) {
			x=977;
		}
		
		this.noteType=noteType;
		
	}
	
	
	public void screenDraw(Graphics2D g) {
		if(!noteType.equals("Space")) {
			
			g.drawImage(gameblockImg, x, y, null);
			
			
		}else{
			g.drawImage(gameblockImg, x, y, null);
			g.drawImage(gameblockImg, x+97, y, null);
		}
	}
	
	
	
	public void drop() {
		y += Main.NOTE_SPEED;
		if(y>630) {
			//System.out.println("Miss");
			MissCnt++;
			
			if(MissCnt>=20) {
				new GameOVER();
				MissCnt=-123456;
				
			}
			
			
			close();
		}
		 
	}
	
	
	
	@Override
	
	public void run() {
		
		try {
			while(true) {
				drop();
				if(proceeded) {
					Thread.sleep(Main.SLEEP_TIME);
				}else {
					interrupt();
					break;
				}
				
			}
		}catch(Exception e) {
			System.err.println(e.getMessage());
		}
		
	}
	
	
	public String judge() {
		if(y>=570) {
			//System.out.println("Slow!");
			close();
			return "Slow";
		}else if(y>=532) {
			//System.out.println("Perfect!");
			GameScore+=10;
			close();
			return "Perfect";
		}else if(y>=535) {
			//System.out.println("Great!");
			GameScore+=5;
			close();
			return "Great";
		}else if(y>=547) {
			//System.out.println("GOOD");
			GameScore+=3;
			close();
			return "Good";
		}else if(y>=500) {
			//System.out.println("Early!");
			GameScore+=1;
			close();
			return "Early";
		}
		
		return "None";
		
	}	
	
	
	
	public int getY() {
		return y;
	}
	
}












