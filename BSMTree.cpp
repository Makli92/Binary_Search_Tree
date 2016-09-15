#include "BSMTree.h"                // Το αρχείο BSMTree.h είναι απαραίτητο για τη χρήση της κλάσης BSMTree

#include <iostream>
#include <queue>                    // Για τη διάσχιση ανά επίπεδα, είναι απαραίτητη η χρήση ουράς

using namespace std;

BSMTree::BSMTree()          // Συνάρτηση κατασκευής αντικειμένου (δυαδικού δέντρου αναζήτησης - σωρού μεγίστων)
{
    rootNode = NULL;        // Αρχικοποίηση τιμών
    currNode = NULL;        // όλων των βοηθητικών
    parentNode = NULL;      // δεικτών του δέντρου
    tempNode = NULL;        // με τιμή NULL
}


bool BSMTree::AddTreeNode(int addPriority, int addElement)          // Συνάρτηση προσθήκης νέου κόμβου
{
    bool helpingVar = true;         // Βοηθητική μεταβλητή για τον προσδιορισμό της επιτυχούς, ή μη, πρόσθεσης του κόμβου
    bool tempParExists = false;     // Βοηθητική μεταβλητή για τον προσδιορισμό της ύπαρξης, ή μη, γονικού κόμβου του γονέα του νέου κόμβου
    if (rootNode != NULL) {     // Η περίπτωση το δέντρο να μην είναι κενό

    // <------------------------------- Δυαδική αναζήτηση ------------------------------->

        /*
            Γίνεται δυαδική αναζήτηση στο δέντρο, με σκοπό να βρεθεί ο γονέας
            του νέου κόμβου, που πρόκειται να προστεθεί. Σε περίπτωση που βρεθεί
            ήδη υπάρχων κόμβος με τιμή στοιχείου ίση με addElement, η μεταβλητή
            helpingVar παίρνει τη τιμή false, και το πρόγραμμα επιστρέφει τιμή
            false, καθώς αποτυγχάνει η προσθήκη του νέου στοιχείου addElement. Σε
            αντίθετη περίπτωση, στο τέλος του βρόγχου, ο δείκτης parentNode έχει
            ένδειξη προς τον γονέα του νέου κόμβου, δηλαδή στον κόμβο στον οποίο
            πρέπει να εισαχθεί ο νέος κόμβος, ως παιδί. Με το βρόγχο while επιτυγχάνεται
            η δυαδική αναζήτηση, καθώς οι επαναλήψεις τερματίζονται όταν ο δείκτης
            currNode πάψει να έχει κάποια ένδειξη.
        */

        currNode = rootNode;        // Αρχικοποίηση, ο τρέχων δείκτης έχει ένδειξη στη ρίζα
        while (currNode) {          // Επαναλήψεις έως ότου ο δείκτης currNode πάψει να δείχνει προς κάποιο κόμβο
            parentNode = currNode;      // Αν υπάρχει ο currNode, τότε ο parentNode γίνεται ίσος με τον currNode
            if (currNode->element > addElement) {           // Δυαδική αναζήτηση
                currNode = currNode->leftChild;             // και μεταφορά στο
            } else if (currNode->element < addElement) {    // παιδί του δείκτη
                currNode = currNode->rightChild;            // currNode
            } else {
                cout << "Element " << addElement << " already exists!" << endl;     // Αν βρεθεί ήδη υπάρχων κόμβος με την ίδια τιμή (addElement),
                helpingVar = false;                                                 // η μεταβλητή helpingVar γίνεται false, εμφανίζεται σχετικό
                break;                                                              // μήνυμα και το πρόγραμμα εξέρχεται από τον βρόγχο while
            }
        }

        if (helpingVar) {                           // Η συνθήκη είναι αληθής όταν έχει βρεθεί ο γονέας του κόμβου που πρόκειται να προστεθεί, και το νέο στοιχείο δεν υπάρχει ήδη στο δέντρο
            TreeNodePtr NewNode = new TreeNode;             // Δημιουργία κόμβου, με
            NewNode->priority = addPriority;                // τιμή στοιχείου ίση με
            NewNode->element = addElement;                  // addElement, προτεραιότητα
            NewNode->leftChild = NULL;                      // ίση με addPriority, κενά
            NewNode->rightChild = NULL;                     // υπόδεντρα ως παιδιά (
            if (NewNode->element < parentNode->element) {   // καθώς είναι φύλλο), και
                parentNode->leftChild = NewNode;            // σύνδεση του νέου κόμβου
            } else {                                        // με τον γονέα του, καθώς
                parentNode->rightChild = NewNode;           // ο νέος κόμβος θα είναι
            }                                               // παιδί του parentNode

    // <------------------------------- Μέχρι εδώ ------------------------------->

    // <------------------------------- Περιστροφές του νέου κόμβου ------------------------------->

        /*
            Με τη χρήση του βρόγχου while, γίνεται περιστροφή μεταξύ του νέου κόμβου και του γονέα του,
            όσο η προτεραιότητα του νέου κόμβου είναι μεγαλύτερη του γονέα του (η προτεραιότητα του γονέα
            πρέπει να είναι μεγαλύτερη ή ίση με των παιδιών, συνεπώς δεν είναι ανάγκη να γίνει περιστροφή
            αν οι δύο προτεραιότητες είναι ίσες. Η λειτουργία του δεύτερου και εσωτερικού βρόγχου while,
            είναι η εύρεση του γονικού κόμβου του γονέα του νέου κόμβου, αν υπάρχει, ώστε μετά την περιστροφή
            να γίνεται σύνδεση του νέου κόμβου με τον κόμβο του ανώτερου επιπέδου. Για την εύρεση του ανώτερου
            αυτού κόμβου, αν αυτός υπάρχει (if (parentNode->element != rootNode->element) και συνεπώς tempParExists
            θα είναι ίσο με true), εκτελείται δυαδική αναζήτηση, στο τέλος της οποίας ο δείκτης tempNode θα
            έχει ένδειξη προς το ζητούμενο αυτό κόμβο.
        */

            while (NewNode->priority > parentNode->priority) {      // Επαναλήψεις όσο η προτεραιότητα του νέου κόμβου είναι μεγαλύτερη της γονικής
                currNode = rootNode;                                // Αρχικοποίηση, ο τρέχων δείκτης έχει ένδειξη στη ρίζα
                if (parentNode->element != rootNode->element) {         // Έλεγχος ύπαρξης γονέα στο ανώτερο επίπεδο
                    tempParExists = true;                               // Ο γονέας αυτός υπάρχει
                    while (currNode->element != parentNode->element) {          // Επαναλήψεις μέχρι ο τρέχων δείκτης να έχει ένδειξη προς το γονέα του νέου κόμβου
                        tempNode = currNode;                                    // Ο δείκτης tempNode δείχνει προς τον τρέχων δείκτη, όσο ο currNode είναι διάφορος του parentNode
                        if (currNode->element < parentNode->element) {          // Δυαδική αναζήτηση
                            currNode = currNode->rightChild;                    // και μεταφορά του
                        } else {                                                // δείκτη currNode
                            currNode = currNode->leftChild;                     // σε παιδί
                        }
                    }
                }

        // <------------------------------- Σύνδεση του ανώτερου γονέα με τον νέο κόμβο ------------------------------->

        /*
            Αν υπάρχει ο γονικός αυτός κόμβος, δηλαδή η συνθήκη if (tempParExists) είναι αληθής, γίνεται σύνδεση του κόμβου
            αυτού με τον νέο κόμβο. Δηλαδή ο νέος κόμβος γίνεται παιδί του γονικού κόμβου του γονεά του (ο tempNode είναι
            γονέας του parentNode, και NewNode, δηλαδή ο νέος κόμβος, είναι το παιδί του parentNode).
        */

                if (tempParExists) {
                    if (parentNode->element < tempNode->element) {
                        tempNode->leftChild = NewNode;
                    } else {
                        tempNode->rightChild = NewNode;
                    }
                }

        // <------------------------------- Μέχρι εδώ ------------------------------->

        // <------------------------------- Περιστροφή και προσδιορισμός των σωστών θέσεων των υποδέντρων των δύο κόμβων ------------------------------->

                if (NewNode->element < parentNode->element) {   // Αν ο νέος κόμβος, έχει μικρότερη τιμή στοιχείου, δηλαδή είναι αριστερό παιδί του parentNode,
                    if (NewNode->rightChild) {                          // γίνεται έλεγχος ύπαρξης δεξιού παιδιού του νέου
                        parentNode->leftChild = NewNode->rightChild;    // κόμβου. Αν υπάρχει, τότε γίνεται αριστερό παιδί
                    } else {                                            // του γονεά. Αλλιώς, το αριστερό παιδί του γονέα θα
                        parentNode->leftChild = NULL;                   // είναι κενό υπόδεντρο. Μετά από αυτό τον έλεγχο,
                    }                                                   // γίνεται η περιστροφή και ο γονέας γίνεται δεξί
                    NewNode->rightChild = parentNode;                   // παιδί του νέου κόμβου.
                } else {                                        // Αν ο νέος κόμβος, έχει μεγαλύτερη τιμή στοιχείου, δηλαδή είναι δεξί παιδί του parentNode,
                    if (NewNode->leftChild) {                           // γίνεται έλεγχος ύπαρξης αριστερού παιδιού του νέου
                        parentNode->rightChild = NewNode->leftChild;    // κόμβου. Αν υπάρχει, τότε γίνεται δεξί παιδί του
                    } else {                                            // γονέα. Αλλιώς, το δεξί παιδί του γονέα θα είναι
                        parentNode->rightChild = NULL;                  // κενό υπόδεντρο. Μετά από αυτό τον έλεγχο, γίνεται
                    }                                                   // η περιστροφή και ο γονέας γίνεται αριστερό παιδί
                    NewNode->leftChild = parentNode;                    // του νέου κόμβου.
                }

        // <------------------------------- Μέχρι εδώ ------------------------------->

        // <------------------------------- Προσδιορισμός του νέου γονέα του νέου κόμβου ------------------------------->

                if (tempParExists) {            // Αν τελικά υπήρχε ο κόμβος tempNode
                    parentNode = tempNode;      // ο νέος γονέας θα είναι αυτός.
                } else {                        // Αλλιώς, ο νέος κόμβος δεν έχει
                    rootNode = NewNode;         // γονέα, συνεπώς αποτελεί πλέον
                    break;                      // τη ρίζα του δέντρου. Έτσι, το
                }                               // πρόγραμμα εξέρχεται από το βρόγχο.
            }
        // <------------------------------- Μέχρι εδώ ------------------------------->

    // <------------------------------- Μέχρι εδώ ------------------------------->

            return true;        // Επιστροφή τιμής true, ως ένδειξη επιτυχίας της προσθήκης του νέου κόμβου
        } else {
            return false;       // Επιστροφή τιμής false, ως ένδειξη αποτυχίας της προσθήκης του νέου κόμβου, διότι το στοιχείο υπάρχει ήδη στο δέντρο
        }
    } else {                    // Η περίπτωση το δέντρο να είναι κενό
        TreeNodePtr NewNode = new TreeNode;             // Δημιουργία κόμβου, με τιμή
        NewNode->priority = addPriority;                // στοιχείου ίση με addElement,
        NewNode->element = addElement;                  // προτεραιότητα ίση με addPriority,
        NewNode->leftChild = NULL;                      // κενά υπόδεντρα ως παιδιά (
        NewNode->rightChild = NULL;                     // καθώς είναι φύλλο), και
        rootNode = NewNode;                             // ορισμός του ως ρίζα.
        return true;            // Επιστροφή τιμής true, ως ένδειξη επιτυχίας της προσθήκης του νέου κόμβου
    }
}


