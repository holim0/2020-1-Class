import java.awt.BorderLayout;
import java.awt.Component;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.EventQueue;

import javax.swing.AbstractButton;
import javax.swing.DefaultListModel;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.JButton;
import javax.swing.JTextField;
import javax.swing.JScrollPane;

import java.awt.GridLayout;
import java.awt.Point;

import javax.swing.JList;

import java.awt.Font;

import javax.swing.SwingConstants;

import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.util.Stack;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.text.DecimalFormat;
import java.text.NumberFormat;

public class Calculator extends JFrame implements ActionListener{

   private JPanel contentPane;
   private JPanel pnDisplay;
   private JPanel pnInput;
   private JPanel pnHistory;
   private JTextField textField;
   private JButton btn7;
   private JButton btn8;
   private JButton btn9;
   private JButton btnAdd;
   private JButton btnClearAll;
   private JButton btn4;
   private JButton btn5;
   private JButton btn6;
   private JButton btnMinus;
   private JButton btnClearText;
   private JButton btn1;
   private JButton btn2;
   private JButton btn3;
   private JButton btnMultiply;
   private JButton btnMemSet;
   private JButton btn0;
   private JButton btnDot;
   private JButton btnEqual;
   private JButton btnDivide;
   private JButton btnMemRead;
   private JList list;

   // String to store input data
   private String num1;
   private String num2;
   private String operator;
   private final String NONE = "NONE";
   private DefaultListModel<String> listData;
   private String cur;
   
   
   
   Stack<Double> stack1;
   Stack<String> stack2;
  
   
   /**
    * Launch the application.
    */
   public static void main(String[] args) {
      EventQueue.invokeLater(new Runnable() {
         public void run() {
            try {
               Calculator frame = new Calculator();
               frame.setVisible(true);
            } catch (Exception e) {
               e.printStackTrace();
            }
         }
      });
   }

