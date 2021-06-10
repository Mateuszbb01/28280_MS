using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Text;

// UWAGA: możesz użyć polecenia „Zmień nazwę” w menu „Refaktoryzuj”, aby zmienić nazwę interfejsu „Iprostokat” w kodzie i pliku konfiguracji.
[ServiceContract]
public interface Iprostokat
{
    [OperationContract]
    int polePr(int a, int b);
}