bool BSMTree::DeleteTreeNode(int delElement)                        // Συνάρτηση διαγραφής κόμβου
{
    bool elementFound = false;      // Βοηθητική μεταβλητή για τον προσδιορισμό της ύπαρξης, ή μη, του στοιχείου προς διαγραφή
    bool hasParent = false;         // Βοηθητική μεταβλητή για τον προσδιορισμό της ύπαρξης, ή μη, γονέα του στοιχείου προς διαγραφή
    if (rootNode) {             // Η περίπτωση το δέντρο να μην είναι κενό

    // <------------------------------- Δυαδική αναζήτηση ------------------------------->

        /*
            Εκτελείται η παρακάτω δυαδική αναζήτηση, με σκοπό την εύρεση του κόμβου που πρόκειται να διαγραφεί. Ο
            δείκτης που πρόκειται να χρησιμοποιηθεί για να έχει ένδειξη προς τον κόμβο αυτό είναι ο δείκτης currNode,
            ενώ ο δείκτης tempNode θα έχει βοηθητική χρήση. Σε περίπτωση που βρεθεί ο ζητούμενος κόμβος, η μεταβλητή
            elementFound παίρνει την τιμή true, και το πρόγραμμα εξέρχεται από το βρόγχο while. Σε αντίθετη περίπτωση,
            η δυαδική αναζήτηση συνεχίζει μέχρι ο δείκτης tempNode να μην έχει ένδειξη προς κάποιο κόμβο, η μεταβλητή
            elementFound θα παραμείνει false και το πρόγραμμα θα εξέλθει μόνο όταν τελειώσει η δυαδική αναζήτηση.
        */

        currNode = rootNode;
        tempNode = currNode;
        while (tempNode) {
            currNode = tempNode;
            if (tempNode->element > delElement) {
                tempNode = tempNode->leftChild;
            } else if (tempNode->element < delElement) {
                tempNode = tempNode->rightChild;
            } else {
                elementFound = true;
                break;
            }
        }

    // <------------------------------- Μέχρι εδώ ------------------------------->

    // <------------------------------- Περιστροφές του κόμβου προς διαγραφή ------------------------------->

        /*
            Αν η συνθήκη if (elementFound) είναι αληθής, δηλαδή υπάρχει ο ζητούμενος κόμβος, τότε με τη χρήση
            ενός βρόγχου while ξεκινά η διαδικασία των περιστροφών, όσο υπάρχει τουλάχιστον ένα παιδί του κόμβου
            προς διαγραφή. Μέσα στο βρόγχο αυτό, γίνεται ένας έλεγχος ύπαρξης γονέα του currNode. Συγκεκριμένα
            αν ο currNode ταυτίζεται με τη ρίζα, τότε δεν υπάρχει γονέας και η τιμή της μεταβλητής hasParent θα
            παραμείνει false. Αλλίως, θα γίνει true και θα εκτελεστεί δυαδική αναζήτηση για την εύρεση του γονέα
            αυτού, στον οποίο θα δείχνει ο parentNode.
        */

        if (elementFound) {     // Αν υπάρχει το στοιχείο προς διαγραφή
            while ((currNode->leftChild) || (currNode->rightChild)) {
                if (currNode->element != rootNode->element) {
                    hasParent = true;
                    tempNode = rootNode;
                    parentNode = tempNode;
                    while (tempNode->element != currNode->element) {
                        parentNode = tempNode;
                        if (tempNode->element > delElement) {
                            tempNode = tempNode->leftChild;
                        } else {
                            tempNode = tempNode->rightChild;
                        }
                    }
                }

        // <------------------------------- Περιστροφή και προσδιορισμός των σωστών θέσεων των υποδέντρων των δύο κόμβων ------------------------------->

        /*
            Αρχικά γίνεται ένας έλεγχος για τον προσδιορισμό της ύπαρξης των παιδιών του κόμβου προς διαγραφή. Συγκεκριμένα, αν ο κόμβος προς διαγραφή
            (currNode), έχει και τα δυο του παιδιά μη κενά, γίνεται έλεγχος μεταξύ των προτεραιοτήτων των δύο παιδιών, και επιλέγεται το παιδί με τη
            μεγαλύτερη τιμή προτεραιότητας (ο δείκτης tempNode παίρνει την ένδειξη του επιλεχθέντος παιδιού). Έτσι γίνεται η περιστροφή μεταξύ των κόμβων
            currNode και tempNode (ο κόμβος προς διαγραφή κατεβαίνει επίπεδο και γίνεται παιδί του tempNode).
        */

                if (currNode->leftChild && currNode->rightChild) {          // Αν ο κόμβος προς διαγραφή έχει και τα δυο του υπόδεντρα μη κενά
                    if (currNode->leftChild->priority >= currNode->rightChild->priority) {      // Αν το αριστερό παιδί έχει μεγαλύτερη προτεραιότητα από το δεξί παιδί,
                        tempNode = currNode->leftChild;                                         // ο δείκτης tempNode έχει ένδειξη προς το αριστερό παιδί του currNode.
                        if (tempNode->rightChild) {                                     // Αν το δεξί παιδί του tempNode είναι μη κενό,
                            currNode->leftChild = tempNode->rightChild;                 // αυτό γίνεται αριστερό παιδί του currNode,
                        } else {                                                        // αλλιώς, το αριστερό παιδί του currNode Θα
                            currNode->leftChild = NULL;                                 // είναι κενό, μετά την περιστροφή. Τα υπόλοιπα
                        }                                                               // υπόδεντρα, αν υπάρχουν, δεν αλλάζουν.
                        tempNode->rightChild = currNode;                                        // Ο currNode γίνεται δεξί παιδί του tempNode.
                    } else {                                                                    // Αν το δεξί παιδί έχει μεγαλύτερη προτεραιότητα από το αριστερό παιδί,
                        tempNode = currNode->rightChild;                                        // ο δείκτης tempNode έχει ένδειξη προς το δεξί παιδί του currNode.
                        if (tempNode->leftChild) {                                      // Αν το αριστερό παιδί του tempNode είναι μη κενό,
                            currNode->rightChild = tempNode->leftChild;                 // αυτό γίνεται δεξί παιδί του currNode, αλλιώς,
                        } else {                                                        // το δεξί παιδί του currNode θα είναι κενό, μετά
                            currNode->rightChild = NULL;                                // την περιστροφή. Τα υπόλοιπα υπόδεντρα, αν υπάρχουν
                        }                                                               // δεν αλλάζουν.
                        tempNode->leftChild = currNode;                                         // O currNode γίνεται αριστερό παιδί του tempNode.
                    }
                } else {                                                    // Αν ο κόμβος προς διαγραφή έχει τουλάχιστον ένα υπόδεντρο μη κενό
                    if (currNode->leftChild) {                                                  // Αν το αριστερό παιδί του currNode είναι μη κενό,
                        tempNode = currNode->leftChild;                                         // ο δείκτης tempNode έχει ένδειξη προς το παιδί αυτό.
                        if (tempNode->rightChild) {                                     // Αν το δεξί παιδί του tempNode είναι μη κενό,
                            currNode->leftChild = tempNode->rightChild;                 // αυτό γίνεται αριστερό παιδί του currNode,
                        } else {                                                        // αλλιώς, το αριστερό παιδί του currNode θα
                            currNode->leftChild = NULL;                                 // είναι κενό, μετά την περιστροφή. Τα υπόλοιπα
                        }                                                               // υπόδεντρα, αν υπάρχουν, δεν αλλάζουν.
                        tempNode->rightChild = currNode;                                        // Ο currNode γίνεται δεξί παιδί του tempNode.
                    } else if (currNode->rightChild) {                                          // Αν το δεξί παιδί του currNode είναι μη κενό,
                        tempNode = currNode->rightChild;                                        // ο δείκτης tempNode, έχει ένδειξη προς το παιδί αυτό.
                        if (tempNode->leftChild) {                                      // Αν το αριστερό παιδί του tempNode είναι μη κενό,
                            currNode->rightChild = tempNode->leftChild;                 // αυτό γίνεται δεξί παιδί του currNode, αλλιώς,
                        } else {                                                        // το δεξί παιδί του currNode θα είναι κενό, μετά
                            currNode->rightChild = NULL;                                // την περιστροφή. Τα υπόλοιπα υπόδεντρα, αν αυτά
                        }                                                               // υπάρχουν, δεν αλλάζουν.
                        tempNode->leftChild = currNode;                                         // O currNode γίνεται αριστερό παιδί του tempNode.
                    }
                }

        // <------------------------------- Μέχρι εδώ ------------------------------->

        // <------------------------------- Προσδιορισμός του νέου γονέα του κόμβου προς διαγραφή ------------------------------->

            /*
                Ο έλεγχος ύπαρξης του γονέα του κόμβου προς διαγραφή (δηλαδή ο γονέας parentNode του currNode), χρησιμοποιώντας τη συνθήκη
                if (hasParent), ουσιαστικά χρησιμεύει μόνο στην πρώτη επανάληψη, σε περίπτωση που ο κόμβος προς διαγραφή, δεν είχε γονέα,
                δηλαδή αποτελούσε τη ρίζα του δέντρου. Έτσι, μετά την περιστροφή η νέα ρίζα είναι ο κόμβος tempNode, δηλαδή ο κόμβος που πριν
                την περιστροφή αποτελούσε παιδί του κόμβου προς διαγραφή. Στις υπόλοιπες περιπτώσεις, ο νέος κόμβος parentNode, δηλαδή ο
                γονέας του currNode, θα είναι ο tempNode (μετά τη διαγραφή το παιδί του currNode αποτελεί πλέον γονέα του currNode).
            */

                if (hasParent) {
                    if (parentNode->leftChild && (parentNode->leftChild->element == currNode->element)) {
                        parentNode->leftChild = tempNode;
                    } else {
                        parentNode->rightChild = tempNode;
                    }
                } else {
                    rootNode = tempNode;
                }
            }

        // <------------------------------- Μέχρι εδώ ------------------------------->

    // <------------------------------- Μέχρι εδώ ------------------------------->

    // <------------------------------- Διαγραφή κόμβου ------------------------------->

        /*
            Το πρόγραμμα έχει εξέλθει από το βρόγχο while, συνεπώς, ο κόμβος currNode είναι πλέον φύλλο. Χρησιμοποιώντας την παρακάτω συνθήκη if - else,
            γίνεται προσδιορισμός του παιδιού του tempNode, το οποίο αποτελεί ο currNode, και ο δεσμός αυτός ελευθερώνεται (δηλαδή ο αντίστοιχος δείκτης
            του tempNode προς το currNode θα γίνει ίσος με NULL). Έτσι, αφού γίνει η διάσπαση του κόμβου προς διαγραφή από το υπόλοιπο δέντρο, ο κόμβος
            αυτός τελικά διαγράφεται (συγκεκριμένα, ελευθερώνεται ο χώρος που καταλάμβανε στη μνήμη).
        */

            if (tempNode->leftChild && (tempNode->leftChild->element == currNode->element)) {           // Αν ο currNode είναι αριστερό παιδί του tempNode,
                tempNode->leftChild = NULL;                                                             // το αριστερό παιδί του tempNode γίνεται κενό.
            } else {                                                                                    // Αν ο currNode είναι δεξί παιδί του tempNode,
                tempNode->rightChild = NULL;                                                            // το δεξί παιδί του tempNode γίνεται κενό.
            }
            delete currNode;                // Απελευθέρωση του χώρου που καταλάμβανε ο κόμβος currNode στη μνήμη
            return true;                    // Η συνάρτηση επιστρέφει τιμή true, η διαγραφή ολοκληρώθηκε επιτυχώς.

    // <------------------------------- Μέχρι εδώ ------------------------------->

        } else {                // Αν δεν υπάρχει το στοιχείο προς διαγραφή
            cout << "Element " << delElement << " does not exist..." << endl;       // Εμφάνιση επεξηγηματικού μηνύματος, και
            return false;                                                           // επιστροφή τιμής false, αποτυχία διαγραφής
        }
    } else {                    // Η περίπτωση το δέντρο να είναι κενό
        cout << "Element " << delElement << " cannot be found! The tree is already empty..." << endl;       // Εμφάνιση επεξηγηματικού μηνύματος, και
        return false;                                                                                       // επιστροφή τιμής false, αποτυχία διαγραφής.
    }
}


