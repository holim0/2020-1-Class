package miniproject;

import static miniproject.Game.LoginButton;
import static miniproject.Game.lblNewLabel;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JPasswordField;
import javax.swing.JTextField;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.Statement;

public class Login extends JFrame {
	private JLabel lblNewLabel;
	private JLabel lblPassword;
	private JTextField textField;
	private JPasswordField textField_1;
	private JButton btnNewButton;
	private JButton btnCreate;
    // 버튼이 눌러지면 만들어지는 새 창을 정의한 클래스
    
	private int Login_check=0;
	
	
	
	
	public Login() {
		setTitle("LOGIN");
		
        
        JPanel NewWindowContainer = new JPanel();
        setContentPane(NewWindowContainer);
        NewWindowContainer.setLayout(null);
        
        lblNewLabel = new JLabel("UserID");
        lblNewLabel.setBounds(158, 34, 89, 15);
        NewWindowContainer.add(lblNewLabel);
        
        lblPassword = new JLabel("PassWord");
        lblPassword.setBounds(145, 132, 89, 15);
        NewWindowContainer.add(lblPassword);
        
        textField = new JTextField();
        
        textField.setBounds(79, 61, 200, 33);
        NewWindowContainer.add(textField);
        textField.setColumns(10);
        
        textField_1 = new JPasswordField();
        
        textField_1.setColumns(10);
        textField_1.setBounds(79, 157, 200, 33);
        NewWindowContainer.add(textField_1);
        
        btnNewButton = new JButton("Login");
        
        	
        btnNewButton.addActionListener(new ActionListener() {
        	public void actionPerformed(ActionEvent e) {
        		
        		String id=textField.getText();
        		String pw=textField_1.getText();
        		
        		int result=1;
        		Statement stmt=null;
        		ResultSet rs= null;
        		Connection conn;
        		String sql=null;
        		try {
        			String dbURL="jdbc:mysql://localhost:3306/Register?useUnicode=true&useJDBCCompliantTimezoneShift=true&useLegacyDatetimeCode=false&serverTimezone=UTC";
        			String dbID="root";
        			String dbPassword="dlgmlwp123";
        			Class.forName("com.mysql.cj.jdbc.Driver");
        			conn=DriverManager.getConnection(dbURL, dbID, dbPassword);
        			stmt=conn.createStatement();
        			sql="select * from user where userID like"+" '"+id+"';";
        			rs=stmt.executeQuery(sql);
        			
        			if(rs.next()==false || (id.isEmpty())==true) {
        				result=1;
        			}else {
        				sql="select * from (select * from user where userID='" + id + "')t";
        				rs=stmt.executeQuery(sql);	
        				while(rs.next()==true) {
        					if(rs.getString(3).equals(pw)) {
        						result=0;
        					}else {
        						result=1;
        					}
        				}
        				
        			}
        			        			
        			
        		}catch(Exception k) {
        			k.printStackTrace();
        		}
        		
        		
        		if(result==0) {
        			new LoginSucess();
        			setVisible(false);
        			LoginButton.setVisible(false);
        			
        			
        		}else {
        			new LoginFail();
        			textField.setText("");
        			textField_1.setText("");
        			
        		}
        		
        		
        	}
        });
        btnNewButton.setBounds(103, 223, 144, 23);
        NewWindowContainer.add(btnNewButton);
        
        btnCreate = new JButton("Create Account");
        btnCreate.addActionListener(new ActionListener() {
        	public void actionPerformed(ActionEvent e) {
        		new Register();
        	}
        });
        btnCreate.setBounds(103, 272, 144, 23);
        NewWindowContainer.add(btnCreate);
        
        setSize(358,389);
        setResizable(false);
        setLocationRelativeTo(null);
        setVisible(true);
        

        
    
        
        
    }
	
	
	


	
}	
	