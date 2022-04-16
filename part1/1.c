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
float O2ml_L
} data;

//Συνάρτηση που κάνει εναλλαγή (χρειάζεται στον Quick Sort)
void swap(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}

//Υποσυνάρτηση του Quick Sort (Διαίρε)
int partition(data array[], int low, int high) {
  float pivot = array[high].T_degC;
  int i = (low - 1);

  for (int j = low; j < high; j++) {
    if (array[j].T_degC <= pivot) {
      i++;
      swap(&array[i].T_degC, &array[j].T_degC);
    }
  }
  swap(&array[i + 1].T_degC, &array[high].T_degC);
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
            j = j - 1;
        }
        arr[j + 1].T_degC = key;
    }
}

//Συνάρτηση που εκτυπώνει τον πίνακα
void printArray(data data[], int n)
{
    for(int r=2; r<=n; r++)
    { printf("Date:%s  Temp:%f  PO4uM:%f  SiO3uM:%f  NO2uM:%f  NO3uM:%f  Salnty:%f  O2ml_L:%f\n", data[r].date, data[r].T_degC, data[r].PO4uM, data[r].SiO3uM, data[r].NO2uM, data[r].NO3uM, data[r].Salnty, data[r].O2ml_L);
}
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
        data d[1406];
         openCSV(d);
        int n = sizeof(d) / sizeof(d[0]);

        printArray(d,n);
        printf("Afta einai ta arxika stoixeia ta3inomimena me vasi tin imerominia\n\n");
        printf("Patiste enter oste na ta3inomi8oun me vasi ton Insertion Sort.\n");
        getchar();

       clock_t start, end;
        /* Recording the starting clock tick.*/
        start = clock();
         printf("Clock ticks at starting time: %ld\n", start);
        insertionSort(d, n);
         end = clock();
        printArray(d, n);
        printf("\nTa stoixeia ta3inomithikan me af3ousa seira 8ermokrasias me vasi ton Insertion Sort.\n");
        printf("Clock ticks at end time: %ld\n", end);
       printf("CLOCKS_PER_SEC: %ld\n", CLOCKS_PER_SEC);
       printf("The duration in seconds since the program was launched: %ld\n\n", (end-start)/CLOCKS_PER_SEC);

    //Eγγραφή ταξινομιμένων στοιχείο σε νέο αρχείο
    FILE *outfile;  //Δημιουργία αρχείου
    outfile = fopen ("insertiondata.csv", "w");
    if (outfile == NULL)
    {
        fprintf(stderr, "\nError opened file\n");
        exit (1);
    }
    //Εγγραφή
      fwrite (&d, sizeof(struct Data), n, outfile);
      if(fwrite != 0)
        printf("Ta ta3inomimena stoixeia graftikan se neo arxeio !\n");
      else
        printf("error writing file !\n");

    fclose (outfile);

       printf("Patiste enter oste na ta3inomi8oun me vasi ton Quick Sort.\n");
       getchar();


         start = clock();
         printf("Clock ticks at starting time: %ld\n", start);
        quickSort(d, 0, n-1);
        end = clock();
        printArray(d, n);
        printf("\nTa stoixeia ta3inomithikan me af3ousa seira 8ermokrasias me vasi ton Quick Sort.\n");
        printf("Clock ticks at end time: %ld\n", end);
       printf("CLOCKS_PER_SEC: %ld\n", CLOCKS_PER_SEC);
       printf("The duration in seconds since the program was launched: %ld\n", (end-start)/CLOCKS_PER_SEC);


//Na dw teleftai seira kai eggrafi se arxeio
    return 0;
}
