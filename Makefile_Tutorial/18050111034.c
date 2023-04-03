/*
#include <stdio.h>
#include <stdlib.h>
#include<mpi.h>
int main(void)
{
	MPI_Init(NULL,NULL);
	int rank, size;
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

if(rank == 0){

printf("I am master!");
int num = 89;
MPI_Send(&num,1,MPI_INT,1,999, MPI_COMM_WORLD);
}
else if (rank==1)
{
int recv;
MPI_Recv(&recv,1,MPI_INT, 0 , 999, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
printf("the recieved messsage: %d\n", recv);
}
MPI_Finalize();
 return 0;
}
*/
//  Author: ZEYNEP AFAT
// ************ Program works with 1011 and 134 but does not work for 1034 and 134 **********
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>


int main(int argc, char *argv[]) {
    int rank, num_procs;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
	int size = atoi(argv[1]);
	int size2 = atoi(argv[2]);
    int i, j, row_start, row_end, row_start2, row_end2;
    double A[size][size], x[size], y[size], y_local[size];
    double B[size2][size2], x2[size2], y2[size2], y_local2[size2];
    double start_time, end_time, start_time2, end_time2;

    // Initialize matrix and vector
    if (rank == 0) {
        for (i = 0; i < size; i++) {
            x[i] = rand() % 100 +1;
            for (j = 0; j < size; j++) {
                A[i][j] = rand() % 100 +1;
            }
        }
	for (i = 0; i < size2; i++) {
            x2[i] = rand() % 100 +1;
            for (j = 0; j < size2; j++) {
                B[i][j] = rand() % 100 +1;
            }
        }
    }

    // Broadcast vector x to all processes
    MPI_Bcast(x, size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(x2, size2, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    // Divide matrix rows among processes
    int rows_per_proc = size / num_procs;
    int rows_per_proc2 = size2/ num_procs;
    row_start = rank * rows_per_proc;
    row_end = row_start + rows_per_proc;
    row_start2 = rank * rows_per_proc2;
    row_end2 = row_start2 + rows_per_proc2;

    // Scatter matrix rows to all processes
    MPI_Scatter(A, rows_per_proc*size, MPI_DOUBLE, A[row_start], rows_per_proc*size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Scatter(B, rows_per_proc2*size2, MPI_DOUBLE, B[row_start2], rows_per_proc2*size2, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    // Compute local part of matrix-vector multiplication
    start_time = MPI_Wtime();
    for (i = row_start; i < row_end; i++) {
        y_local[i] = 0.0;
        for (j = 0; j < size; j++) {
            y_local[i] += A[i][j] * x[j];
        }
    }

    // Gather results from all processes
    MPI_Gather(y_local+row_start, rows_per_proc, MPI_DOUBLE, y, rows_per_proc, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    end_time = MPI_Wtime();

	start_time2 = MPI_Wtime();
    for (i = row_start2; i < row_end2; i++) {
        y_local2[i] = 0.0;
        for (j = 0; j < size2; j++) {
            y_local2[i] += B[i][j] * x2[j];
        }
    }

    // Gather results from all processes
    MPI_Gather(y_local2+row_start2, rows_per_proc2, MPI_DOUBLE, y2, rows_per_proc2, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    end_time2 = MPI_Wtime();
    // Print timing and result
    if (rank == 0) {
        printf("Elapsed time for bigger matrix = %.6f seconds\n", end_time - start_time);
	printf("Elapsed time small matrix = %.6f seconds\n", end_time2 - start_time2);
/*
        printf("Result:\n");
        for (i = 0; i < size; i++) {
            printf("%.2f ", y[i]);
        }
  */      printf("\n");
    }


	// print the result to a file
    FILE *f = fopen(argv[3], "w");
    if (f == NULL) {
        printf("Error opening file.\n");
        return 1;
    }
    fprintf(f, "Result for bigger matrix:\n");
            for (int i = 0; i < size; i++) {

        fprintf(f, "%.2f ", y[i]);
    }
	fprintf(f,"\n\nResult for smaller matrix:\n");
	        for (int i = 0; i < size2; i++) {

        fprintf(f, "%.2f ", y2[i]);
    }
    fprintf(f, "\n");
    fclose(f);

 MPI_Finalize();

    return 0;
}