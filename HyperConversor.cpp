/*Davi Sollar - 15/02/2024*/
/*Descrição: Programa que converte números de bases diferentes*/

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <filesystem>

#ifdef _WIN32
    #include <windows.h> // Biblioteca para Windows
#elif __linux__
    #include <cstdlib> // Biblioteca para Linux
#endif

using namespace std;

const char Char[36] = {'0','1','2','3','4','5','6','7','8','9','a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

void mostrarApresentacao() {
    cout << "------------------------------------------------------------" << endl;
    cout << "|            HYPER CONVERSOR DE BASE NUMÉRICA              |" << endl;
    cout << "------------------------------------------------------------" << endl;
    cout << "| Este programa permite converter números entre diferentes |" << endl;
    cout << "| bases numéricas. Você pode inserir um número em qualquer |" << endl;
    cout << "| base de 2 a 36 e convertê-lo para outra base de 2 a 36.  |" << endl;
    cout << "| O programa também permite que você salve os resultados   |" << endl;
    cout << "| em um arquivo de texto em um local de sua escolha.       |" << endl;
    cout << "------------------------------------------------------------" << endl;
    cout << "|                   COMO UTILIZAR:                         |" << endl;
    cout << "| 1. Insira o número que deseja converter.                 |" << endl;
    cout << "| 2. Especifique a base atual do número (entre 2 e 36).    |" << endl;
    cout << "| 3. Escolha a base para a qual deseja converter o número. |" << endl;
    cout << "| 4. Veja o resultado da conversão na tela.                |" << endl;
    cout << "| 5. Repita o processo ou encerre o programa quando quiser.|" << endl;
    cout << "| 6. Abra o arquivo e veja seu histórico de conversões.    |" << endl;
    cout << "------------------------------------------------------------" << endl;
    cout << "|             Davi Sollar - HyperSonic3608                 |" << endl;
    cout << "------------------------------------------------------------" << endl;
    cout << endl;
}

bool validarBase(int base) {
    return (base >= 2 && base <= 36);
}

int converterParaDecimal(const string& Num, int Bs1) {
    int De = 0, k = 0;
    for (int i = Num.length() - 1; i >= 0; i--) {
        for (int j = 0; j < Bs1; j++) {
            if (Num[i] == Char[j]) {
            	if (j >= Bs1)
            	{
            		printf("\nErro! Algarismo maior ou igual a base.");
           			return(1);
            	}
                De += j * pow(Bs1, k);
                break;
            }
        }
        k++;
    }
    return De;
}

string converterDeDecimal(int De, int Bs2) {
    string Res;
    do {
        int Aux = De % Bs2;
        Res.push_back(Char[Aux]);
        De = De / Bs2;
    } while (De > 0);

    return string(Res.rbegin(), Res.rend());
}

void imprimirResultado(const string& Res, int Bs2) {
    if (Bs2 == 2) {
        cout << "\nO número transformado em binário é: ";
    } else if (Bs2 == 10) {
        cout << "\nO número transformado em decimal é: ";
    } else if (Bs2 == 16) {
        cout << "\nO número transformado em hexadecimal é: ";
    } else {
        cout << "\nO número transformado na base " << Bs2 << " é: ";
    }

    cout << Res << endl;
}

void abrirArquivoAutomaticamente(const string& fullFilePath) {
    #ifdef _WIN32
        string command = "start \"\" \"" + fullFilePath + "\"";
        system(command.c_str());
    #elif __linux__
        string command = "xdg-open \"" + fullFilePath + "\"";
        system(command.c_str());
    #endif
}

int main() {
    ios::sync_with_stdio(false);

    mostrarApresentacao();

    string Num, Res, locArq, locArqCompleta;
    int Bs1, Bs2, x;

    cout << "Digite o caminho onde deseja salvar o arquivo de histórico (deixe em branco para usar o diretório atual): ";
    getline(cin, locArq);

    if (locArq.empty()) {
        locArq = "./";
    } else if (!filesystem::exists(locArq)) {
        cout << "Diretório não existe. Criando diretório..." << endl;
        filesystem::create_directories(locArq);
    }

    locArqCompleta = locArq + "/hyperconversor.txt";

    ofstream arq(locArqCompleta);

    if (!arq) {
        cout << "\nNão foi possível abrir o arquivo no caminho especificado.\n";
        system("pause");
        return 1;
    }

    do {
        cout  << endl << "Digite um número: ";
        cin >> Num;

        cout << "Digite a base desse número (2 até 36): ";
        cin >> Bs1;

        if (!validarBase(Bs1)) {
            cout << "\nBase inválida digitada";
            return 2;
        }

        int De = converterParaDecimal(Num, Bs1);

        cout << "Digite a base desejada (2 até 36): ";
        cin >> Bs2;

        if (!validarBase(Bs2)) {
            cout << "\nBase inválida digitada";
            return 3;
        }

        Res = converterDeDecimal(De, Bs2);

        imprimirResultado(Res, Bs2);

        arq << Num << ", base " << Bs1 << " -> base " << Bs2 << " = " << Res << "\n";

        cout << "\n\nAperte 0 para encerrar ou outro inteiro para continuar: ";
        cin >> x;

        if (x == 0) {
            system("cls");
            cout << "Programa encerrado" << endl;
            arq.close();
            cout << "Arquivo salvo em: " << locArqCompleta;
            abrirArquivoAutomaticamente(locArqCompleta);
            return 0;
        } else {
            Num.clear();
            Res.clear();
            system("cls");
        }
    } while (true);
}