   /**
    * Create the frame.
    */
   public Calculator() {

      /*
       * GUI code
       */
      setTitle("Simple Calculator");
      setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
      setBounds(100, 100, 450, 300);
      contentPane = new JPanel();
      contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
      contentPane.setLayout(new BorderLayout(0, 0));
      setContentPane(contentPane);

      pnDisplay = new JPanel();
      contentPane.add(pnDisplay, BorderLayout.NORTH);
      pnDisplay.setLayout(new GridLayout(0, 1, 0, 0));

      textField = new JTextField();
      textField.setHorizontalAlignment(SwingConstants.RIGHT);
      textField.setFont(new Font("Courier New", Font.PLAIN, 28));
      pnDisplay.add(textField);
      textField.setColumns(10);

      pnInput = new JPanel();
      contentPane.add(pnInput, BorderLayout.CENTER);
      pnInput.setLayout(new GridLayout(4, 5, 5, 5));

      btn7 = new JButton("7");
      btn7.setFont(new Font("±¼¸²", Font.BOLD, 14));
      btn7.addActionListener(this);
      pnInput.add(btn7);

      btn8 = new JButton("8");
      btn8.setFont(new Font("±¼¸²", Font.BOLD, 14));
      btn8.addActionListener(this);
      pnInput.add(btn8);

      btn9 = new JButton("9");
      btn9.setFont(new Font("±¼¸²", Font.BOLD, 14));
      btn9.addActionListener(this);
      pnInput.add(btn9);

      btnAdd = new JButton("+");
      btnAdd.setFont(new Font("±¼¸²", Font.BOLD, 14));
      btnAdd.addActionListener(this);
      pnInput.add(btnAdd);

      btnClearAll = new JButton("C");
      btnClearAll.addActionListener(new ActionListener() {
         public void actionPerformed(ActionEvent arg0) {
            // reset all the data
            textField.setText("");
            num1 = NONE;
            num2 = NONE;
            operator = NONE;
         }
      });
      btnClearAll.setFont(new Font("±¼¸²", Font.BOLD, 14));
      pnInput.add(btnClearAll);

      btn4 = new JButton("4");
      btn4.setFont(new Font("±¼¸²", Font.BOLD, 14));
      btn4.addActionListener(this);
      pnInput.add(btn4);

      btn5 = new JButton("5");
      btn5.setFont(new Font("±¼¸²", Font.BOLD, 14));
      btn5.addActionListener(this);
      pnInput.add(btn5);

      btn6 = new JButton("6");
      btn6.setFont(new Font("±¼¸²", Font.BOLD, 14));
      btn6.addActionListener(this);
      pnInput.add(btn6);

      btnMinus = new JButton("-");
      btnMinus.setFont(new Font("±¼¸²", Font.BOLD, 14));
      btnMinus.addActionListener(this);
      pnInput.add(btnMinus);

      btnClearText = new JButton("CE");
      btnClearText.addActionListener(new ActionListener() {
         public void actionPerformed(ActionEvent e) {
            // reset the textfield only
            textField.setText("");
            textField.setEditable(true);
            listData.clear();
         }
      });
      btnClearText.setFont(new Font("±¼¸²", Font.BOLD, 14));
      pnInput.add(btnClearText);

      btn1 = new JButton("1");
      btn1.setFont(new Font("±¼¸²", Font.BOLD, 14));
      btn1.addActionListener(this);
      pnInput.add(btn1);

      btn2 = new JButton("2");
      btn2.setFont(new Font("±¼¸²", Font.BOLD, 14));
      btn2.addActionListener(this);
      pnInput.add(btn2);

      btn3 = new JButton("3");
      btn3.setFont(new Font("±¼¸²", Font.BOLD, 14));
      btn3.addActionListener(this);
      pnInput.add(btn3);

      btnMultiply = new JButton("x");
      btnMultiply.setFont(new Font("±¼¸²", Font.BOLD, 14));
      btnMultiply.addActionListener(this);
      pnInput.add(btnMultiply);

      btnMemSet = new JButton("MS");
      btnMemSet.setFont(new Font("±¼¸²", Font.BOLD, 14));
      pnInput.add(btnMemSet);

      btn0 = new JButton("0");
      btn0.setFont(new Font("±¼¸²", Font.BOLD, 14));
      btn0.addActionListener(this);
      pnInput.add(btn0);
      btn0.removeActionListener(this);

      btnDot = new JButton(".");
      btnDot.addActionListener(new ActionListener() {
         public void actionPerformed(ActionEvent e) {
            textField.setText(textField.getText()+".");
         }
      });
      btnDot.setFont(new Font("±¼¸²", Font.BOLD, 14));
      btn0.addActionListener(this);
      pnInput.add(btnDot);

      btnEqual = new JButton("=");
      btnEqual.setFont(new Font("±¼¸²", Font.BOLD, 14));
      btnEqual.addActionListener(this);
      pnInput.add(btnEqual);

      btnDivide = new JButton("/");
      btnDivide.setFont(new Font("±¼¸²", Font.BOLD, 14));
      btnDivide.addActionListener(this);
      pnInput.add(btnDivide);

      btnMemRead = new JButton("MR");
      btnMemRead.setFont(new Font("±¼¸²", Font.BOLD, 14));
      pnInput.add(btnMemRead);

      pnHistory = new JPanel();
      contentPane.add(pnHistory, BorderLayout.EAST);
      pnHistory.setPreferredSize(new Dimension(120, 200));
      
      
      listData = new DefaultListModel();
      list = new JList(listData);
      list.addMouseListener(new MouseAdapter() {
         public void mouseClicked(MouseEvent e) {
            int idx=list.locationToIndex(e.getPoint());
            textField.setText(listData.get(idx)+"");
            stack1.push(Double.parseDouble(listData.get(idx)));
         }
      });
      pnHistory.setLayout(new BorderLayout(5, 5));
      JScrollPane scrollPane =new JScrollPane(list);
      pnHistory.add(scrollPane);
      /*
       * End of GUI code
       */

      // initialize data
      
      stack1=new Stack<>();
      stack2=new Stack<>();
      
      num1 = NONE;
      num2 = NONE;
      operator = NONE;
      
      

   }

   // Receive the events from all buttons
   
