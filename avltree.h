#ifndef AVLTREE_H
#define AVLTREE_H

#define N 50

struct Node {
    // Patients information
    char name[N];
    char surname[N];
    char birth[N];
    float height;
    int weight;
    struct Node *next;
};

struct Tree {
    float BMI;
    struct Node *patientInfo;
    struct Tree *left;
    struct Tree *right;
    int treeHeight;
};

typedef struct Node *Node;
typedef struct Tree *AVLTree;

// AVL Tree Functions
AVLTree CreateTree(void);
AVLTree MakeEmptyTree(AVLTree t);
AVLTree SingleRotateWithLeft(AVLTree t);
AVLTree SingleRotateWithRight(AVLTree t);
AVLTree DoubleRotateWithLeft(AVLTree t);
AVLTree DoubleRotateWithRight(AVLTree t);
void displayPatients(AVLTree t);
void DisplayTreeStructure(AVLTree t, int depth);
int AVLTreeHeight(AVLTree t);
int Max(int x, int y);

// Functions from Assignment Paper
AVLTree loadPatients(char fileName[], int *depth);
AVLTree infoPatients(AVLTree t, float BMI);
Node youngestPatient(AVLTree t, Node youngesPat);
AVLTree insertPatients(float BMI, AVLTree t, Node p);

// Additional Functions
int compareBirthDates(char patient_1[], char patient_2[]);



#endif // AVLTREE_H
