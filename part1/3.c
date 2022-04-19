#include <stdio.h>
#include <string.h>

//creat a struct in order to store csv's data
typedef struct ocean {
char date[10];
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
                    if (column == 1) {data[r].T_degC = atof(value);}

                // Column 3
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


int binarySearch(data array[], int Left, int Right, string W){

    if(Right>=1){
        
        int m=(Left+(Right-1))/2 //find the middle of the array
    

            if(array[m]==W) //W(anted) element is in the middle
                return m;
    
            if(array[m]>W) //W(anted) element is smaller than mid
                return binarySearch(array, Left, m-1, W); //smaller list, change Right 

            //W is after the middle (to the Right)
            else return binarySearch(array, m+1, Right , W); //smaller list, change Left 
    }

    return -1; //the array has only one element, nothing to search
    
}


int interpolationSearch(data array[], int n, string W){     //array of sorted data, n=number, W=value we want
    if(n==0)
        { printf("Error! No data found");
          exit(1)}
    
    int l=0, h=n-1, mid; //l=lower bound, h=higher bound, mid=middle 

    //loop
    while (array[h] != array[l] && W >= array[l] && W <= array[h])
        {
            //find mid
            mid = l + ((W - array[l]) * (h - l) / (array[h] - array[l]));
 
            //value is found
            if (W == array[mid]) {return mid;}

            else if(W < array[mid]) {h = mid - 1;} //change high bound

            else {l = mid + 1;} //change low bound
        }

    }

    //value found
    if (x == array[l]) {return l;}

    //value doesn't exist 
    else {return -1;}
}


int main() {

  openCSV(array); //call the function that read the csv file

  data array[1500]; 

    int s=sizeof(array)/sizeof(array[0]); //used to find right limit, binary search
    int n=sizeof(array); 

    int date; //date
    int h; //variable to save user's choice
  
  printf("Enter the date:\n"); //ask for a date
  scanf("%d",&date);  

  printf("Select what do you want to search for:\n"); //ask for temp, phosp or both
  printf(" Type t for Temperature \n Type p for Phosphate \n Type b for both Temperature and Phosphate \n ");
  scanf("%d", &h);
    
    switch(h) //cases for every choice 
    {
        case 't': //only temperature
            
            //binary search for temp
            int result_temp_bin = binarySearch(array, 0 , s-1, date)
            if (result_temp_bin != -1) {printf("Temperature found with binary search: %f \n" array[result_temp_bin].T_degC);}
            if (result_temp_bin == -1) {printf("No data found\n");}

            //interpolation search for temp
            int result_temp_inter = interpolationSearch(array, n, date);
            if (result_temp_inter != -1) {printf("Temperature found with interpolation search: %f \n" array[result_temp_inter].T_degC);}
            if (result_temp_inter == -1) {printf("No data found\n");}

            break;

        case 'p': //only phosphate

            //binary search for temp
            int result_phosp_bin = binarySearch(array, 0 , s-1, date)
            if (result_phosp_bin != -1) {printf("The value of the phosphate found with binary search: %f \n" array[result_phosp_bin].PO4uM);}
            if (result_phosp_bin == -1) {printf("No data found\n");}

            //interpolation search for temp
            int result_phosp_inter = interpolationSearch(array, n, date);
            if (result_phosp_inter != -1) {printf("The value of the phosphate found with interpolation search: %f \n" array[result_phosp_inter].PO4uM);}
            if (result_phosp_inter == -1) {printf("No data found\n");}

            break;

        case 'b': //both temperature and phosphate

            //binary search for both
            int result_b_bin = binarySearch(array, 0 , s-1, date)
            if (result_b_bin != -1) {printf("The value of the phosphate found with binary search: %f " array[result_b_bin].PO4uM, "and the temperature was: %f \n" array[result_b_bin].T_degC);}
            if (result_b_bin == -1) {printf("No data found\n");}

             //interpolation search for temp
            int result_b_inter = interpolationSearch(array, n, date);
            if (result_b_inter != -1) {printf("The value of the phosphate found with binary search: %f " array[result_b_inter].PO4uM, "and the temperature was: %f \n" array[result_b_inter].T_degC);}
            if (result_b_inter == -1) {printf("No data found\n");}

            break;

        //doesn't match any case 
        default:
            printf("Error! This is not a choice!\n");//In case user type wrong letter
    }

    /*char cont_prog = 'n';
            do {
                /* main program in here */
                printf("Do you want to start again? (y/n): ");
                cont_prog = getchar();
            } while (cont_prog == 'y' || cont_prog == 'Y'); */

  return 0;
}
