// test_cs.cs
// Simple tests to observe C# type compatibility rules.
// Compile with: csc test_cs.cs  (Microsoft C# Compiler) or use `dotnet` tooling
using System;
using System.Collections.Generic;

class Base { }
class Derived : Base { }

class TestCS {
    static void Main() {
        int i = 42;
        long l = i; // implicit widening
        Console.WriteLine($"int {i} -> long {l}");

        long L = 10000000000L;
        // int k = L; // compile-time error: cannot implicitly convert long to int
        int k = (int)L; // explicit cast required (possible overflow)
        Console.WriteLine($"long {L} -> int {k} (after cast)");

        object o = 5; // boxing
        int unboxed = (int)o; // unboxing (must match boxed type)
        Console.WriteLine($"boxed 5 -> unboxed {unboxed}");

        // invalid unbox would compile but throw at runtime:
        // object s = "hello"; int bad = (int)s; // InvalidCastException at runtime

        Derived d = new Derived();
        Base b = d; // upcast (implicit)
        // Derived d2 = b; // compile error: cannot implicitly convert Base to Derived
        Derived d2 = (Derived)b; // downcast requires explicit cast

        // generics invariance
        List<Derived> ld = new List<Derived>();
        // List<Base> lb = ld; // compile error: cannot convert List<Derived> to List<Base>
        IEnumerable<Base> ie = ld; // allowed: IEnumerable<T> is covariant (out T)
    }
}
