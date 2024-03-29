package es.ucm.fdi.ici.c2021.practica3.grupo09.ghosts.actions;

import java.util.Vector;

import es.ucm.fdi.ici.c2021.practica3.grupo09.MapaInfoGhost;
import es.ucm.fdi.ici.c2021.practica3.grupo09.MapaInfoGhost.interseccion;
import es.ucm.fdi.ici.rules.Action;
import jess.Fact;
import pacman.game.Constants.DM;
import pacman.game.Constants.GHOST;
import pacman.game.Constants.MOVE;
import pacman.game.Game;

public class GoToActiveGhostAction implements Action {

	private MapaInfoGhost mymap;
	GHOST ghost;

	public GoToActiveGhostAction(GHOST ghost, MapaInfoGhost map) {
		this.ghost = ghost;
		this.mymap = map;
	}

	public void parseFact(Fact actionFact){
		
	}

	private Vector<GHOST> activeGhosts(Game game) {
		Vector<GHOST> activeGhosts = new Vector<GHOST>();
		for (GHOST ghost : GHOST.values()) {
			if (!game.isGhostEdible(ghost) && game.getGhostLairTime(ghost) <= 0)
				activeGhosts.add(ghost);
		}
		return activeGhosts;
	}

	private double nearestGhostDistance(int[] pos, MOVE m, Game game) {


		double nearestDist = Double.MAX_VALUE;
		for (int p : pos) {
			double aux = game.getDistance(game.getGhostCurrentNodeIndex(ghost), p, m, DM.EUCLID);
			if (aux < nearestDist) {
				nearestDist = aux;
			}
		}

		return nearestDist;
	}

	@Override
	public MOVE execute(Game game) {

		//No hace falta comprobar que el vector de activos est� vac�o ya que si estamos en 
		//este estado existe alguno que est� a la distancia suficiente para perseguirlo
		Vector<GHOST> actives = activeGhosts(game);
		MOVE best = MOVE.NEUTRAL;
		interseccion inter = mymap.getInterseccion(game.getGhostCurrentNodeIndex(ghost));
		if (inter != null) {
			int[] posGhosts = new int[3];
			int i = 0;
			i = 0;
			// rellenamos las posiciones de los fantasmas activos para ver a qu� distancia
			// esta el m�s cercano y elegirlo a �l para perseguirlo
			for (GHOST gh : actives) {
				if (gh == ghost)
					continue;
				posGhosts[i] = game.getGhostCurrentNodeIndex(gh);
				i++;
			}
			MOVE prohibido = game.getApproximateNextMoveTowardsTarget(game.getGhostCurrentNodeIndex(ghost),
					game.getPacmanCurrentNodeIndex(), game.getGhostLastMoveMade(ghost),DM.EUCLID);
			double nearest = 0;
			// elegimos el fantasma m�s cercano buscando en todas direcciones excepto
			// en la prohibida
			for (MOVE move : inter.destinos.keySet()) {
				if (move == prohibido)
					continue;
				double aux = nearestGhostDistance(posGhosts, move, game);
				if (aux < nearest) {
					nearest = aux;
					best = move;

				}
			}
		}
		return best;

	}
}
