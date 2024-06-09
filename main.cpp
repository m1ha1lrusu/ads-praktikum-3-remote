/*************************************************
 * ADS Praktikum 1.2
 * main.cpp
 *
 *************************************************/
#define CATCH_CONFIG_RUNNER

#include "Tree.h"
#include "catch.h"
#include <iostream>

using namespace std;

///////////////////////////////////////
// Hilfsmethoden fürs Menü hier:

/***************************
 ** Vorgegebene  Funktion **
 ***************************
   "mainscreen_addTreeCSV"

Importiert CSV Datei in bestehenden Baum.
Bei Aufruf in der main() Methode, muss der Pointer auf den Anker des Baums, als Parameter übergeben werden.
Es wird die im gleichen Verzeichnis liegende Datei "ExportZielanalyse.csv" geladen.
****************************/

void mainscreen_addTreeCSV(Tree *&ref) {
    char j;
    cout << "+ Moechten Sie die Daten aus der Datei ExportZielanalyse.csv "
            "importieren(j / n) ? >";
    cin >> j;
    if (j == 'j') {
        ifstream csvread;
        csvread.open(R"(C:\Users\rusum\CLionProjects\ADS\Praktikum\1-2\ExportZielanalyse.csv)", ios::in);
        if (!csvread.is_open()) {
            cout << "Fehler beim Lesen!" << endl;
            return;
        } else {
            string name, age, postcode, income;

            while (!csvread.eof()) {
                getline(csvread, name, ';');
                getline(csvread, age, ';');
                getline(csvread, income, ';');
                getline(csvread, postcode, '\n');
                ref->addNode(name, stoi(age), stod(income), stoi(postcode));
            }
            csvread.close();
        }
        cout << "+ Daten wurden dem Baum hinzugefuegt." << endl;
    }
}

///////////////////////////////////////
int main() {

    int result = Catch::Session().run();

    ///////////////////////////////////////
    // Ihr Code hier:
    Tree *tree = new Tree();
    int choice;
    string name;
    int age, postcode;
    double income;

    //CSV-Datei importieren
    mainscreen_addTreeCSV(tree);

    while (true) {
        cout << "=========================================\n";
        cout << "ADS - ELK - Stack v1.9, by 25th Bam\n";
        cout << "=========================================\n";
        cout << "1) Datensatz einfuegen, manuell\n";
        cout << "2) Datensatz einfuegen, CSV Datei\n";
        cout << "3) Datensatz loeschen\n";
        cout << "4) Suchen\n";
        cout << "5) Datenstruktur anzeigen (pre/post/in)\n";
        cout << "6) Level-Order Ausgabe\n";
        cout << "7) Beenden\n";
        cout << "?> ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "+ Bitte geben Sie die den Datensatz ein:\n";
                cout << "Name ?> ";
                cin >> name;
                cout << "Alter ?> ";
                cin >> age;
                cout << "Einkommen ?> ";
                cin >> income;
                cout << "PLZ ?> ";
                cin >> postcode;
                tree->addNode(name, age, income, postcode);
                cout << "+ Ihr Datensatz wurde eingefuegt\n";
                break;
            case 2:
                mainscreen_addTreeCSV(tree);
                break;
            case 3:
                int NodeOrderID;
                cout << "+ Bitte geben Sie den zu loeschenden Datensatz an\n";
                cout << "NodeOrderID ?> ";
                cin >> NodeOrderID;
                if (tree->deleteNode(NodeOrderID)) {
                    cout << "+ Eintrag wurde geloescht\n";
                } else {
                    cout << "+ Eintrag nicht gefunden\n";
                }
                break;
            case 4:
                cout << "+ Bitte geben Sie den zu suchenden Datensatz an\n";
                cout << "Name ?> ";
                cin >> name;
                if (tree->searchNode(name)) {
                    cout << "+ Fundstellen:\n";
                    tree->printNodesWithName(name);
                } else {
                    cout << "+ Keine Fundstellen\n";
                }
                break;
            case 5: {
                string order;
                cout << "Ausgabereihenfolge (pre/post/in) ?> ";
                cin >> order;
                if (order == "pre") {
                    tree->publicPrintPreOrder();
                } else if (order == "post") {
                    tree->publicPrintPostOrder();
                } else if (order == "in") {
                    tree->publicPrintInOrder();
                } else {
                    cout << "Ungültige Eingabe, bitte versuchen Sie es erneut.\n";
                }
            }
                break;
            case 6:
                tree->levelOrder();
                break;
            case 7:
                delete tree;
                return 0;
            default:
                cout << "Ungueltige Eingabe, bitte versuchen Sie es erneut.\n";
        }
    }

    //
    ///////////////////////////////////////
    system("PAUSE");

    return 0;
}
