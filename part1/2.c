#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <math.h>
typedef struct Data {
char date[10];
float T_degC;
float PO4uM;
float SiO3uM;
float NO2uM;
float NO3uM;
float Salnty;
float O2ml_L;
} data;

//struct to use for the countingsort
typedef struct Data2 {
char date[10];
float T_degC;
long int PO4uM;
float SiO3uM;
float NO2uM;
float NO3uM;
float Salnty;
float O2ml_L
} data2;


//this is the function to open the file for heapsort
void openCSV1(data data[]){
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
                    strcpy(data[r].date, value);
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

        // Close the file
        fclose(fp);
}
}

//this is the function to open the file for countingsort
void openCSV2(data2 data[]){
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
                    strcpy(data[r].date, value);
                }


                if (column == 1) {
                    data[r].T_degC = atof(value);
                }


                if (column == 2) {
                  double i=atof(value);
                  double j= i*100;
                  data[r].PO4uM=j;

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

//this is the function to create the output file for heapsort
 void createCSV1(data data[],int s){
     FILE *fpt;

    fpt = fopen("outputHeapsort.csv", "w+");
    fprintf(fpt,"Date,       PO4Um,       T_degC,      SiO3uM,      NO2uM,      NO3uM,      Salnty,       O2ml_L\n");
    for (int i=2; i<s; i++)
    {

        fprintf(fpt,"%s,  %f,   %f,   %f,   %f,   %f,   %f,   %f\n",data[i].date,data[i].PO4uM, data[i].T_degC,data[i].SiO3uM,data[i].NO2uM, data[i].NO3uM,data[i].Salnty, data[i].O2ml_L);
    }

    fclose(fpt);
 }


//this is the function to create the output file for counting sort
 void createCSV3(data2 data[],int s){
     FILE *fpt;

    fpt = fopen("outputCountingsort.csv", "w+");
    fprintf(fpt,"Date,       PO4Um,       T_degC,      SiO3uM,      NO2uM,      NO3uM,      Salnty,       O2ml_L\n");
    for (int i=2; i<s; i++)
    {
        double phosphate = (double)(data[i].PO4uM)/(double)100;
        fprintf(fpt,"%s,  %.2f,   %f,   %f,   %f,   %f,   %f,   %f\n",data[i].date,phosphate, data[i].T_degC,data[i].SiO3uM,data[i].NO2uM, data[i].NO3uM,data[i].Salnty, data[i].O2ml_L);
    }

    fclose(fpt);
 }


// function to swap integers
  void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
  }

//function to swap strings
  void swap2(char *str1, char *str2)
{
  char *temp = (char *)malloc((strlen(str1) + 1) * sizeof(char));
  strcpy(temp, str1);
  strcpy(str1, str2);
  strcpy(str2, temp);
  free(temp);
}


  void heapify(data arr[], int s, int i) {  //s=size
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
            //we swap and the other elements of data
            swap2(arr[i].date, arr[smallest].date);
            swap(&arr[i].T_degC, &arr[smallest].T_degC);
            swap(&arr[i].SiO3uM, &arr[smallest].SiO3uM);
            swap(&arr[i].NO2uM, &arr[smallest].NO2uM);
            swap(&arr[i].NO3uM, &arr[smallest].NO3uM);
            swap(&arr[i].Salnty, &arr[smallest].Salnty);
            swap(&arr[i].O2ml_L, &arr[smallest].O2ml_L);

      heapify(arr, s, smallest);
    }
  }

//function for heapsort
  void heapSort(data arr[], int s) {

    for (int i = s / 2 - 1; i >= 0; i--)
      heapify(arr, s, i);

    for (int i = s - 1; i >= 0; i--) {
      swap(&arr[0].PO4uM, &arr[i].PO4uM);
      swap2(arr[0].date, arr[i].date);

      heapify(arr, i, 0);
    }
  }


  //function to print the results of heapsort
  void printArray1(data data[], int s)
{
    for(int i=2; i<s; i++)
    { printf("Date:%s  PO4uM:%.2f  Temp:%f  SiO3uM:%f  NO2uM:%f  NO3uM:%f  Salnty:%f  O2ml_L:%f\n", data[i].date, data[i].PO4uM, data[i].T_degC, data[i].SiO3uM, data[i].NO2uM, data[i].NO3uM, data[i].Salnty, data[i].O2ml_L);
}
}



//function for countingsort
void countingSort(data2 array[], int s) {
  int output[1406];


  // Find the largest element of the array
  int max = array[0].PO4uM;

  for (int i = 1; i < s; i++) {
        if (array[i].PO4uM > max)
        max = array[i].PO4uM;
  }


  int count[333];

  for (int i = 0; i <= max; ++i) {
        count[i] = 0;
  }


  for (int i = 0; i < s; i++) {
        count[array[i].PO4uM]++;
  }


  for (int i = 1; i <= max; i++) {
        count[i] += count[i - 1];
  }


  for (int i = s - 1; i >= 0; i--) {
    output[count[array[i].PO4uM] - 1] = array[i].PO4uM;
    count[array[i].PO4uM]--;


  }


  for (int i = 0; i < s; i++) {
    array[i].PO4uM = output[i];

  }
}
//function to print the results of countingsort
void printArray2(data2 data[], int s)
{
    for(int i=2; i<s; i++)
    {
        double phosphate = (double)(data[i].PO4uM)/(double)100;
         printf("Date:%s  PO4uM:%.2f Temp:%f  SiO3uM:%f  NO2uM:%f  NO3uM:%f  Salnty:%f  O2ml_L:%f\n", data[i].date,phosphate, data[i].T_degC, data[i].SiO3uM, data[i].NO2uM, data[i].NO3uM, data[i].Salnty, data[i].O2ml_L);
}
}

  int main() {

        data d1[1406];
        data d2[1406];

        openCSV1(d1);
        openCSV2(d2);

        int s = sizeof(d1) / sizeof(d1[0]);

        printf("Press enter to start sorting using HEAP SORT.\n");
        getchar();

        clock_t start, end;
        //start the clock
        start = clock();

        printf("\nClock at starting time: %ld\n", start);

        //call the heap sort function
        heapSort(d1, s);

        //stop the clock
        end = clock();

        printf("\nthe elements were sorted using HEAP SORT: \n\n");
        printArray1(d1 , s);

        printf("\nClock ticks at end time: %ld\n", end);
        printf("CLOCKS_PER_SEC: %ld\n", CLOCKS_PER_SEC);
        printf("The duration in seconds since the program was launched: %fl\n\n", (double)(end-start)/CLOCKS_PER_SEC);

       createCSV1(d1,s); //save the output in a new CSV file


        //from here we start the code for countingsort
        printf("Press enter to start sorting using COUNTING SORT.\n\n");
        getchar();



        data2 d3[1406];


        openCSV2(d3);//open the new file


        //start the clock
        start = clock();

        printf("\nClock at starting time: %ld\n", start);


         //call the counting sort function
        countingSort(d3, s);

        //stop the clock
        end = clock();

        printf("\nthe elements were sorted using COUNTING SORT: \n");
        printArray2(d3 , s);

        printf("\nClock ticks at end time: %ld\n", end);
        printf("CLOCKS_PER_SEC: %ld\n", CLOCKS_PER_SEC);
        printf("The duration in seconds since the program was launched: %fl\n\n", (double)(end-start)/CLOCKS_PER_SEC);


        createCSV3(d3,s); //save the output in a new CSV file


    return 0;
  }