void BSMTree::PreOrder(TreeNodePtr t)           // Συνάρτηση προδιάταξης
{
    if (t) {                    // Αν υπάρχει ο κόμβος t
        cout << "\t" << t->priority << "," << t->element;       // Εμφάνιση της προτεραιότητας και του στοιχείου του κόμβου

        if (t->leftChild) {             // Αν υπάρχει αριστερό παιδί, εκτέλεση
            PreOrder(t->leftChild);     // προδιάταξης στο αριστερό υπόδεντρο
        }

        if (t->rightChild) {            // Αν υπάρχει δεξί παιδί, εκτέλεση
            PreOrder(t->rightChild);    // προδιάταξης στο δεξί υπόδεντρο
        }
    }
}


void BSMTree::InOrder(TreeNodePtr t)            // Συνάρτηση ενδοδιάταξης
{
    if (t) {                    // Αν υπάρχει ο κόμβος t
        if (t->leftChild) {             // Αν υπάρχει αριστερό παιδί, εκτέλεση
            InOrder(t->leftChild);      // ενδοδιάταξης στο αριστερό υπόδεντρο
        }

        cout << "\t" << t->priority << "," << t->element;       // Εμφάνιση της προτεραιότητας και του στοιχείου του κόμβου

        if (t->rightChild) {            // Αν υπάρχει δεξί παιδί, εκτέλεση
            InOrder(t->rightChild);     // ενδοδιάταξης στο δεξί υπόδεντρο
        }
    }
}


