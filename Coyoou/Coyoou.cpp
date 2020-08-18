// Coyoou.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "sqlite3.h"
#include "coyoouDB.h"
#include "ElementsList.h"
#include "logs.h"

using namespace std;

bool is_number(const std::string& s);
int main(int argc, char** argv)
{
    coyoouDB* db = new coyoouDB("AlphaTest");
    db->createTable("AlphaTest");
    ElementsList* elt_list = new ElementsList(db);

    stringstream application_statu;
    application_statu << "[" << db->getTimeNow() << "]" << "Application Started;\n";
    CYO_logging(application_statu.str());

    cout << "Coyoou Project a0.0.1 - GaumKap\nThis application is under GPL-3.0 Licence for more informations read LICENCE.txt\n\n";
    cout << "This application is Open source you can get full VS project at https://github.com/GaumKap/Coyoou .\nIf you have some issues please send your problem on https://github.com/GaumKap/Coyoou/issues";
    cout << " You need a Github account. \nYou can send mail at gaumkap@gmail.com with object \"[issue] Coyoou - ...\". \n";
    cout << "If you send mail please respect the same format as on Github issues see README at https://github.com/GaumKap/Coyoou/blob/master/README.md#bug-report .\nBefore sending issue please verify if this issue as been already declared or fixed for the next update.\n\n" << endl;
    string entry;
    while (entry != "exit") {
        cout << "Commands : \n  - read : read list\n  - write : edit or create Element in list\n  - remove : Remove element from Database\n  - update : Update list\n  - exit : exit application\n" << endl;
        cout << "coyoou a0.0.1> ";
        cin >> entry;
        cout << "" << endl;

        if (entry == "read") {
            // Read List
            int i;
            vector<Element*> read_list;
            elt_list->getAll(&read_list,0);
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
        }
        else if (entry == "write") {
            // Edit Mode
            
            while (entry != "cancel") {

                system("cls");
                cout << "Coyoou Project a-0.0.1" << endl;
                cout << "==== Edit Mod ====\n" << endl;
                cout << "Create a new element and add it into list and DB\nwrite cancel to go back on main menu\n  - new : add new element\n  - edit : edit specified element" << endl;
                cout << "coyoou a0.0.1> ";
                cin >> entry;

                if (entry == "edit") {
                    int i;
                    vector<Element*> read_list;
                    elt_list->getAll(&read_list, 0);
                    system("cls");
                    cout << "Coyoou Project a-0.0.1" << endl;
                    cout << "==== Edit Mod ====\n" << endl;
                    cout << "Create a new element and add it into list and DB\nwrite cancel to go back on main menu\n  - new : add new element\n  - edit : edit specified element\n" << endl;
                    cout << "--- Edit Mod : SELECT AN ID ---" << endl;
                    cout << "    id    |    name    |    topic    |    date    |    price    " << endl;
                    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                    for (unsigned int i = 0; i < read_list.size(); i++) {
                        cout << "  " << read_list[i]->getID();
                        cout << " | " << read_list[i]->get("name");
                        cout << " | " << read_list[i]->get("topic");
                        cout << " | " << read_list[i]->get("date");
                        cout << " | " << read_list[i]->get("price") << endl;
                    }
                    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << endl;
                    cout << "coyoou a0.0.1> ";
                    cin >> entry;
                    cout << " " << endl;
                    if (is_number(entry)){

                        stringstream buffer(entry);
                        int id = 0;
                        buffer >> id;

                        string name;
                        string topic;
                        string price;
                        cout << "enter new name " << endl;
                        cout << "coyoou a0.0.1> ";
                        cin >> name;
                        cout << " " << endl;
                        cout << "enter new topic " << endl;
                        cout << "coyoou a0.0.1> ";
                        cin >> topic;
                        cout << " " << endl;
                        cout << "enter new price (you can set \"lol\" price it work)" << endl;
                        cout << "coyoou a0.0.1> ";
                        cin >> price;
                        cout << " " << endl;

                        elt_list->edit(id, name, topic, price, "");
                        system("PAUSE");
                    }
                    else {
                        cout << "\n is not a number my friend retry...\n" << endl;
                        system("PAUSE");
                    }
                }
                else if (entry == "new") {
                    system("cls");
                    cout << "Creation of a new element\n" << endl;
                    
                    string name;
                    string topic;
                    string price;
                    cout << "enter new name" << endl;
                    cout << "coyoou a0.0.1> ";
                    cin >> name;
                    cout << " " << endl;
                    cout << "enter new topic" << endl;
                    cout << "coyoou a0.0.1> ";
                    cin >> topic;
                    cout << " " << endl;
                    cout << "enter new price (you can set \"lol\" price it work)" << endl;
                    cout << "coyoou a0.0.1> ";
                    cin >> price;
                    cout << " " << endl;
                    Element *eltBuff = new Element(0, name, topic, price, "");
                    elt_list->add(eltBuff);
                    eltBuff = nullptr;
                    system("PAUSE");
                }
                else {
                    if (entry != "cancel") {
                        cout << "- Invalid Command -" << endl;
                        system("PAUSE");
                    }
                }
            }
        }
        else if (entry == "update") {
            // Update List from DB
            elt_list->updateList();
            cout << "[INFO] List as been Updated by Database values" << endl;
        }
        else if (entry == "clear") {
            // Clear List
            elt_list->clear();
            cout << "[INFO] List is clear" << endl;
        }
        else if (entry == "remove") {
            // Remove Mode
            int i;
            vector<Element*> read_list;
            elt_list->getAll(&read_list, 0);
            system("cls");
            cout << "Coyoou Project a-0.0.1" << endl;
            cout << "==== Remove Mod ====\n" << endl;
            cout << "Remove a element on list and DB\nwrite cancel to go back on main menu\n" << endl;
            cout << "--- Remove Mod : SELECT AN ID ---" << endl;
            cout << "    id    |    name    |    topic    |    date    |    price    " << endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            for (unsigned int i = 0; i < read_list.size(); i++) {
                cout << "  " << read_list[i]->getID();
                cout << " | " << read_list[i]->get("name");
                cout << " | " << read_list[i]->get("topic");
                cout << " | " << read_list[i]->get("date");
                cout << " | " << read_list[i]->get("price") << endl;
            }
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << endl;
            cout << "coyoou a0.0.1> ";
            cin >> entry;
            cout << " " << endl;
            if (entry == "cancel") {}
            else {
                if (is_number(entry)) {
                    stringstream buffer(entry);
                    int id = 0;
                    buffer >> id;

                    elt_list->remove(id);
                    cout << "Element with id : " << id << "has been removed from Database" << endl;
                }
                else {
                    if (entry != "exit")cout << "- Invalid Entry -" << endl;
                }
            }
        }
    }

    application_statu.str("");
    application_statu << "[" << db->getTimeNow() << "]" << "Application Closed by User;\n";
    CYO_logging(application_statu.str());
    /* GTK SECTION FOR FUTURES UPDATES */
    /* Variables */
    //GtkWidget* MainWindow = NULL;

    /* Initialisation de GTK+ */
    //gtk_init(&argc, &argv);

    /* Création de la fenêtre */
    //MainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    //g_signal_connect(G_OBJECT(MainWindow), "delete-event", G_CALLBACK(gtk_main_quit), NULL);

    /* Affichage et boucle évènementielle */
    //gtk_widget_show(MainWindow);
    //gtk_main();

    /* On quitte.. */
    return EXIT_SUCCESS;
}


bool is_number(const string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}