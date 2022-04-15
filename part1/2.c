#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Data {
char date[12];
float T_degC;
float PO4uM;
float SiO3uM;
float NO2uM;
float NO3uM;
float Salnty;
float O2ml_L
} data;

void openCSV(data data[]){// Substitute the full file path
    // for the string file_path
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


            // To avoid printing of column
            // names in file can be changed
            // according to need
            if (row == 1)
                continue;

            // Splitting the data
            char* value = strtok(buffer, ", ");

            while (value) {
                // Column 1
                if (column == 0) {
                    strcpy(data[r].date, value);
                }

                // Column 2
                if (column == 1) {
                    data[r].T_degC = atof(value);
                }

                // Column 3
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

        // Close the file
        fclose(fp);
}
}

// Function to swap the the position of two elements
  void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
  }

  void heapify(data arr[], int s, int i) {
    // Finds what is the smallest the root, the left child or the right child
    int smallest = i;
    int l = 2 * i + 1; //left child
    int r = 2 * i + 2; //right child

    if (l < s && arr[l].PO4uM > arr[smallest].PO4uM)
      smallest = l;

    if (r < s && arr[r].PO4uM > arr[smallest].PO4uM)
      smallest = r;

    //if the root is not the smallest swap and heapify
    if (smallest != i) {
      swap(&arr[i].PO4uM, &arr[smallest].PO4uM);
      heapify(arr, s, smallest);
    }
  }


  void heapSort(data arr[], int s) {

    for (int i = s / 2 - 1; i >= 0; i--)
      heapify(arr, s, i);

    // Heap sort
    for (int i = s - 1; i >= 0; i--) {
      swap(&arr[0].PO4uM, &arr[i].PO4uM);


      heapify(arr, i, 0);
    }
  }

  // Print an array
  void printArray(data arr[], int s) {
    for (int i = 0; i < s; i++)
      printf("Date:%s PO4uM:%f \n", arr[i].date,arr[i].PO4uM);

  }


  int main() {
       data d[1406];
         openCSV(d);
        int s = sizeof(d) / sizeof(d[0]);


    heapSort(d, s);

    printf("the elements were sorted using heapsort \n");
    printArray(d , s);

  }
