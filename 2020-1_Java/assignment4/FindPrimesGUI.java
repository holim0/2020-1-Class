import javax.swing.JFrame;

import javax.swing.JTextField;
import javax.swing.JTextArea;
import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.JProgressBar;
import javax.swing.JLabel;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.ScrollPaneConstants;
import java.awt.BorderLayout;


import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Comparator;
import java.util.Vector;
import java.awt.GridBagLayout;
import java.awt.GridBagConstraints;
import java.awt.Insets;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.FileWriter;
import java.awt.event.ActionEvent;

public class FindPrimesGUI extends JFrame {
	public static JTextField highestPrimeJTextField = new JTextField();
	public static JButton getPrimesJButton = new JButton("Get Primes");
	public static JTextArea displayPrimesJTextArea = new JTextArea();
	public static JButton cancelJButton = new JButton("Cancel");
	public static JProgressBar progressJProgressBar = new JProgressBar(0,100);
	public static JLabel statusJLabel = new JLabel();

	JMenuBar menuBar = new JMenuBar();
	private JMenuItem mntmLoad;
	private JMenuItem mntmSave;
	private JMenuItem mntmExit;
	private JMenu mnOperations;
	private JMenuItem mntmOrderA;
	private JMenuItem mntmOrderD;
	private JMenuItem mntmShuffle;
	public static ArrayList<Integer> PrimeList;
	
	PrimeGet t1;
	public static int[] NumArray; 
	public static boolean IsStop=false;
	
