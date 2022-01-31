package es.ucm.fdi.tfg.robotpacman.pruebas;

import java.io.IOException;

import com.fazecast.jSerialComm.SerialPort;

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
		
		
		try {
			sp.getInputStream().close();
		} catch (IOException e1) {
			e1.printStackTrace();
			System.out.println("ERROR: No se ha podido limpiar el InputStream");
		}
		
		boolean start = false;
		
		
		while(!start) {
			
			try {
				Integer i = 20;
				sp.getOutputStream().write(i.byteValue());
				sp.getOutputStream().flush();
				
			} catch (IOException e) {
				e.printStackTrace();
				System.out.println("ERROR: No se ha podido mandar el dato");
			}
						
			try {
				int byteRead = 0;
				byteRead = sp.getInputStream().read();
				
				if(byteRead == 10) {
					start = true;
				}
			} catch(IOException e) {
				System.out.println("ERROR: Ha fallado la lectura de datos");
			}
			
		}

		System.out.println("SINCRONIZADOS");	

		sp.getInputStream().close(); //limpiamos antes de cerrar para cuando se vuelva a abrir	
		if(sp.closePort()) {
			System.out.println("Puerto cerrado");	
		}
		else {
			System.out.println("ERROR: no se ha podido cerrar el puerto");		
		}
	}

}