void BSMTree::PostOrder(TreeNodePtr t)          // Συνάρτηση μεταδιάταξης
{
    if (t) {                    // Αν υπάρχει ο κόμβος t
        if (t->leftChild) {             // Αν υπάρχει αριστερό παιδί, εκτέλεση
            PostOrder(t->leftChild);    // μεταδιάταξης στο δεξί υπόδεντρο
        }

        if (t->rightChild) {            // Αν υπάρχει δεξί παιδί, εκτέλεση
            PostOrder(t->rightChild);   // μεταδιάταξης στο αριστερό υπόδεντρο
        }

        cout << "\t" << t->priority << "," << t->element;       // Εμφάνιση της προτεραιότητας και του στοιχείου του κόμβου
    }
}


void BSMTree::LeverOrder(TreeNodePtr t)         // Συνάρτηση διάσχισης ανά επίπεδα
{
    queue <TreeNodePtr> q;          // Δημιουργία ουράς
    while (t) {                 // Όσο υπάρχει ο κόμβος t
        cout << "\t" << t->priority << "," << t->element;       // Εμφάνιση της προτεραιότητας και του στοιχείου του κόμβου

        if (t->leftChild) {             // Αν υπάρχει αριστερό παιδί,
            q.push(t->leftChild);       // αυτό εισάγεται στην ουρά
        }

        if (t->rightChild) {            // Αν υπάρχει δεξί παιδί,
            q.push(t->rightChild);      // αυτό εισάγεται στην ουρά
        }

        if (!q.empty()) {               // Αν η ουρά δεν είναι άδεια, ο τρέχον κόμβος
            t = q.front();              // γίνεται ο πρώτος κόμβος της ουράς, και στη
            q.pop();                    // συνέχεια αφαιρείται από την ουρά (δομή FIFO)
        } else {
            t = NULL;                   // Αν η ουρά είναι άδεια, ο δείκτης γίνεται NULL
        }
    }
}


