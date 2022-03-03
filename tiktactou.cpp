#include <iostream>
#include <string>
#include <numeric>

int input = 0;
std::string ready = "n";
bool gameOn = true;
int pc = 0;
std::string fields[3][3] = {{"   ", "   ", "   "},{"   ", "   ", "   "},{"   ", "   ", "   "}};
int backfields[3][3] = {{0,0,0}, {0,0,0}, {0,0,0}};

// debugging, was steht in fields
void print_fields()
{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            std::cout << fields[i][j] << backfields[i][j];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


int setenemy(int backfields[3][3])
{
    // summe zeile und spalte berechnen
    int rowsum[3] = {0,0,0};
    int colsum[3] = {0,0,0};
    int diag[2] = {0,0};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            rowsum[i]+=backfields[i][j];
            colsum[i]+=backfields[j][i];
            if (i == j) {
                diag[0]+=backfields[j][i];
            }
            if (i+j == 2) {
                diag[1]+=backfields[j][i];
            }
        }
    }

    int sum = std::accumulate(std::begin(rowsum), std::end(rowsum), 0);
    if (sum > 19) {
        return 3;
    }

    // Wenn Zeile, Spalte oder diag 8 oder 2 (Abwehren oder Gewinnen)
    for (int i = 0; i < 3; i++) {
        // Sieg Zeile
        if (rowsum[i] == 2) {
            for (int j = 0; j < 3; j++) {
                if (backfields[i][j] == 0) {
                    backfields[i][j] = 1;
                    return 2;
                }
            }
        }
        //Sieg Spalte
        else if (colsum[i] == 2) {
            for (int j = 0; j < 3; j++) {
                if (backfields[j][i] == 0) {
                    backfields[j][i] = 1;
                    return 2;
                }
            }
        }
        // Sieg Diagonale
        else if (diag[i] == 2) {
            for (int m = 0; m < 3; m++) {
                for (int n = 0; n < 3; n++) {
                    if (m == n && backfields[m][n] == 0 && i == 0) {
                        backfields[m][n] = 1;
                        return false;
                    } else if (m+n == 2 && backfields[m][n] == 0 && i == 1) {
                        backfields[m][n] = 1;
                        return 2;
                    }
                }
            }
        }
    }
    for (int i = 0; i < 3; i++) {
        //Zeile Verteidigen
        if (rowsum[i] == 8) {
            for (int j = 0; j < 3; j++) {
                if (backfields[i][j] == 0) {
                    backfields[i][j] = 1;
                    return 0;
                }
            }
        }
        //Spalte Verteidigen
        else if (colsum[i] == 8) {
            for (int j = 0; j < 3; j++) {
                if (backfields[j][i] == 0) {
                    backfields[j][i] = 1;
                    return 0;
                }
            }
        }
        //Diagonale Verteidigen
        else if (diag[i] == 8) {
            for (int m = 0; m < 3; m++) {
                for (int n = 0; n < 3; n++) {
                    if (m == n && backfields[m][n] == 0 && i == 0) {
                        backfields[m][n] = 1;
                        return 0;
                    } else if (m+n == 2 && backfields[m][n] == 0 && i == 1) {
                        backfields[m][n] = 1;
                        return 0;
                    }
                }
            }
        }
    }

    // erste Antwort
    if (sum == 4) {
        if (backfields[1][1] == 0) {
            backfields[1][1] = 1;
            return 0;
        } else {
            backfields[0][0] = 1;
            return 0;
        }
    }

    // Fehler absichern (Unten recht ausfüllen)
    if (sum == 9 && (backfields[2][1] == 4 || backfields[1][2] == 4)) {
        backfields[2][2] = 1;
        return 0;
    }

    // Schritt nach gegner hat mitte und Diagonale
    if (sum == 9 && diag[0] == 9 && diag[1] == 4) {
        backfields[0][2] = 1;
        return 0;
    }

    // Wenn man nicht verteidigen muss, dann das O setzen wo frei ist
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++) {
            if (backfields[i][j] == 0) {
                backfields[i][j] = 1;
                return 0;
            }
        }
    }
    return 1;
}

// checken ob eingegebene Zahl schon belegt ist 
bool checkF(int input)
{
    int n = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            n+=1;
            if (n == input) {
                if (backfields[i][j] == 4 || backfields[i][j] == 1) {
                    std::cout << "try again, du kek" << std::endl;
                    //print_fields();
                    return 0;
                } else {
                    backfields[i][j] = 4;
                    //print_fields();
                    return 1;
                }
            }
        }
    }
    return false;
}


int main() {
    std::cout << "Ready to get f*cked? [y/n]";
    std::cin >> ready;

    if (ready == "y" || ready == "Y")
    {
        do {
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (backfields[i][j] == 4){
                        fields[i][j] = " X ";
                    }
                    if (backfields[i][j] == 1){
                        fields[i][j] = " O ";
                    }
                }
            }
            if (pc == 1) {
                pc = setenemy(backfields);
            } else {
                std::cout << fields[0][0] << "|" << fields[0][1] << "|" << fields[0][2]<< std::endl;
                std::cout << "-----------" << std::endl;
                std::cout << fields[1][0] << "|" << fields[1][1] << "|" << fields[1][2] << std::endl;
                std::cout << "-----------" << std::endl;
                std::cout << fields[2][0]<< "|" << fields[2][1] << "|" << fields[2][2] << std::endl;
                if (pc == 0) {
                    std::cout << std::endl <<"Enter Field: ";
                    std::cin >> input;
                    pc = checkF(input);
                } else if (pc == 2) {
                    std::cout << std::endl << "How does it feel to lose against me? Does it hurt?" << std::endl;
                    gameOn = false;
                } else if (pc == 3) {
                    std::cout << std::endl << "As always..." << std::endl;
                    gameOn = false;
                }
            }
        }
        while (gameOn);
    } else {
        std::cout << "sad" << std::endl;
    }
    return 0;
}