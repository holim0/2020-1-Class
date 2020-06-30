package miniproject;



import java.awt.Color;
import java.awt.Cursor;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Image;
import java.awt.RenderingHints;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionAdapter;
import java.util.ArrayList;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;





public class Game extends JFrame{
   
   
      private Image background;
      private Graphics backgraphic;
      
      private JLabel menubar= new JLabel(new ImageIcon(Main.class.getResource("../images/menubar.png"))); 
      
      private static Image firstback=new ImageIcon(Main.class.getResource("../images/background.jpg")).getImage();
      
      
      private static ImageIcon exitgo= new ImageIcon(Main.class.getResource("../images/exit.png"));
      private static ImageIcon exitout= new ImageIcon(Main.class.getResource("../images/exit2.png"));
      private static ImageIcon startimg =new ImageIcon(Main.class.getResource("../images/start.png"));
      private static ImageIcon finishimg =new ImageIcon(Main.class.getResource("../images/finish.png"));
      private static ImageIcon start2img =new ImageIcon(Main.class.getResource("../images/start2.png"));
      private static ImageIcon finish2img =new ImageIcon(Main.class.getResource("../images/finish2.png"));
      
      
      
      private static ImageIcon leftbtnimg =new ImageIcon(Main.class.getResource("../images/left.png"));
      private static ImageIcon rightbtnimg =new ImageIcon(Main.class.getResource("../images/right.png"));
      private static ImageIcon left2btnimg =new ImageIcon(Main.class.getResource("../images/left2.png"));
      private static ImageIcon right2btnimg =new ImageIcon(Main.class.getResource("../images/right2.png"));
      
      private static ImageIcon easybtnimg =new ImageIcon(Main.class.getResource("../images/eastbtn1.png"));
      private static ImageIcon easybtn2img =new ImageIcon(Main.class.getResource("../images/eastbtn2.png"));
      private static ImageIcon hardbtnimg =new ImageIcon(Main.class.getResource("../images/hardbtn1.png"));
      private static ImageIcon hardbtn2img =new ImageIcon(Main.class.getResource("../images/hardbtn2.png"));
      
      private static ImageIcon backbtnimg =new ImageIcon(Main.class.getResource("../images/backbtn.png"));
      private static ImageIcon backbtn2img =new ImageIcon(Main.class.getResource("../images/backbtn2.png"));
      
      
      
      
      
      private JButton exitbtn= new JButton(exitgo);
      private static JButton startbtn= new JButton(startimg);
      private static JButton finishbtn= new JButton(finishimg);
      
      private static JButton leftbtn= new JButton(leftbtnimg);
      private static JButton rightbtn= new JButton(rightbtnimg);
      private static JButton left2btn= new JButton(left2btnimg);
      private static JButton right2btn= new JButton(right2btnimg);
      
      private static JButton easybtn= new JButton(easybtnimg);
      private static JButton hardbtn= new JButton(hardbtnimg);
      
      private static JButton backbtn= new JButton(backbtnimg);
      private static JButton backbtn2= new JButton(backbtnimg);
      
      
      private int mx, my;
      
      
      private static boolean ismain= false;
      private static boolean isGameScreen=false;
      
      
      
      ArrayList<MusicTrack> tracklist=new ArrayList<MusicTrack>();
      
      private static Music selectedMusic;
      private Image musicselectback;//=new ImageIcon(Main.class.getResource("../images/song1.jpg")).getImage();
      private Image titleNameImg;//= new ImageIcon(Main.class.getResource("../images/song1 title.png")).getImage();
      
      private Music intro= new Music("INTRO.mp3", true);
      
      private int nowSelected=0;
      public static JButton LoginButton = new JButton("Login");
      
      public static MusicGame game; 
      
      public static boolean check_login= false;
      public static JLabel lblNewLabel = new JLabel("holim0");
      
