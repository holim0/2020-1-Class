package miniproject;



import java.awt.Graphics;

import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

import javax.imageio.ImageIO;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JLayeredPane;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JPasswordField;

import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.Font;
import javax.swing.SwingConstants;
import javax.swing.JRadioButton;
import javax.swing.JTextField;

public class Register extends JFrame {
	private JLabel lblNewLabel;
	private JLabel lblPassword;
	private JTextField textField;
	private JTextField textField_1;
	private JButton btnNewButton;
	private JButton btnCancel;
	private JLabel lblNewLabel_1;
	private JTextField textField_2;
    // 버튼이 눌러지면 만들어지는 새 창을 정의한 클래스
    
	public Register() {
		setTitle("Are you sure?");
		
        
        JPanel NewWindowContainer = new JPanel();
        setContentPane(NewWindowContainer);
        NewWindowContainer.setLayout(null);
        
        lblNewLabel = new JLabel("ID");
        lblNewLabel.setBounds(45, 92, 57, 15);
        NewWindowContainer.add(lblNewLabel);
        
        lblPassword = new JLabel("PASSWORD");
        lblPassword.setBounds(45, 149, 114, 15);
        NewWindowContainer.add(lblPassword);
        
        textField = new JTextField();
        textField.setBounds(186, 89, 198, 21);
        NewWindowContainer.add(textField);
        textField.setColumns(10);
        
        textField_1 = new JPasswordField();
        textField_1.setColumns(10);
        textField_1.setBounds(186, 146, 198, 21);
        NewWindowContainer.add(textField_1);
        
        btnNewButton = new JButton("SAVE");
        btnNewButton.addActionListener(new ActionListener() {
        	public void actionPerformed(ActionEvent e) {
        		Connection conn;
        		try {
        			String dbURL="jdbc:mysql://localhost:3306/Register?useUnicode=true&useJDBCCompliantTimezoneShift=true&useLegacyDatetimeCode=false&serverTimezone=UTC";
        			String dbID="root";
        			String dbPassword="dlgmlwp123";
        			Class.forName("com.mysql.cj.jdbc.Driver");
        			conn=DriverManager.getConnection(dbURL, dbID, dbPassword);
        			String id2=textField.getText(); String pass2=textField_1.getText();
        			String userName= textField_2.getText();
        			String sql="insert into user values("+ "'"+ userName + "',"+"'"+ id2 +"'"+ ","+"'"+pass2+"');";
        			PreparedStatement stm= conn.prepareStatement(sql);
        			stm.execute();
        			stm.close();
        			
        		}catch(Exception k){
        			k.printStackTrace();
        		}
        		
        		setVisible(false);
        	}
        });
        btnNewButton.setBounds(103, 228, 97, 23);
        NewWindowContainer.add(btnNewButton);
        
        btnCancel = new JButton("CANCEL");
        btnCancel.addActionListener(new ActionListener() {
        	public void actionPerformed(ActionEvent e) {
        		setVisible(false);
        	}
        });
        btnCancel.setBounds(272, 228, 97, 23);
        NewWindowContainer.add(btnCancel);
        
        lblNewLabel_1 = new JLabel("NAME");
        lblNewLabel_1.setBounds(45, 37, 57, 15);
        NewWindowContainer.add(lblNewLabel_1);
        
        textField_2 = new JTextField();
        textField_2.setText("");
        textField_2.setBounds(186, 34, 198, 21);
        NewWindowContainer.add(textField_2);
        textField_2.setColumns(10);
        
        setSize(474,328);
        setResizable(false);
        setLocationRelativeTo(null);
        setVisible(true);
        

        
        
    
        
        
        
        
    }
}	
	
