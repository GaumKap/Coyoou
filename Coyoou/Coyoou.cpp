//
// Coyoou Project - Main File
//
// GaumKap 2020, GPL-3.0
// version main_0.2 (Dec 2020)
//

#include <iostream>
#include <stdlib.h>
#include "sqlite3.h"
#include "coyoouDB.h"
#include "ElementsList.h"
#include "logs.h"
using namespace std;


/// <summary>Main Function</summary>
/// <param name="argc">Number of entry in terminal user input</param>  
/// <param name="argv">Table containig char values (terminal user entry)</param>  
/// <returns>EXIT_SUCCESS</returns>
int main(int argc, char** argv)
{

    coyoouDB* db = new coyoouDB("AlphaTest");
    db->createTable("AlphaTest");
    ElementsList* elt_list = new ElementsList(db);

    // Read List
    vector<Element*> read_list;
    
    elt_list->search(&read_list, "name;version2");
    elt_list->getAll(&read_list, 0);
    system("cls");
    cout << "--- Full Table From Database ---" << endl;
    cout << "    id    |    name    |    topic    |    date    |    price    " << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    for (unsigned int i = 0; i < read_list.size(); i++) {
        string name, price, topic, date;
        name = read_list[i]->get("name");
        price = read_list[i]->get("price");
        topic = read_list[i]->get("topic");
        date = read_list[i]->get("date");
        cout << "  " << read_list[i]->getID();
        cout << " | " << read_list[i]->get("name");
        cout << " | " << read_list[i]->get("topic");
        cout << " | " << read_list[i]->get("date");
        cout << " | " << read_list[i]->get("price") << endl;
    }
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << endl;
    system("PAUSE");
    return EXIT_SUCCESS;
}

