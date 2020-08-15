#include "coyoouDB.h"
#include <iostream>

coyoouDB::coyoouDB(string target)
{
    m_tableTarget = target;
	rc = sqlite3_open("CoyoouDB.db", &db);
    if (rc)
    {
        std::cerr << "Error opening SQLite3 database: " << sqlite3_errmsg(db) << std::endl << std::endl;
        sqlite3_close(db);
    }
    else
    {
        std::cout << "Opened CoyoouDB.db." << std::endl << std::endl;
    }
}

coyoouDB::~coyoouDB()
{
}

// Création d'une Table dans la base de données
int coyoouDB::createTable(string name)
{
    int e = CYO_DB_SUCCESS;
    char* message;
    // Execute SQL
    cout << "Creating " + name + " Table ..." << endl;
    string sqlCreateTable = "CREATE TABLE " + name + " (id INTEGER PRIMARY KEY, name STRING,date STRING,topic STRING,price STRING);";
    rc = sqlite3_exec(db, sqlCreateTable.c_str(), NULL, NULL, &message);
    if (rc)
    {
        cerr << "Error executing SQLite3 statement: " << sqlite3_errmsg(db) << endl << endl;
        sqlite3_free(message);
        e = CYO_DB_WRITE_ERROR;
    }
    else
    {
        cout << "Created " + name + "." << endl << endl;
    }
    return e;
}

//Supression d'une Table et tout ce qui la compose dans la base de données
int coyoouDB::removeTable(string name)
{
    int e = CYO_DB_SUCCESS;

    cout << "Remove Table ..." << endl;
    string sqlQuery2 = "DELETE TABLE " + name + ";";
    rc = sqlite3_exec(db, sqlQuery2.c_str(), NULL, NULL, &error);
#ifdef DEBUG
    cout << ">-SQL-< : " + rc << endl; // DEBUG INFO
#endif // DEBUG
    return e;
}

// Création d'une ligne dans la Table de la BDD
int coyoouDB::createElement(string name, string topic, string price, string date)
{
    int e = CYO_DB_SUCCESS;
    // Execute SQL
    cout << "Inserting a value into " + m_tableTarget +" ..." << endl;
    string sqlInsert = "INSERT INTO " + m_tableTarget + " VALUES(NULL, \""+ name +"\",\"" + date + "\",\"" + topic + "\",\"" + price + "\");";
    cout << sqlInsert << endl;
    rc = sqlite3_exec(db, sqlInsert.c_str(), NULL, NULL, &error);

#ifdef DEBUG
    cout << ">-SQL-< : " + rc << endl; // DEBUG INFO
#endif // DEBUG

    if (rc)
    {
        cerr << "Error executing SQLite3 statement: " << sqlite3_errmsg(db) << endl << endl;
        sqlite3_free(error);
        e = CYO_DB_WRITE_ERROR;
    }
    else
    {
        cout << "Inserted a value into " + m_tableTarget + "." << endl << endl;
    }
    return e;
}

// Supression d'une ligne dans la Table de la BDD
int coyoouDB::removeElement(int id)
{
    int e = CYO_DB_SUCCESS;
    // Execute SQL
    cout << "Delete a value into " + m_tableTarget + " ..." << endl;
    string sqlQuery = "DELETE FROM `" + m_tableTarget + "` WHERE `id`=" + to_string(id) + ";";
    cout << "[Query] " + sqlQuery << endl;
    rc = sqlite3_exec(db, sqlQuery.c_str(), NULL, NULL, &error);

#ifdef DEBUG
    cout << ">-SQL-< : " + rc << endl; // DEBUG INFO
#endif // DEBUG

    if (rc)
    {
        cerr << "Error executing SQLite3 statement: " << sqlite3_errmsg(db) << endl << endl;
        sqlite3_free(error);
        e = CYO_DB_DELETE_ERROR;
    }
    else
    {
        cout << "Value deleted in " + m_tableTarget + "." << endl << endl;
    }
    return e;
}

//Modification d'une ligne dans la table de la BDD
int coyoouDB::editElement(int id, string name, string topic, string date, string price)
{
    int e = CYO_DB_SUCCESS;

    cout << "Edit value into " + m_tableTarget + "..." << endl;
    string sqlQuery = "UPDATE " + m_tableTarget + " SET name = '" + name + "', topic = '" + topic + "', date = '" + date + "', price = '" + price + "' WHERE id = " + to_string(id);
    cout << "[Query]" + sqlQuery << endl;
    rc = sqlite3_exec(db, sqlQuery.c_str(), NULL, NULL, &error);

#ifdef DEBUG
    cout << ">-SQL-< : " + rc << endl; // DEBUG INFO
#endif // DEBUG

    if (rc)
    {
        cerr << "Error executing SQLite3 statement: " << sqlite3_errmsg(db) << endl << endl;
        sqlite3_free(error);
        e = CYO_DB_WRITE_ERROR;
    }
    else
    {
        cout << "Value Edited in " + m_tableTarget + "." << endl << endl;
    }
    return e;
}

// Recherche d'un ou plusieurs élements dans la BDD
// Note : Definir le retour de la fonction pour l'affichage en graphique
void coyoouDB::searchElement(string name, string topic, string date, string price)
{

    // Display MyTable
    cout << "Retrieving values in MyTable ..." << endl;
    string sqlSelect = "SELECT * FROM " + m_tableTarget + ";";
    char** results = NULL;
    int rows, columns;
    sqlite3_get_table(db, sqlSelect.c_str(), &results, &rows, &columns, &error);
    if (rc)
    {
        cerr << "Error executing SQLite3 query: " << sqlite3_errmsg(db) << endl << endl;
        sqlite3_free(error);
    }
    else
    {
        // Display Table
        for (int rowCtr = 0; rowCtr <= rows; ++rowCtr)
        {
            for (int colCtr = 0; colCtr < columns; ++colCtr)
            {
                // Determine Cell Position
                int cellPosition = (rowCtr * columns) + colCtr;

                // Display Cell Value
                cout.width(12);
                cout.setf(ios::left);
                cout << results[cellPosition] << " ";
            }

            // End Line
            cout << endl;

            // Display Separator For Header
            if (0 == rowCtr)
            {
                for (int colCtr = 0; colCtr < columns; ++colCtr)
                {
                    cout.width(12);
                    cout.setf(ios::left);
                    cout << "~~~~~~~~~~~~ ";
                }
                cout << endl;
            }
        }
    }
    sqlite3_free_table(results);

}

char* coyoouDB::getError()
{
    return error;
}
