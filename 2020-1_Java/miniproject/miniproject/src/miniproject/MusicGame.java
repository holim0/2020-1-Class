package miniproject;


import static miniproject.noteFall.GameScore;
import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics2D;
import java.awt.Image;
import java.awt.RenderingHints;
import java.util.ArrayList;

import javax.swing.ImageIcon;

public class MusicGame extends Thread {
	
	
	
	private Image gameBarImg=new ImageIcon(Main.class.getResource("../images/gameBar.png")).getImage();
    private Image judgeBarImg=new ImageIcon(Main.class.getResource("../images/jdgbar.png")).getImage();
    private Image divideBarImg=new ImageIcon(Main.class.getResource("../images/divide.png")).getImage();
    
    
    
    private Image musicRoadSImg=new ImageIcon(Main.class.getResource("../images/musicRoad.png")).getImage();
    private Image musicRoadDImg=new ImageIcon(Main.class.getResource("../images/musicRoad.png")).getImage();
    private Image musicRoadFImg=new ImageIcon(Main.class.getResource("../images/musicRoad.png")).getImage();
    private Image musicRoadSpaceImg=new ImageIcon(Main.class.getResource("../images/spacebarNormal.png")).getImage();
    private Image musicRoadJImg=new ImageIcon(Main.class.getResource("../images/musicRoad.png")).getImage();
    private Image musicRoadKImg=new ImageIcon(Main.class.getResource("../images/musicRoad.png")).getImage();
    private Image musicRoadLImg=new ImageIcon(Main.class.getResource("../images/musicRoad.png")).getImage();
    
    private Image RedFlareimg;
    
    private Image Perfectimg;
    
    private String MusicTitle;
    private String Diff;
    private String title;
    private Music gameMusic;
    
    
    
    
    ArrayList<noteFall> noteList=new ArrayList<noteFall>();
    
    
    
    
    
    
    public MusicGame( String MusicTitle, String Diff, String title) {
    	this.MusicTitle=MusicTitle;
    	this.Diff=Diff;
    	this.title=title;
    	gameMusic=new Music(this.title, false);
    	
    	
    	
    }
    
    

	public void screenDraw(Graphics2D g) {
	
	 g.drawImage(divideBarImg, 209, 29, null);
   	 g.drawImage(musicRoadSImg, 210, 29, null);
   	 g.drawImage(divideBarImg, 315, 29, null);
   	 g.drawImage(musicRoadDImg, 320, 29, null);
   	 g.drawImage(divideBarImg, 425, 29, null);
   	 g.drawImage(musicRoadFImg, 430, 29, null);
   	 g.drawImage(divideBarImg, 535, 29, null);
   	 g.drawImage(musicRoadSpaceImg, 540, 29, null);
   	 g.drawImage(divideBarImg, 749, 29, null);
   	 g.drawImage(musicRoadJImg, 754, 29, null);
   	 g.drawImage(divideBarImg, 859, 29, null);
   	 g.drawImage(musicRoadKImg, 864, 29, null);
   	 g.drawImage(divideBarImg, 969, 29, null);
   	 g.drawImage(musicRoadLImg, 974, 29, null);
   	 g.drawImage(divideBarImg, 1079, 29, null);
   	
   	 
   	 
   	 
   	 g.drawImage(gameBarImg, 0, 630, null);
   	 g.drawImage(judgeBarImg, 0, 530, null);
   	 
   	 for(int i=0; i<noteList.size(); i++) {
  		 
  		 noteFall note=noteList.get(i);
  		 if(note.getY()>630) {
  			 Perfectimg=new ImageIcon(Main.class.getResource("../images/Miss.png")).getImage();
  		 }
  		 if(!note.isProceeded()) {
  			 noteList.remove(i);
  			 i--;
  		 }else {
  			 
  			 note.screenDraw(g);
  		 }
  		 
  			 
  		 
  		 
  	 }
   	 
   	 g.setRenderingHint(RenderingHints.KEY_TEXT_ANTIALIASING, RenderingHints.VALUE_TEXT_ANTIALIAS_ON);
   	 g.setColor(Color.white);
   	 g.setFont(new Font("Arial", Font.BOLD, 30));
   	 g.drawString(MusicTitle, 20, 702);
   	 g.drawString(Diff, 1190, 702);
   	 g.setFont(new Font("Arial", Font.PLAIN, 30));
   	 g.drawString("S", 255, 570);
   	 g.drawString("D", 364, 570);
   	 g.drawString("F", 478, 570);
   	 g.drawString("SPACE BAR", 560, 570);
   	 g.drawString("J", 800, 570);
   	 g.drawString("K", 905, 570);
   	 g.drawString("L", 1023, 570);
   	 g.setColor(Color.LIGHT_GRAY);
   	        	
   	 g.setFont(new Font("Elephant", Font.BOLD, 25));
   	 g.drawString("SCORE:"+ GameScore, 570, 702);
   	 
   	 
   	 g.drawImage(RedFlareimg, 370, 320, null);
   	 g.drawImage(Perfectimg, 543, 330, null);
   	 
   	 
	}
	
