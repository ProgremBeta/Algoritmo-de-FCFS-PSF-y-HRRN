#include <iostream>
using namespace std;

int main()
{
    int CantidadProcesos;
    int TiempoInicio = 0;
    int TiempoFinalizacion = 0;
    int TiempoRetorno = 0;
    int TiempoEjecucion = 0;
    int TiempoEspera = 0;
    float TiempoRetornoTotal = 0;

    cout << "Ingresa la cantidad de procesos: ";
    cin >> CantidadProcesos;

    int Tabla[CantidadProcesos][5];

    for (int i = 0; i < CantidadProcesos; ++i)
    {
        cout << "Ingresa tiempo de llegada del proceso " << i + 1 << " : ";
        cin >> Tabla[i][0];
        cout << "Ingresa tiempo de ejecución del proceso " << i + 1 << " : ";
        cin >> Tabla[i][1];
    }

    // FCFS
    TiempoEjecucion = 0;
    TiempoRetornoTotal = 0;

    for (int i = 0; i < CantidadProcesos; i++)
    {
        int TiempoLlegada = Tabla[i][0];
        int TiempoServicio = Tabla[i][1];

        if (TiempoEjecucion < TiempoLlegada)
        {
            TiempoInicio = TiempoLlegada;
        }
        else
        {
            TiempoInicio = TiempoEjecucion;
        }

        TiempoFinalizacion = TiempoInicio + TiempoServicio;
        TiempoRetorno = TiempoFinalizacion - TiempoLlegada;
        Tabla[i][2] = TiempoRetorno;
        TiempoEspera = TiempoInicio - TiempoLlegada;
        Tabla[i][3] = TiempoEspera;

        TiempoRetornoTotal += TiempoRetorno;
        TiempoEjecucion = TiempoFinalizacion;
    }

    cout << "\n  FCFS     :  L| S| R| E" << endl;
    for (int i = 0; i < CantidadProcesos; ++i)
    {
        cout << "Proceso " << i + 1 << " : ";
        for (int j = 0; j < 4; ++j)
        {
            cout << " " << Tabla[i][j] << " ";
        }
        cout << endl;
    }
    float resultado = TiempoRetornoTotal / CantidadProcesos;
    cout << "\nEl Promedio total es: " << resultado << endl;

    // Inicialización para HRRN
    bool terminado[CantidadProcesos];
    for (int i = 0; i < CantidadProcesos; ++i)
    {
        terminado[i] = false;
    }

    int procesosRestantes = CantidadProcesos;
    int TiempoActual = 0;
    TiempoRetornoTotal = 0;

    while (procesosRestantes > 0)
    {
        int idx = -1;
        float mejorRatio = -1;

        for (int i = 0; i < CantidadProcesos; i++)
        {
            if (!terminado[i] && Tabla[i][0] <= TiempoActual)
            {
                int tiempoEspera = TiempoActual - Tabla[i][0];
                float ratio = 1.0 + (float)tiempoEspera / Tabla[i][1];

                if (ratio > mejorRatio)
                {
                    mejorRatio = ratio;
                    idx = i;
                }
            }
        }

        if (idx == -1)
        {
            TiempoActual++; 
            continue;
        }

        TiempoInicio = TiempoActual;
        TiempoFinalizacion = TiempoInicio + Tabla[idx][1];
        TiempoRetorno = TiempoFinalizacion - Tabla[idx][0];
        TiempoEspera = TiempoInicio - Tabla[idx][0];

        Tabla[idx][2] = TiempoRetorno;
        Tabla[idx][3] = TiempoEspera;

        TiempoRetornoTotal += TiempoRetorno;
        TiempoActual = TiempoFinalizacion;
        terminado[idx] = true;
        procesosRestantes--;
    }

    // Mostrar los resultados de HRRN
    cout << "\n  HRRN     : L| S| R| E" << endl;
    for (int i = 0; i < CantidadProcesos; ++i)
    {
        cout << "Proceso " << i + 1 << " : ";
        for (int j = 0; j < 4; ++j)
        {
            cout << " " << Tabla[i][j] << " ";
        }
        cout << endl;
    }
    resultado = TiempoRetornoTotal / CantidadProcesos;
    cout << "\nEl Promedio de Retorno es: " << resultado << endl;

    // Inicialización para PSF
    for (int i = 0; i < CantidadProcesos; ++i)
    {
        terminado[i] = false;
    }

    procesosRestantes = CantidadProcesos;
    TiempoActual = 0;
    TiempoRetornoTotal = 0;

    const int VALOR_MAXIMO = 1000000;

    while (procesosRestantes > 0)
    {
        int idx = -1;
        int minTiempoEjecucion = VALOR_MAXIMO;

        for (int i = 0; i < CantidadProcesos; i++)
        {
            if (!terminado[i] && Tabla[i][0] <= TiempoActual)
            {
                if (Tabla[i][1] < minTiempoEjecucion)
                {
                    minTiempoEjecucion = Tabla[i][1];
                    idx = i;
                }
            }
        }

        if (idx == -1)
        {
            TiempoActual++; 
            continue;
        }

        TiempoInicio = TiempoActual;
        TiempoFinalizacion = TiempoInicio + Tabla[idx][1];
        TiempoRetorno = TiempoFinalizacion - Tabla[idx][0];
        TiempoEspera = TiempoInicio - Tabla[idx][0];

        Tabla[idx][2] = TiempoRetorno;
        Tabla[idx][3] = TiempoEspera;

        TiempoRetornoTotal += TiempoRetorno;
        TiempoActual = TiempoFinalizacion;
        terminado[idx] = true;
        procesosRestantes--;
    }

    // Mostrar los resultados de PSF
    cout << "\n  PSF     : L| S| R| E" << endl;
    for (int i = 0; i < CantidadProcesos; ++i)
    {
        cout << "Proceso " << i + 1 << " : ";
        for (int j = 0; j < 4; ++j)
        {
            cout << " " << Tabla[i][j] << " ";
        }
        cout << endl;
    }
    resultado = TiempoRetornoTotal / CantidadProcesos;
    cout << "\nEl Promedio de Retorno es: " << resultado << endl;

    return 0;
}
