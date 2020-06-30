package miniproject;

import javax.swing.JFrame;
import javax.swing.JLabel;
import java.awt.BorderLayout;
import java.awt.GridBagLayout;
import java.awt.Font;
import javax.swing.JButton;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

public class LoginSucess extends JFrame {
	private JLabel lblNewLabel;
	private JButton btnNewButton;
	public LoginSucess() {
		getContentPane().setLayout(null);
		
		lblNewLabel = new JLabel("Login Success!");
		lblNewLabel.setFont(new Font("a파도소리", Font.BOLD, 17));
		lblNewLabel.setBounds(27, 10, 144, 104);
		getContentPane().add(lblNewLabel);
		
		btnNewButton = new JButton("OK");
		btnNewButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				setVisible(false);
				
			}
		});
		btnNewButton.setBounds(50, 103, 97, 23);
		getContentPane().add(btnNewButton);
		
		
		
		
		
		setSize(200, 200);
		setResizable(false);
        setLocationRelativeTo(null);
        setVisible(true);
		
	}
	
	
	
}
