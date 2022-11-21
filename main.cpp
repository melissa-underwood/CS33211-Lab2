#include <iostream>
#include <fstream>
#include <string>


using namespace std;

int main() {

    int n = 5;              // number of processes
    int m = 3;              // number of resources types
    int safe[n], vari = 0;  // for checked processes

/////////////////////////////////////////////////////////////////////////////////

    int avail[m];
    {
    ifstream fileAvailable("available.txt");
    if (!fileAvailable) { 
        cout << "Cannot open or find file: 'available.txt'";
        exit(EXIT_FAILURE);
    }

    char input;
    fileAvailable >> input;
    for (int i = 0; i < m; i++) {
        avail[i] = input - '0';
        fileAvailable >> input;
    }
    fileAvailable.close();
    }

/////////////////////////////////////////////////////////////////////////////////
    
    int max[n][m];
    {
    ifstream fileMax("max.txt");
    if (!fileMax) {
        cout << "Cannot open or find file: 'max.txt'";
        exit(EXIT_FAILURE);
    }

    char input;
    fileMax >> input;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            max[i][j] = input - '0';
            fileMax >> input;
        }
    }

    fileMax.close();
    }

/////////////////////////////////////////////////////////////////////////////////
    
    int allo[n][m];
    {
    ifstream fileAllocation("allocation.txt");
    if (!fileAllocation) {
        cout << "Cannot open or find file: 'allocation.txt'";
        exit(EXIT_FAILURE);
    }

    char input;
    fileAllocation >> input;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            allo[i][j] = input - '0';
            fileAllocation >> input;
        }
    }

    fileAllocation.close();
    }

/////////////////////////////////////////////////////////////////////////////////

    int need[n][m];
    {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) 
            need[i][j] = max[i][j] - allo[i][j];
    }
    }

/////////////////////////////////////////////////////////////////////////////////

    bool finish[n];
    for (int s = 0; s < n; s++) finish[s] = false;

/////////////////////////////////////////////////////////////////////////////////

    int t = 0;
    do {
        for (int i = 0; i < n; i++) {
            if (finish[i] == false) { // if process not finished
            bool flag = false;
                for (int j = 0; j < m; j++) { 
                    if (need[i][j] > avail[j]) { 
                        flag = true;
                        break;
                    }
                }

                if (!flag) {
                    safe[vari++] = i;
                    for (int x = 0; x < m; x++)
                        avail[x] += allo[i][x];
                    finish[i] = 1;
                }
            }
        }
    t++;
    } while (t < n);

/////////////////////////////////////////////////////////////////////////////////

    int flag = 1;
    for (int i = 0; i < n; i++) {
        if (finish[i] == false) { // need > available
            cout << "THIS IS NOT A SAFE SYSTEM.";
            flag = 0;
            break;
        }
    }

    if (flag == 1) {
        cout << "Safest process order: ";
        for (int i = 0; i < n; i++) {
            cout << safe[i];
            cout << " ";
        }
    }

    return(0);

}

