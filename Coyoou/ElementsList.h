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
	int edit(int l_id); // Edit element Target from list
	int clear(); // Clear all list (long process)
	Element* search(int id); //search in list element with id

private:
	int getIterator(int id);
	vector<Element*> m_list; // List of Elements
	coyoouDB* asso_db; // Association with coyoou DB SQLite class.

};

