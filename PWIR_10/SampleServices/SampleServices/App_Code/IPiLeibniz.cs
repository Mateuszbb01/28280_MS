using System.ServiceModel;

// UWAGA:możesz użyć polecenia „Zmień nazwę” w menu „Refaktoryzuj”, aby zmienić nazwę interfejsu „IPiLeibniz” w kodzie i pliku konfiguracji.
[ServiceContract]
public interface IPiLeibniz
{
    [OperationContract]
    void DoWork();

    [OperationContract]
    double CalculatePi(int accuracy);
}
