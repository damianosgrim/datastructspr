#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

//creat a struct in order to store csv's data
typedef struct data {
char date[10];
float T_degC;
float PO4uM;
float SiO3uM;
float NO2uM;
float NO3uM;
float Salnty;
float O2ml_L
} data;

typedef struct data2 {
long int date[10];
float T_degC;
float PO4uM;
float SiO3uM;
float NO2uM;
float NO3uM;
float Salnty;
float O2ml_L
} data2;

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
                        strcpy(data[r].date, value);
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

void openCSV2(data2 data[]){
    FILE* fp = fopen("new.csv", "r");

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
                    data[r].T_degC = atol(value);
                }
           

                if (column == 1) {
                    data[r].T_degC = atof(value);
                }


                if (column == 2) {
                  data[r].PO4uM= atof(value);  //we save the phosphate as long integers
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

void createCSV2(data2 data[],int s){
     FILE *fpt;
	int i;
    fpt = fopen("new.csv", "w+");
    fprintf(fpt,"Date,       PO4Um,       T_degC,      SiO3uM,      NO2uM,      NO3uM,      Salnty,       O2ml_L\n");
    
    for (i=2; i<s; i++)
    {
		
        fprintf(fpt,"%s,  %f,   %f,   %f,   %f,   %f,   %f,   %f\n",data[i].date,  data[i].T_degC, data[i].PO4uM,data[i].SiO3uM,data[i].NO2uM, data[i].NO3uM,data[i].Salnty, data[i].O2ml_L);
    }

    fclose(fpt);
 }

void keep_number(data2 data[], char str[]){
	
	int i=0;
    int j = 0;
	
    for (i=2; str[i] ; i++)
    {
        
        if (str[i] >= '0' && str[i] <= '9')
        {
            str[j] = str[i];
            j++;
        }
    }

    str[i] = '\0';

    
}

int binarySearch(data data[], int Left, int Right, char W){

    if(Right>=1){

        int m=(Left+(Right-1))/2; //find the middle of the array


            if(data[m].date==W) //W(anted) element is in the middle
            	return m;

            if(data[m].date>W) //W(anted) element is smaller than mid
                return binarySearch(data, Left, m-1, W); //smaller list, change Right

            //W is after the middle (to the Right)
            else return binarySearch(data, m+1, Right , W); //smaller list, change Left
    }

    return -1; //the array has only one element, nothing to search

}


/*int interpolationSearch(data data[], int n, char W){     //array of sorted data, n=number, W=value we want
    if(n==0)
        { printf("Error! No data found");
          exit(1);}

    int l=0, h=n-1, mid; //l=lower bound, h=higher bound, mid=middle

    //loop
    while (data[h].date != data[l].date && W >= data[l].date && W <= data[h].date)
        {
            //find mid
            mid = l + ((W - data[l].date) * (h - l) / (data[h].date - data[l].date));

            //value is found
            if (W == data[mid].date) {return mid;}

            else if(W < data[mid].date) {h = mid - 1;} //change high bound

            else {l = mid + 1;} //change low bound
        }



    //value found
    if(W == data[l].date) {return l;}

    //value doesn't exist
    else {return -1;}
}
*/

int main() {

  data d[1500];
  data data[1500];

  openCSV(d); //call the function that read the csv file
  openCSV2(data);


    int s=sizeof(data)/sizeof(data[0]); //used to find right limit, binary search
    int n=sizeof(data);

    int date; //date
    int h; //variable to save user's choice

  printf("Enter the date:\n"); //ask for a date
  scanf("%s",&date);

  printf("Select what do you want to search for:\n"); //ask for temp, phosp or both
  printf(" Type t for Temperature \n Type p for Phosphate \n Type b for both Temperature and Phosphate \n ");
  scanf("%d", &h);


   int result_temp_bin = binarySearch(data, 0 , s-1, date);
 //  int result_temp_inter = interpolationSearch(data, n, date);
   int result_phosp_bin = binarySearch(data, 0 , s-1, date);
  // int result_phosp_inter = interpolationSearch(data, n, date);
   int result_b_bin = binarySearch(data, 0 , s-1, date);
  // int result_b_inter = interpolationSearch(data, n, date);

    switch(h) //cases for every choice
    {
        case 't': //only temperature

	            //binary search for temp
	            if (result_temp_bin != -1) {printf("Temperature found with binary search: %f \n", data[result_temp_bin].T_degC);}
	            if (result_temp_bin == -1) {printf("No data found\n");}

	            //interpolation search for temp
	         //   if (result_temp_inter != -1) {printf("Temperature found with interpolation search: %f \n", data[result_temp_inter].T_degC);}
	        //    if(result_temp_inter == -1) {printf("No data found\n");}

            break;

        case 'p': //only phosphate

	            //binary search for temp
	            if (result_phosp_bin != -1) {printf("The value of the phosphate found with binary search: %f \n", data[result_phosp_bin].PO4uM);}
	            if (result_phosp_bin == -1) {printf("No data found\n");}

	            //interpolation search for temp
	          //  if (result_phosp_inter != -1) {printf("The value of the phosphate found with interpolation search: %f \n", data[result_phosp_inter].PO4uM);}
	           // if (result_phosp_inter == -1) {printf("No data found\n");}

            break;

        case 'b': //both temperature and phosphate

	            //binary search for both
	            if (result_b_bin != -1) {printf("The value of the phosphate found with binary search: %f ", data[result_b_bin].PO4uM, "and the temperature was: %f \n", data[result_b_bin].T_degC);}
	            if (result_b_bin == -1) {printf("No data found\n");}

	             //interpolation search for temp
//	            if (result_b_inter != -1) {printf("The value of the phosphate found with binary search: %f ", data[result_b_inter].PO4uM, "and the temperature was: %f \n", data[result_b_inter].T_degC);}
	//            if (result_b_inter == -1) {printf("No data found\n");}

            break;

        //doesn't match any case
        default:
            printf("Error! This is not a choice!\n");//In case user type wrong letter
    }

    /*char cont_prog = 'n';
            do {
                 main program in here
                printf("Do you want to start again? (y/n): ");
                cont_prog = getchar();
            } while (cont_prog == 'y' || cont_prog == 'Y'); */

  return 0;
}
