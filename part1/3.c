#include <stdio.h>

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


int binarySearch(int array[], int Left, int Right, int W){

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


int interpolationSearch(int array[], int n, int W){     //array of sorted data, n=number, W=value we want
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

  read_csv(); //call the function to read the csv file

  //ask from the user to enter the value he want 
  printf("Enter the value W you want to find, using binary and interpolation search:");
  scanf("%d",&W);  
  
  //binary
  int result_b = binarySearch(array, ); //result of binary search
  if(result_b == -1){printf("Element isn't found with binary search\n");}
  if(result_b != -1){printf("Element found at index:\n %d \n using binary search \n",result);}

  //interpolation
  int n=sizeof(array)/sizeof(array[0]);
  int result_p = interpolationSearch(array, n, W); //result of interpolation search
  if(result_p == -1){printf("Element isn't found with interpolation search\n");}
  if(result_p != -1){printf("Element found at index:\n %d \n using interpolation search \n",result);}

  return 0;
}
