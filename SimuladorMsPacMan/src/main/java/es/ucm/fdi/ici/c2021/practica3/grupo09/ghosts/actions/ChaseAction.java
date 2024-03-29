package es.ucm.fdi.ici.c2021.practica3.grupo09.ghosts.actions;

import es.ucm.fdi.ici.c2021.practica3.grupo09.MapaInfoGhost;
import es.ucm.fdi.ici.c2021.practica3.grupo09.MapaInfoGhost.interseccion;
import es.ucm.fdi.ici.rules.Action;
import jess.Fact;
import pacman.game.Constants.DM;
import pacman.game.Constants.GHOST;
import pacman.game.Constants.MOVE;
import pacman.game.Game;

public class ChaseAction implements Action {

	DM CONSTANT_MEASURE_DISTANCE = DM.EUCLID;
	DM CONSTANT_MEASURE_DIRECTION = DM.EUCLID;

	private MapaInfoGhost mapa;
	GHOST ghostType;
	
	public ChaseAction( GHOST ghost, MapaInfoGhost mapa_ ) {
		this.ghostType = ghost;
		this.mapa= mapa_;
	}

	public void parseFact(Fact actionFact) {
		
	}

	// Se dirige a la interseccion donde es mas probable que se dirija el PacMan y que yo este más cerca
	@Override
	public MOVE execute(Game game) {
		if (game.doesGhostRequireAction(ghostType)) { //if it requires an action	
			int myPos = game.getGhostCurrentNodeIndex(ghostType);
			MOVE mylastMove = game.getGhostLastMoveMade(ghostType);
			int destino = 0, destinoFinal = -1;
			float valorMasAlto = -10, valor = 0;

			interseccion proximaInterseccionPacman, interseccionActual = mapa.getInterseccionActual();
				if(mapa.getCheckLastModeMade()) proximaInterseccionPacman = interseccionActual;
				else proximaInterseccionPacman = mapa.getInterseccion(interseccionActual.destinos.get(mapa.getUltimoMovReal()));

			//Miro el movimiento mas logico para el pacman y me dirigo hacia ahi
			for (MOVE m : proximaInterseccionPacman.destinos.keySet()) {
				//El pacman no puede dar marcha atras 
				if(proximaInterseccionPacman.destinos.get(m) == interseccionActual.identificador)
					continue;
				//Si estoy en esa interseccion, voy hacia el pacman
				if(myPos == proximaInterseccionPacman.destinos.get(m)){
					destinoFinal = proximaInterseccionPacman.identificador;
					break;
				}

				destino = proximaInterseccionPacman.destinos.get(m);

				//Valor = pills del camino / (distancia a la siguiente interseccion + distancia ghost a la interseccion)
				double distanceG = game.getDistance(myPos, proximaInterseccionPacman.identificador, mylastMove, CONSTANT_MEASURE_DISTANCE);
				valor = (float)proximaInterseccionPacman.pills.get(m) / 
						(float)(proximaInterseccionPacman.distancias.get(m) + distanceG);

 				// Si hay un fantasma que se dirige hacia ahí, y llega antes, yo no voy ahí
				for (GHOST g : mapa.destinosGhosts.keySet()) {
					//si existe un destino && no soy yo && si el destino es el mismo && llega antes que yo
				 	if (mapa.destinosGhosts.get(g) != null && g != ghostType && mapa.destinosGhosts.get(g).identificador == destino
				 		&& distanceG < game.getDistance(myPos, proximaInterseccionPacman.destinos.get(m), mylastMove, CONSTANT_MEASURE_DISTANCE)) {
				 		valor--;
				 		break;
				 	}
				}
				if (valor > valorMasAlto) {
					valorMasAlto = valor;
					destinoFinal = destino;
				}
			}

			mapa.destinosGhosts.put(ghostType, mapa.getInterseccion(destinoFinal));

			return game.getNextMoveTowardsTarget(myPos, destinoFinal, mylastMove, CONSTANT_MEASURE_DIRECTION);
        }
		else 
			return MOVE.NEUTRAL;
	}
}