void BSMTree::InOrderEditedV1(TreeNodePtr t, int refElement, int &counter, bool &secondNextFound, int &element)             // Τροποποιημένη συνάρτηση ενδοδιάταξης, καλείται από την Find_second_next
{
    if (t) {                    // Αν υπάρχει ο κόμβος t
        if (t->leftChild) {                                                                     // Αν υπάρχει αριστερό παιδί,
            InOrderEditedV1(t->leftChild, refElement, counter, secondNextFound, element);       // εκτέλεση της τροποιημένης
        }                                                                                       // ενδοδιάταξης στο αριστερό υπόδεντρο

        if (t->element > refElement) {          // Αν το τρέχον στοιχείο είναι μεγαλύτερο του στοιχείου που δόθηκε στην Find_second_next ως όρισμα,
            counter++;                          // γίνεται αύξηση της μεταβλητής counter κατά μια μονάδα.
            if (counter == 2) {                                         // Αν η μεταβλητή counter είναι ίση με 2 (δηλαδή το τρέχον στοιχείο είναι το δεύτερο μεγαλύτερο, δηλαδή το επιθυμητό)
                cout << "The second next element, greater than the element " << refElement << ", is " << t->element << ".\n";       // το στοιχείο αυτό εμφανίζεται στην οθόνη, η μεταβλητή
                secondNextFound = true;                                                                                             // secondNextFound γίνεται ίση με true, και η μεταβλητή
                element = t->element;                                                                                               // element γίνεται ίση με το επιθυμητό στοιχείο που βρέθηκε.
            }
        }

        if (secondNextFound == false) {         // Αν η τιμή της μεταβλητής secondNextFound είναι false, δηλαδή δεν έχει βρεθεί ακόμα το επιθυμητό στοιχείο
            if (t->rightChild) {                                                                // Αν υπάρχει δεξί παιδί εκτέλεση
                InOrderEditedV1(t->rightChild, refElement, counter, secondNextFound, element);  // της τροποποιημένης ενδοδιάταξης
            }                                                                                   // στο δεξί υπόδεντρο.
        }

    }
}


