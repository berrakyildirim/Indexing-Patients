#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "avltree.h"
#include "string.h"

AVLTree CreateTree(void)
{
	return NULL;
}

AVLTree MakeEmptyTree(AVLTree t)
{
	if (t != NULL)
	{
		MakeEmptyTree(t->left);
		MakeEmptyTree(t->right);
		free(t);
	}
	return NULL;
}

// It inserts patients to an avl tree according to their bmi's
AVLTree insertPatients(float BMI, AVLTree t, Node p) {
	if (t == NULL) {
		t = malloc(sizeof(struct Tree));
		if (t == NULL) {
			printf("Out of memory space!!!\n");
			return NULL;
		} else {
			t->patientInfo = p;
			t->BMI = BMI;
			t->left = t->right = NULL;
			t->treeHeight = Max(AVLTreeHeight(t->left), AVLTreeHeight(t->right)) + 1;
			return t;
		}
	} else if (BMI < t->BMI) {
		t->left = insertPatients(BMI, t->left, p);
		if (AVLTreeHeight(t->left) - AVLTreeHeight(t->right) == 2) {
			if (BMI < t->left->BMI) {
				t = SingleRotateWithLeft(t);
			} else {
				t = DoubleRotateWithLeft(t);
			}
		}
	} else if (BMI > t->BMI) {
		t->right = insertPatients(BMI, t->right, p);

		if (AVLTreeHeight(t->right) - AVLTreeHeight(t->left) == 2) {
			if (BMI > t->right->BMI) {
				t = SingleRotateWithRight(t);
			} else {
				t = DoubleRotateWithRight(t);
			}
		}
	} else { // If it has the same BMI value insert it in the same avl tree node
		struct Node *current = t->patientInfo;
		struct Node *prev = (struct Node*)malloc(sizeof(struct Node));
		while (current != NULL) {
			prev = current;
			current = current->next;
		}
		prev->next = p;
		return t;
	}
	// Update height
	t->treeHeight = Max(AVLTreeHeight(t->left), AVLTreeHeight(t->right)) + 1;
	return t;
}

int AVLTreeHeight(AVLTree t)
{
	if (t == NULL)
		return -1;
	else
		return t->treeHeight;
}


AVLTree SingleRotateWithLeft(AVLTree k1)
{
	AVLTree k2;
	k2 = k1->right;
	k1->right = k2->left;
	k2->left = k1;

	// Update height
	k1->treeHeight = Max(AVLTreeHeight(k1->left), AVLTreeHeight(k1->right)) + 1;
	k2->treeHeight = Max(AVLTreeHeight(k2->left), k1->treeHeight) + 1;

	return k2;
}

AVLTree SingleRotateWithRight(AVLTree k2)
{
	AVLTree k1;
	k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;

	// Update height
	k2->treeHeight = Max(AVLTreeHeight(k2->left), AVLTreeHeight(k2->right)) + 1;
	k1->treeHeight = Max(AVLTreeHeight(k1->left), k1->treeHeight) + 1;

	return k1;
}

AVLTree DoubleRotateWithLeft(AVLTree k3)
{
	k3->left = SingleRotateWithRight(k3->left);
	return SingleRotateWithLeft(k3);
}

AVLTree DoubleRotateWithRight(AVLTree k3)
{
	k3->right = SingleRotateWithLeft(k3->right);
	return SingleRotateWithRight(k3);
}

int Max(int x, int y)
{
	if (x >= y)
		return x;
	else
		return y;
}

// It reads the file and calls the insert function
AVLTree loadPatients(char fileName[], int *depth) {
	AVLTree t = NULL;
	FILE *inFile = fopen(fileName, "r");
	if (inFile == NULL) {
		printf("\nError opening file!");
		exit(-1);
	}
	// Start at the beggining
	rewind(inFile);

	char string[N];
	fgets(string, N, inFile); // Removes the first line of the file "Name;Surname;Date of birth; Height; Weight; BMI"

	int size = 0; // Number of patients
	float BMI;

	// Read until the end of file
	while (!feof(inFile)) {
		struct Node *patient = (struct Node *) malloc(sizeof(struct Node));
		fscanf(inFile, "%[^;];%[^;];%[^;];%f;%d;%f\n",
			// When i use "%s;%s;%s;%f;%d;%f\n" I am having issues with my fscanf
			// So i used %[^:] which means, take the string till the semicolon
			patient->name, patient->surname, patient->birth,
			&patient->height, &patient->weight, &BMI);

		// Insert the patient
		t = insertPatients(BMI, t, patient);

		size++;
	}
	depth = &size;
	fclose(inFile);
	return t;
}

