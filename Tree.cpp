/*************************************************
 * ADS Praktikum 1.2
 * Tree.cpp
 * Erweiterung um Hilfsfunktionen gestattet.
 *************************************************/
#include "Tree.h"
#include "TreeNode.h"
#include <iostream>

// Public
Tree::Tree() : m_anker(nullptr), m_currentNodeChronologicalID(0) {}

Tree::~Tree() {
    deleteTree(m_anker);
}

void Tree::addNode(std::string name, int age, double income, int postcode) {
    TreeNode *newNode = new TreeNode(calculateNodeOrderID(age, income, postcode),
                                     m_currentNodeChronologicalID++, name, age, income, postcode);
    if (!m_anker) { // falls Baum leer.
        m_anker = newNode;
    } else {
        TreeNode *current = m_anker;
        TreeNode *parent = nullptr; // Elternknoten.
        while (current != nullptr) {    // Baum durchlaufen, um die richtige Position für den neuen Knoten zu finden.
            parent = current;
            //  Wenn NodeOrderID des neuen Knotens < als des aktuellen Knotens, geht der Algorithmus zum linken Kindknoten.
            if (newNode->getNodeOrderID() < current->getNodeOrderID())
                current = current->getLeft();
            else    //sonst zum rechten
                current = current->getRight();
        }
        // Neunen Knoten entweder als linker oder rechter Kindknoten des Elternknotens.
        if (newNode->getNodeOrderID() < parent->getNodeOrderID())
            parent->setLeft(newNode);
        else
            parent->setRight(newNode);
    }
}

bool Tree::deleteNode(int NodeOrderID) {
    TreeNode *parent = nullptr, *node = m_anker;

    while (node != nullptr && node->getNodeOrderID() != NodeOrderID) {
        parent = node;  // Elternknoten speichern
        if (NodeOrderID < node->getNodeOrderID())
            node = node->getLeft(); // Links gehen, wenn der gesuchte Wert kleiner ist.
        else
            node = node->getRight();
    }
    if (!node) return false; // Knoten nicht gefunden.

    /// Fall: nur ein Kind oder kein Kind.
    if (node->getLeft() == nullptr || node->getRight() == nullptr) {
        TreeNode *newChild = node->getLeft() ? node->getLeft() : node->getRight();
        if (!parent) {
            m_anker = newChild; // Wenn 'node' die Wurzel ist, wird 'newChild' zur neuen Wurzel.
        } else if (parent->getLeft() == node) {
            parent->setLeft(newChild);  // Das linke Kind des Elternknotens setzen, wenn 'node' ein linkes Kind ist.
        } else {
            parent->setRight(newChild);
        }
    } else { /// Fall: 2 Kinder.
        // In-Order-Nachfolger finden (kleinster Knoten im rechten Unterbaum).
        TreeNode *successor = getMinimum(node->getRight());
        TreeNode *successorParent = parentOf(successor);    // Elternknoten des Nachfolgers bestimmen.
        if (successorParent != node) {
            transplant(successor, successor->getRight(), successorParent); // Nachfolger transplantieren.
            successor->setRight(node->getRight());  // Das rechte Kind des nachfolgers setzen.
        }
        transplant(node, successor, parent); // 'node' durch den Nachfolger ersetzen.
        successor->setLeft(node->getLeft());    // Das linke Kind des Nachfolgers setzen.
    }
    delete node;
    return true;
}

bool Tree::searchNode(std::string name) {
    return searchRecursive(m_anker, name);
}

void Tree::printAll() {
    printInOrder(m_anker);
}

void Tree::levelOrder() {
    int h = height(m_anker);    // Höhe des Baumes bestimmen.
    for (int i = 1; i <= h; i++)     // Durchlaufen durch Ebenen.
        printGivenLevel(m_anker, i); // Alle Knoten aus der aktuellen Ebene 'i'.
}


/// Hilfsfunktionen

// Ersetzt den Knoten 'oldNode' mit 'newNode' im Baum. (Buch Seite 299)
void Tree::transplant(TreeNode *oldNode, TreeNode *newNode, TreeNode *parent) {
    if (parent == nullptr) {
        m_anker = newNode; // oldNode ist die Wurzel des Baumes.
    } else if (oldNode == parent->getLeft()) {
        parent->setLeft(newNode);
    } else {
        parent->setRight(newNode);
    }
}

TreeNode *Tree::getMinimum(TreeNode *node) {
    if (node == nullptr) return nullptr;
    while (node->getLeft() != nullptr) {  // Geht so weit wie möglich nach links.
        node = node->getLeft();
    }
    return node;
}