void BSMTree::InOrderEditedV2(TreeNodePtr t, int startNum, int endNum, bool &numsExist, bool &numsCease)                    // Τροποποιημένη συνάρτηση ενδοδιάταξης, καλείται από την Print_between
{
    if (t) {                    // Αν υπάρχει ο κόμβος t
        if (t->leftChild) {                                                                     // Αν υπάρχει αριστερό παιδί,
            InOrderEditedV2(t->leftChild, startNum, endNum, numsExist, numsCease);              // εκτελείται η τροποποιημένη
        }                                                                                       // ενδοδιάταξη στο αριστερό υπόδεντρο.

        if (t->element > endNum) {              // Αν το τρέχον στοιχείο είναι μεγαλύτερο του ανώτατου ορίου του διαστήματος, η μεταβλητή numsCease γίνεται ίση
            numsCease = true;                   // με true. Με αυτό το τρόπο δηλώνεται ότι η ενδοδιάταξη δεν είναι ανάγκη να συνεχιστεί εφόσον τα υπόλοιπα
        }                                       // στοιχεία που πρόκειται να αναγνωστούν, θα είναι και αυτά μεγαλύτερα του ανώτατου ορίου του διαστήματος.

        if (!numsCease) {                       // Αν η μεταβλητή numsCease είναι ίση με false,
            if (t->element >= startNum && t->element <= endNum) {           // γίνεται έλεγχος του τρέχοντος στοιχείου, και αν η τιμή του βρίσκεται εντός του διαστήματος,
                numsExist = true;                                           // η τιμή της μεταβλητής numsExist γίνεται ίση με true, ως ένδειξη της ύπαρξης λύσεων στο διάστημα,
                cout << t->element << "\t";                                 // και στη συνέχεια το στοιχείο αυτό εμφανίζεται στην οθόνη.
            }

            if (t->rightChild) {                                                                // Στη συνέχεια, εφόσον υπάρχει δεξί
                InOrderEditedV2(t->rightChild, startNum, endNum, numsExist, numsCease);         // παιδί, εκτελείται η τροποποιημένη
            }                                                                                   // ενδοδιάταξη στο δεξί υπόδεντρο.
        }
    }
}


