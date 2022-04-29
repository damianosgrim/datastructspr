#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

typedef struct data {
long int date;
float T_degC;
float PO4uM;
float SiO3uM;
float NO2uM;
float NO3uM;
float Salnty;
float O2ml_L
} data;

void openCSV(data data[]){
    // Substitute the full file path
    // for the string file_path
        FILE* fp = fopen("ocean.csv", "r");

    if (!fp)
        printf("Can't open file\n");

    else{
        char buffer[1024];

        int row = 0;
        int column = 0;
        int r = 0;

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

                if (column == 1) {data[r].T_degC = atof(value);}

                if (column == 2) {data[r].PO4uM = atof(value);}

                if (column == 3) {data[r].SiO3uM = atof(value);}

                if (column == 4) {data[r].NO2uM = atof(value);}

                if (column == 5) {data[r].NO3uM = atof(value);}

                if (column == 6) {data[r].Salnty = atof(value);}

                if (column == 7) {data[r].O2ml_L = atof(value);}

                value = strtok(NULL, ", ");
                column++;
            }

            printf("\n");
        }

        // Close the file
        fclose(fp);
    }
}

void createCSV2(data data[],int s){
     FILE *fpt;
	int i;
    fpt = fopen("new.csv", "w+");
    fprintf(fpt,"Date,       PO4Um,       T_degC,      SiO3uM,      NO2uM,      NO3uM,      Salnty,       O2ml_L\n");

    for (i=2; i<s; i++)
    {

        fprintf(fpt,"%ld,  %f,   %f,   %f,   %f,   %f,   %f,   %f\n",data[i].date,  data[i].T_degC, data[i].PO4uM,data[i].SiO3uM,data[i].NO2uM, data[i].NO3uM,data[i].Salnty, data[i].O2ml_L);
    }

    fclose(fpt);
 }



void removeChar(char* s, char c)
{

    int j, n = strlen(s);
    for (int i = j = 0; i < n; i++)
        if (s[i] != c)
            s[j++] = s[i];

    s[j] = '\0';
}
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



int binarySearch(data data[], int left, int right, long int w){

    while (left <= right) {
    int m = left + (right - left) / 2;

    if (data[m].date == w)
      return m;

    if (data[m].date < w)
      left = m + 1;

    else
      right = m - 1;
  }

  return -1;
}




int main() {

  data d[1406];
 // data data[1500];

  openCSV(d); //call the function that read the csv file



    int s=sizeof(d)/sizeof(d[0]); //used to find right limit, binary search

      //createCSV2(d,s);


    char dat[10]; //date
    char h; //variable to save user's choice
    int date;

  printf("Enter the date: (mm/dd/yyyy) \n"); //ask for a date
  scanf("%s", &dat);
  removeChar(dat,'/');
  swapdate(dat);
  date = atol(dat);

 //printf("the date you entered %ld\n", date);


  printf("Select what do you want to search for:\n"); //ask for temp, phosp or both
  printf(" Type t for Temperature \n Type p for Phosphate \n Type b for both Temperature and Phosphate \n ");
  scanf("%s", &h);

 int result = binarySearch(d, 0 , s-1, date);


  switch(h) //cases for every choice
    {
        case 't': //only temperature

	            //binary search for temp
	             if (result == -1) {printf("No data found\n");}
	            else {printf("Temperature found with binary search: %f \n", d[result].T_degC);}

          break;

        case 'p': //only phosphate

	            //binary search for temp
	            if (result == -1) {printf("No data found\n");}
	            else {printf("The value of the phosphate found with binary search: %f \n", d[result].PO4uM);}

            break;

        case 'b': //both temperature and phosphate

	            //binary search for both
	            if (result == -1) {printf("No data found\n");}
	            else{printf("The value of the phosphate found with binary search: %f ", d[result].PO4uM);
                         printf("and the temperature was: %f \n", d[result].T_degC);}


            break;

        //doesn't match any case
        default:
            printf("Error! This is not a choice!\n");//In case user type wrong letter
    }



  return 0;
}
