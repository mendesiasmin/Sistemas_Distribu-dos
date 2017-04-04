// Counter.java
import java.rmi.*;
public interface Counter
extends Remote {
	public long operation(long a, long b, String op) throws RemoteException;
}