void BSMTree::PrintPreOrder()               // Συνάρτηση εκτύπωσης της προδιάταξης
{
    if (rootNode) {                                         // Αν υπάρχει ρίζα, δηλαδή το δέντρο δεν είναι κενό,
        cout << "The Pre-Order of the tree, is the following : " << endl;   // τυπώνεται το επεξηγηματικό μήνυμα
        PreOrder(rootNode);                                                 // και καλείται η ιδιωτική συνάρτηση
        cout << endl;                                                       // προδιάταξης με όρισμα τη ρίζα.

    } else {                                                // Αν δεν υπάρχει ρίζα, δηλαδή το δέντρο είναι κενό,
        cout << "The tree is empty..." << endl;             // πραγματοποείται εμφάνιση του σχετικού μηνύματος
    }
}


void BSMTree::PrintInOrder()                // Συνάρτηση εκτύπωσης της ενδοδιάταξης
{
    if (rootNode) {                                         // Αν υπάρχει ρίζα, δηλαδή το δέντρο δεν είναι κενό,
        cout << "The In-Order of the tree, is the following : " << endl;    // τυπώνεται το επεξηγηματικό μήνυμα
        InOrder(rootNode);                                                  // και καλείται η ιδιωτική συνάρτηση
        cout << endl;                                                       // ενδοδιάταξης με όρισμα τη ρίζα.

    } else {                                                // Αν δεν υπάρχει ρίζα, δηλαδή το δέντρο είναι κενό,
        cout << "The tree is empty..." << endl;             // πραγματοποείται εμφάνιση του σχετικού μηνύματος
    }
}


void BSMTree::PrintPostOrder()              // Συνάρτηση εκτύπωσης της μεταδιάταξης
{
    if (rootNode) {                                         // Αν υπάρχει ρίζα, δηλαδή το δέντρο δεν είναι κενό,
        cout << "The Post-Order of the tree, is the following : " << endl;  // τυπώνεται το επεξηγηματικό μήνυμα
        PostOrder(rootNode);                                                // και καλείται η ιδιωτική συνάρτηση
        cout << endl;                                                       // μεταδιάταξης με όρισμα τη ρίζα.

    } else {                                                // Αν δεν υπάρχει ρίζα, δηλαδή το δέντρο είναι κενό,
        cout << "The tree is empty..." << endl;             // πραγματοποείται εμφάνιση του σχετικού μηνύματος
    }
}


void BSMTree::PrintLevelOrder()             // Συνάρτηση εκτύπωσης της διάσχισης ανά επίπεδα
{
    if (rootNode) {                                         // Αν υπάρχει ρίζα, δηλαδή το δέντρο δεν είναι κενό,
        cout << "The Level Order of the tree, is the following : " << endl; // τυπώνεται το επεξηγηματικό μήνυμα
        LeverOrder(rootNode);                                               // και καλείται η ιδιωτική συνάρτηση
        cout << endl;                                                       // διάσχισης ανά επίπεδα με όρισμα τη ρίζα.

    } else {                                                // Αν δεν υπάρχει ρίζα, δηλαδή το δέντρο είναι κενό,
        cout << "The tree is empty..." << endl;             // πραγματοποείται εμφάνιση του σχετικού μηνύματος
    }
}


