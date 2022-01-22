package es.ucm.fdi.tfg.robotpacman.pruebas;

import java.io.IOException;

import com.fazecast.jSerialComm.SerialPort;

public class main {

	public static void main(String[] args) throws IOException, InterruptedException{
		System.out.println("Vamos a inicializar el arduino");
	
		SerialPort sp = SerialPort.getCommPort("/dev/ttyACM9"); //TODO esto deberia estar parametrizado
		sp.setComPortParameters(9600, 8, 1, 0);
		sp.setComPortTimeouts(SerialPort.TIMEOUT_READ_BLOCKING | SerialPort.TIMEOUT_WRITE_BLOCKING, 0, 0);
		

		
		if(sp.openPort()) {
			System.out.println("Puerto abierto");
			sp.getInputStream().close();
			//Thread.sleep(5000); //Tiempo para que se inicialice el arduino
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
			int byteRead = 0;
			try {
				byteRead = sp.getInputStream().read();
			} catch(IOException e) {
				System.out.println("ERROR: Ha fallado la lectura de datos");
			}
			
			if(byteRead == 10) {
				System.out.println("Dato correcto");
				start = true;
			}
			else
				System.out.println("Dato incorrecto");
		}
		
		
		try {
			Integer i = 1;
			sp.getOutputStream().write(i.byteValue());
			sp.getOutputStream().flush();
			System.out.println("DatoMandado");
			
		} catch (IOException e) {
			e.printStackTrace();
			System.out.println("ERROR: No se ha podido mandar el dato");
		}
			
		if(sp.closePort()) {
			System.out.println("Puerto cerrado");	
		}
		else {
			System.out.println("ERROR: no se ha podido cerrar el puerto");		
		}
	}

}
