#pragma once
#include <iostream>

using namespace std;
class Element
{
public:
	Element(int id, string name, string topic, string price, string date);
	string get(string param);
	int set(string param, string val);
	int getID();
private:
	string m_name;
	// Indique le topic de l'élement extrait
	string m_topic;
	// This is the price get in DB
	string m_price;
	// Date in JSON Format
	string m_date;
	// Required id of element in DB
	int m_id;
};


struct SomeTIHNG {
	string m_name;
	// Indique le topic de l'élement extrait
	string m_topic;
	// This is the price get in DB
	string m_price;
	// Date in JSON Format
	string m_date;
	// Required id of element in DB
	int m_id;
};
// Just some informations about my program
// I have anothers class this is a list "ElementsList" and another class
// This is DB SQLite class
// and thoses codes will be used for draw a list of elements get in DB file
// I want Edit or delete Elements if i want in my DB by ElementsList class