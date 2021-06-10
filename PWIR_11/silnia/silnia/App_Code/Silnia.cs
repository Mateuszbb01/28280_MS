using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Text;

// UWAGA: możesz użyć polecenia „Zmień nazwę” w menu „Refaktoryzuj”, aby zmienić nazwę klasy „Silnia” w kodzie, usłudze i pliku konfiguracji.
public class Silnia : ISilnia
{
   public long silnia(int n)
    {

        if (n == 0)
        {
            return 1;
        }
        else
        {
            return n * silnia(n - 1);
        }
        
    }
}
