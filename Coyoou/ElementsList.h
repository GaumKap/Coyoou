#pragma once
#include "Element.h"
#include <iostream>
#include <list>
#include "coyoouDB.h"
using namespace std;

struct Element {
	int id;
	string name;
	string topic;
};
class ElementsList
{
public:
	ElementsList(coyoouDB* db);
	~ElementsList();
	int add(Element* obj);
	int remove(int l_id); // Remove Target object from list
	int edit(int l_id); // Edit element Target from list
	int clear(); // Clear all list (long process)
	Element* search(int id); //search in list element with id
private:
	Element* m_start_id;
	Element* m_end_id;
	list<Element*> m_list;
	coyoouDB* asso_db;

};

