
//////////////////////////////////////////////////////////////
// methods of ElementsList.h Class
//
// GaumKap
// 16/08/2020
//////////////////////////////////////////////////////////////
#include "ElementsList.h"

// Add a new Element in vector
int ElementsList::add(Element* obj)
{
    int e = 0;
    try {
        string time = asso_db->getTimeNow();
        e = asso_db->createElement(obj->get("name"), obj->get("topic"), time, obj->get("price"));
        if (e == CYO_DB_SUCCESS)this->updateList(); // update list (solution temporaire)
        else { 
            stringstream log;
            log << "[ERROR] " << e << " From Database at ElementsList::add\n";
            cout << log.str() << endl;
            this->sendLog(log.str());
        }
    }
    catch (int e) {
        cout << "[ERROR] - An exception occurred " << e << " in ElementList::add" << endl;
    }
    return 0; // Modification Required
}

// Initialisation of Object with an association with coyoouDB object
ElementsList::ElementsList(coyoouDB* db)
{
    asso_db = db;
    updateList();
}

// Destructor
ElementsList::~ElementsList()
{
    m_list.clear(); // Clear all List
}

// Remove specified Element in vector list by id
int ElementsList::remove(int id)
{
    int it = -1;
    it = getIterator(id); // Get position of Element
    try {
        if (it < 0) cout << "[INFO] Element don't exist in List - ElementsList::remove" << endl;
        else {
            asso_db->removeElement(m_list[it]->getID());
            m_list.erase(m_list.begin()+it); // Remove element from vector list
        }
    }
    catch (int e) {
        cout << "[ERROR] Error when remove Element in ElementList::remove - " << e << endl;
    }
    return 0; // Modification Required
}

// Edit Element
int ElementsList::edit(int id, string name = "", string topic = "", string price = "", string date = "")
{
    Element* obj = this->search(id); // Get pointer of Element in vector list
    bool modification = false;
    int e = 0;
    if (name != obj->get("name")) {
        obj->set("name", name); // Edit Element object
        modification = true;
    }
    if (topic != obj->get("topic")) {
        obj->set("topic", topic); // Edit Element object
        modification = true;
    }
    if (price != "" || price != obj->get("price")) {
        obj->set("price", price); // Edit Element object
        modification = true;
    }
    else if (price == "") { cout << "[INFO] Price not modified Can't be Empty" << endl; }
    if (date != "" || date != obj->get("date")) {
        obj->set("date", date); // Edit Element object
        modification = true;
    }
    else if (date == "") { cout << "[INFO] date not modified Can't be Empty (disabled in a0.0.1)" << endl;}

    if (modification) {
        e = asso_db->editElement(obj->getID(), obj->get("name"), obj->get("topic"), obj->get("date"), obj->get("price"));
    } else { cout << "[INFO] No Modification Made on Element..." << endl; }
    return e; // Modification Required
}

//Clear all vector List
int ElementsList::clear()
{
    m_list.clear();
    return 0;
}

// This function return an Element object from list
// Search by ID
Element* ElementsList::search(int id)
{
    Element* target = nullptr; // Init empty object
    bool isFound = false; // Modification Required
    for (unsigned int i = 0; i < m_list.size(); ++i) {
        if (m_list[i]->getID() == id) {
            target = m_list[i]; // target is now pointing Element
        }
    }
    return target;
}

// Search Element in list
// method : "name" or "topic"
// req : value of what we search
void ElementsList::search(vector<Element*> *targ_tab, string method, string req)
{
    Element* target = nullptr; // Init empty object
    bool isFound = false; // Modification Required
    if (method == "name") {
        for (unsigned int i = 0; i < m_list.size(); ++i) {
            if (m_list[i]->get("name") == req) {
                target = m_list[i]; // target is now pointing Element
            }
        }
    }
    else if (method == "topic") {
        for (unsigned int i = 0; i < m_list.size(); ++i) {
            if (m_list[i]->get("topic") == req) {
                target = m_list[i]; // target is now pointing Element
            }
        }
    }
    else {
        cout << "[ERROR] Invalide argument on ElementList::search" << endl;
        this->sendLog("[ERROR] Invalide argument on ElementList::search : " + method);
    }
}

// This function search Elements by date
// req[0] : start Period
// req[1] : end Period
//
// Also this Function execute an update on list 
void ElementsList::search(vector<Element*> *targ_tab,string selector)
{
    this->clear();
    asso_db->searchElement(&m_list, selector);
}

void ElementsList::getAll(vector<Element*>* targ_tab, int limit)
{
    targ_tab->clear();
    if (limit <= 0) {
        for (unsigned int i = 0; i < m_list.size(); i++) {
            targ_tab->push_back(m_list[i]);
        }
    }
    else {
        if (m_list.size() <= limit) {
            for (unsigned int i = 0; i < m_list.size(); i++) {
                targ_tab->push_back(m_list[i]);
            }
        }
        else {
            for (unsigned int i = 0; i < limit; i++) {
                targ_tab->push_back(m_list[i]);
            }
        }
    }
}


void ElementsList::updateList()
{
    this->clear();
    asso_db->searchElement(&m_list);
}

// Get position of Element in vector List [usable by methods of this class only]
int ElementsList::getIterator(int id)
{
    int target = -1; 
    bool isFound = false; // Modification Required
    for (unsigned int i = 0; i < m_list.size(); ++i) {
        if (m_list[i]->getID() == id) {
            target = i;
        }
    }
    return target;
}