	// constructor
	public FindPrimesGUI() {
		
		super("Finding Primes");
		setTitle("Finding Primes Application");
		PrimeList = new ArrayList<Integer>();
		getContentPane().setLayout(new BorderLayout());

		// initialize panel to get a number from the user
		JPanel northJPanel = new JPanel();
		setJMenuBar(menuBar);
		JMenu mnFile = new JMenu("File");
		menuBar.add(mnFile);
		mntmSave = new JMenuItem("Save");
		mntmSave.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				JFileChooser jfc = new JFileChooser();
				int returnVal = jfc.showSaveDialog(null);
		        if(returnVal == 0) {
		            File file = jfc.getSelectedFile();
		            //System.out.println("당신이 저장할 파일은 " + file.getName() + " 입니다.");
		            
		            JOptionPane a= new JOptionPane();
		            a.showMessageDialog(null, "File Saved");
		            String str = displayPrimesJTextArea.getText();
		            try {
		                BufferedWriter bw = new BufferedWriter(new FileWriter(file));
		                bw.write(str);
		                bw.flush();
		                bw.close();
		                 
		            }catch(Exception e) {e.printStackTrace();}
		             
		        }
			
			
			}
			
			
		});
		mnFile.add(mntmSave);
		

		mntmLoad = new JMenuItem("Load");
		
		mntmLoad.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				
				PrimeList= new ArrayList<>();
				
				JFileChooser jfc = new JFileChooser();
				
		        int returnVal = jfc.showSaveDialog(null);
		        if(returnVal == 0) {
		            File file = jfc.getSelectedFile();
		            try {
		                String tmp, str="";
		                BufferedReader br = new BufferedReader(new FileReader(file));
		                while((tmp = br.readLine()) != null)
		                {	
		                	PrimeList.add(Integer.parseInt(tmp));
		                    str += tmp+"\n";
		                }
		                displayPrimesJTextArea.setText("");
		                displayPrimesJTextArea.append(str);
		                // System.out.println(str);
		            }catch(Exception e) {
		                e.printStackTrace();
		            }
		             
		        }
		        else
		        {
		        	JOptionPane b= new JOptionPane();
		            b.showMessageDialog(null, "No File Selected");
		            
		        }
			
			
			}
			
			
		});
		
		
		
		mnFile.add(mntmLoad);
		mntmExit = new JMenuItem("Exit");
		mntmExit.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				
				System.exit(0);
			}
		});
		mnFile.add(mntmExit);
		mnOperations = new JMenu("Operations ");
		menuBar.add(mnOperations);
		mntmOrderA = new JMenuItem("Order ascending");
		mntmOrderA.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				
				Collections.sort(PrimeList, new Ascending());
				displayPrimesJTextArea.setText("");
				for(int i: PrimeList) {
					//System.out.println(i);
					displayPrimesJTextArea.append(Integer.toString(i)+"\n");
				}
				
				
			}
		});
		mnOperations.add(mntmOrderA);
		
		
		mntmOrderD = new JMenuItem("Order descending ");
		mntmOrderD.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent arg0) {
				
				Collections.sort(PrimeList, new Descending());
				displayPrimesJTextArea.setText("");
				for(int i: PrimeList) {
					//System.out.println(i);
					displayPrimesJTextArea.append(Integer.toString(i)+"\n");
				}
				
				
			}
		});
		mnOperations.add(mntmOrderD);
		mntmShuffle = new JMenuItem("Shuffle ");
		mntmShuffle.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent arg0) {
				
				Collections.shuffle(PrimeList);
				displayPrimesJTextArea.setText("");
				for(int i: PrimeList) {
					//System.out.println(i);
					displayPrimesJTextArea.append(Integer.toString(i)+"\n");
				}
				
				
			}
		});
		
		
		
		
		mnOperations.add(mntmShuffle);
		northJPanel.add(new JLabel("Find primes less than: "));
		highestPrimeJTextField.setColumns(5);
		northJPanel.add(highestPrimeJTextField);
		
		getPrimesJButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {  /// when click the button then get the prime number
				getPrimesJButton.setEnabled(false);
				String check=highestPrimeJTextField.getText();
				statusJLabel.setText("");
				
				boolean flag= false;
				for(int i=0; i<check.length(); i++) {
					char val=check.charAt(i);
					if( val < 48 || val > 58)
					{
						JOptionPane.showMessageDialog(null,"Please Insert Integer Number!", "ERROR MESSAGE", JOptionPane.ERROR_MESSAGE);
						getPrimesJButton.setEnabled(true);
						progressJProgressBar.setValue(0);
						flag=true;
						break;
					}
				}
				
				
				if(!flag) {
					cancelJButton.setEnabled(true);
					displayPrimesJTextArea.setText("");
				}
				else {
					highestPrimeJTextField.setText("");
				}
				PrimeList=new ArrayList<>();
				 
				//displayPrimesJTextArea.setText("");
				
				t1= new PrimeGet();
				t1.start();
				
				
				
				
			}
		});
		northJPanel.add(getPrimesJButton);

		// add a scrollable JList to display results of calculation
		displayPrimesJTextArea.setEditable(false);
		getContentPane().add(new JScrollPane(displayPrimesJTextArea, ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS,
				ScrollPaneConstants.HORIZONTAL_SCROLLBAR_NEVER));

		// initialize a panel to display cancelJButton,
		// progressJProgressBar, and statusJLabel
		JPanel southJPanel = new JPanel();
		GridBagLayout gbl_southJPanel = new GridBagLayout();
		gbl_southJPanel.rowHeights = new int[] { 16, 0 };
		gbl_southJPanel.columnWeights = new double[] { 0.0, 0.0, 0.0 };
		gbl_southJPanel.rowWeights = new double[] { 0.0, Double.MIN_VALUE };
		southJPanel.setLayout(gbl_southJPanel);
		progressJProgressBar.setStringPainted(true);
		GridBagConstraints gbc_progressJProgressBar = new GridBagConstraints();
		gbc_progressJProgressBar.weightx = 0.6;
		gbc_progressJProgressBar.gridwidth = 2;
		gbc_progressJProgressBar.fill = GridBagConstraints.BOTH;
		gbc_progressJProgressBar.insets = new Insets(0, 0, 0, 1);
		gbc_progressJProgressBar.gridx = 0;
		gbc_progressJProgressBar.gridy = 0;
		southJPanel.add(progressJProgressBar, gbc_progressJProgressBar);

		getContentPane().add(northJPanel, BorderLayout.NORTH);
		cancelJButton.setEnabled(false);
		
		cancelJButton.addActionListener(new ActionListener(){

			@Override
			public void actionPerformed(ActionEvent e) {
				t1.stop();
				getPrimesJButton.setEnabled(true);
				cancelJButton.setEnabled(false);
				statusJLabel.setText("");
				statusJLabel.setText("Found "+PrimeGet.pcnt+" primes.");
				PrimeGet.pcnt=0;
				
			}
			
		});
		
		
		
		
		northJPanel.add(cancelJButton);

		getContentPane().add(southJPanel, BorderLayout.SOUTH);
		GridBagConstraints gbc_statusJLabel = new GridBagConstraints();
		gbc_statusJLabel.weightx = 0.3;
		gbc_statusJLabel.anchor = GridBagConstraints.EAST;
		gbc_statusJLabel.fill = GridBagConstraints.HORIZONTAL;
		gbc_statusJLabel.gridx = 2;
		gbc_statusJLabel.gridy = 0;
		southJPanel.add(statusJLabel, gbc_statusJLabel);
		setSize(442, 415);
		setVisible(true);
		setLocationRelativeTo(null);
		
		
	} // end constructor
	
	
	
	

	// main method begins program execution
	public static void main(String[] args) {
		FindPrimesGUI application = new FindPrimesGUI();
		application.setDefaultCloseOperation(EXIT_ON_CLOSE);
		
		
		
		
		
	} // end main
	
	
	
	
	
} // end class FindPrimes



