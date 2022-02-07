package pacman.controllers;

import java.awt.event.KeyEvent;

import es.ucm.fdi.tfg.robotpacman.pruebas.CommunicationManager;
import es.ucm.fdi.tfg.robotpacman.pruebas.JAVA_MESSAGE;
import pacman.game.Constants.MOVE;
import pacman.game.Game;

/*
 * Allows a human player to play the game using the arrow key of the keyboard.
 */
public class HumanController extends PacmanController {
    public KeyBoardInput input;

    public HumanController(KeyBoardInput input) {
        this.input = input;
    }

    public KeyBoardInput getKeyboardInput() {
        return input;
    }

    @Override
    public MOVE getMove(Game game, long dueTime) {
        //        System.out.println("Returned: " + input.getKey());    
    	
    	//TODO esto deberia estar en una clase padre o algo
    	if(game.isJunction(game.getPacmanCurrentNodeIndex())) {
    		
    		MOVE move;
    		
    		switch (input.getKey()) {
		        case KeyEvent.VK_UP:{
		            move = MOVE.UP;		            
		    		CommunicationManager.MessageSender.SendMsg(JAVA_MESSAGE.PAC_MAN_UP);	
		    		break;
		        }
		        case KeyEvent.VK_RIGHT:{
		            move = MOVE.RIGHT;
		    		CommunicationManager.MessageSender.SendMsg(JAVA_MESSAGE.PAC_MAN_RIGHT);		
		    		break;        	
		        }
		        case KeyEvent.VK_DOWN:{
		            move = MOVE.DOWN;
		    		CommunicationManager.MessageSender.SendMsg(JAVA_MESSAGE.PAC_MAN_DOWN);	
		    		break;	        	
		        }
		        case KeyEvent.VK_LEFT:{
		            move = MOVE.LEFT;
		    		CommunicationManager.MessageSender.SendMsg(JAVA_MESSAGE.PAC_MAN_LEFT);	
		    		break;	        	
		        }
		        default:{
		        	move = MOVE.NEUTRAL;
		        	CommunicationManager.MessageSender.SendMsg(JAVA_MESSAGE.PAC_MAN_NEUTRAL);	
		        	break;
		        }
    		}
    		
    		try {
				Thread.sleep(250);
			} catch (InterruptedException e) {
				System.out.println("El sleep de la interseccion en el PacMan ha fallado");
				e.printStackTrace();
			}
    		
    		return move;
    	}
    	else return MOVE.NEUTRAL;
    }
}