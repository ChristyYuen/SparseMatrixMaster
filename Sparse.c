//Sparse.c
#include<stdio.h>
#include<stdlib.h>
//#include "Matrix.c"
#include "Matrix.h"
// #include "List.c"//NEVER EVER INCLUDE THIS AGAIN!! 
//#include "List.h"
#define MAX_LEN 3000

int main(int argc, char* argv[])
{
	//how to read in the file? 

	FILE *in, *out;
    //char line[MAX_LEN];

    // check command line for correct number of arguments
    if( argc != 3 )
    {
    	printf("Usage: %s <input file> <output file>\n", argv[0]);
     	exit(1);
    }

    // open files for reading and writing 
    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");
    if( in==NULL )
    {
     	printf("Unable to open file %s for reading\n", argv[1]);
     	exit(1);
    }
    if( out==NULL )
    {
    	printf("Unable to open file %s for writing\n", argv[2]);
    	exit(1);
    }

    int a, b, c;

    fscanf (in, "%d %d %d ", &a, &b, &c);
    fscanf (in, "/n");
    fscanf (in, "/n");

    Matrix A = newMatrix(a);
    Matrix B = newMatrix(a);

    for(int i = 0; i < size(A); i++)
    {
      int col; 
      int row;
      double val; 
      fscanf (in, "%d, %d, %lf", &col, &row, &val);
      changeEntry(A, col, row, val);
    }

    for(int i = 0; i < size(B); i++)
    {
      int col; 
      int row;
      double val; 
      fscanf (in, "%d, %d, %lf", &col, &row, &val);
      changeEntry(B, col, row, val);
    }

    Matrix C, D, E, F, G, H, I, J;

    //loop through the file somehow


 	printf("A has %d non-zero entries:\n", NNZ(A));
    printMatrix(stdout, A);
    printf("\n");

    printf("B has %d non-zero entries:\n", NNZ(B));
    printMatrix(stdout, B);
    printf("\n");

    C = scalarMult(1.5, A);
    printf("(1.5)*A =\n");
    printMatrix(stdout, C);
    printf("\n");

    D = sum(A, B);
    printf("A+B =\n");
    printMatrix(stdout, D);
    printf("\n");

    E = sum(A, A);
    printf("A+A =\n");
    printMatrix(stdout, E);
    printf("\n");

    F = diff(B, A);
    printf("B-A =\n");
    printMatrix(stdout, F);
    printf("\n");

    G = diff(A, A);
    printf("A-A =\n");
    printMatrix(stdout, E);
    printf("\n");

    H = transpose(A);
    printf("Transpose(A) =\n");
    printMatrix(stdout, A);
    printf("\n");

    I = product(A, B);
    printf("A*B =\n");
    printMatrix(stdout, G);
    printf("\n");

    J = product(B, B);
    printf("B*B =\n");
    printMatrix(stdout, G);
    printf("\n");

    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&C);
    freeMatrix(&D);
    freeMatrix(&E);
    freeMatrix(&F);
    freeMatrix(&G);
    freeMatrix(&H);
    freeMatrix(&I);
    freeMatrix(&J);
}