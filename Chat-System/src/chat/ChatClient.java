package chat;

import java.net.MalformedURLException;
import java.rmi.Naming;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.Scanner;

public class ChatClient extends UnicastRemoteObject	 implements ClientProxyIF, Runnable {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private ChatServerIF chatServer;
	private String name = null;
	boolean chatExit = true;
	
	public ChatClient(String name, ChatServerIF chatServer) throws RemoteException {
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
		System.out.println("Geben Sie .LOGOUT ein um sich auszuloggen");
		@SuppressWarnings("resource")
		Scanner scanner = new Scanner(System.in);
		String message;
		
		while (chatExit) {
			message = scanner.nextLine();
			try {
				if (message.equals(".LOGOUT")) {
					chatServer.unsubscribeUser(this);
					System.out.println("Erfolgreich ausgeloggt");
					chatExit = false;
				} else {
					chatServer.broadcast(this.name + " : " + message);
				}
				
				
			} catch (RemoteException e) {
				e.printStackTrace();
			}
		}
		
	}
	
	public static void main(String[] args) throws RemoteException, MalformedURLException, NotBoundException {
		String chatServerURL = "rmi://localhost/RMIChatServer";
		ChatServerIF chatServer = (ChatServerIF) Naming.lookup(chatServerURL);
		new Thread(new ChatClient(args[0], chatServer)).start();

	}

	

	

}
