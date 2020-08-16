//////////////////////////////////////////////////////////////
// methods of Element.h Class
//
// GaumKap
// 16/08/2020
//////////////////////////////////////////////////////////////
#include "Element.h"
#include "coyoouDB.h"

// Initialization of Object with name and id as required parameter
Element::Element(int id, string name, string topic = "", string price = "", string date = "")
{
    m_id = id;
    m_name = name;
    m_topic = topic;
    m_price = price;
    m_date = date;
}

// Get parameter by sending a string with name of parameter
string Element::get(string param)
{
    string selected = "";
    if (param == "name") selected = m_name;
    if (param == "topic") selected = m_topic;
    if (param == "price") selected = m_price;
    if (param == "date") selected = m_date;
    return selected;
}

// Set parameter by sending a string with name of parameter
int Element::set(string param, string val)
{
    if (param == "name") { m_name = val; }
    if (param == "topic") { m_topic = val; }
    if (param == "price") { m_price = val; }
    if (param == "date") { m_date = val; }
    return 0;
}


int Element::getID()
{
    // TODO: Ajoutez ici votre code d'implémentation..
    return m_id;
}
