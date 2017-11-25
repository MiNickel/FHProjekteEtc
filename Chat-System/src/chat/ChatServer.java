package chat;

import java.rmi.RemoteException;
import java.util.ArrayList;

public class ChatServer implements ChatServerIF {

	private ArrayList<ClientProxyIF> chatClients;

	protected ChatServer() throws RemoteException {
		chatClients = new ArrayList<ClientProxyIF>();
	}

	@Override
	public void subscribeUser(ClientProxyIF handle) throws RemoteException {
		this.chatClients.add(handle);

	}

	@Override
	public void broadcastMessage(String message) throws RemoteException {
		int i = 0;
		while (i < chatClients.size()) {
			chatClients.get(i++).receiveMessage(message);
		}
		
	}

	

	

}
