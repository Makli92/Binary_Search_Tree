#include "BSMTree.h"                // Το αρχείο BSMTree.h είναι απαραίτητο για τη χρήση της κλάσης BSMTree

#include <iostream>
#include <queue>                    // Για τη διάσχιση ανά επίπεδα, είναι απαραίτητη η χρήση ουράς

using namespace std;

int main()
{
    BSMTree makli;              // Δημιουργία αντικειμένου (δυαδικού δέντρου αναζήτησης - σωρού μεγίστων)
    makli.Find_second_next(20);     // Εύρεση του δεύτερου μικρότερου στοιχείου από τα μεγαλύτερα του 20, Αποτυχία (κενό δέντρο)
    makli.Print_between(5, 9);      // Εμφάνιση των στοιχείων που βρίσκονται μέσα στο διάστημα [5, 9], Αποτυχία (κενό δέντρο)
    makli.DeleteTreeNode(30);       // Διαγραφή του στοιχείου 30, Αποτυχία (κενό δέντρο)
    makli.AddTreeNode(10, 10);          // Προσθήκη νέων
    makli.AddTreeNode(20, 20);          // κόμβων στο
    makli.AddTreeNode(30, 30);          // δυαδικό δέντρο
    makli.AddTreeNode(40, 40);          // αναζήτησης,
    makli.AddTreeNode(50, 50);          // καλώντας τη
    makli.AddTreeNode(60, 60);          // συνάρτηση AddTreeNode
    makli.PrintInOrder();           // Ενδοδιάταξη πριν τη διαγραφή του στοιχείου 30
    makli.DeleteTreeNode(30);       // Διαγραφή του στοιχείου 30
    makli.PrintInOrder();           // Ενδοδιάταξη μετά τη διαγραφή του στοιχείου 30
    makli.PrintPreOrder();          // Προδιάταξη
    makli.PrintPostOrder();         // Μεταδιάταξη
    makli.PrintLevelOrder();        // Διάσχιση κατά επίπεδα
    makli.Find_second_next(20);         // Εύρεση του δεύτερου μικρότερου στοιχείου από τα μεγαλύτερα του 20
    makli.Print_between(5, 9);          // Εμφάνιση των στοιχείων που βρίσκονται μέσα στο διάστημα [5, 9], Αποτυχία (κανένα στοιχείο)
    makli.Print_between(9, 40);         // Εμφάνιση των στοιχείων που βρίσκονται μέσα στο διάστημα [9, 40]

    return 0;
}
