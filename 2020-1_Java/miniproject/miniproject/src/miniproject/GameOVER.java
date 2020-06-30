package miniproject;

import javax.swing.JFrame;
import javax.swing.JLabel;
import java.awt.BorderLayout;
import java.awt.Font;
import javax.swing.JButton;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

public class GameOVER extends JFrame {
	private JLabel lblNewLabel;
	private JButton btnNewButton;
	public GameOVER() {
		getContentPane().setLayout(null);
		
		lblNewLabel = new JLabel("Game Over!");
		lblNewLabel.setFont(new Font("210 ∏«πﬂ¿«√ª√· L", Font.PLAIN, 20));
		lblNewLabel.setBounds(99, 29, 143, 64);
		getContentPane().add(lblNewLabel);
		
		btnNewButton = new JButton("OK");
		btnNewButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				Game.backToMain2();
				setVisible(false);
				
			}
		});
		btnNewButton.setBounds(115, 117, 97, 23);
		getContentPane().add(btnNewButton);
		
		setSize(358,389);
        setResizable(false);
		setLocationRelativeTo(null);
        setVisible(true);
	}
}
