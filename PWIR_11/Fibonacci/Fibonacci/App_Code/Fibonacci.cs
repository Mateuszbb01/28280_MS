using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Text;

// UWAGA: możesz użyć polecenia „Zmień nazwę” w menu „Refaktoryzuj”, aby zmienić nazwę klasy „Fibonacci” w kodzie, usłudze i pliku konfiguracji.
public class Fibonacci : IFibonacci
{
    public int Fib(int n)
    {
    
        if ((n == 1) || (n == 2))
            return 1;
        else
            return Fib(n - 1) + Fib(n - 2);
        
    }

    
}

