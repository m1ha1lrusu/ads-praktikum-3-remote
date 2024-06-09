/*************************************************
 * ADS Praktikum 1.2
 * Tree.h
 * Erweiterung um Hilfsattribute und -funktionen gestattet, wenn erforderlich.
 *************************************************/
#pragma once

#include "TreeNode.h"
#include "catch.h"
#include <string>

using namespace std;

class Tree {

private:
    TreeNode *m_anker;  // Wurzelknoten des Baums.
    int m_currentNodeChronologicalID;   // Fortlaufende ID, die bei der Erstellung eines neuen Knotens vergeben wird.

    void printPreOrder(TreeNode *node);
    void printInOrder(TreeNode *node);
    void printPostOrder(TreeNode *node);

    // Hilfsfunktionen
    void deleteTree(TreeNode *node);
    bool searchRecursive(TreeNode *node, std::string name);
    void printNodesWithNameRecursive(TreeNode *node, std::string name);

public:
    Tree();
    ~Tree();
    void addNode(std::string name, int age, double income, int postcode);
    bool deleteNode(int NodeOrderID);
    bool searchNode(std::string name);

    void printNodesWithName(std::string name) {
        printNodesWithNameRecursive(m_anker, name);
    }

    void printAll();
    void levelOrder();
    void printGivenLevel(TreeNode *node, int level);
    int height(TreeNode *node);
    static int calculateNodeOrderID(int age, double income, int postcode);
    void transplant(TreeNode *oldNode, TreeNode *newNode, TreeNode *oldNodeParent);
    TreeNode* parentOf(TreeNode* node);
    TreeNode* getMinimum(TreeNode* node);

    // Wraper-Funktionen
    void publicPrintPreOrder();
    void publicPrintInOrder();
    void publicPrintPostOrder();

    friend TreeNode *get_anker(Tree &TN);


};