// infoPatients:
// Displays the patients who has given BMI
// It's complexity for searching  is O(logn)
// and traversing the linked list is O(m)
// So in total complexity of the function is O(logn + m)
// I could have used dynamic array instead of each linked list in tree for less complexity
AVLTree infoPatients(AVLTree t, float BMI) {
	// Searching BMI
	if (t == NULL) {
		return NULL; // BMI not found
	} else if (BMI == t->BMI) {
		// Display all patients with the same BMI
		struct Node* patient = t->patientInfo;
		while (patient != NULL) { // Traversing the linked list
			printf("%s;%s;%s;%.2f;%d;%.1f\n",
				patient->name, patient->surname, patient->birth,
				patient->height, patient->weight, t->BMI);
			patient = patient->next;
		}
		return t;
	} else if (BMI > t->BMI) {
		return infoPatients(t->right, BMI);
	} else {
		return infoPatients(t->left, BMI);
	}
}

// Displays patients in an AVL tree in ascending order
void displayPatients(AVLTree t)
{
	if (t != NULL)
	{
		displayPatients(t->left);
		printf("%s;%s;%s;%f;%d;%f\n", t->patientInfo->name, t->patientInfo->surname, t->patientInfo->birth,
			t->patientInfo->height, t->patientInfo->weight, t->BMI);
		displayPatients(t->right);
	}
}

// I used this function in my tests to see structure
void DisplayTreeStructure(AVLTree t, int depth)
{
	int i;

	if (t != NULL)
	{
		DisplayTreeStructure(t->right, depth + 1);

		for (i = 0; i < depth; i++)
			printf("     ");
		printf("%s;%s;%s;%f;%d;%f\n", t->patientInfo->name, t->patientInfo->surname, t->patientInfo->birth,
			t->patientInfo->height, t->patientInfo->weight, t->BMI);

		DisplayTreeStructure(t->left, depth + 1);
	}
}

// Since I took birth dates as strings, I did comparison of birth in this function
int compareBirthDates(char patient_1[], char patient_2[]) {
	int day_1, month_1, year_1, day_2, month_2, year_2;

	// Use %d to correctly parse integers
	sscanf(patient_1, "%d/%d/%d", &day_1, &month_1, &year_1);
	sscanf(patient_2, "%d/%d/%d", &day_2, &month_2, &year_2);

	if (year_1 > year_2) { //2nd is younger
		return 2;
	} else if (year_1 < year_2) { //1st is younger
		return 1;

	} else { // If they were born in same year, check for months
		if (month_1 > month_2) {
			return 2;
		} else if (month_1 < month_2) {
			return 1;
		} else {
			if (day_1 > day_2) {
				return 2;
			} else {
				return 1;
			}
		}
	}
}

// youngestPatient:
// Finds the youngest patient
// Tree traversal is O(n)
// compareBirthDates is O(1)
// so the overall complexity is O(n)
// I could have store birth dates as 3 different integers instead of a string
// I could have store their birth date in my avltree and search it which would have give us O(logn) complexity
struct Node* youngestPatient(struct Tree* t, struct Node* youngesPat) {
	if (t == NULL) {
		return youngesPat;
	}
	youngesPat = youngestPatient(t->left, youngesPat);
	if (youngesPat == NULL || compareBirthDates(t->patientInfo->birth, youngesPat->birth) == 2) {
		youngesPat = t->patientInfo;
	}
	youngesPat = youngestPatient(t->right, youngesPat);
	return youngesPat;
}



