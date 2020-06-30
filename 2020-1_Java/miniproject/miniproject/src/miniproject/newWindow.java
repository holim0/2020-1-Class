package miniproject;

import java.awt.Graphics;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JLayeredPane;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.Font;
import javax.swing.SwingConstants;

public class newWindow extends JFrame {
	private JButton btnNewButton;
	private JButton btnYes;
    // 버튼이 눌러지면 만들어지는 새 창을 정의한 클래스
    
	public newWindow() {
		setTitle("Are you sure?");
		
        
        JPanel NewWindowContainer = new JPanel();
        setContentPane(NewWindowContainer);
        NewWindowContainer.setLayout(null);
        
        JLabel NewLabel = new JLabel("  Are you sure?");
        NewLabel.setFont(new Font("10X10 Bold", Font.PLAIN, 17));
        NewLabel.setBounds(106, 32, 123, 40);
        
        NewWindowContainer.add(NewLabel);
        
        btnNewButton = new JButton("NO!");
        btnNewButton.setFont(new Font("10X10 Bold", Font.PLAIN, 15));
        btnNewButton.addActionListener(new ActionListener() {
        	public void actionPerformed(ActionEvent e) {
        		setVisible(false);
        	}
        });
        btnNewButton.setBounds(182, 150, 118, 40);
        NewWindowContainer.add(btnNewButton);
        
        btnYes = new JButton("YES!");
        btnYes.addActionListener(new ActionListener() {
        	public void actionPerformed(ActionEvent e) {
        		System.exit(0);
        	}
        });
        btnYes.setFont(new Font("10X10 Bold", Font.PLAIN, 15));
        btnYes.setBounds(33, 150, 118, 40);
        NewWindowContainer.add(btnYes);
        
        setSize(334,245);
        setResizable(false);
        setLocationRelativeTo(null);
        setVisible(true);
        

        
        
    
        
        
        
        
    }
}	
	