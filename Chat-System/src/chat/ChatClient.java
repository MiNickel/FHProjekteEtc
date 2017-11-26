package chat;

import java.net.MalformedURLException;
import java.rmi.Naming;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.util.Scanner;

public class ChatClient implements ClientProxyIF, Runnable {

	private ChatServerIF chatServer;
	private String name = null;
	
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
		Scanner scanner = new Scanner(System.in);
		String message;
		while (true) {
			message = scanner.nextLine();
			try {
				chatServer.broadcast(name + " : "+ message);
				
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