      public Game() {
    	  
    	  
    	  tracklist.add(new MusicTrack("song1 title.png", "song1.jpg", "whileGame.jpg", "Sappheiros - Awake_highlight.mp3", 
         		 "Sappheiros - Awake.mp3", "Sappheiros - Awake"));
          
          tracklist.add(new MusicTrack("song2 title.png", "song2.jpg", "whileGame.jpg", "Sunshine - urpleactus_highlight.mp3", 
         		 "Sunshine - urpleactus.mp3", "Sunshine - urpleactus"));
          
          tracklist.add(new MusicTrack("song3 title.png", "song3.jpg", "whileGame.jpg", "Eneko Artola - Becoming True_highlight.mp3", 
         		 "Eneko Artola - Becoming True.mp3", "Eneko Artola - Becoming True"));
    	  
    	  
    	 setUndecorated(true);
         setTitle("SKKU Rythm Game!");
         setSize(Main.SCREEN_HEIGHT, Main.SCREEN_WIDTH);
         setVisible(true);
         setResizable(false);
         setLocationRelativeTo(null);
         setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
         setBackground(new Color(0, 0, 0, 0));
         getContentPane().setLayout(null);
         
         addKeyListener(new KeyListener());
         
         intro.start();
         
        
         
         
         
         
         backbtn.setVisible(false);
         backbtn.setBounds(20, 30, 70, 70);
         backbtn.setBorderPainted(false);
         backbtn.setContentAreaFilled(false);
         backbtn.setFocusPainted(false);
         backbtn.addMouseListener(new MouseAdapter() {
        	 @Override
        	 public void mouseEntered(MouseEvent e) {
        		 backbtn.setIcon(backbtn2img);
        		 backbtn.setCursor(new Cursor(Cursor.HAND_CURSOR));
        		 Music btnEntered= new Music("mouseClick.mp3", false);
     		     btnEntered.start();
        	 }
        	 @Override
        	 public void mouseExited(MouseEvent e) {
        		 backbtn.setIcon(backbtnimg);
        		 backbtn.setCursor(new Cursor(Cursor.DEFAULT_CURSOR));
        	 }
        	 @Override
        	 public void mousePressed(MouseEvent e) {
        		backToMain();
        		 
        	 }
        	 
         });
         getContentPane().add(backbtn);
         
         
         
         backbtn2.setVisible(false);
         backbtn2.setBounds(20, 30, 70, 70);
         backbtn2.setBorderPainted(false);
         backbtn2.setContentAreaFilled(false);
         backbtn2.setFocusPainted(false);
         backbtn2.addMouseListener(new MouseAdapter() {
        	 @Override
        	 public void mouseEntered(MouseEvent e) {
        		 backbtn2.setIcon(backbtn2img);
        		 backbtn2.setCursor(new Cursor(Cursor.HAND_CURSOR));
        		 Music btnEntered= new Music("mouseClick.mp3", false);
     		     btnEntered.start();
        	 }
        	 @Override
        	 public void mouseExited(MouseEvent e) {
        		 backbtn2.setIcon(backbtnimg);
        		 backbtn2.setCursor(new Cursor(Cursor.DEFAULT_CURSOR));
        	 }
        	 @Override
        	 public void mousePressed(MouseEvent e) {
        		backToMain2();
        		
        	 }
        	 
         });
         getContentPane().add(backbtn2);
         
         
         
         
         
         
         
         
         
         
         easybtn.setVisible(false);
         easybtn.setBounds(375,  610, 250, 67);
         easybtn.setBorderPainted(false);
         easybtn.setContentAreaFilled(false);
         easybtn.setFocusPainted(false);
         easybtn.addMouseListener(new MouseAdapter() {
        	 @Override
        	 public void mouseEntered(MouseEvent e) {
        		 easybtn.setIcon(easybtn2img);
        		 easybtn.setCursor(new Cursor(Cursor.HAND_CURSOR));
        		 Music btnEntered= new Music("mouseClick.mp3", false);
     		     btnEntered.start();
        	 }
        	 @Override
        	 public void mouseExited(MouseEvent e) {
        		 easybtn.setIcon(easybtnimg);
        		 easybtn.setCursor(new Cursor(Cursor.DEFAULT_CURSOR));
        	 }
        	 @Override
        	 public void mousePressed(MouseEvent e) {
        		 gameStart(nowSelected, "Easy");
        		 
        		 
        	 }
        	 
         });
         getContentPane().add(easybtn);
         
         
         
         hardbtn.setVisible(false);
         hardbtn.setBounds(655, 610, 250, 67);
         hardbtn.setBorderPainted(false);
         hardbtn.setContentAreaFilled(false);
         hardbtn.setFocusPainted(false);
         hardbtn.addMouseListener(new MouseAdapter() {
        	 @Override
        	 public void mouseEntered(MouseEvent e) {
        		 hardbtn.setIcon(hardbtn2img);
        		 hardbtn.setCursor(new Cursor(Cursor.HAND_CURSOR));
        		 Music btnEntered= new Music("mouseClick.mp3", false);
        		 btnEntered.start();
        	 }
        	 @Override
        	 public void mouseExited(MouseEvent e) {
        		 hardbtn.setIcon(hardbtnimg);
        		 hardbtn.setCursor(new Cursor(Cursor.DEFAULT_CURSOR));
        	 }
        	 @Override
        	 public void mousePressed(MouseEvent e) {
        		 gameStart(nowSelected, "Hard");
        		 
        		 
        	 }
        	 
         });
         getContentPane().add(hardbtn);
         
                                               
         
         
         
         rightbtn.setVisible(false);
         rightbtn.setBounds(1080, 310, 60, 60);
         rightbtn.setBorderPainted(false);
         rightbtn.setContentAreaFilled(false);
         rightbtn.setFocusPainted(false);
         rightbtn.addMouseListener(new MouseAdapter() {
        	 @Override
        	 public void mouseEntered(MouseEvent e) {
        		 rightbtn.setIcon(right2btnimg);
        		 rightbtn.setCursor(new Cursor(Cursor.HAND_CURSOR));
        	 }
        	 @Override
        	 public void mouseExited(MouseEvent e) {
        		 rightbtn.setIcon(rightbtnimg);
        		 rightbtn.setCursor(new Cursor(Cursor.DEFAULT_CURSOR));
        	 }
        	 @Override
        	 public void mousePressed(MouseEvent e) {
        		 pressRight();
        		 
        		 
        		 
        	 }
        	 
         });
         getContentPane().add(rightbtn);
         
         
         leftbtn.setVisible(false);
         leftbtn.setBounds(140, 310, 60, 60);
         leftbtn.setBorderPainted(false);
         leftbtn.setContentAreaFilled(false);
         leftbtn.setFocusPainted(false);
         leftbtn.addMouseListener(new MouseAdapter() {
        	 @Override
        	 public void mouseEntered(MouseEvent e) {
        		 leftbtn.setIcon(left2btnimg);
        		 leftbtn.setCursor(new Cursor(Cursor.HAND_CURSOR));
        	 }
        	 @Override
        	 public void mouseExited(MouseEvent e) {
        		 leftbtn.setIcon(leftbtnimg);
        		 leftbtn.setCursor(new Cursor(Cursor.DEFAULT_CURSOR));
        	 }
        	 @Override
        	 public void mousePressed(MouseEvent e) {
        		 pressLeft();
        		 
        		 
        		 
        	 }
        	 
         });
         getContentPane().add(leftbtn);
         
         
         
         exitbtn.setBounds(1245, 0, 30, 30);
         exitbtn.setBorderPainted(false);
         exitbtn.setContentAreaFilled(false);
         exitbtn.setFocusPainted(false);
         exitbtn.addMouseListener(new MouseAdapter() {
        	 @Override
        	 public void mouseEntered(MouseEvent e) {
        		 exitbtn.setIcon(exitout);
        		 exitbtn.setCursor(new Cursor(Cursor.HAND_CURSOR));
        		 
        	 }
        	 @Override
        	 public void mouseExited(MouseEvent e) {
        		 exitbtn.setIcon(exitgo);
        		 exitbtn.setCursor(new Cursor(Cursor.DEFAULT_CURSOR));
        	 }
        	 @Override
        	 public void mousePressed(MouseEvent e) {
        		 System.exit(0);
        	 }
        	 
         });
         getContentPane().add(exitbtn);
         
         
         finishbtn.setBounds(420, 550, 400, 100);
         finishbtn.setBorderPainted(false);
         finishbtn.setContentAreaFilled(false);
         finishbtn.setFocusPainted(false);
         finishbtn.addMouseListener(new MouseAdapter() {
        	 @Override
        	 public void mouseEntered(MouseEvent e) {
        		 finishbtn.setIcon(finish2img);
        		 finishbtn.setCursor(new Cursor(Cursor.HAND_CURSOR));
        		 Music btnEntered= new Music("mouseClick.mp3", false);
        		    btnEntered.start();
        	 }
        	 @Override
        	 public void mouseExited(MouseEvent e) {
        		 finishbtn.setIcon(finishimg);
        		 finishbtn.setCursor(new Cursor(Cursor.DEFAULT_CURSOR));
        		 
        	 }
        	 @Override
        	 public void mousePressed(MouseEvent e) {
        		 new newWindow();
  
        	 }
        	 
         });
         getContentPane().add(finishbtn);
         
         
         
         
         startbtn.setBounds(420, 420, 400, 100);
         startbtn.setBorderPainted(false);
         startbtn.setContentAreaFilled(false);
         startbtn.setFocusPainted(false);
         startbtn.addMouseListener(new MouseAdapter() {
       	 @Override
       	 public void mouseEntered(MouseEvent e) {
       		 startbtn.setIcon(start2img);
       		 startbtn.setCursor(new Cursor(Cursor.HAND_CURSOR));
       		Music btnEntered= new Music("mouseClick.mp3", false);
   		    btnEntered.start();
       	 }
       	 @Override
       	 public void mouseExited(MouseEvent e) {
       		 startbtn.setIcon(startimg);
       		 startbtn.setCursor(new Cursor(Cursor.DEFAULT_CURSOR));
       		 
       	 }
       	 @Override
       	 public void mousePressed(MouseEvent e) {
       		 EnterMain();

       	 }
       	 
        });
        getContentPane().add(startbtn);
         
         
         
         
         
         
         
         
         menubar.setBounds(0,0,1280, 30);
         menubar.addMouseListener(new MouseAdapter() {
        	 @Override
        	 public void mousePressed(MouseEvent e) {
        		 mx=e.getX();
        		 my=e.getY();
        
        	 }
        	 
         });
         menubar.addMouseMotionListener(new MouseMotionAdapter() {
        	 @Override
        	 
        	 public void mouseDragged(MouseEvent e) {
        		 int x=e.getXOnScreen();
        		 int y=e.getYOnScreen();
        		 setLocation(x-mx, y-my);
        	 }
        	 
        	 
        	 
        	 
         });
         getContentPane().add(menubar);
         
         
         LoginButton.setFont(new Font("210 맨발의청춘 R", Font.BOLD, 15));
         LoginButton.addActionListener(new ActionListener() {
         	public void actionPerformed(ActionEvent e) {
         		new Login();
         		
         	}
         });
         LoginButton.setBounds(20, 40, 139, 60);
         getContentPane().add(LoginButton);
         
         
         
         
         lblNewLabel.setVisible(false);
         lblNewLabel.setFont(new Font("a파도소리", Font.PLAIN, 20));
         lblNewLabel.setForeground(Color.white);
         lblNewLabel.setBounds(1153, 50, 103, 50);
         
         getContentPane().add(lblNewLabel);
         
         
         
         
         
         
      }
      
      
      public void paint(Graphics g) {
         background= createImage(Main.SCREEN_HEIGHT,Main.SCREEN_WIDTH);
         backgraphic=background.getGraphics();
         MakeScreen((Graphics2D) backgraphic);
         
         g.drawImage(background, 0, 0, null);
      }
      
