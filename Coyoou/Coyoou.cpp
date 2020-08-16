// Coyoou.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "sqlite3.h"
#include "coyoouDB.h"
#include "ElementsList.h"

using namespace std;

int main(int argc, char** argv)
{
    coyoouDB* db = new coyoouDB("Test");
    ElementsList* elt_list = new ElementsList(db);

    //db->createTable("Test");
    //db->createElement("valeur1", "topic", "50.00","0");
    //db->createElement("valeur2", "jauj", "30.00", "0");
    //db->createElement("valeur3", "7blue", "15.00", "0");
    //db->createElement("valeu4", "CPT", "11.34", "0");
    //db->createElement("valeur5", "GKC3", "1.00", "0");
    //db->editElement(1, "jotun", "jotun", "jotun", "jotun");
    //db->editElement(2, "jotun", "jotun", "jotun", "jotun");
    //db->editElement(3, "jotun", "jotun", "jotun", "jotun");
    //db->searchElement("","","","");
    //db->searchElement("", "", "", "");

    for (int i = 0; i < 10; i++)
    {
        Element* elt = new Element(i, to_string(i), to_string(i), to_string(i), to_string(i));
        elt_list->add(elt);
    }
    cout << "Writing finish" << endl;
    for (int i = 0; i < 10; i++) {
        Element* temp;
        temp = elt_list->search(i);
        if (temp == nullptr) {
            cout << "- Element NULL" << endl;
        }
        else {
            cout << "+ " << temp->get("name") << " | " << temp->get("topic") << " | " << temp->get("price") << " | " << temp->get("date") << " || id = " << temp->getID() << endl;
        }
    }
    cout << "======================================" << endl;
    cout << "Modifications :" << endl;
    elt_list->edit(0);
    elt_list->edit(9);
    elt_list->edit(4);
    for (int i = 0; i < 10; i++) {
        Element* temp;
        temp = elt_list->search(i);
        if (temp == nullptr) {
            cout << "? Element with id : " << i << " is Deleted or Undefined" << endl;
        }
        else {
            cout << "+ " << temp->get("name") << " | " << temp->get("topic") << "|" << temp->get("price") << " | " << temp->get("date") << " || " << temp->getID() << endl;
        }
    }
    cout << "======================================" << endl;
    cout << "Deleting :" << endl;
    elt_list->remove(1);
    elt_list->remove(8);
    elt_list->remove(5);
    for (int i = 0; i < 10; i++) {
        Element* temp;
        temp = elt_list->search(i);
        if (temp == nullptr) {
            cout << "? Element with id : " << i << " is Deleted or Undefined"<< endl;
        }
        else {
            cout << "+ " << temp->get("name") << " | " << temp->get("topic") << "|" << temp->get("price") << " | " << temp->get("date") << " || " << temp->getID() << endl;
        }
    }

    cout << "======================================" << endl;
    cout << "Clear :" << endl;
    elt_list->clear();
    for (int i = 0; i < 10; i++) {
        Element* temp;
        temp = elt_list->search(i);
        if (temp == nullptr) {
            cout << "? Element with id : " << i << " is Deleted or Undefined" << endl;
        }
        else {
            cout << "+ " << temp->get("name") << " | " << temp->get("topic") << "|" << temp->get("price") << " | " << temp->get("date") << " || " << temp->getID() << endl;
        }
    }
        

    /* Variables */
    GtkWidget* MainWindow = NULL;

    /* Initialisation de GTK+ */
    gtk_init(&argc, &argv);

    /* Création de la fenêtre */
    MainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(G_OBJECT(MainWindow), "delete-event", G_CALLBACK(gtk_main_quit), NULL);

    /* Affichage et boucle évènementielle */
    gtk_widget_show(MainWindow);
    gtk_main();

    /* On quitte.. */
    return EXIT_SUCCESS;
}
// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
