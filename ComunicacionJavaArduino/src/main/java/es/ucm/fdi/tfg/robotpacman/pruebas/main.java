package es.ucm.fdi.tfg.robotpacman.pruebas;

import java.io.IOException;

import com.fazecast.jSerialComm.SerialPort;

/*import pacman.Executor;
import pacman.controllers.GhostController;
import pacman.controllers.GhostsRandom;
import pacman.controllers.HumanController;
import pacman.controllers.KeyBoardInput;
import pacman.controllers.PacmanController;
import pacman.game.internal.POType;*/

public class main {

	public static void main(String[] args) throws IOException, InterruptedException{		
		
		System.out.println("Vamos a inicializar el arduino");
	
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
			
			try {
				JAVA_MESSAGE msg = JAVA_MESSAGE.SYNC_ATTEMP;				
				sp.getOutputStream().write((byte)msg.ordinal());
				sp.getOutputStream().flush();
				
			} catch (IOException e) {
				e.printStackTrace();
				System.out.println("ERROR: No se ha podido mandar el dato");
			}
						
			try {
				int byteRead = 0;
				byteRead = sp.getInputStream().read();
				if(byteRead < JAVA_MESSAGE.values().length)
				{
					JAVA_MESSAGE msg = JAVA_MESSAGE.values()[byteRead];
					
					if(msg == JAVA_MESSAGE.SYNC) {
						start = true;
					}
				}
					
			} catch(IOException e) {
				System.out.println("ERROR: Ha fallado la lectura de datos");
			}
			
		}

		System.out.println("SINCRONIZADOS");	
		
		
		//INICIAR EL SIMULADOR
		
		

		sp.getInputStream().close(); //limpiamos antes de cerrar para cuando se vuelva a abrir	
		if(sp.closePort()) {
			System.out.println("Puerto cerrado");	
		}
		else {
			System.out.println("ERROR: no se ha podido cerrar el puerto");		
		}
	}
	
	
	
	/*void startExecution() {
	        Executor executor = new Executor.Builder()
	                .setTickLimit(4000)
	                .setTimeLimit(40)
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
	        
	        System.out.println( 
	        		executor.runGame(pacMan, ghosts, 40)
	        );	    
	}*/
}
