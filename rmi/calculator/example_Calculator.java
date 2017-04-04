// example_Calculator.java
import java.rmi.*;
import java.rmi.server.*;
public class example_Calculator extends UnicastRemoteObject implements Calculator {

  public example_Calculator() throws RemoteException {
    super();
  }

  public long add(long a, long b,String op) throws RemoteException {
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