      public void MakeScreen(Graphics2D g) {
         g.drawImage(firstback, 0, 0, null);
         if(ismain) {
        	 g.drawImage(musicselectback, 320, 100, null);
        	 g.drawImage(titleNameImg, 290, 85, null);
        	 
         }
         if(isGameScreen){
        	 
        	 game.screenDraw(g);
        	 
         }
         
       
         
         paintComponents(g);
         
         try {
        	 Thread.sleep(6);
        	 
         }catch(Exception e){
        	 
        	e.printStackTrace();
         }
         
         this.repaint();
         
      }
      
      
      
      public void selectTrack(int nowSelected) {
    	  
    	  if(selectedMusic!=null) {
    		  selectedMusic.close();
    	  }
    	  
    	  titleNameImg = new ImageIcon(Main.class.getResource("../images/"+ tracklist.get(nowSelected).getTitleImage())).getImage();
    	  
    	  musicselectback = new ImageIcon(Main.class.getResource("../images/"+ tracklist.get(nowSelected).getStartImage())).getImage();
    	  
    	  selectedMusic= new Music(tracklist.get(nowSelected).getStartMusic(), true);
    	  selectedMusic.start();
      }
      
      
      
      public void pressLeft() {

    	  if(nowSelected==0) {
    		  nowSelected=tracklist.size()-1;
    		  
    	  }else {
    		  nowSelected--;
    	  }
    	  
    	  selectTrack(nowSelected);
    	  
      }
      
