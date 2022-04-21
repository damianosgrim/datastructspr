//Bιβλιοθήκες που θα χρειαστώ
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
float O2ml_L;
} data;

//Συνάρτηση που κάνει εναλλαγή (χρειαζεται στον Quick Sort)
void swap(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}

void swap2(char *str1, char *str2)
{
  char *temp = (char *)malloc((strlen(str1) + 1) * sizeof(char));
  strcpy(temp, str1);
  strcpy(str1, str2);
  strcpy(str2, temp);
  free(temp);
}

//Υποσυνάρτηση του Quick Sort (Διαίρε)
int partition(data array[], int low, int high) {
  float pivot = array[high].T_degC;
  int i = (low - 1);

  for (int j = low; j < high; j++) {
    if (array[j].T_degC <= pivot) {
      i++;
     swap(&array[i].T_degC, &array[j].T_degC);
     swap(&array[i].PO4uM, &array[j].PO4uM);
     swap(&array[i].SiO3uM, &array[j].SiO3uM);
     swap(&array[i].NO2uM, &array[j].NO2uM);
     swap(&array[i].NO3uM, &array[j].NO3uM);
     swap(&array[i].Salnty, &array[j].Salnty);
     swap(&array[i].O2ml_L, &array[j].O2ml_L);
     swap2(array[i].date, array[j].date);
    }
  }
  swap(&array[i + 1].T_degC, &array[high].T_degC);
  swap(&array[i+1].PO4uM, &array[high].PO4uM);
  swap(&array[i+1].SiO3uM, &array[high].SiO3uM);
  swap(&array[i+1].NO2uM, &array[high].NO2uM);
  swap(&array[i+1].NO3uM, &array[high].NO3uM);
  swap(&array[i+1].Salnty, &array[high].Salnty);
  swap(&array[i+1].O2ml_L, &array[high].O2ml_L);
  swap2(array[i + 1].date, array[high].date);
  return (i + 1);
}

void quickSort(data array[], int low, int high) {
  if (low < high) {
    int pi = partition(array, low, high);
    quickSort(array, low, pi - 1);
    quickSort(array, pi + 1, high);
  }
}

// Πρόγραμμα ταξινομησης insertion Sort
void insertionSort(data arr[], int n)
{
    int i,  j;
    float key;
    for (i = 1; i < n; i++) {
        key = arr[i].T_degC;
        j = i - 1;

        while (j >= 0 && arr[j].T_degC > key) {
            arr[j + 1].T_degC = arr[j].T_degC;
            swap(&arr[j + 1].PO4uM, &arr[j].PO4uM);
            swap(&arr[j + 1].SiO3uM, &arr[j].SiO3uM);
            swap(&arr[j + 1].NO2uM, &arr[j].NO2uM);
            swap(&arr[j + 1].NO3uM, &arr[j].NO3uM);
            swap(&arr[j + 1].Salnty, &arr[j].Salnty);
            swap(&arr[j + 1].O2ml_L, &arr[j].O2ml_L);
            swap2(arr[j + 1].date, arr[j].date);
            j = j - 1;
        }
        arr[j + 1].T_degC = key;
    }
}

//Συνάρτηση που εκτυπώνει τον πίνακα
void printArray(data data[], int n)
{
    for(int r=2; r<n; r++)
    { printf("Date:%s  Temp:%.2f  PO4uM:%.2f  SiO3uM:%.2f  NO2uM:%.2f  NO3uM:%.2f  Salnty:%.3f  O2ml_L:%.2f\n", data[r].date, data[r].T_degC, data[r].PO4uM, data[r].SiO3uM, data[r].NO2uM, data[r].NO3uM, data[r].Salnty, data[r].O2ml_L);
}
}

//Συνάρτηση για δημιουργεία αρχειου csv
 void createCSV(data data[],int s){
     FILE *fpt;

    fpt = fopen("ordereddata.csv", "w+");
    fprintf(fpt,"Date,Temp\n");
    for (int i=2; i<s; i++)
    {

        fprintf(fpt,"%s, %f\n",data[i].date,data[i].T_degC );
    }

    fclose(fpt);
 }

//Συνάρτηση που ανοίγει το csv και τα αποθηκεύει σε Stucts
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

        fclose(fp);
}
}

int main()
{
        data d1[1406];
        data d2[1406]; //Ξεχοριστά stracts ώστε να γίνει η ταξινόμιση για τους 2 αλγορίθμους από την αρχή
         openCSV(d1);
         openCSV(d2);
        int n1 = sizeof(d1) / sizeof(d2[0]);
        int n2 = sizeof(d1) / sizeof(d2[0]);

        printArray(d1,n1);
        printf("Afta einai ta arxika stoixeia ta3inomimena me vasi tin imerominia\n\n");

     printf("Patiste enter oste na ta3inomi8oun me vasi ton Quick Sort.\n");
       getchar();
        clock_t start, end;
       // Recording the starting clock tick
         start = clock();
         printf("Clock ticks at starting time: %ld\n", start);
        quickSort(d1, 0, n1-1);
        end = clock();
        printArray(d1, n1);
        printf("\nTa stoixeia ta3inomithikan me af3ousa seira 8ermokrasias me vasi ton Quick Sort.\n");
        printf("Clock ticks at end time: %ld\n", end);
       printf("CLOCKS_PER_SEC: %ld\n", CLOCKS_PER_SEC);
       printf("The duration in seconds since the program was launched: %fl\n\n", (double)(end-start)/CLOCKS_PER_SEC);


      createCSV(d1,n1);
      printf("Ta ta3inomimena stoixeia apo8ikeftikan se neo arxeio me onoma: ordereddata.csv\n\n");

       printf("Patiste enter oste na ta3inomi8oun me vasi ton Insertion Sort.\n");
        getchar();
        start = clock();
         printf("Clock ticks at starting time: %ld\n", start);
        insertionSort(d2, n2);
         end = clock();
        printArray(d2, n2);
        printf("\nTa stoixeia ta3inomithikan me af3ousa seira 8ermokrasias me vasi ton Insertion Sort.\n");
        printf("Clock ticks at end time: %ld\n", end);
       printf("CLOCKS_PER_SEC: %ld\n", CLOCKS_PER_SEC);
       printf("The duration in seconds since the program was launched: %fl\n\n", (double)(end-start)/CLOCKS_PER_SEC);




    return 0;
}

