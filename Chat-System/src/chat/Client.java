package chat;

import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;
import java.util.Scanner;

public class Client extends UnicastRemoteObject implements ClientProxyIF, Runnable {
	
	private ChatServerIF chatServer;
	private String name = null;
	
	protected Client(String name, ChatServerIF chatServer) throws RemoteException {
		this.name = name;
		this.chatServer = chatServer;
		chatServer.subscribeUser(this);
		
	}
	@Override
	public void receiveMessage(String message) throws RemoteException {
		System.out.println(message);
		
	}
	@Override
	public void run() {
		Scanner scan = new Scanner(System.in);
		String message;
		while (true) {
			message = scan.nextLine();
			try {
				chatServer.broadcastMessage(name + " : "+message);
			} catch (RemoteException e) {
				e.printStackTrace();
			}
		}
		
	}

	
	

}
