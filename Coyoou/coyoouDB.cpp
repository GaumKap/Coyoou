//////////////////////////////////////////////////////////////
// methods of ElementsList.h Class
// Some methods is based/Copied on Tutorials of SQLite 
// GaumKap, https://www.sqlite.org
// 16/08/2020
//////////////////////////////////////////////////////////////

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
        //std::cout << "Opened CoyoouDB.db." << std::endl << std::endl;
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
    //cout << "Creating " + name + " Table ..." << endl;
    string sqlCreateTable = "CREATE TABLE if not exists " + name + " (id INTEGER PRIMARY KEY, name STRING,date DATETIME,topic STRING,price STRING);";
    rc = sqlite3_exec(db, sqlCreateTable.c_str(), NULL, NULL, &message);
    if (rc)
    {
        cerr << "Error executing SQLite3 statement: " << sqlite3_errmsg(db) << endl << endl;
        sqlite3_free(message);
        e = CYO_DB_WRITE_ERROR;
    }
    else
    {
        //cout << "Created " + name + "." << endl << endl;
    }
    return e;
}

//Supression d'une Table et tout ce qui la compose dans la base de données
int coyoouDB::removeTable(string name)
{
    int e = CYO_DB_SUCCESS;

    cout << "Remove Table ..." << endl;
    string sqlQuery2 = "DELETE TABLE if exists " + name + ";";
    rc = sqlite3_exec(db, sqlQuery2.c_str(), NULL, NULL, &error);
#ifdef DEBUG
    cout << ">-SQL-< : " + rc << endl; // DEBUG INFO
#endif // DEBUG
    return e;
}

// Create Date in Database
// If sucess function send 100
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
void coyoouDB::searchElement(vector<Element*>* l_list, string selector)
{
    // Display MyTable
    //cout << "Retrieving values in MyTable ..." << endl;
    string sqlSelect;

    std::string s = selector;
    std::string delimiter = ";";
    // Parse string to get "token"
    size_t pos = 0;
    string token = s.substr(0, s.find(delimiter));
    s.erase(0, s.find(delimiter) + delimiter.length());

    //Condtition WHERE ...
    if (token == "date") {
        sqlSelect = "SELECT * FROM " + m_tableTarget + " WHERE date=\""+s+"\";";
    }
    else if (token == "name") {
        sqlSelect = "SELECT * FROM " + m_tableTarget + " WHERE name=\"" + s + "\";";
    }
    else if (token == "tag") {
        sqlSelect = "SELECT * FROM " + m_tableTarget + " WHERE topic=\"" + s + "\";";
    }
    else if (token == "price") {
        sqlSelect = "SELECT * FROM " + m_tableTarget + " WHERE price=" + s + ";";
    }
    else if (token == "dateperiod"){
        string begin = s.substr(0, s.find(delimiter));
        s.erase(0, s.find(delimiter) + delimiter.length());
        // sql: SELECT * FROM Table WHERE date<="2012-04-23T18:25:43.511Z" AND date>="2010-04-23T18:25:43.511Z"
        sqlSelect = "SELECT * FROM " + m_tableTarget + " WHERE date<=\"" + s + "\" AND date>=\""+ begin +"\";";
    }
    else
    {
        sqlSelect = "SELECT * FROM " + m_tableTarget + ";";
    }
    
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
        // Position 0 : id ;
        // 1 : name;
        // 2 : date;
        // 3 : topic;
        // 4 : prix
        int position = 0;

        
        // Display Table
        for (int rowCtr = 0; rowCtr <= rows; ++rowCtr)
        {
            string values[5];
            position = 0;
            for (int colCtr = 0; colCtr < columns; ++colCtr)
            {
                // Determine Cell Position
                int cellPosition = (rowCtr * columns) + colCtr;

                // Display Cell Value
                //cout.width(12);
                //cout.setf(ios::left);
                //cout << results[cellPosition] << " ";
                if (position == 0) {
                    
                    values[0] = results[cellPosition];
                }
                else if (position == 1) {
                    values[1] = results[cellPosition];
                }
                else if (position == 2) {
                    values[2] = results[cellPosition];
                }
                else if (position == 3) {
                    values[3] = results[cellPosition];
                }
                else if (position == 4) {
                    values[4] = results[cellPosition];
                }
                position++;
            }

            // End Line
            //cout << endl;
            if (rowCtr != 0)l_list->push_back(new Element(stoi(values[0]), values[1], values[3], values[2], values[4]));
            // Display Separator For Header
            if (0 == rowCtr)
            {
                for (int colCtr = 0; colCtr < columns; ++colCtr)
                {
                    //cout.width(12);
                    //cout.setf(ios::left);
                    //cout << "~~~~~~~~~~~~ ";
                }
                //cout << endl;
            }
        }
    }
    sqlite3_free_table(results);

}

// -- Get current time -- 
//  tm.tm_year : years
//  tm.tm_mon + 1 : month +1 to (january = 0)
//  tm.tm_mday : day
//  tm.tm_hour : hours
//  tm.tm_min : minutes
//  tm.tm_sec : seconds
string coyoouDB::getTimeNow()
{
    string date;
    time_t t = time(NULL);
    struct tm tm;
    localtime_s(&tm, &t);
    // Exemple 2012-04-23T18:25:43.511Z
    stringstream cc;
    cc << (1900 + tm.tm_year) << "-" << (tm.tm_mon + 1) << "-" << tm.tm_mday << "T" << tm.tm_hour << ":" << tm.tm_min << ":" << tm.tm_sec << ".000Z";
    date = cc.str();
    //cout << date << endl;
    return date;
}

char* coyoouDB::getError()
{
    return error;
}
