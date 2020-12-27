// Coyoou.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <stdlib.h>
#include "sqlite3.h"
#include "coyoouDB.h"
#include "ElementsList.h"
#include "logs.h"

using namespace std;

bool is_number(const std::string& s);
int main(int argc, char** argv)
{

    cout << "Coyoou Project a0.0.1 - GaumKap\nThis application is under GPL-3.0 Licence for more informations read LICENCE.txt\n\n";
    cout << "This application is Open source you can get full VS project at https://github.com/GaumKap/Coyoou .\nIf you have some issues please send your problem on https://github.com/GaumKap/Coyoou/issues";
    cout << " You need a Github account. \nYou can send mail at gaumkap@gmail.com with object \"[issue] Coyoou - ...\". \n";
    cout << "If you send mail please respect the same format as on Github issues see README at https://github.com/GaumKap/Coyoou/blob/master/README.md#bug-report .\nBefore sending issue please verify if this issue as been already declared or fixed for the next update.\n\n" << endl;
    cout << "\n This source Code is under developpment for Coyoou a0.2 you can get old sources in Releases" << endl;
    system("PAUSE");
    return EXIT_SUCCESS;
}