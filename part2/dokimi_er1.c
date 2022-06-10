#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>


typedef struct Data {
long int date;
float T_degC;
float PO4uM;
float SiO3uM;
float NO2uM;
float NO3uM;
float Salnty;
float O2ml_L;
} data;

//function to remove th "/" from the dates
void removeChar(char* s, char c)
{

    int j, n = strlen(s);
    for (int i = j = 0; i < n; i++)
        if (s[i] != c)
            s[j++] = s[i];

    s[j] = '\0';
}

//function to swap the date as YYYY/MM/DD to be in ascending order
void swapdate (char* str)
{
    char temp;
    int n;

    n = strlen(str);
	// swap str[0] and str[n-4]
	temp = str[0];
	str[0] = str[n - 4];
	str[n - 4] = temp;
	// swap str[1] and str[n-3]
	temp = str[1];
	str[1] = str[n - 3];
	str[n - 3] = temp;
	// swap str[2] and str[n-2]
	temp = str[2];
	str[2] = str[n - 2];
	str[n - 2] = temp;
	// swap str[3] and str[n-1]
	temp = str[3];
	str[3] = str[n - 1];
	str[n - 1] = temp;

}

//OoiUnococ ?io aii?aae oi csv eae oa a?ieceayae oa Stucts
void openCSV(data data[]){
    FILE* fp = fopen("ocean.csv", "r");

    if (!fp)
        printf("Can't open file\n");

    else {
        char buffer[1024];
        int row = 0;
        int column = 0;
        int r=0;

        while (fgets(buffer,1024, fp)) {
            column = 0;
            row++;
            r++;
            if (row == 1)
                continue;
            char* value = strtok(buffer, ", ");
            while (value) {

                if (column == 0) {

                        removeChar(value, '/');
                        swapdate(value);
                        data[r].date = atol(value);
                }
                if (column == 1) {
                    data[r].T_degC = atof(value);
                }
                if (column == 2) {
                    data[r].PO4uM = atof(value);
                }
                if (column == 3) {
                    data[r].SiO3uM = atof(value);
                }
                if (column == 4) {
                    data[r].NO2uM = atof(value);
                }
                if (column == 5) {
                    data[r].NO3uM = atof(value);
                }
                if (column == 6) {
                    data[r].Salnty = atof(value);
                }

                if (column == 7) {
                    data[r].O2ml_L = atof(value);
                }

                value = strtok(NULL, ", ");
                column++;
            }

            printf("\n");
        }

        fclose(fp);
}
}


void swap(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}
//shorting by date
void insertionSort(data arr[], int n)
{
    int i,  j;
    long int key;
    for (i = 1; i < n; i++) {
        key = arr[i].date;
        j = i - 1;

        while (j >= 0 && arr[j].date > key) {
            arr[j + 1].date= arr[j].date;
            swap(&arr[j + 1].T_degC, &arr[j].T_degC);
            swap(&arr[j + 1].PO4uM, &arr[j].PO4uM);
            swap(&arr[j + 1].SiO3uM, &arr[j].SiO3uM);
            swap(&arr[j + 1].NO2uM, &arr[j].NO2uM);
            swap(&arr[j + 1].NO3uM, &arr[j].NO3uM);
            swap(&arr[j + 1].Salnty, &arr[j].Salnty);
            swap(&arr[j + 1].O2ml_L, &arr[j].O2ml_L);
            j = j - 1;
        }
        arr[j + 1].date = key;
    }
}

// An AVL tree node
struct TNode
{
    int d;
    struct TNode* left;
    struct TNode* right;
};
 
struct TNode* newNode(int d);
 
/* A function that constructs Balanced Binary Search Tree from a sorted array */
struct TNode* sortedArrayToBST(data arr[], int start, int end)
{
    /* Base Case */
    if (start > end)
      return NULL;
 
    /* Get the middle element and make it root */
    int mid = (start + end)/2;
    struct TNode *root = newNode(arr[mid].date);
 
    /* Recursively construct the left subtree and make it
       left child of root */
    root->left =  sortedArrayToBST(arr, start, mid-1);
 
    /* Recursively construct the right subtree and make it
       right child of root */
    root->right = sortedArrayToBST(arr, mid+1, end);
 
    return root;
}
 
/* Helper function that allocates a new node with the
   given data and NULL left and right pointers. */
struct TNode* newNode(int d)
{
    struct TNode* node = (struct TNode*)
                         malloc(sizeof(struct TNode));
    node->d = d;
    node->left = NULL;
    node->right = NULL;
 
    return node;
}
 
/* A utility function to print preorder traversal of BST */
void preOrder(struct TNode* node)
{
    if (node == NULL)
        return;
    printf("%d ", node->d);
    preOrder(node->left);
    preOrder(node->right);
}

/* Driver program to test above function*/
int main()
{
    data d[1407];
    openCSV(d); //call the function that read the csv file
    int s=sizeof(d)/sizeof(d[0]); //used to find right limit, binary search

  struct Node *root = NULL;
  insertionSort(d,s);

  /* Constructing tree given in the above figure */
  for (int i=0; i<1406; i++) {
  	struct TNode *root = sortedArrayToBST(d, 0, s-1);

  }

int answer=0;
int choice;
long int date;


do{

printf("\n\nDo you want to run the programm? 1.Yes 2.No (Type a number): \n");
scanf("%d", &choice);
if (choice==2){return 0;}

else{
        answer=1;
        char number;
         printf("Type what do you want to happen with the AVL:\n 1.Inorder traversal \n 2.Search a temperature\n 3.Modify a temperature\n 4.Delete a date/\n 5.exit\n (choose a number): \n");
        scanf("%s", &number);
            switch(number){
                case '1':
                      printf("Inorder traversal of the constructed AVL tree is \n");
                      preOrder(root);
                       break;

                case '2':
                     break;

                case '3':
                    break;

                case '4':
                	printf("Type the date you want to remove (YYYYMMDD):\n");
                	scanf("%ld", &date);
                	deleteNode(root, date);
			      printInorder(root);
                    break;

                case '5':
                     return 0;
            }
}
}while(answer!=0);




  return 0;
}
