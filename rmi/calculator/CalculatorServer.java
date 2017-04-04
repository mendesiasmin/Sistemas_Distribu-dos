// CalculatorServer.java
import java.rmi.*;
public class CalculatorServer {
  public static void main(String args[])  {
    try { Calculator c = new example_Calculator();
      Naming.rebind("Contador", c);
      // System.out.println(c);
      System.out.println("Calculator ready.");}
    catch (Exception e) {
      System.out.println("Erro:"+e.getMessage());}
  }
}
