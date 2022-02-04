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
    	
    	if(game.isJunction(game.getPacmanCurrentNodeIndex())) {
    		System.out.println("Estamos en una interseccion");
    		CommunicationManager.MessageSender.SendMsg(JAVA_MESSAGE.OK);
    		try {
				Thread.sleep(500);
			} catch (InterruptedException e) {
				System.out.println("El sleep de la interseccion en el PacMan ha fallado");
				e.printStackTrace();
			}
    	}
    	
    	switch (input.getKey()) {
            case KeyEvent.VK_UP:
                return MOVE.UP;
            case KeyEvent.VK_RIGHT:
                return MOVE.RIGHT;
            case KeyEvent.VK_DOWN:
                return MOVE.DOWN;
            case KeyEvent.VK_LEFT:
                return MOVE.LEFT;
            default:
                return MOVE.NEUTRAL;
        }
    }
}