      public void pressRight() {
    	  if(nowSelected==tracklist.size()-1) {
    		  nowSelected=0;
    		  
    	  }else {
    		  nowSelected++;
    	  }
    	  
    	  selectTrack(nowSelected);
    	  
      }
      
      
      public void gameStart(int nowSelected, String difficulty) {
    	  if(selectedMusic!=null) {
    		  selectedMusic.close();
    	  }
    	  
    	  
    	  ismain= false;
    	  LoginButton.setVisible(false);
    	  leftbtn.setVisible(false);
    	  rightbtn.setVisible(false);
    	  easybtn.setVisible(false);
    	  hardbtn.setVisible(false);
    	  backbtn2.setVisible(false);
    	  
    	  firstback=new ImageIcon(Main.class.getResource("../images/"+tracklist.get(nowSelected).getGameImage())).getImage();
    	  
    	  backbtn.setVisible(true);
    	  isGameScreen=true;
    	  game= new MusicGame(tracklist.get(nowSelected).getMusicTitle(), difficulty, tracklist.get(nowSelected).getGameMusic());
    	  game.start();
    	  setFocusable(true);
      }
      
      
      
      public void backToMain() {
    	  ismain=true;
    	  leftbtn.setVisible(true);
    	  rightbtn.setVisible(true);
    	  hardbtn.setVisible(true);
    	  easybtn.setVisible(true);
    	  LoginButton.setVisible(false);
    	  firstback=new ImageIcon(Main.class.getResource("../images/background.jpg")).getImage();
    	  
    	  backbtn.setVisible(false);
    	  backbtn2.setVisible(true);
    	  
    	  selectTrack(nowSelected);
    	  isGameScreen=false;
    	  
    	  game.close();
    	  
    	  
      }
      
      
      public static void backToMain2() {
    	  ismain=false;
    	  startbtn.setVisible(true);
    	  finishbtn.setVisible(true);
    	  leftbtn.setVisible(false);
 		  rightbtn.setVisible(false);
 		  easybtn.setVisible(false);
		  hardbtn.setVisible(false);
		  LoginButton.setVisible(true);
    	  
    	  firstback=new ImageIcon(Main.class.getResource("../images/background.jpg")).getImage();
    	  
    	  backbtn2.setVisible(false);
    	  isGameScreen=false;
    	  selectedMusic.close();
    	  
    	  
      }
      
      
      public void EnterMain() {
    	  
    	   firstback=new ImageIcon(Main.class.getResource("../images/mainback.jpg")).getImage();
    	   ismain=true;
    		 startbtn.setVisible(false);
    		 finishbtn.setVisible(false);
    		 leftbtn.setVisible(true);
    		 rightbtn.setVisible(true);
    		 easybtn.setVisible(true);
   		     hardbtn.setVisible(true);
   		     backbtn2.setVisible(true);
   		     backbtn.setVisible(false);
   		     LoginButton.setVisible(false);
   		     intro.close();
   		     
    		 selectTrack(0);
    	  
    	  
      }

}