   @Override
   public void actionPerformed(ActionEvent e) {
      // Get the string from the button
      JTextField txtDisplay = textField;
      String s = e.getActionCommand();
      
      if(s.equals(".")) {
    	  textField.setText(textField.getText()+".");
      }else
      if(s.equals("0")) {
    	  if(cur=="x"||cur=="/"||cur=="-"||cur=="+"|| cur=="=") {
  	  		txtDisplay.setText("1");
  	  		cur="";
    	  }else {	
         txtDisplay.setText(txtDisplay.getText() + "0");
    	  }
         
      
      }
      else if(s.equals("1")) {
         
    	  	if(cur=="x"||cur=="/"||cur=="-"||cur=="+"|| cur=="=") {
    	  		txtDisplay.setText("1");
    	  		cur="";
    	  	}else {
    	  
            txtDisplay.setText(txtDisplay.getText() + "1");
    	  	}
         
         
         
      }else if(s.equals("2")) {
    	  if(cur=="x"||cur=="/"||cur=="-"||cur=="+"|| cur=="=") {
  	  		txtDisplay.setText("2");
  	  		cur="";
  	  	}else {
            
            txtDisplay.setText(txtDisplay.getText() + "2");
  	  	}
         
         
      }else if(s.equals("3")) {
    	  if(cur=="x"||cur=="/"||cur=="-"||cur=="+"|| cur=="=") {
  	  		txtDisplay.setText("3");
  	  		cur="";
  	  	}else {
            txtDisplay.setText(txtDisplay.getText() + "3");
  	  	}
         
         
         
      }else if(s.equals("4")) {
    	  if(cur=="x"||cur=="/"||cur=="-"||cur=="+"|| cur=="=") {
  	  		txtDisplay.setText("4");
  	  		cur="";
  	  	}else {
            txtDisplay.setText(txtDisplay.getText() + "4");
  	  	}
         
         
         
      }else if(s.equals("5")) {
    	  if(cur=="x"||cur=="/"||cur=="-"||cur=="+"|| cur=="=") {
  	  		txtDisplay.setText("5");
  	  		cur="";
  	  	}else {
         txtDisplay.setText(txtDisplay.getText() + "5");
         }
         
         
         
      }else if(s.equals("6")) {
    	  if(cur=="x"||cur=="/"||cur=="-"||cur=="+"|| cur=="=") {
  	  		txtDisplay.setText("6");
  	  		cur="";
  	  	}else {
         txtDisplay.setText(txtDisplay.getText() + "6");
  	  	}
         
         
         
      }else if(s.equals("7")) {
    	  if(cur=="x"||cur=="/"||cur=="-"||cur=="+"|| cur=="=") {
  	  		txtDisplay.setText("7");
  	  		cur="";
  	  	}else {
            txtDisplay.setText(txtDisplay.getText() + "7");
  	  	}
         
         
         
      }else if(s.equals("8")) {
    	  if(cur=="x"||cur=="/"||cur=="-"||cur=="+"|| cur=="=") {
  	  		txtDisplay.setText("8");
  	  		cur="";	
  	  	}else {
         txtDisplay.setText(txtDisplay.getText() + "8");
  	  	}
         
         
      }else if(s.equals("9")) {
    	  if(cur=="x"||cur=="/"||cur=="-"||cur=="+" || cur=="=") {
  	  		txtDisplay.setText("9");
  	  		cur="";	
  	  	}else {

            txtDisplay.setText(txtDisplay.getText() + "9");
  	  	}
         
         
         
      }else if(s.equals("+") ) {
    	 cur="+";
         num1=txtDisplay.getText(); 
         stack1.push(Double.parseDouble(num1));
         listData.addElement(num1);
         listData.addElement("+");
         if(!stack2.empty()) {
            while(true) {
               if(stack2.empty()) {break;}
               Double n1=stack1.peek(); stack1.pop();
               Double n2=stack1.peek(); stack1.pop();
               if(stack2.peek()=="x") {stack1.push(n1*n2); stack2.pop();}
               else if(stack2.peek()=="+") { stack1.push(n1+n2); stack2.pop();}
               else if(stack2.peek()=="-") { stack1.push(n2-n1); stack2.pop();}
               else{
                  stack1.push(n2/n1);
                  stack2.pop();
               }
            }
            stack2.push("+");
         }else {
            stack2.push("+");
         }
         
         
      }else if(s.equals("x")){
    	  cur="x";
         num1= txtDisplay.getText();
         stack1.push(Double.parseDouble(num1));
         listData.addElement(num1);
         listData.addElement("x");
         if(!stack2.empty()) {
            while(!stack2.empty()) {
               if(stack2.peek()=="+" || stack2.peek()=="-") break;
               Double n1=stack1.peek(); stack1.pop();
               Double n2=stack1.peek(); stack1.pop();
               if(stack2.peek()=="/") {stack1.push(n2/n1); stack2.pop();}
               else if(stack2.peek()=="x") {stack1.push(n2*n1); stack2.pop();}
            }
            stack2.push("x");
         }
         else {
            stack2.push("x");
         }
         
         
      }else if(s.equals("/")){
    	  cur="/";
         num1= txtDisplay.getText();
         stack1.push(Double.parseDouble(num1));
         listData.addElement(num1);
         listData.addElement("/");
         if(!stack2.empty()) {
            while(!stack2.empty()) {
               if(stack2.peek()=="+" || stack2.peek()=="-") break;
               Double n1=stack1.peek(); stack1.pop();
               Double n2=stack1.peek(); stack1.pop();
               if(stack2.peek()=="x") {stack1.push(n2*n1); stack2.pop();}
               else if(stack2.peek()=="/") {stack1.push(n2/n1); stack2.pop();}
            }
            stack2.push("/");
         }
         else {
            stack2.push("/");
         }
         
         
      }else if(s.equals("-")){
    	  cur="-";
         num1= txtDisplay.getText();
         stack1.push(Double.parseDouble(num1));
         listData.addElement(num1);
         listData.addElement("-");
         if(!stack2.empty()) {
            while(true) {
               if(stack2.empty()) {break;}
               Double n1=stack1.peek(); stack1.pop();
               Double n2=stack1.peek(); stack1.pop();
               if(stack2.peek()=="x") {stack1.push(n1*n2); stack2.pop();}
               else if(stack2.peek()=="+") { stack1.push(n1+n2); stack2.pop();}
               else if(stack2.peek()=="-") { stack1.push(n2-n1); stack2.pop();}
               else{
                  stack1.push(n2/n1);
                  stack2.pop();
               }
            }
            stack2.push("-");
         }else {
            stack2.push("-");
         }
      }
      else if(s.equals("=") ) { 
    	 cur="=";
    	 Double lastval=Double.parseDouble(txtDisplay.getText());
         stack1.push(lastval);
         while(!stack2.empty()){
            operator=stack2.peek();
            
            if(operator=="+") {
               Double n1=stack1.peek(); stack1.pop();
               Double n2=stack1.peek(); stack1.pop();
               stack1.push(n1+n2); 
               stack2.pop();
               
            }else if(operator=="x") {
               Double n1=stack1.peek(); stack1.pop();
               Double n2=stack1.peek(); stack1.pop();
               stack1.push(n1*n2);
               stack2.pop();
               
            }else if(operator=="-") {
               Double n1=stack1.peek(); stack1.pop();
               Double n2=stack1.peek(); stack1.pop();
               
               stack1.push(n2-n1);
               stack2.pop();
               
            }else if(operator=="/") {
               Double n1=stack1.peek(); stack1.pop();
               Double n2=stack1.peek(); stack1.pop();
               stack1.push(n2/n1);
               stack2.pop();
            }   
         }
         
         listData.addElement(txtDisplay.getText());
         listData.addElement("=");
         DecimalFormat df=new DecimalFormat("#.#####");
         listData.addElement(df.format(stack1.peek())+"");
         txtDisplay.setText(df.format(stack1.peek())+"");
         stack1.clear(); stack2.clear();
         
      }
   
   }
   
}