TreeNode *Tree::parentOf(TreeNode *node) {
    TreeNode *current = m_anker;
    TreeNode *parent = nullptr;
    while (current != nullptr && current != node) {
        parent = current;
        if (node->getNodeOrderID() < current->getNodeOrderID())
            current = current->getLeft();
        else
            current = current->getRight();
    }
    return parent;
}

void Tree::printGivenLevel(TreeNode *node, int level) {
    if (!node) return;
    if (level == 1)
        node->print(); // Wenn 1 erreicht -> Knoten "drucken"
    else if (level > 1) {
        // Rekursive Aufrufe für den linken und rechten Unterbaum.
        printGivenLevel(node->getLeft(), level - 1);
        printGivenLevel(node->getRight(), level - 1);
    }
}

int Tree::height(TreeNode *node) {
    if (!node) return 0;
    else {
        // Rekursiver Aufruf für den linken und rechten Kindknoten des aktuellen Knotens
        int lheight = height(node->getLeft());
        int rheight = height(node->getRight());

        // Den größeren + 1 zurückgeben.
        /*
         * Die Addition von 1 berücksichtigt den aktuellen Knoten selbst im Pfad.
         * Das bedeutet, dass die Gesamthöhe des Baumes die Höhe des längsten Pfades vom
         * aktuellen Knoten bis zum tiefsten Blattknoten ist, plus der aktuelle Knoten selbst.
         */
        return (lheight > rheight ? lheight : rheight) + 1;
    }
}

int Tree::calculateNodeOrderID(int age, double income, int postcode) {
    return age + static_cast<int>(income) + postcode;
}

/// Wraper-Funktionen
void Tree::publicPrintPreOrder() {
    cout << "ID | Name       | Age | Income | PostCode | OrderID\n";
    cout << "---+------------+-----+--------+----------+--------\n";
    printPreOrder(m_anker);
}

void Tree::publicPrintInOrder() {
    printInOrder(m_anker);
}

void Tree::publicPrintPostOrder() {
    printPostOrder(m_anker);
}

void Tree::deleteTree(TreeNode *node) {
    if (node == nullptr) return;

    // Rekursiver Aufruf für den linken und rechten Kindknoten des aktuellen Knotens.
    deleteTree(node->getLeft());
    deleteTree(node->getRight());

    // Aktuellen Knoten löschen.
    delete node;
}

bool Tree::searchRecursive(TreeNode *node, std::string name) {
    if (node == nullptr) {
        return false;
    }

    // Überprüfung des aktuellen Knotens.
    if (node->getName() == name) {
        return true;
    }
    // Linken und rechten Kindnoten rekursiv suchen.
    return searchRecursive(node->getLeft(), name) || searchRecursive(node->getRight(), name);
}

void Tree::printNodesWithNameRecursive(TreeNode *node, std::string name) {
    if (node == nullptr) {
        return;
    }
    if (node->getName() == name) {
        node->print();
    }
    printNodesWithNameRecursive(node->getLeft(), name);
    printNodesWithNameRecursive(node->getRight(), name);
}

/// Private-Funktionen
void Tree::printPreOrder(TreeNode *node) {
    if (node == nullptr) return;
    node->print();  // Druckt die Daten des aktuellen Knotens, vor seine Kinder.

    // Rekursiver Aufruf für den linken und rechten Kindknoten.
    printPreOrder(node->getLeft());
    printPreOrder(node->getRight());
}

void Tree::printInOrder(TreeNode *node) {

    // Basisfall
    if (node == nullptr) return;

    // Rekursiver Aufruf: durch den linken Teilbaum
    /*
     * Dieser Aufruf erkundet den gesamten linken Teilbaum des aktuellen Knotens,
     * bevor der Knoten selbst bearbeitet wird. Das bedeutet, dass alle Knoten,
     * die kleiner sind als der aktuelle Knoten, zuerst besucht und gedruckt werden.
     */
    printInOrder(node->getLeft());

    // Erstmal linker Teilbaum, dann der aktuelle Knoten, dann rechter Teilbaum => aufsteigende Reihenfolge
    node->print();
    printInOrder(node->getRight());
}

void Tree::printPostOrder(TreeNode *node) {
    if (node == nullptr) return;

    // Rekursiver Aufruf für den linken und rechten Kindknoten des aktuellen Knotens.
    printPostOrder(node->getLeft());
    printPostOrder(node->getRight());

    // Nach Kinder, Daten des aktuellen Knotens drucken.
    node->print();
}
