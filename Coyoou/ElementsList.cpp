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
    try {
        m_list.push_back(obj); // add at end of vector
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
        else m_list.erase(m_list.begin()+it); // Remove element from vector list
    }
    catch (int e) {
        cout << "[ERROR] Error when remove Element in ElementList::remove - " << e << endl;
    }
    return 0; // Modification Required
}

// Edit Element
int ElementsList::edit(int l_id)
{
    Element* obj = this->search(l_id); // Get pointer of Element in vector list
    obj->set("name", "ElementsList::edit"); // Edit Element object
    return 0; // Modification Required
}

//Clear all vector List
int ElementsList::clear()
{
    m_list.clear();
    return 0;
}

// Search in vector list a Element with id 
Element* ElementsList::search(int id)
{
    Element* target = nullptr; // Init empty object
    bool isFound = false; // Modification Required
    for (int i = 0; i < m_list.size(); ++i) {
        if (m_list[i]->getID() == id) {
            target = m_list[i]; // target is now pointing Element
        }
    }
    return target; // return Element pointer
}

// Get position of Element in vector List [usable by methods of this class only]
int ElementsList::getIterator(int id)
{
    int target = -1; 
    bool isFound = false; // Modification Required
    for (int i = 0; i < m_list.size(); ++i) {
        if (m_list[i]->getID() == id) {
            target = i;
        }
    }
    return target;
}