class PrimeGet extends Thread{
	
	public static int pcnt=0;
	public void run() {
		
			
			
		try {
			int PrimeCnt=0;      ///// total number of primeNumber
			int num1=Integer.parseInt(FindPrimesGUI.highestPrimeJTextField.getText());
			int k=2; 
			boolean isPrime1 = true;
			while(k<num1) {
				isPrime1 = true;
				for(int n=2; n<k; n++) {
					if(k%n==0) {
						isPrime1=false;
						break;
					}
					
				}
				if(isPrime1==true) {
					PrimeCnt++;
				}
				k++;
			}
			
			
			int cur=0;
			
			
			int num=Integer.parseInt(FindPrimesGUI.highestPrimeJTextField.getText());
			int i=2; 
			boolean isPrime = true;
			
			while(i<num) {
				
				isPrime = true;
				
				for(int n=2; n<i; n++) {
					if(i%n==0) {
						isPrime=false;
						break;
					}
					
				}
				
				if(isPrime==true) {
					pcnt++;
					cur+=1;
					FindPrimesGUI.displayPrimesJTextArea.append(Integer.toString(i)+"\n");
					FindPrimesGUI.PrimeList.add(i);
					FindPrimesGUI.progressJProgressBar.setValue((cur*100)/PrimeCnt);
					Thread.sleep(300);
				}
				
				i++;
				
				
			}
			if(FindPrimesGUI.progressJProgressBar.getValue()<100) {
				FindPrimesGUI.progressJProgressBar.setValue(100);
				FindPrimesGUI.statusJLabel.setText("Found "+ pcnt+" primes.");
				FindPrimesGUI.getPrimesJButton.setEnabled(true);
				FindPrimesGUI.cancelJButton.setEnabled(false);
				
				pcnt=0;
			}else {
				FindPrimesGUI.statusJLabel.setText("Found "+ pcnt+" primes.");
				FindPrimesGUI.getPrimesJButton.setEnabled(true);
				FindPrimesGUI.cancelJButton.setEnabled(false);
				pcnt=0;
			}
			
			
		}catch(Exception e) {
			//System.out.println(e);
		}
		
		
	}
	
}



//내림차순
class Descending implements Comparator<Integer> {

 @Override
 public int compare(Integer o1, Integer o2) {
     return o2.compareTo(o1);
 }

}

//오름차순
class Ascending implements Comparator<Integer> {

 @Override
 public int compare(Integer o1, Integer o2) {
     return o1.compareTo(o2);
 }

}






















