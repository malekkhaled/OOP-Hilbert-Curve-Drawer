//DRIVER: Thomas Bivins
//NAVIGATOR: Malek Khaled Zaben

#include <iostream>
#include "instruction_list.h"

using namespace std;

//operator<<: override function for the << operator
ostream& operator<<(ostream& out, const InstructionList& list)
{
  
  if (list.head == nullptr) //iterator.begin() == nullptr?
  {
    out << "There is no data in the list.\n";
    return out;
  }
  else
  {
    InstructionList::node_t* temp = list.head;
    while (temp != nullptr)
    {
      if (temp->move == 0)
      {
        out << "F ";
      }
      else if (temp->move == 1)
      {
        out << "L ";
      }
      else if (temp->move == 2)
      {
        out << "R ";
      }
      else if (temp->move == 3)
      {
        out << "O ";
      }
      else if (temp->move == 4)
      {
        out << "E ";
      }
      temp = temp->next;
    }
    return out;
  }
}

//append: inserts a pointer to the end of the specified InstructionList
void InstructionList::append(hilbert_t move)
{
  node_t* n = new node_t;
  n->next = nullptr;
  n->move = move;
  if (head == nullptr)
  {
    head = n;
  }
  else
  {
    node_t* iter = head;
    while (iter->next != nullptr)
    {
        iter = iter->next;
    }
    iter->next = n;
    tail = n;
  }
}

//~InstructionList: deallocates and deletes an object of type InstructionList
InstructionList::~InstructionList()
{
  node_t* iter = head;
  node_t* temp;
  while (iter != nullptr)
  {
    temp = iter->next;
    delete iter;
    iter = temp;
  }
}

//Substitute: replaces a move in the rules InstructionList with another set of moves specified by the rules sent to the function in a map structure
void InstructionList::substitute(const unordered_map<hilbert_t, const InstructionList*>& map)
{
  node_t* iter = head;
  node_t* temp;
  while (iter != nullptr)
  {
    auto it2 = map.find(iter->move);
    if (it2 != map.end())     //if a match is found
    {
      const InstructionList* insIL = map.at(iter->move);
      
      node_t* insIter = insIL->head;
      
      temp = iter->next;
      node_t* now;
      int i = 0;
      while (insIter != nullptr)
      {
        
        if (i == 0)
        {
          iter->move = insIter->move;
          now = iter;
        }
        else
        {
          node_t* newNode = new node_t;
          newNode->move = insIter->move;
          now->next = newNode;
          now = newNode;
        }
        
        i++;
        insIter = insIter->next;
        
      }
      now->next = temp;
      iter = now->next;
      

    }
    else
    {
      iter = iter->next;
    }
  }
}
