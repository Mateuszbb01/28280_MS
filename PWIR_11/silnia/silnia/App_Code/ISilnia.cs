using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Text;

// UWAGA: możesz użyć polecenia „Zmień nazwę” w menu „Refaktoryzuj”, aby zmienić nazwę interfejsu „ISilnia” w kodzie i pliku konfiguracji.
[ServiceContract]
public interface ISilnia
{
    [OperationContract]
     long silnia(int n);
}
