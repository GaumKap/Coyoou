#pragma once
#include "sqlite3.h"
#include <iostream>
#include "errors_list.h"
#include <string>
#include <vector>
#include <time.h>
#include <sstream>
#include "Element.h"

using namespace std;
class coyoouDB
{
public:
	coyoouDB(string target);
	~coyoouDB();
	int createTable(string name);
	int removeTable(string name);
	int createElement(string name, string topic, string date, string price);
	int removeElement(int id);
	int editElement(int id, string name, string topic, string date, string price);
	void searchElement(vector<Element*>* l_list, string selector="none;none");
	string getTimeNow();
	char* getError();
private:
	int rc;
	char* error = nullptr;
	sqlite3* db;
	string m_tableTarget;
};

