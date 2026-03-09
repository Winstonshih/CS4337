// TestJava.java
// Simple tests to observe Java type compatibility rules.
// Compile with: javac TestJava.java
import java.util.*;

class Base { }
class Derived extends Base { }

public class TestJava {
    public static void main(String[] args) {
        int i = 42;
        double d = i; // widening allowed
        System.out.println("int " + i + " -> double " + d);

        double e = 3.14;
        int j = (int)e; // narrowing requires cast
        System.out.println("double " + e + " -> int " + j + " (after cast)");

        Derived der = new Derived();
        Base b = der; // upcast allowed
        // Derived d2 = b; // compile-time error: incompatible types
        Derived d2 = (Derived)b; // requires cast

        Derived[] darr = new Derived[1];
        Base[] barr = darr; // arrays are covariant in Java
        try {
            barr[0] = new Base(); // ArrayStoreException at runtime
        } catch (ArrayStoreException ex) {
            System.out.println("ArrayStoreException observed when storing Base into Derived[] via Base[] reference");
        }

        List<Derived> ld = new ArrayList<>();
        // List<Base> lb = ld; // compile-time error: incompatible types (generics are invariant)
        List<? extends Base> wildcard = ld; // use wildcard covariance for reading
    }
}
