// example_Counter.java
import java.rmi.*;
import java.rmi.server.*;
public class example_Counter extends UnicastRemoteObject implements Counter {

  public example_Counter() throws RemoteException {
    super();
  }

  public long operation(long a, long b,String op) throws RemoteException {
    if(op.equals("+")) {
      return a+b;
    } else if(op.equals("-")){
      return a-b;
    } else if(op.equals("*")){
      return a*b;
    } else if(op.equals("/")){
      return a/b;
    } else {
      return 0;
    }
  }
}