	public void pressS() {
		judge("S");
		musicRoadSImg=new ImageIcon(Main.class.getResource("../images/keyPressedBar.png")).getImage();
		new Music("bit.mp3", false).start();
		
	}
	
	public void releaseS() {
		
		musicRoadSImg=new ImageIcon(Main.class.getResource("../images/musicRoad.png")).getImage();
		
	}
	
	public void pressD() {
		judge("D");
		musicRoadDImg=new ImageIcon(Main.class.getResource("../images/keyPressedBar.png")).getImage();
		new Music("bit.mp3", false).start();
	}
	
	public void releaseD() {
		
		musicRoadDImg=new ImageIcon(Main.class.getResource("../images/musicRoad.png")).getImage();
		
	}
	
	
	public void pressF() {
		judge("F");
		
		musicRoadFImg=new ImageIcon(Main.class.getResource("../images/keyPressedBar.png")).getImage();
		new Music("bit.mp3", false).start();
	}
	
	public void releaseF() {
		
		musicRoadFImg=new ImageIcon(Main.class.getResource("../images/musicRoad.png")).getImage();
		
	}
	
	
	public void pressSpace() {
		judge("Space");
		
		musicRoadSpaceImg=new ImageIcon(Main.class.getResource("../images/SpaceBar.png")).getImage();
		new Music("bit.mp3", false).start();
	}
	
	public void releaseSpace() {
		
		musicRoadSpaceImg=new ImageIcon(Main.class.getResource("../images/spacebarNormal.png")).getImage();
		
	}
	public void pressJ() {
		judge("J");
		
		musicRoadJImg=new ImageIcon(Main.class.getResource("../images/keyPressedBar.png")).getImage();
		new Music("bit.mp3", false).start();
	}
	
	public void releaseJ() {
		
		musicRoadJImg=new ImageIcon(Main.class.getResource("../images/musicRoad.png")).getImage();
		
	}
	
	public void pressK() {
		judge("K");
		
		musicRoadKImg=new ImageIcon(Main.class.getResource("../images/keyPressedBar.png")).getImage();
		new Music("bit.mp3", false).start();
	}
	
	public void releaseK() {
		
		musicRoadKImg=new ImageIcon(Main.class.getResource("../images/musicRoad.png")).getImage();
		
	}
	
	
	public void pressL() {
		judge("L");
		
		musicRoadLImg=new ImageIcon(Main.class.getResource("../images/keyPressedBar.png")).getImage();
		new Music("bit.mp3", false).start();
	}
	
	public void releaseL() {
		
		musicRoadLImg=new ImageIcon(Main.class.getResource("../images/musicRoad.png")).getImage();
		
	}
	
	

	
	
	@Override
		
	public void run() {
			dropNote(this.MusicTitle);
	}
	
	public void close() {
		gameMusic.close();
		this.interrupt();
	}
	
