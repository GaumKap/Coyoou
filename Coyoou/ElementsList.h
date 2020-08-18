#pragma once
#include <iostream>
#include <vector>
#include "coyoouDB.h"
#include "Element.h"
using namespace std;

class ElementsList
{
public:
	ElementsList(coyoouDB* db);
	~ElementsList();
	int add(Element* obj); // Add element in list of Elements
	int remove(int id); // Remove Target object from list
	int edit(int id, string name, string topic, string price, string date); // Edit element Target from list
	int clear(); // Clear all list (long process)
	Element* search(int id); // Search by ID
	void search(vector<Element*> *targ_tab, string method, string req); //search by something else
	void search(vector<Element*>* targ_tab,string req[2]); // Search by date
	void getAll(vector<Element*>* targ_tab, int limit); // Get All table or set a limit
	/* Soon Set start position on getAll or others search function for GUI*/
	void updateList();
private:
	static void sendLog(string log) {
		FILE* f;
		errno_t err;
		err = fopen_s(&f, "coyoou.log", "a+"); // a+ (create + append) option will allow appending which is useful in a log file
		if (f == NULL) {
			std::cout << "[FATAL ERROR] LOG FILE : " << err << std::endl;
		}
		else {
			fprintf(f, log.c_str());
			fclose(f);
		}
	}
	int getIterator(int id);
	vector<Element*> m_list; // List of Elements
	coyoouDB* asso_db; // Association with coyoou DB SQLite class.

};

