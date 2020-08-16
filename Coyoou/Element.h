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