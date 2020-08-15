#include "ElementsList.h"

int ElementsList::add(Element* obj)
{
    if (m_list.size() < 1)
    {
        m_list.begin();
    }
    else {
        m_list.push_front(new Element());
    }
    return 0;
}

ElementsList::ElementsList(coyoouDB* db)
{
    asso_db = db;
}

ElementsList::~ElementsList()
{
    m_list.clear();
}

int ElementsList::remove(int l_id)
{
    return 0;
}

int ElementsList::edit(int l_id)
{
    return 0;
}

int ElementsList::clear()
{
    return 0;
}

Element* ElementsList::search(int id)
{
    list<Element*>::iterator begin = m_list.begin();
    Element* target = nullptr;
    bool isFound = false;
    while (begin != m_list.end() || isFound == true) {
        Element* var = *begin;
        if (var->id == id) {
            target = var;
            isFound = true;
        }
        begin++;
    }
    if (target == nullptr) {
        // Action when nullptr or do something in function
        // how call this method
    }
    return target;
}
