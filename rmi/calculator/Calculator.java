// Calculator.java
import java.rmi.*;
public interface Calculator extends Remote {
  public long add(long a, long b, String op) throws RemoteException;
}
