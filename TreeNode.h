/*************************************************
 * ADS Praktikum 1.2
 * TreeNode.h
 * Erweiterung um Hilfsattribute und -funktionen gestattet, wenn erforderlich.
 *************************************************/
#pragma once

#include <string>
#include <iomanip>
#include "iostream"

using namespace std;

class TreeNode {

private:
    int m_NodeOrderID;  // ID, die die Reihenfolge der Knoten im Baum bestimmt.
    int m_NodeChronologicalID;  // ID, die die Reihenfolge der Knoten basierend auf ihrer Erstellungszeit bestimmt.
    std::string m_Name;
    int m_Age;
    double m_Income;
    int m_PostCode;
    TreeNode *m_left;   // Zeiger auf den linken Kindknoten.
    TreeNode *m_right;  // Zeiger auf den rechten Kindknoten.
    int m_level{};        // Ebene des Knotens im Baum.

public:
    TreeNode(int nNodePos, int id, string name, int alter, double einkommen, int plz);
    //TreeNode(int nNodePos, int id, string name, int alter, double einkommen, int plz, int level);
    /*
    TreeNode(int NodeOrderID, int NodeChronologicalID, std::string Name, int Age, double Income, int PostCode)
            : m_NodeOrderID(NodeOrderID), m_NodeChronologicalID(NodeChronologicalID), m_Name(Name), m_Age(Age),
              m_Income(Income), m_PostCode(PostCode), m_left(nullptr), m_right(nullptr) {}
    */

    int getNodeOrderID() const { return m_NodeOrderID; }
    void setNodeOrderID(int NodeOrderID) { m_NodeOrderID = NodeOrderID; }

    int getNodeChronologicalID() const { return m_NodeChronologicalID; }
    void setNodeChronologicalID(int NodeChronologicalID) { m_NodeChronologicalID = NodeChronologicalID; }

    std::string getName() const { return m_Name; }
    void setName(std::string Name) { m_Name = Name; }

    int getAge() const { return m_Age; }
    void setAge(int Age) { m_Age = Age; }

    double getIncome() const { return m_Income; }
    void setIncome(double Income) { m_Income = Income; }

    int getPostCode() const { return m_PostCode; }
    void setPostCode(int PostCode) { m_PostCode = PostCode; }

    TreeNode *getLeft() const { return m_left; }
    void setLeft(TreeNode *left) { m_left = left; }

    TreeNode *getRight() const { return m_right; }
    void setRight(TreeNode *right) { m_right = right; }

    void print() {
        cout << setw(2) << setfill(' ') << m_NodeOrderID << " | "
             << left << setw(10) << m_Name << " | "
             << right << setw(2) << m_Age << " | "
             << setw(6) << m_Income << " | "
             << setw(8) << m_PostCode << " | "
             << setw(5) << m_NodeOrderID
             << setw(2) << m_level << endl << endl;
    }
};