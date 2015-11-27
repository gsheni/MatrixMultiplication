#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int round_gaurav(double number );
void print_matrices(float*, float*, float*, int);
void multiply_matrices(float*, float*, float*, int);
void fill_matrices(float *A_Matrix, float *B_Matrix, int N);
void output_file(float* ANS_Matrix, int N);
void check_arguments( int argc, char *argv[] );

void multiply_matrices(float *A_Matrix, float*B_Matrix, float*ANS_Matrix, int N){
	int i;
	int j;
	int k;
	float sum;
	float m;
	float n;
	for (i = 0; i <  N; i++){
		for (j = 0; j < N; j++){
			sum = 0;
			for (k  = 0; k< N ; k++){
				m = *(A_Matrix + i*N + k);
				n = *(B_Matrix + k*N + j);
				sum += m*n;
			}
			*(ANS_Matrix + i*N + j) = sum;
		}
	}
}
void print_matrices(float *A_Matrix, float*B_Matrix, float*ANS_Matrix, int N){
	int i;
	int j;
	printf("A Matrix is: \n");
	// int w = 0;
	for (i = 0; i <  N; i++){
		for (j = 0; j < N; j++){
			printf("%.4f ", *(A_Matrix + i*N + j));
		}
		printf("\n");
	}

	printf("B Matrix is: \n");
	for (i = 0; i <  N; i++){
		for (j = 0; j < N; j++){
			printf("%.4f ", *(B_Matrix + i*N + j));
		}
		printf("\n");
	}

	printf("Resulting Matrix is: \n");
	for (i = 0; i <  N; i++){
		for (j = 0; j < N; j++){
			printf("%.4f ", *(ANS_Matrix + i*N + j));
		}
		printf("\n");
	}
}
void fill_matrices(float *A_Matrix, float *B_Matrix, int N){
	srand48(time(NULL)); // randomize seed
	int i;
	int j;

	for (i = 0; i <  N; i++){
		for (j = 0; j < N; j++){
			float A_input = drand48() * 5.0;
			*(A_Matrix + i*N + j) = A_input;
		}
	}
	for (i = 0; i <  N; i++){
		for (j = 0; j < N; j++){
			float B_input =  drand48() * 5.0;
			*(B_Matrix + i*N + j) = B_input;
		}
	}
}
void output_file(float* ANS_Matrix, int N){
	FILE *file_output = fopen("product.dat", "w");
	if (file_output == NULL) {
	    printf("File could not be created. ");
	    exit(1);
	}
	int i;
	int j;
	for (i = 0; i <  N; i++){
		for (j = 0; j < N; j++){
			fprintf(file_output, "%.4f\t", *(ANS_Matrix + i*N + j));
		}
		fprintf(file_output, "\n");
	}
	fclose ( file_output );
}
void check_arguments( int argc, char *argv[] ){
	//check for correct # of arguments
	if (argc != 2){
		printf ("Incorrect number of command line arugments.\r\n");
		exit(1);
	}

	//check for command line input corresponds to positive number
	int current = atoi(argv[1]);
	if (current < 0 ){
		printf ("The arugment which is equal to %d  is less than zero.\r\n", current);
		exit(1);
	}
}
int round_gaurav(double number)
{
    return (number >= 0) ? (int)(number + 0.5) : (int)(number - 0.5);
}
int main ( int argc, char *argv[] )
{
	check_arguments(argc, argv);
	
	//treat each number as a float
	//round then to the nearest integer
	// ex 5.4 = 5.0
	// ex 5.6 = 6.0
	//named round_gaurav because it avoids warning error of conflict types with built-in function
	int N = round_gaurav(atof(argv[1]));

	//Create the matrices
	//below was in class given information
	float *A_Matrix = (float *)malloc(N * N * sizeof(float));
	float *B_Matrix = (float *)malloc(N * N * sizeof(float));

	fill_matrices(A_Matrix, B_Matrix, N);

	float *ANS_Matrix =  (float *)malloc(N * N * sizeof(float));

	//from in class notes
	clock_t start; // declaration of ftype
	clock_t stop;
	double execution_time;
	start = clock();

	multiply_matrices(A_Matrix, B_Matrix, ANS_Matrix, N);

	stop = clock();

	execution_time = ((double) (stop - start)) / CLOCKS_PER_SEC;
	printf("Execution Time in seconds: %.10lf\n", execution_time );

	//print_matrices(A_Matrix,B_Matrix,ANS_Matrix, N);

	output_file(ANS_Matrix, N);
}
