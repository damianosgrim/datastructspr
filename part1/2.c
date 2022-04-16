#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
typedef struct Data {
char date[10];
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

 void createCSV(data data[],int s){
     FILE *fpt;

    fpt = fopen("MyFile.csv", "w+");
    fprintf(fpt,"Date,      PO4Um\n");
    for (int i=2; i<s; i++)
    {
        
        fprintf(fpt,"%s, %f\n",data[i].date,data[i].PO4uM );
    }

    fclose(fpt);
 }

// Function to swap the the position of two elements
  void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
  }


  void swa(char *str1, char *str2)
{
  char *temp = (char *)malloc((strlen(str1) + 1) * sizeof(char));
  strcpy(temp, str1);
  strcpy(str1, str2);
  strcpy(str2, temp);
  free(temp);
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
      swa(arr[i].date, arr[smallest].date);
      heapify(arr, s, smallest);
    }
  }


  void heapSort(data arr[], int s) {

    for (int i = s / 2 - 1; i >= 0; i--)
      heapify(arr, s, i);

    // Heap sort
    for (int i = s - 1; i >= 0; i--) {
      swap(&arr[0].PO4uM, &arr[i].PO4uM);
      swa(arr[0].date, arr[i].date);


      heapify(arr, i, 0);
    }
  }

  // Print an array
  void printArray(data arr[], int s) {
      data arr2[1046];
       data arr3[1046];
    for (int i = 2; i < s; i++){
      printf("Date:%s  PO4uM:%f  \n", arr[i].date,arr[i].PO4uM);

    
      }

  }




/*void countingSort(data array[], float s) {
  int output[1046];

  // Find the largest element of the array
  int max = array[0].PO4uM;
  for (int i = 1; i < s; i++) {
        int arr=(int) array[i].PO4uM;
    if (arr > max)
      max = arr;
  }

  // The size of count must be at least (max+1) but
  // we cannot declare it as int count(max+1) in C as
  // it does not support dynamic memory allocation.
  // So, its size is provided statically.
  int count[4];

  // Initialize count array with all zeros.
  for (int i = 0; i <= max; ++i) {
    count[i] = 0;
  }

  // Store the count of each element
  for (int i = 0; i < s; i++) {
         int arr=(int) array[i].PO4uM;
    count[arr]++;
  }

  // Store the cummulative count of each array
  for (int i = 1; i <= max; i++) {
    count[i] += count[i - 1];
  }

  // Find the index of each element of the original array in count array, and
  // place the elements in output array
  for (int i = s - 1; i >= 0; i--) {
         int arr=(int) array[i].PO4uM;
    output[count[arr] - 1] = arr;
    count[arr]--;
  }

  // Copy the sorted elements into original array
  for (int i = 0; i < s; i++) {
    array[i].PO4uM = output[i];
  }
}*/

  int main() {
       data d[1406];
data a[1406];
         openCSV(d);
        int s = sizeof(d) / sizeof(d[0]);

       clock_t start, end;

        /* Recording the starting clock tick.*/
        start = clock();

        printf("Clock ticks at starting time: %ld\n", start);

        //call the heap sort function
        heapSort(d, s);

        end = clock();

        printf("the elements were sorted using heapsort \n");
        printArray(d , s);

        printf("Clock ticks at end time: %ld\n", end);


  printf("CLOCKS_PER_SEC: %ld\n", CLOCKS_PER_SEC);
  printf("The duration in seconds since the program was launched: %ld\n", (end-start)/CLOCKS_PER_SEC);

   createCSV(d,s);
    /*countingSort(d, s);

    printf("the elements were sorted using counting sort \n");
    printArray(d , s);*/


  
    return 0;
  }
