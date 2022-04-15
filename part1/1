// C program for the above approach
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

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
// function to swap elements
void swap(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}

// function to find the partition position
int partition(data array[], int low, int high) {

  // select the rightmost element as pivot
  float pivot = array[high].T_degC;

  // pointer for greater element
  int i = (low - 1);

  // traverse each element of the array
  // compare them with the pivot
  for (int j = low; j < high; j++) {
    if (array[j].T_degC <= pivot) {

      // if element smaller than pivot is found
      // swap it with the greater element pointed by i
      i++;

      // swap element at i with element at j
      swap(&array[i].T_degC, &array[j].T_degC);
    }
  }

  // swap the pivot element with the greater element at i
  swap(&array[i + 1].T_degC, &array[high].T_degC);

  // return the partition point
  return (i + 1);
}

void quickSort(data array[], int low, int high) {
  if (low < high) {

    // find the pivot element such that
    // elements smaller than pivot are on left of pivot
    // elements greater than pivot are on right of pivot
    int pi = partition(array, low, high);

    // recursive call on the left of pivot
    quickSort(array, low, pi - 1);

    // recursive call on the right of pivot
    quickSort(array, pi + 1, high);
  }
}

/* Πρόγραμμα ταξινομησης*/
void insertionSort(data arr[], int n)
{
    int i,  j;
    float key;
    for (i = 1; i < n; i++) {
        key = arr[i].T_degC;
        j = i - 1;

        /* Move elements of arr[0..i-1], that are
          greater than key, to one position ahead
          of their current position */
        while (j >= 0 && arr[j].T_degC > key) {
            arr[j + 1].T_degC = arr[j].T_degC;
            j = j - 1;
        }
        arr[j + 1].T_degC = key;
    }
}

// A utility function to print an array of size n
void printArray(data data[], int n)
{

    for(int r=2; r<=n; r++)
    { printf("Date:%s  Temp:%f  PO4uM:%f  SiO3uM:%f  NO2uM:%f  NO3uM:%f  Salnty:%f  O2ml_L:%f\n", data[r].date, data[r].T_degC, data[r].PO4uM, data[r].SiO3uM, data[r].NO2uM, data[r].NO3uM, data[r].Salnty, data[r].O2ml_L);
}
}

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
int main()

{
        data d[1406];
         openCSV(d);
        int n = sizeof(d) / sizeof(d[0]);

        clock_t t;
        t = clock();
        insertionSort(d, n);
        t = clock() - t;
        double time_taken = ((double)t)/CLOCKS_PER_SEC;
        printArray(d, n);
        printf("Ta stoixeia ta3inomithikan me af3ousa seira 8ermokrasias me vasi ton Insertion Sort.\nTime nedded: %d second\n",time_taken);

        t = clock();
        quickSort(d, 0, n-1);
        t = clock() - t;
        time_taken = ((double)t)/CLOCKS_PER_SEC;
        printArray(d, n);
        printf("Ta stoixeia ta3inomithikan me af3ousa seira 8ermokrasias me vasi ton Quick Sort.\nTime nedded: %d second\n",time_taken);


//Na dw teleftaia seira kai clock


    return 0;
}
