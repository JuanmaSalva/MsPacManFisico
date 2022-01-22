package es.ucm.fdi.tfg.robotpacman.pruebas;

import java.io.IOException;

import com.fazecast.jSerialComm.SerialPort;

public class main {

	public static void main(String[] args){
		System.out.println("Vamos a inicializar el arduino");
	
		SerialPort sp = SerialPort.getCommPort("/dev/ttyACM1"); //TODO esto deberia estar parametrizado
		sp.setComPortParameters(9600, 8, 1, 0);
		sp.setComPortTimeouts(SerialPort.TIMEOUT_WRITE_BLOCKING, 0, 0);
		
		if(sp.openPort()) {
			System.out.println("Puerto abierto");
		}
		else {
			System.out.println("No se pudo abrir el puerto");
			return;
		}
		
		try {
			for(Integer i =0; i < 5; ++i) {
				sp.getOutputStream().write(i.byteValue());
				sp.getOutputStream().flush();
				System.out.println("DatoMandado");
				try {
					Thread.sleep(1000);
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
			
		if(sp.closePort()) {
			System.out.println("Puerto cerrado");	
		}
	}

}