int BSMTree::Find_second_next(int refElement)                   // Συνάρτηση Find_second_next
{
    if (rootNode) {                                         // Αν υπάρχει ρίζα, δηλαδή το δέντρο δεν είναι κενό,
        bool nodeExists = false;                // Ορισμός μεταβλητής τύπου bool, για τον προσδιορισμό της ύπαρξης, ή μη, του κόμβου αναφοράς που δόθηκε ως όρισμα
        currNode = rootNode;                                    // Αρχικοποίηση του δείκτη currNode,
        while (currNode) {                                      // με ένδειξη τη ρίζα του δέντρου,
            if (currNode->element > refElement) {               // και εκτέλεση δυαδικής αναζήτησης
                currNode = currNode->leftChild;                 // έως ότου βρεθεί ο κόμβος αναφοράς
            } else if (currNode->element < refElement) {        // οπότε έχει νόημα η αναζήτηση του
                currNode = currNode->rightChild;                // δεύτερου μικρότερου στοιχείου,
            } else {                                            // μεταξύ των στοιχείων που είναι
                nodeExists = true;                              // μεγαλύτερα του στοιχείου αναφοράς.
                break;                                          // Αν βρεθεί το στοιχείο αναφοράς,
            }                                                   // ο μεταβλητή nodeExists παίρνει τιμή
        }                                                       // true, και γίνεται έξοδος από το βρόγχο.

        bool secondNextFound = false;           // Ορισμός βοηθητικών μεταβλητών που
        int counter = 0;                        // χρησιμοποιούνται αργότερα ως ορίσματα
        int element = 0;                        // στην κλήση της InOrderEditedV1.

        if (nodeExists) {                                                               // Αν υπάρχει ο κόμβος αναφοράς,
            InOrderEditedV1(rootNode, refElement, counter, secondNextFound, element);   // γίνεται κλήση της συνάρτησης InOrderEditedV1
            if (secondNextFound) {                                                                              // Αν η τιμή της secondNextFound είναι ίση με true, δηλαδή έχει βρεθεί το επιθυμητό στοιχείο,
                return element;                                                                                 // τότε η συνάρτηση Find_second_next, η οποία είναι τύπου int, επιστρέφει το στοιχείο αυτό.
            } else {
                cout << "There is not second next element, of the element " << refElement << "..." << endl;     // Αλλιώς, εμφανίζεται στην οθόνη αντίστοιχο μήνυμα λάθους, και η συνάρτηση επιστρέφει την
                return -1;                                                                                      // τιμή -1, ως κωδικό λάθους.
            }
        } else {                                                                        // Αν δεν υπάρχει ο κόμβος αναφοράς,
            cout << "Element " << refElement << " does not exist..." << endl;           // εμφάνιση αντίστοιχου μηνύματος,
            return -1;                                                                  // και επιστροφή του κωδικού σφάλματος.
        }
    } else {                                                // Αν δεν υπάρχει ρίζα, δηλαδή το δέντρο είναι κενό,
        cout << "The tree is empty..." << endl;             // πραγματοποείται εμφάνιση του σχετικού μηνύματος,
        return -1;                                          // και επιστροφή του κωδικού λάθους (δηλαδή του -1).
    }
}


void BSMTree::Print_between(int startNum, int endNum)           // Συνάρτηση Print_between
{
    if (rootNode) {                                         // Αν υπάρχει ρίζα, δηλαδή το δέντρο δεν είναι κενό,
        bool numsExist = false;                 // Ορισμός των δύο
        bool numsCease = false;                 // μεταβλητών, τύπου bool
        if (startNum < endNum) {                                                        // Αν οι τιμές των ορίων του διαστήματος είναι έγκυρες, τότε
            cout << "The elements, between the numbers " << startNum << " and " << endNum << ", are :\n";   // εμφανίζεται σχετικό μήνυμα και καλείται
            InOrderEditedV2(rootNode, startNum, endNum, numsExist, numsCease);                              // η InOrderEditedV2 με όρισμα την ρίζα.
            if (!numsExist) {                   // Αν μετά το πέρας της συνάρτησης δεν υπάρχει αποτέλεσμα
                cout << "None..." << endl;      // εκτυπώνεται σχετικό μήνυμα στην οθόνη.
            }
        } else {                                                                        // Αν οι τιμές των ορίων του διαστήματος δεν είναι έγκυρες, τότε
            cout << "Invalid values inserted..." << endl;                               // εμφανίζεται αντίστοιχο επεξηγηματικό μήνυμα στην οθόνη.
        }
    } else {                                                // Αν δεν υπάρχει ρίζα, δηλαδή το δέντρο είναι κενό
        cout << "The tree is empty..." << endl;             // πραγματοποείται εμφάνιση του σχετικού μηνύματος.
    }
}