	public void dropNote(String MusicTitle) {
		Beat[] beats=null;
		
		if(MusicTitle.equals("Sappheiros - Awake") && Diff.equals("Easy")) {
			
			int startTime=3000-Main.REACH_TIME*1000;
			int gap=125;
			beats= new Beat[] {
					
					new Beat(startTime+gap*2, "S"),
					new Beat(startTime+gap*5, "K"),
					new Beat(startTime+gap*6, "L"),
					new Beat(startTime+gap*7, "Space"),
					new Beat(startTime+gap*9, "S"),
					new Beat(startTime+gap*13, "S"),
					new Beat(startTime+gap*15, "D"),
					new Beat(startTime+gap*17, "S"),
					new Beat(startTime+gap*20, "S"),
					new Beat(startTime+gap*23, "D"),
					new Beat(startTime+gap*27, "J"),
					new Beat(startTime+gap*30, "S"),
					new Beat(startTime+gap*31, "F"),
					new Beat(startTime+gap*32, "Space"),
					new Beat(startTime+gap*40, "K"),
					new Beat(startTime+gap*60, "L"),
					new Beat(startTime+gap*66, "Space"),
					new Beat(startTime+gap*70, "S"),
					new Beat(startTime+gap*40, "J"),
					new Beat(startTime+gap*45, "S"),
					new Beat(startTime+gap*47, "F"),
					new Beat(startTime+gap*49, "Space"),
					new Beat(startTime+gap*54, "K"),
					new Beat(startTime+gap*60, "L"),
					new Beat(startTime+gap*66, "Space"),
					new Beat(startTime+gap*70, "S"),
					new Beat(startTime+gap*80, "S"),
					new Beat(startTime+gap*82, "S"),
					new Beat(startTime+gap*83, "D"),
					new Beat(startTime+gap*86, "J"),
					new Beat(startTime+gap*90, "S"),
					new Beat(startTime+gap*91, "F"),
					new Beat(startTime+gap*92, "Space"),
					new Beat(startTime+gap*94, "Space"),
					new Beat(startTime+gap*100, "K"),
					new Beat(startTime+gap*103, "L"),
					new Beat(startTime+gap*113, "Space"),
					new Beat(startTime+gap*115, "S"),
					new Beat(startTime+gap*120, "S"),
					new Beat(startTime+gap*130, "S"),
					new Beat(startTime+gap*134, "D"),
					new Beat(startTime+gap*137, "J"),
					new Beat(startTime+gap*140, "S"),
					new Beat(startTime+gap*145, "F"),
					new Beat(startTime+gap*150, "Space"),
					new Beat(startTime+gap*152, "D"),
					new Beat(startTime+gap*154, "J"),
					new Beat(startTime+gap*157, "S"),
					new Beat(startTime+gap*160, "F"),
					new Beat(startTime+gap*162, "Space"),
					new Beat(startTime+gap*164, "S"),
					new Beat(startTime+gap*166, "K"),
					new Beat(startTime+gap*168, "L"),
					new Beat(startTime+gap*170, "Space"),
					new Beat(startTime+gap*172, "S"),
					new Beat(startTime+gap*174, "S"),
					new Beat(startTime+gap*176, "D"),
					new Beat(startTime+gap*177, "S"),
					new Beat(startTime+gap*179, "S"),
					new Beat(startTime+gap*181, "D"),
					new Beat(startTime+gap*183, "J"),
					new Beat(startTime+gap*184, "S"),
					new Beat(startTime+gap*186, "F"),
					new Beat(startTime+gap*188, "Space"),
					new Beat(startTime+gap*190, "K"),
					new Beat(startTime+gap*192, "L"),
					new Beat(startTime+gap*194, "Space"),
					new Beat(startTime+gap*196, "S"),
					new Beat(startTime+gap*198, "J"),
					new Beat(startTime+gap*200, "S"),
					new Beat(startTime+gap*202, "F"),
					new Beat(startTime+gap*203, "Space"),
					new Beat(startTime+gap*204, "K"),
					new Beat(startTime+gap*206, "L"),
					new Beat(startTime+gap*208, "Space"),
					new Beat(startTime+gap*210, "S"),
					new Beat(startTime+gap*212, "S"),
					new Beat(startTime+gap*214, "S"),
					new Beat(startTime+gap*216, "D"),
					new Beat(startTime+gap*219, "J"),
					new Beat(startTime+gap*222, "S"),
					new Beat(startTime+gap*223, "F"),
					new Beat(startTime+gap*225, "Space"),
					new Beat(startTime+gap*227, "Space"),
					new Beat(startTime+gap*230, "K"),
					new Beat(startTime+gap*232, "L"),
					new Beat(startTime+gap*234, "Space"),
					new Beat(startTime+gap*236, "S"),
					new Beat(startTime+gap*238, "S"),
					new Beat(startTime+gap*240, "S"),
					new Beat(startTime+gap*242, "D"),
					new Beat(startTime+gap*244, "J"),
					new Beat(startTime+gap*246, "S"),
					new Beat(startTime+gap*250, "F"),
					new Beat(startTime+gap*251, "Space"),
					new Beat(startTime+gap*253, "D"),
					new Beat(startTime+gap*255, "J"),
					new Beat(startTime+gap*257, "S"),
					new Beat(startTime+gap*260, "F"),
					new Beat(startTime+gap*262, "Space")
					
					
			};
			
		}else if(MusicTitle.equals("Sunshine - urpleactus")&& Diff.equals("Easy")) {
			
			int startTime=3000-Main.REACH_TIME*1000;
			int gap=125;
			beats= new Beat[] {
					
					new Beat(startTime+gap*2, "S"),
					new Beat(startTime+gap*5, "K"),
					new Beat(startTime+gap*6, "L"),
					new Beat(startTime+gap*7, "Space"),
					new Beat(startTime+gap*9, "S"),
					new Beat(startTime+gap*13, "S"),
					new Beat(startTime+gap*15, "D"),
					new Beat(startTime+gap*17, "S"),
					new Beat(startTime+gap*20, "S"),
					new Beat(startTime+gap*23, "D"),
					new Beat(startTime+gap*27, "J"),
					new Beat(startTime+gap*30, "S"),
					new Beat(startTime+gap*31, "F"),
					new Beat(startTime+gap*32, "Space"),
					new Beat(startTime+gap*40, "K"),
					new Beat(startTime+gap*60, "L"),
					new Beat(startTime+gap*66, "Space"),
					new Beat(startTime+gap*70, "S"),
					new Beat(startTime+gap*40, "J"),
					new Beat(startTime+gap*45, "S"),
					new Beat(startTime+gap*47, "F"),
					new Beat(startTime+gap*49, "Space"),
					new Beat(startTime+gap*54, "K"),
					new Beat(startTime+gap*60, "L"),
					new Beat(startTime+gap*66, "Space"),
					new Beat(startTime+gap*70, "S"),
					new Beat(startTime+gap*80, "S"),
					new Beat(startTime+gap*82, "S"),
					new Beat(startTime+gap*83, "D"),
					new Beat(startTime+gap*86, "J"),
					new Beat(startTime+gap*90, "S"),
					new Beat(startTime+gap*91, "F"),
					new Beat(startTime+gap*92, "Space"),
					new Beat(startTime+gap*100, "K"),
					new Beat(startTime+gap*102, "D"),
					new Beat(startTime+gap*110, "S"),
					new Beat(startTime+gap*130, "F"),
					new Beat(startTime+gap*133, "Space"),
					new Beat(startTime+gap*134, "Space"),
					new Beat(startTime+gap*134, "K"),
					new Beat(startTime+gap*136, "K"),
					new Beat(startTime+gap*140, "S"),
					new Beat(startTime+gap*142, "D"),
					new Beat(startTime+gap*144, "S"),
					new Beat(startTime+gap*146, "D"),
					new Beat(startTime+gap*148, "S"),
					new Beat(startTime+gap*150, "D"),
					new Beat(startTime+gap*152, "S"),
					new Beat(startTime+gap*154, "S"),
					new Beat(startTime+gap*156, "K"),
					new Beat(startTime+gap*158, "L"),
					new Beat(startTime+gap*160, "Space"),
					new Beat(startTime+gap*164, "S"),
					new Beat(startTime+gap*165, "K"),
					new Beat(startTime+gap*170, "D"),
					new Beat(startTime+gap*171, "S"),
					new Beat(startTime+gap*173, "S"),
					new Beat(startTime+gap*179, "S"),
					new Beat(startTime+gap*181, "D"),
					new Beat(startTime+gap*183, "J"),
					new Beat(startTime+gap*184, "S"),
					new Beat(startTime+gap*186, "F"),
					new Beat(startTime+gap*188, "Space"),
					new Beat(startTime+gap*190, "K"),
					new Beat(startTime+gap*192, "L"),
					new Beat(startTime+gap*194, "Space"),
					new Beat(startTime+gap*196, "S"),
					new Beat(startTime+gap*198, "J"),
					new Beat(startTime+gap*200, "S"),
					new Beat(startTime+gap*202, "F"),
					new Beat(startTime+gap*203, "Space"),
					new Beat(startTime+gap*204, "K"),
					new Beat(startTime+gap*206, "L"),
					new Beat(startTime+gap*208, "Space"),
					new Beat(startTime+gap*210, "S"),
					new Beat(startTime+gap*212, "S"),
					new Beat(startTime+gap*214, "S"),
					new Beat(startTime+gap*216, "D"),
					new Beat(startTime+gap*219, "J"),
					new Beat(startTime+gap*222, "S"),
					new Beat(startTime+gap*223, "F"),
					new Beat(startTime+gap*225, "Space"),
					new Beat(startTime+gap*227, "Space"),
					new Beat(startTime+gap*230, "K"),
					new Beat(startTime+gap*232, "L"),
					new Beat(startTime+gap*234, "Space"),
					new Beat(startTime+gap*236, "S"),
					new Beat(startTime+gap*238, "S"),
					new Beat(startTime+gap*240, "S"),
					new Beat(startTime+gap*242, "D"),
					new Beat(startTime+gap*244, "J"),
					new Beat(startTime+gap*246, "S"),
					new Beat(startTime+gap*250, "F"),
					new Beat(startTime+gap*251, "Space"),
					new Beat(startTime+gap*253, "D"),
					new Beat(startTime+gap*255, "J"),
					new Beat(startTime+gap*257, "S"),
					new Beat(startTime+gap*260, "F"),
					new Beat(startTime+gap*262, "Space")
					
					
			};
			
			
			
		}else if(MusicTitle.equals("Eneko Artola - Becoming True")&& Diff.equals("Easy")) {
			
			
			
			int startTime=3000-Main.REACH_TIME*1000;
			int gap=125;
			beats= new Beat[] {
					
					new Beat(startTime+gap*2, "S"),
					new Beat(startTime+gap*5, "K"),
					new Beat(startTime+gap*6, "L"),
					new Beat(startTime+gap*7, "Space"),
					new Beat(startTime+gap*9, "S"),
					new Beat(startTime+gap*13, "S"),
					new Beat(startTime+gap*15, "D"),
					new Beat(startTime+gap*17, "S"),
					new Beat(startTime+gap*20, "S"),
					new Beat(startTime+gap*23, "D"),
					new Beat(startTime+gap*27, "J"),
					new Beat(startTime+gap*30, "S"),
					new Beat(startTime+gap*31, "F"),
					new Beat(startTime+gap*32, "Space"),
					new Beat(startTime+gap*40, "K"),
					new Beat(startTime+gap*60, "S"),
					new Beat(startTime+gap*66, "Space"),
					new Beat(startTime+gap*70, "S"),
					new Beat(startTime+gap*74, "J"),
					new Beat(startTime+gap*80, "S"),
					new Beat(startTime+gap*85, "F"),
					new Beat(startTime+gap*87, "Space"),
					new Beat(startTime+gap*90, "K"),
					new Beat(startTime+gap*92, "L"),
					new Beat(startTime+gap*94, "Space"),
					new Beat(startTime+gap*99, "S"),
					new Beat(startTime+gap*105, "S"),
					new Beat(startTime+gap*108, "S"),
					new Beat(startTime+gap*111, "D"),
					new Beat(startTime+gap*116, "J"),
					new Beat(startTime+gap*117, "S"),
					new Beat(startTime+gap*120, "F"),
					new Beat(startTime+gap*130, "F"),
					new Beat(startTime+gap*133, "Space"),
					new Beat(startTime+gap*134, "Space"),
					new Beat(startTime+gap*134, "K"),
					new Beat(startTime+gap*136, "K"),
					new Beat(startTime+gap*140, "S"),
					new Beat(startTime+gap*142, "D"),
					new Beat(startTime+gap*144, "S"),
					new Beat(startTime+gap*146, "D"),
					new Beat(startTime+gap*148, "S"),
					new Beat(startTime+gap*150, "D"),
					new Beat(startTime+gap*152, "S"),
					new Beat(startTime+gap*154, "S"),
					new Beat(startTime+gap*156, "K"),
					new Beat(startTime+gap*158, "L"),
					new Beat(startTime+gap*160, "Space"),
					new Beat(startTime+gap*164, "S"),
					new Beat(startTime+gap*165, "K"),
					new Beat(startTime+gap*170, "D"),
					new Beat(startTime+gap*171, "S"),
					
					
			};
			
			
			
			
		}else if(MusicTitle.equals("Sappheiros - Awake") && Diff.equals("Hard")) {
			int startTime=3000-Main.REACH_TIME*1000;
			int gap=125;
			beats= new Beat[] {
					
					new Beat(startTime+gap*2, "S"),
					new Beat(startTime+gap*5, "K"),
					new Beat(startTime+gap*6, "L"),
					new Beat(startTime+gap*7, "Space"),
					new Beat(startTime+gap*9, "S"),
					new Beat(startTime+gap*13, "S"),
					new Beat(startTime+gap*15, "D"),
					new Beat(startTime+gap*17, "S"),
					new Beat(startTime+gap*20, "S"),
					new Beat(startTime+gap*23, "D"),
					new Beat(startTime+gap*27, "J"),
					new Beat(startTime+gap*30, "S"),
					new Beat(startTime+gap*31, "F"),
					new Beat(startTime+gap*32, "Space"),
					new Beat(startTime+gap*40, "K"),
					new Beat(startTime+gap*60, "L"),
					new Beat(startTime+gap*66, "Space"),
					new Beat(startTime+gap*70, "S"),
					new Beat(startTime+gap*40, "J"),
					new Beat(startTime+gap*45, "S"),
					new Beat(startTime+gap*47, "F"),
					new Beat(startTime+gap*49, "Space"),
					new Beat(startTime+gap*54, "K"),
					new Beat(startTime+gap*60, "L"),
					new Beat(startTime+gap*66, "Space"),
					new Beat(startTime+gap*70, "S"),
					new Beat(startTime+gap*80, "S"),
					new Beat(startTime+gap*82, "S"),
					new Beat(startTime+gap*83, "D"),
					new Beat(startTime+gap*86, "J"),
					new Beat(startTime+gap*90, "S"),
					new Beat(startTime+gap*91, "F"),
					new Beat(startTime+gap*92, "Space"),
					new Beat(startTime+gap*100, "K"),
					new Beat(startTime+gap*102, "D"),
					new Beat(startTime+gap*110, "S"),
					new Beat(startTime+gap*130, "F"),
					new Beat(startTime+gap*133, "Space"),
					new Beat(startTime+gap*134, "Space"),
					new Beat(startTime+gap*134, "K"),
					new Beat(startTime+gap*136, "K"),
					new Beat(startTime+gap*140, "S"),
					new Beat(startTime+gap*142, "D"),
					new Beat(startTime+gap*144, "S"),
					new Beat(startTime+gap*146, "D"),
					new Beat(startTime+gap*148, "S"),
					new Beat(startTime+gap*150, "D"),
					new Beat(startTime+gap*152, "S"),
					new Beat(startTime+gap*154, "S"),
					new Beat(startTime+gap*156, "K"),
					new Beat(startTime+gap*158, "L"),
					new Beat(startTime+gap*160, "Space"),
					new Beat(startTime+gap*164, "S"),
					new Beat(startTime+gap*165, "K"),
					new Beat(startTime+gap*170, "D"),
					new Beat(startTime+gap*171, "S"),
					new Beat(startTime+gap*173, "S"),
					new Beat(startTime+gap*179, "S"),
					new Beat(startTime+gap*181, "D"),
					new Beat(startTime+gap*183, "J"),
					new Beat(startTime+gap*184, "S"),
					new Beat(startTime+gap*186, "F"),
					new Beat(startTime+gap*188, "Space"),
					new Beat(startTime+gap*190, "K"),
					new Beat(startTime+gap*192, "L"),
					new Beat(startTime+gap*194, "Space"),
					new Beat(startTime+gap*196, "S"),
					new Beat(startTime+gap*198, "J"),
					new Beat(startTime+gap*200, "S"),
					new Beat(startTime+gap*202, "F"),
					new Beat(startTime+gap*203, "Space"),
					new Beat(startTime+gap*204, "K"),
					new Beat(startTime+gap*206, "L"),
					new Beat(startTime+gap*208, "Space"),
					new Beat(startTime+gap*210, "S"),
					new Beat(startTime+gap*212, "S"),
					new Beat(startTime+gap*214, "S"),
					new Beat(startTime+gap*216, "D"),
					new Beat(startTime+gap*219, "J"),
					new Beat(startTime+gap*222, "S"),
					new Beat(startTime+gap*223, "F"),
					new Beat(startTime+gap*225, "Space"),
					new Beat(startTime+gap*227, "Space"),
					new Beat(startTime+gap*230, "K"),
					new Beat(startTime+gap*232, "L"),
					new Beat(startTime+gap*234, "Space"),
					new Beat(startTime+gap*236, "S"),
					new Beat(startTime+gap*238, "S"),
					new Beat(startTime+gap*240, "S"),
					new Beat(startTime+gap*242, "D"),
					new Beat(startTime+gap*244, "J"),
					new Beat(startTime+gap*246, "S"),
					new Beat(startTime+gap*250, "F"),
					new Beat(startTime+gap*251, "Space"),
					new Beat(startTime+gap*253, "D"),
					new Beat(startTime+gap*255, "J"),
					new Beat(startTime+gap*257, "S"),
					new Beat(startTime+gap*260, "F"),
					new Beat(startTime+gap*262, "Space")
					
					
			};
			
		}else if(MusicTitle.equals("Sunshine - urpleactus") && Diff.equals("Hard")) {
			int startTime=3000-Main.REACH_TIME*1000;
			int gap=125;
			beats= new Beat[] {
					
					new Beat(startTime+gap*2, "S"),
					new Beat(startTime+gap*5, "K"),
					new Beat(startTime+gap*6, "L"),
					new Beat(startTime+gap*7, "Space"),
					new Beat(startTime+gap*9, "S"),
					new Beat(startTime+gap*13, "S"),
					new Beat(startTime+gap*15, "D"),
					new Beat(startTime+gap*17, "S"),
					new Beat(startTime+gap*20, "S"),
					new Beat(startTime+gap*23, "D"),
					new Beat(startTime+gap*27, "J"),
					new Beat(startTime+gap*30, "S"),
					new Beat(startTime+gap*31, "F"),
					new Beat(startTime+gap*32, "Space"),
					new Beat(startTime+gap*40, "K"),
					new Beat(startTime+gap*60, "L"),
					new Beat(startTime+gap*66, "Space"),
					new Beat(startTime+gap*70, "S"),
					new Beat(startTime+gap*40, "J"),
					new Beat(startTime+gap*45, "S"),
					new Beat(startTime+gap*47, "F"),
					new Beat(startTime+gap*49, "Space"),
					new Beat(startTime+gap*54, "K"),
					new Beat(startTime+gap*60, "L"),
					new Beat(startTime+gap*66, "Space"),
					new Beat(startTime+gap*70, "S"),
					new Beat(startTime+gap*80, "S"),
					new Beat(startTime+gap*82, "S"),
					new Beat(startTime+gap*83, "D"),
					new Beat(startTime+gap*86, "J"),
					new Beat(startTime+gap*90, "S"),
					new Beat(startTime+gap*91, "F"),
					new Beat(startTime+gap*92, "Space"),
					new Beat(startTime+gap*100, "K"),
					new Beat(startTime+gap*102, "D"),
					new Beat(startTime+gap*110, "S"),
					new Beat(startTime+gap*130, "F"),
					new Beat(startTime+gap*133, "Space"),
					new Beat(startTime+gap*134, "Space"),
					new Beat(startTime+gap*134, "K"),
					new Beat(startTime+gap*136, "K"),
					new Beat(startTime+gap*140, "S"),
					new Beat(startTime+gap*142, "D"),
					new Beat(startTime+gap*144, "S"),
					new Beat(startTime+gap*146, "D"),
					new Beat(startTime+gap*148, "S"),
					new Beat(startTime+gap*150, "D"),
					new Beat(startTime+gap*152, "S"),
					new Beat(startTime+gap*154, "S"),
					new Beat(startTime+gap*156, "K"),
					new Beat(startTime+gap*158, "L"),
					new Beat(startTime+gap*160, "Space"),
					new Beat(startTime+gap*164, "S"),
					new Beat(startTime+gap*165, "K"),
					new Beat(startTime+gap*170, "D"),
					new Beat(startTime+gap*171, "S"),
					new Beat(startTime+gap*173, "S"),
					new Beat(startTime+gap*179, "S"),
					new Beat(startTime+gap*181, "D"),
					new Beat(startTime+gap*183, "J"),
					new Beat(startTime+gap*184, "S"),
					new Beat(startTime+gap*186, "F"),
					new Beat(startTime+gap*188, "Space"),
					new Beat(startTime+gap*190, "K"),
					new Beat(startTime+gap*192, "L"),
					new Beat(startTime+gap*194, "Space"),
					new Beat(startTime+gap*196, "S"),
					new Beat(startTime+gap*198, "J"),
					new Beat(startTime+gap*200, "S"),
					new Beat(startTime+gap*202, "F"),
					new Beat(startTime+gap*203, "Space"),
					new Beat(startTime+gap*204, "K"),
					new Beat(startTime+gap*206, "L"),
					new Beat(startTime+gap*208, "Space"),
					new Beat(startTime+gap*210, "S"),
					new Beat(startTime+gap*212, "S"),
					new Beat(startTime+gap*214, "S"),
					new Beat(startTime+gap*216, "D"),
					new Beat(startTime+gap*219, "J"),
					new Beat(startTime+gap*222, "S"),
					new Beat(startTime+gap*223, "F"),
					new Beat(startTime+gap*225, "Space"),
					new Beat(startTime+gap*227, "Space"),
					new Beat(startTime+gap*230, "K"),
					new Beat(startTime+gap*232, "L"),
					new Beat(startTime+gap*234, "Space"),
					new Beat(startTime+gap*236, "S"),
					new Beat(startTime+gap*238, "S"),
					new Beat(startTime+gap*240, "S"),
					new Beat(startTime+gap*242, "D"),
					new Beat(startTime+gap*244, "J"),
					new Beat(startTime+gap*246, "S"),
					new Beat(startTime+gap*250, "F"),
					new Beat(startTime+gap*251, "Space"),
					new Beat(startTime+gap*253, "D"),
					new Beat(startTime+gap*255, "J"),
					new Beat(startTime+gap*257, "S"),
					new Beat(startTime+gap*260, "F"),
					new Beat(startTime+gap*262, "Space")
					
					
			};
		}else if(MusicTitle.equals("Eneko Artola - Becoming True") && Diff.equals("Hard")) {
			int startTime=3000-Main.REACH_TIME*1000;
			int gap=125;
			beats= new Beat[] {
					
					new Beat(startTime+gap*2, "S"),
					new Beat(startTime+gap*5, "K"),
					new Beat(startTime+gap*6, "L"),
					new Beat(startTime+gap*7, "Space"),
					new Beat(startTime+gap*9, "S"),
					new Beat(startTime+gap*13, "S"),
					new Beat(startTime+gap*15, "D"),
					new Beat(startTime+gap*17, "S"),
					new Beat(startTime+gap*20, "S"),
					new Beat(startTime+gap*23, "D"),
					new Beat(startTime+gap*27, "J"),
					new Beat(startTime+gap*30, "S"),
					new Beat(startTime+gap*31, "F"),
					new Beat(startTime+gap*32, "Space"),
					new Beat(startTime+gap*40, "K"),
					new Beat(startTime+gap*60, "L"),
					new Beat(startTime+gap*66, "Space"),
					new Beat(startTime+gap*70, "S"),
					new Beat(startTime+gap*40, "J"),
					new Beat(startTime+gap*45, "S"),
					new Beat(startTime+gap*47, "F"),
					new Beat(startTime+gap*49, "Space"),
					new Beat(startTime+gap*54, "K"),
					new Beat(startTime+gap*60, "L"),
					new Beat(startTime+gap*66, "Space"),
					new Beat(startTime+gap*70, "S"),
					new Beat(startTime+gap*80, "S"),
					new Beat(startTime+gap*82, "S"),
					new Beat(startTime+gap*83, "D"),
					new Beat(startTime+gap*86, "J"),
					new Beat(startTime+gap*90, "S"),
					new Beat(startTime+gap*91, "F"),
					new Beat(startTime+gap*92, "Space"),
					new Beat(startTime+gap*100, "K"),
					new Beat(startTime+gap*102, "D"),
					new Beat(startTime+gap*110, "S"),
					new Beat(startTime+gap*130, "F"),
					new Beat(startTime+gap*133, "Space"),
					new Beat(startTime+gap*134, "Space"),
					new Beat(startTime+gap*134, "K"),
					new Beat(startTime+gap*136, "K"),
					new Beat(startTime+gap*140, "S"),
					new Beat(startTime+gap*142, "D"),
					new Beat(startTime+gap*144, "S"),
					new Beat(startTime+gap*146, "D"),
					new Beat(startTime+gap*148, "S"),
					new Beat(startTime+gap*150, "D"),
					new Beat(startTime+gap*152, "S"),
					new Beat(startTime+gap*154, "S"),
					new Beat(startTime+gap*156, "K"),
					new Beat(startTime+gap*158, "L"),
					new Beat(startTime+gap*160, "Space"),
					new Beat(startTime+gap*164, "S"),
					new Beat(startTime+gap*165, "K"),
					new Beat(startTime+gap*170, "D"),
					new Beat(startTime+gap*171, "S"),
					new Beat(startTime+gap*173, "S"),
					new Beat(startTime+gap*179, "S"),
					new Beat(startTime+gap*181, "D"),
					new Beat(startTime+gap*183, "J"),
					new Beat(startTime+gap*184, "S"),
					new Beat(startTime+gap*186, "F"),
					new Beat(startTime+gap*188, "Space"),
					new Beat(startTime+gap*190, "K"),
					new Beat(startTime+gap*192, "L"),
					new Beat(startTime+gap*194, "Space"),
					new Beat(startTime+gap*196, "S"),
					new Beat(startTime+gap*198, "J"),
					new Beat(startTime+gap*200, "S"),
					new Beat(startTime+gap*202, "F"),
					new Beat(startTime+gap*203, "Space"),
					new Beat(startTime+gap*204, "K"),
					new Beat(startTime+gap*206, "L"),
					new Beat(startTime+gap*208, "Space"),
					new Beat(startTime+gap*210, "S"),
					new Beat(startTime+gap*212, "S"),
					new Beat(startTime+gap*214, "S"),
					new Beat(startTime+gap*216, "D"),
					new Beat(startTime+gap*219, "J"),
					new Beat(startTime+gap*222, "S"),
					new Beat(startTime+gap*223, "F"),
					new Beat(startTime+gap*225, "Space"),
					new Beat(startTime+gap*227, "Space"),
					new Beat(startTime+gap*230, "K"),
					new Beat(startTime+gap*232, "L"),
					new Beat(startTime+gap*234, "Space"),
					new Beat(startTime+gap*236, "S"),
					new Beat(startTime+gap*238, "S"),
					new Beat(startTime+gap*240, "S"),
					new Beat(startTime+gap*242, "D"),
					new Beat(startTime+gap*244, "J"),
					new Beat(startTime+gap*246, "S"),
					new Beat(startTime+gap*250, "F"),
					new Beat(startTime+gap*251, "Space"),
					new Beat(startTime+gap*253, "D"),
					new Beat(startTime+gap*255, "J"),
					new Beat(startTime+gap*257, "S"),
					new Beat(startTime+gap*260, "F"),
					new Beat(startTime+gap*262, "Space")
					
					
			};
			
			
		}
		
		int i=0;
		gameMusic.start();
		while(i<beats.length && !isInterrupted()) {
			boolean dropped= false;
			if(beats[i].getTime() <= gameMusic.getTime()) {
				noteFall note=new noteFall(beats[i].getNoteName());
				note.start();
				noteList.add(note);
				i++;
				dropped= true;
			}
			if(!dropped) {
				try {
					Thread.sleep(5);
					
				}catch(Exception e) {
					
				}
			}
			
			
		}
		
		
		
		

		
		
	}
	
	
	public void judge(String inp) {
		for(int i=0; i<noteList.size(); i++) {
			noteFall note= noteList.get(i);
			if(inp.equals(note.getNoteType())) {
				judgeEvent(note.judge());
				break;
			}
			
			
		}
	}
	
	public void judgeEvent(String j) {
		if(!j.equals("None")) {
			RedFlareimg= new ImageIcon(Main.class.getResource("../images/flare.png")).getImage();
		}
		
		if(j.equals("Perfect")) {
			Perfectimg=new ImageIcon(Main.class.getResource("../images/Perfect.png")).getImage();
		}
		else if(j.equals("Miss")) {
			Perfectimg=new ImageIcon(Main.class.getResource("../images/Miss.png")).getImage();
			
		}
		else if(j.equals("Great")) {
			Perfectimg=new ImageIcon(Main.class.getResource("../images/Great.png")).getImage();
		}
		else if(j.equals("Early")) {
			Perfectimg=new ImageIcon(Main.class.getResource("../images/Early.png")).getImage();
		}
		else if(j.equals("Slow")) {
			Perfectimg=new ImageIcon(Main.class.getResource("../images/Slow.png")).getImage();
		}
		else if(j.equals("Good")) {
			Perfectimg=new ImageIcon(Main.class.getResource("../images/Good.png")).getImage();
		}
	}
	
	
	
		
		
}

