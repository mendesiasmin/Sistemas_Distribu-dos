// CalculatorCliente.java
import java.rmi.*;
public class CalculatorClient {
  public static void main(String args[]) {
    try {
      String host = args[0];
      int A = Integer.parseInt(args[1]);
      int B = Integer.parseInt(args[3]);
      String op = args[2];

      Calculator c = (Calculator)
        Naming.lookup("rmi://"+host+"/Calculator");
      System.out.println("Resultado: "+c.add(A,B,op));
    } catch (Exception e) {
      System.out.println("Erro: "+e.getMessage());}
  }
}
