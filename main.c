// 2690964 Berrak Yildirim
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "avltree.h"

/*inside of my patients.txt
Name;Surname;Date of birth; Height; Weight; BMI
Alex;Black;20/02/2000;1.80;85;26.2
John;Brown;18/08/2004;1.80;85;26.2
Brainy;Smurf;04/05/1980;1.75;170;55.5
Clumsy;Smurf;18/02/2000;1.80;45;13.9 */

int main()
{
    printf("Welcome to Patient Indexing!!!");

    AVLTree myTree;
    myTree = CreateTree();
    myTree = MakeEmptyTree(myTree);
    myTree = loadPatients("patients.txt", myTree);
    //DisplayTreeStructure(myTree, 5);

    int option;
    float searchBMI;

    do {
        printf("\n-------Menu-------");
        printf("\n(1)Display the full index of patients");
        printf("\n(2)Display the details of the patients");
        printf("\n(3)Display the youngest patient");
        printf("\n(4)Exit");
        printf("\nEnter your option:");
        scanf("%d", &option);

        if (option == 1) {
            displayPatients(myTree);
        }
        else if (option == 2) {
            int a = 1;
            do {
                printf("\nEnter patient's BMI: ");
                scanf("%f", &searchBMI);
                AVLTree tmp = myTree;
                tmp = infoPatients(tmp, searchBMI);
                if (tmp != NULL) {
                    a = 0; // Exit the loop
                } else {
                    printf("\nThere is no patient with a BMI of %.1f", searchBMI);
                }
            } while (a == 1);
        }
        else if (option == 3) {
            struct Node* p = NULL;
            p = youngestPatient(myTree, p);
            if (p != NULL) {
                printf("\n%s %s is the youngest patient.\n", p->name, p->surname);
            } else {
                printf("No patients found.\n");
            }
        }
    } while (option<4 && option>0);


    return 0;
}


