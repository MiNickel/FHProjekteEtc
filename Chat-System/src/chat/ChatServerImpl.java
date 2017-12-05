package chat;

import java.net.MalformedURLException;
import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;
import java.util.List;

public class ChatServerImpl extends UnicastRemoteObject implements ChatServerIF {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private List<ClientProxyIF> clients;

	public ChatServerImpl() throws RemoteException {
		this.clients = new ArrayList<ClientProxyIF>();
	}

	@Override
	public synchronized void subscribeUser(ClientProxyIF handle) throws RemoteException {
		this.clients.add(handle);
	}

	@Override
	public synchronized boolean unsubscribeUser(ClientProxyIF handle) throws RemoteException {
		return this.clients.remove(handle);
	}

	@Override
	public synchronized void broadcast(String message) throws RemoteException {
		for (int i = 0; i < clients.size(); i++) {
			clients.get(i).receiveMessage(message);
		}

	}

	public static void main(String[] args) throws RemoteException, MalformedURLException {
		Naming.rebind("RMIChatServer", new ChatServerImpl());
	}

}
