#include <hellomake.h>
#include <stdio.h>  
#include <stdlib.h>  
int main(int argc, char* argv[]){

/*
 printf("You have entered %d arguments:\n", argc);
 
    for (int i = 0; i < argc; i++) {
        printf("%s\n", argv[i]);
    }

*/



	//call a function in other file
	int n = atoi(argv[1]);
	int m = atoi(argv[2]);
 	srand(34);
int vec[6] = {14,18,22,65,48,79};
int **arr;
 arr = (int **) malloc(n * sizeof(int *)); 
for (int i = 0; i < n; i++) { 
arr[i] = (int *) malloc(m * sizeof(int)); }


 // fill the array with random numbers between 0 and 99
 for (int i = 0; i < n; i++) {
 for (int j = 0; j < m; j++) {
 arr[i][j] = rand() % 100; } }

//perform the matrix-vector multiplication
int result[5];
    for (int i = 0; i < 5; i++) {
        result[i] = 0;
        for (int j = 0; j < 6; j++) {
            result[i] += arr[i][j] * vec[j]; // perform the matrix-vector multiplication
        }
    }



//Print the matrix, vector and the result

printf("\nMatrix\n");

	for(int i=0; i<n; i++)
{
	for(int j=0; j<m; j++)
{
	printf("%d  " ,arr[i][j]);
}
printf("\n");
}


printf("\nVector:\n");
    for (int i = 0; i < 6; i++) {
        printf("%d ", vec[i]);
    }
    printf("\n\nResult:\n");
    for (int i = 0; i < 5; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

// print the result to a file
    FILE *f = fopen(argv[3], "w");
    if (f == NULL) {
        printf("Error opening file.\n");
        return 1;
    }
    fprintf(f, "Result:\n");
    for (int i = 0; i < 5; i++) {
        fprintf(f, "%d ", result[i]);
    }
    fprintf(f, "\n");
    fclose(f);







 // use the array
 // free the memory
 for (int i = 0; i < n; i++)
 { free(arr[i]);
 }
 free(arr);






	return(0);
}
