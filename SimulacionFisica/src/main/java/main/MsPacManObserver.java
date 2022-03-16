package main;

import java.util.EnumMap;

import communication.CommunicationManager;
import communication.JAVA_MESSAGE;
import pacman.game.Constants.GHOST;
import pacman.game.Constants.MOVE;
import pacman.game.GameObserver;

public class MsPacManObserver implements GameObserver{
	private MOVE lastPacManMove = MOVE.NEUTRAL;
	
	
	public void pacManMove(MOVE move, boolean inJunction) {
		if(move != lastPacManMove || inJunction) {
			System.out.println(move);
			CommunicationManager.MessageSender.SendMsg(fromMoveToJavaMessagePacMan(move));
			lastPacManMove = move;
		}
	}

	public void ghostsMove(EnumMap<GHOST, MOVE> moves, EnumMap<GHOST, Boolean> inJunction) {
		//System.out.println("Ghost move");
		
	}
	
	public void gameStarted() {
        CommunicationManager.MessageSender.SendMsg(JAVA_MESSAGE.START);
        System.out.println("Mandamos mensaje de empezar la partida");
	}
	
	private JAVA_MESSAGE fromMoveToJavaMessagePacMan(MOVE move) {
		switch(move) {
		case UP:
			return JAVA_MESSAGE.PAC_MAN_UP;
		case DOWN:
			return JAVA_MESSAGE.PAC_MAN_DOWN;
		case RIGHT:
			return JAVA_MESSAGE.PAC_MAN_RIGHT;
		case LEFT:
			return JAVA_MESSAGE.PAC_MAN_LEFT;
		}
		
		//nunca llegará aquí en teoría
		return JAVA_MESSAGE.PAC_MAN_NEUTRAL;
	}

}

