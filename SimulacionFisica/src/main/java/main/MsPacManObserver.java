package main;

import java.util.EnumMap;

import pacman.game.Constants.GHOST;
import pacman.game.Constants.MOVE;
import pacman.game.GameObserver;

public class MsPacManObserver implements GameObserver{

	public void pacManMove(MOVE move, boolean inJunction) {
		// TODO Auto-generated method stub
		if(inJunction) {
			System.out.println("AAAAAAAAA");
		}
		
	}

	public void ghostsMove(EnumMap<GHOST, MOVE> moves, EnumMap<GHOST, Boolean> inJunction) {
		// TODO Auto-generated method stub
		//System.out.println("Ghost move");
		
	}

}

