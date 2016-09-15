#ifndef BSMTREE_H
#define BSMTREE_H


class BSMTree
{
    private:    // Ιδιωτικός τομέας κλάσης

        typedef struct TreeNode {       // Η δομή του κόμβου του δυαδικού δέντρου αναζήτησης που
            int priority;               // λειτουργεί ταυτόχρονα ως σωρό μεγίστων, περιλαμβάνει
            int element;                // προτεραιότητα, τιμή στοιχείου, καθώς και δείκτες προς
            TreeNode* leftChild;        // τα δύο του παιδιά, κενά ή μη, αριστερά ή δεξιά. Χρησιμοποιείται
            TreeNode* rightChild;       // ο ορισμός typedef για τον ευκολότερο συμβολισμό ενός δείκτη
        }* TreeNodePtr;                 // τύπου TreeNode, ως TreeNodePtr αντί για TreeNode*

        TreeNodePtr rootNode;       // Βοηθητικοί δείκτες για
        TreeNodePtr currNode;       // δυαδική αναζήτηση, διάσχιση
        TreeNodePtr parentNode;     // των δέντρων, προσθήκη
        TreeNodePtr tempNode;       // καθώς και διαγραφή κόμβου

        void PreOrder(TreeNodePtr t);       // Προδιάταξη
        void InOrder(TreeNodePtr t);        // Ενδοδιάταξη
        void PostOrder(TreeNodePtr t);      // Μεταδιάταξη
        void LeverOrder(TreeNodePtr t);     // Διάσχιση ανά επίπεδα
        void InOrderEditedV1(TreeNodePtr t, int RefElement, int &counter, bool &secondNextFound, int &element);     // Αναδρομικές συναρτήσεις, αποτελούν τροποποιημένες μορφές ενδοδιάταξης
        void InOrderEditedV2(TreeNodePtr t, int startNum, int endNum, bool &numsExist, bool &numsCease);            // και καλούνται από τις Find_second_next και Print_between, αντίστοιχα

    public:     // Δημόσιος τομέας κλάσης

        BSMTree();          // Συνάρτηση κατασκευής αντικειμένου (δυαδικού δέντρου αναζήτησης - σωρού μεγίστων)
        bool AddTreeNode(int addPriority, int addElement);      // Προσθήκη νέου κόμβου
        bool DeleteTreeNode(int delElement);                    // Διαγραφή υπάρχοντος κόμβου
        void PrintPreOrder();       // Εκτύπωση προδιάταξης στην οθόνη
        void PrintInOrder();        // Εκτύπωση ενδοδιάταξης στην οθόνη
        void PrintPostOrder();      // Εκτύπωση μεταδιάταξης στην οθόνη
        void PrintLevelOrder();     // Εκτύπωση διάσχισης ανά επίπεδα στην οθόνη
        int Find_second_next(int refElement);               // Επιστροφή του δεύτερου μικρότερου στοιχείου, από όλα τα στοιχεία, που είναι μεγαλύτερα του refElement
        void Print_between(int startNum, int endNum);       // Εμφάνιση στην οθόνη, των στοιχείων που βρίσκονται μέσα στο διάστημα [startNum, endNum]

};

#endif // BSMTREE_H
