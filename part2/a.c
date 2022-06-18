#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <stdbool.h>  
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
struct Node
{   data d;
    int key;
    struct Node *left;
    struct Node *right;
    int height;
};

// A utility function to get maximum of two integers
int max(int a, int b);

// A utility function to get the height of the tree
int height(struct Node *N)
{
    if (N == NULL)
        return 0;
    return 1+max(height(N->left), height(N->right));
}

// A utility function to get maximum of two integers
int max(int a, int b)
{
    return (a > b)? a : b;
}

/* Helper function that allocates a new node with the given key and
    NULL left and right pointers. */
struct Node* newNode(int key, data d)
{
    struct Node* node = (struct Node*)
                        malloc(sizeof(struct Node));
    node->d   = d;
    node->left   = NULL;
    node->right  = NULL;
    node->height = 0;  // new node is initially added at leaf
    return(node);
}

// A utility function to right rotate subtree rooted with y
// See the diagram given above.
struct Node *rightRotate(struct Node *y)
{
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = height(y);
    x->height = height(x);
    
    // Return new root
    return x;
}

// A utility function to left rotate subtree rooted with x
// See the diagram given above.
struct Node *leftRotate(struct Node *x)
{
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    //  Update heights
    x->height = height(x);
    y->height = height(y);

    // Return new root
    return y;
}

// Get Balance factor of node N
int getBalance(struct Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

// Recursive function to insert a key in the subtree rooted
// with node and returns the new root of the subtree.
struct Node* insert(struct Node* node, int key, data d)
{
    /* 1.  Perform the normal BST insertion */
    if (node == NULL)
        return(newNode(key, d));

    if (key < node->key)
        node->left  = insert(node->left, key, d);
    else if (key > node->key)
        node->right = insert(node->right, key, d);
    else // Equal keys are not allowed in BST
        return node;

    /* 2. Update height of this ancestor node */
    node->height = height(node);

    /* 3. Get the balance factor of this ancestor
          node to check whether this node became
          unbalanced */
    int balance = getBalance(node);

    // If this node becomes unbalanced, then
    // there are 4 cases

    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && key > node->left->key)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    /* return the (unchanged) node pointer */
    return node;
}


void printInorder(struct Node *root)
{
    if (root == NULL)
        return;

    /* first recur on left child */
    printInorder(root->left);

    /* then print the data of node */
    printf("Date:%d\Temp:%fl  ", root->d.date, root->d.T_degC );

    /* now recur on right child */
    printInorder(root->right);
}

/* Given a non-empty binary search tree, return the
   node with minimum key value found in that tree.
   Note that the entire tree does not need to be
   searched. */
struct Node * minValueNode(struct Node* node)
{
    struct Node* current = node;

    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;

    return current;
}
// Recursive function to delete a node with given key
// from subtree with given root. It returns root of
// the modified subtree.
struct Node* deleteNode(struct Node* root, int key)
{
    // STEP 1: PERFORM STANDARD BST DELETE
    if (root == NULL)
        return root;

    // If the key to be deleted is smaller than the
    // root's key, then it lies in left subtree
    if ( key < root->key )
        root->left = deleteNode(root->left, key);

    // If the key to be deleted is greater than the
    // root's key, then it lies in right subtree
    else if( key > root->key )
        root->right = deleteNode(root->right, key);

    // if key is same as root's key, then This is
    // the node to be deleted
    else
    {
        // node with only one child or no child
        if( (root->left == NULL) || (root->right == NULL) )
        {
            struct Node *temp = root->left ? root->left :
                                             root->right;

            // No child case
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else // One child case
             *root = *temp; // Copy the contents of
                            // the non-empty child
            free(temp);
        }
        else
        {
            // node with two children: Get the inorder
            // successor (smallest in the right subtree)
            struct Node* temp = minValueNode(root->right);

            // Copy the inorder successor's data to this node
            root->key = temp->key;

            // Delete the inorder successor
            root->right = deleteNode(root->right, temp->key);
        }
    }

    // If the tree had only one node then return
    if (root == NULL)
      return root;

    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    root->height = 1 + max(height(root->left),
                           height(root->right));

    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to
    // check whether this node became unbalanced)
    int balance = getBalance(root);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left =  leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);


    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

struct Node * searchNode(struct Node* root, int key) {
	
	//node not found
    if(root == NULL) {
      printf("No data found\n");
      return NULL;
    
    } else if (root-> d.date == key) {
      return root;
    } 
	//node is in the left subtree
	else {
      struct Node* x = search(root->left,key);
      if (x)
        return x;         //if we find in left subtree, return result
      
      //note is in the right subtree
	  return search(root->right,key);
    }
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
    root = insert(root, d[i].date, d[i]);
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
         printf("Type what do you want to happen with the AVL:\n 1.Inorder traversal \n 2.Search a temperature\n 3.Modify a temperature\n 4.Delete a date\n 5.Åxit\n (choose a number): \n");
        scanf("%s", &number);
            switch(number){
                case '1':
                      printf("Inorder traversal of the constructed AVL tree is \n");
                      printInorder(root);
                       break;

                case '2':
                	  printf("Enter a date (YYYYMMDD) to find it's temperature:'");
                	  scanf("%ld", &date);
                	  search(root, date);
                	  printInorder(root);
                	  
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
