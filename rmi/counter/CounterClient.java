// CounterCliente.java
import java.rmi.*;
public class CounterClient {
public static void main(String args[]) {
try {
	String host = args[0];
  int a = Integer.parseInt(args[1]);
  int b = Integer.parseInt(args[3]);
  String op = args[2];

	Counter c = (Counter)
		Naming.lookup("rmi://"+host+"/Contador");
	System.out.println("Contador: "+c.operation(a,b,op));
} catch (Exception e) {
	System.out.println("Erro: "+e.getMessage());}
}
}
