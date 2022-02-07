package es.ucm.fdi.tfg.robotpacman.pruebas;

import com.fazecast.jSerialComm.SerialPort;

public class CommunicationManager {
	public static class MessageSender{		
				
		static SerialPort sp = null;
		
		public static void SetSerialPort(SerialPort _sp) {
			sp = _sp;
		}
		
		
		public static void SendMsg(JAVA_MESSAGE msg) {
			switch(msg) {
			case PAC_MAN_UP:
				System.out.println("UP");
			break;
			case PAC_MAN_RIGHT:
				System.out.println("RIGHT");
			break;
			case PAC_MAN_DOWN:
				System.out.println("DOWN");
			break;
			case PAC_MAN_LEFT:
				System.out.println("LEFT");
			break;
			case PAC_MAN_NEUTRAL:
				System.out.println("NEUTRAL");
			break;
			default:
				System.out.println("Non identified msg");
			break;
			}
			
			if(sp != null) {
				try {
					sp.getOutputStream().write((byte)msg.ordinal());
					sp.getOutputStream().flush();
				} catch (Exception e) {
					System.out.println("ERROR when sending message to arduino");
					e.printStackTrace();
				}
			}
		}
	}
}
