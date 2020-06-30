package miniproject;

import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;

public class KeyListener extends KeyAdapter {
 
	
	@Override
	public void keyPressed(KeyEvent e) {
		if(Game.game==null) {
			return;
		}
		
		
		if(e.getKeyCode()==KeyEvent.VK_S) {
			Game.game.pressS();
		}
		else if(e.getKeyCode()==KeyEvent.VK_D) {
			Game.game.pressD();
		}
		else if(e.getKeyCode()==KeyEvent.VK_F) {
			Game.game.pressF();
		}
		else if(e.getKeyCode()==KeyEvent.VK_SPACE) {
			Game.game.pressSpace();
			
        }else if(e.getKeyCode()==KeyEvent.VK_J) {
        	Game.game.pressJ();
        	
        }else if(e.getKeyCode()==KeyEvent.VK_K) {
        	Game.game.pressK();
        	
        }else if(e.getKeyCode()==KeyEvent.VK_L) {
        	Game.game.pressL();
        	
        }
		
	}
	
	
	public void keyReleased(KeyEvent e) {
		
		if(Game.game==null) {
			return;
		}
		
		
		if(e.getKeyCode()==KeyEvent.VK_S) {
			Game.game.releaseS();
		}
		else if(e.getKeyCode()==KeyEvent.VK_D) {
			Game.game.releaseD();
		}
		else if(e.getKeyCode()==KeyEvent.VK_F) {
			Game.game.releaseF();
		}
		else if(e.getKeyCode()==KeyEvent.VK_SPACE) {
			Game.game.releaseSpace();
			
        }else if(e.getKeyCode()==KeyEvent.VK_J) {
        	Game.game.releaseJ();
        	
        }else if(e.getKeyCode()==KeyEvent.VK_K) {
        	Game.game.releaseK();
        	
        }else if(e.getKeyCode()==KeyEvent.VK_L) {
        	Game.game.releaseL();
        	
        }
		
		
		
	}
	
	
	
}
