package main;

import java.io.IOException;

import com.fazecast.jSerialComm.SerialPort;

import communication.CommunicationManager;
import communication.JAVA_MESSAGE;
import pacman.Executor;
import pacman.controllers.GhostController;
import pacman.controllers.GhostsRandom;
import pacman.controllers.HumanController;
import pacman.controllers.KeyBoardInput;
import pacman.controllers.PacmanController;
import pacman.game.internal.POType;


public class main {

	public static void main(String[] args) throws IOException, InterruptedException{		
		
		/*System.out.println("Vamos a inicializar el arduino");
	
		SerialPort sp = SerialPort.getCommPort("/dev/ttyACM0"); //TODO esto deberia estar parametrizado
		sp.setComPortParameters(9600, 8, 1, 0);
		sp.setComPortTimeouts(SerialPort.TIMEOUT_READ_BLOCKING | SerialPort.TIMEOUT_WRITE_BLOCKING, 0, 0);
		

		
		if(sp.openPort()) {
			System.out.println("Puerto abierto");
			sp.getInputStream().close();			
			//Thread.sleep(2000); //Tiempo para que se inicialice el arduino
		}
		else {
			System.out.println("ERROR: No se pudo abrir el puerto");
			return;
		}
		
		
		CommunicationManager.MessageSender.SetSerialPort(sp);
		
		try {
			sp.getInputStream().close();
		} catch (IOException e1) {
			e1.printStackTrace();
			System.out.println("ERROR: No se ha podido limpiar el InputStream");
		}
		
		boolean start = false;
		
		
		while(!start) {
			CommunicationManager.MessageSender.SendMsg(JAVA_MESSAGE.SYNC_ATTEMP);
			
			if(CommunicationManager.MessageSender.ReadMsg() == JAVA_MESSAGE.SYNC)	
				start = true;			
		}
		

		System.out.println("SINCRONIZADOS");	
		*/
		
		//INICIAR EL SIMULADOR
		startExecution();
		System.out.println("Emepzamos el simulador");	
		
		
		/*
		sp.getInputStream().close(); //limpiamos antes de cerrar para cuando se vuelva a abrir	
		if(sp.closePort()) {
			System.out.println("Puerto cerrado");	
		}
		else {
			System.out.println("ERROR: no se ha podido cerrar el puerto");		
		}*/
	}
	
	
	
	static void startExecution() {
        Executor executor = new Executor.Builder()
                .setTickLimit(4000)
                .setTimeLimit(60)
                .setGhostPO(false)
                .setPacmanPO(false)
                .setPacmanPOvisual(false) 
                .setPOType(POType.LOS)
                .setVisual(true)
                .setScaleFactor(3.0)
                .build();

        PacmanController pacMan = //new pacman.controllers.examples.PacManRandom();
        						new HumanController(new KeyBoardInput());
        GhostController ghosts = new GhostsRandom();
        MsPacManObserver observer = new MsPacManObserver();
       
        
        System.out.println( 
        		executor.runGame(pacMan, ghosts, 40, observer)
        );
        System.out.println("CERRADO");    
	}
}
