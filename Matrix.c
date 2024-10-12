#include<stdio.h>
#include<stdlib.h>
#include "Matrix.h"
#include <stdbool.h>

typedef struct MatrixObj
{
   List* row;
   int size;
   int NNZ; 
}MatrixObj;

typedef struct EntryObj
{
	int col;
	double val; 
}EntryObj;

typedef EntryObj* Entry;

Entry newEntry(int col, double val){
	Entry E = NULL;
   	E = malloc(sizeof(EntryObj));
   	E->col = col;
   	E->val = val;
   	return(E);
}

// newMatrix()
// Returns a reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n){
	Matrix M = malloc(sizeof(MatrixObj));
	M->row = calloc(n, sizeof(List));
	if (n < 1)
	{
		printf("Matrix Error: Matrix is too small\n");
      	exit(1);
	}
	//row = newList[n+1];
	for(int i = 0; i<n; i++) 
	{
		M->row[i] = newList();
	}
	M->size = n;
	M->NNZ =0;
	return M;
}

// freeMatrix()
// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM){
	//Entry E; 
  for(int i = 0; i < size(*pM); i++)
  {
    //E = (Entry)get((*pM)->row[i]); 
    while(length((*pM)->row[i]) >= 0)
    {
      moveFront((*pM)->row[i]);
      //while(index((*pM)->row[i]) >= 0)
      //{
        deleteFront((*pM)->row[i]);
        //moveNext((*pM)->row[i]);
      //}
    }
    freeList(&(*pM)->row[i]);
  }
  free((*pM)->row);
  free(*pM);
  *pM = NULL;
}

// Access functions
// size()
// Return the size of square Matrix M.
int size(Matrix M)
{
	return M->size;
}

// NNZ()
// Return the number of non-zero elements in M.
int NNZ(Matrix M)
{
	return M->NNZ;
}

// equals()
// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B)
{
    int counter = 0;
    Entry Ea, Eb;
	//how do i go into each node object of a list?
	if(size(A) != size(B))
	{
		return 0;
	}
	for(int i = 0; i < size(A); i++)
	{
    	moveFront(A->row[i]);
    	moveFront(B->row[i]);
    	Ea = (Entry)get(A->row[i]);
    	Eb = (Entry)get(B->row[i]);
		if( length(A->row[i]) == length(B->row[i]) )
		{
        while(index(A->row[i]) != -1 && index(B->row[i]) != -1)
        {
      		if(Eb->col == Ea->col &&  Eb->val == Ea->val)
      		{
        		counter++;
            moveNext(A->row[i]);
    	      moveNext(B->row[i]);
      		}
        }
		}
	}
    if(A->NNZ == B->NNZ && A->NNZ == counter)
    {
    	return 1;
    }
    else
    {
    	return 0;
    }
    free(Ea);
    free(Eb);
}

// Manipulation procedures
// makeZero()
// Re-sets M to the zero Matrix.
void makeZero(Matrix M)
{
	Entry E = newEntry(0, 0.0);
	for(int i=0; i< size(M); i++)
	{
		moveFront(M->row[i]);
		while(index(M->row[i]) != -1)
		{
			E = (Entry)get(M->row[i]); //how to pull entry out?
			changeEntry(M, i, E->col, 0.0); //trying to get Entry's col and value into changeEntry
			moveNext(M->row[i]);
		}
 	}
 	M->NNZ = 0;// is this right? How to update NNZ of M 
}


// changeEntry()
// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x)
{
	bool location = false; //false
  Entry E = newEntry(j, x);
	if(i < 1 || j < 1 || i > size(M) || j > size(M)) 
	{
		printf("Matrix Error: unable to change entry\n");
    exit(1);
	}
	moveFront(M->row[i]);
	while(index(M->row[i]) != 0) //find location
	{
		E = (Entry)get(M->row[i]);
		location = (E->col ==j);
		if(location)
		{
			if(x == 0.0)
			{
				delete(M->row[i]);
				M->NNZ--;
				exit(1);
			}
			else
			{
				E->val=x;
				exit(1);
			}
		}
		moveNext(M->row[i]);
	

	  if(!location && x != 0.0)
	  {
		  moveFront(M->row[i]);
		  if(index(M->row[i]) == -1) //empaty List
		  {
			  append(M->row[i],E); //append or prepend
			  M->NNZ++;
			  exit(1);
		  }
		  else
		  {
        int c = ((Entry)get(M->row[i]))->col; //get column
			  while(index(M->row[i])>-1 && c > j )
			  {
			  	moveNext(M->row[i]); //finds the location of j
			  }
			  if(index(M->row[i]) > -1)
			  {
				  insertBefore(M->row[i],E);
				  M->NNZ++;
				  exit(1);
			  }
			  else
			  {
				  append(M->row[i],E);
				  M->NNZ++;
				  exit(1);
			  }
		   }
  	}
   }

}

// Matrix Arithmetic operations
// copy()
// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A)
{
	Matrix temp = newMatrix(size(A)); 
	Entry E;
	for(int i = 1; i<= size(A); i++) 
	{
		for(moveFront(A->row[i]); index(A->row[i]) != -1; moveNext(A->row[i])) //might change to while loop for easy reading 
		{
			E = (Entry)get(A->row[i]); //is this legal? 
			changeEntry(temp, i, E->col, E->val);
		}
	}
	temp->NNZ = A->NNZ;
	return temp;
	free(E); 
	free(temp);
}

// transpose()
// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A)
{
	Entry E = newEntry(0, 0.0);
  Matrix temp = newMatrix(size(A));
	for(int i = 1; i <= size(A); i++)
	{
		moveFront(A->row[i]);
		while(index(A->row[i]) != -1)
		{
			E->col= (*(int*)get(A->row[i]));
			E->val= *(double*)(get(A->row[i]));
			changeEntry(temp, E->col, i, E->val);
			moveNext(A->row[i]);
		}
	}
    return temp;
	free(E);//maybe
    free(temp);
}

// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A)
{
	Matrix temp = newMatrix(size(A));
	int col = 0; 
	double valInt = 0.0; //intial value
	double valFin = 0.0; //final value
	Entry T; 
	temp->NNZ = A->NNZ; 
	for(int i = 0; i < size(A); i++)
	{
		moveFront(A->row[i]);
		while(index(A->row[i]) != -1)
		{
			valInt = *(double*)(get(A->row[i])); 
			col = (*(int*)get(A->row[i]));
			valFin = x*valInt;
			T = newEntry(col, valFin);
			append(A->row[i],T);
			moveNext(A->row[i]);
		}
	}
	return temp;
}

// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B)
{
	List tempA;
	List tempB;
	Matrix temp = newMatrix(size(A));
	double val1 = 0.0, val2 = 0.0; //values
	int c1 = 0; //column
	if(size(A) != size(B))
	{
		printf("Matrix Error: Matrices don't match.\n");
      	exit(1);
	}
	if(equals(A,B))
	{
		temp = scalarMult(2, A);
	}
	else
	{
		for(int i = 0; i <= size(A); i++)
		{
			tempA = A->row[i]; 
			tempB = B->row[i]; 
			
			if(length(tempA)==0 && length(tempB)!=0) //what if entry is 0.0?
			{
				moveFront(tempB);
				while(index(tempB) != -1)
				{
					changeEntry(temp, i, ((Entry)get(tempB))->col, ((Entry)get(tempB))->val);
					moveNext(tempB);
					temp->NNZ++;//temp's matrix gets added
				}
			}
			else if(length(tempA)!=0 && length(tempB)==0)
			{
				moveFront(tempA);
				while(index(tempA) != -1)
				{
					changeEntry(temp, i, ((Entry)get(tempA))->col, (((Entry)get(tempA))->val));
					moveNext(tempA);
					temp->NNZ++;//temp's matrix gets added
				}
			}
			else if(length(tempA)!=0 && length(tempB)!=0)
			{
				moveFront(tempA);
				moveFront(tempB);
				while(index(tempA) != -1 && index(tempB) != -1)
				{
					if(((Entry)get(tempA))->col == ((Entry)get(tempB))->col)
					{
						val1=((Entry)get(tempA))->val;
						val2=((Entry)get(tempB))->val;
						c1=((Entry)get(tempB))->col;
						changeEntry(temp, i, c1, (val1+val2));
						moveNext(tempA);
						if(!equals(A,B))
						{
							moveNext(tempB);
						}
					}
					else if(((Entry)get(tempA))->col < ((Entry)get(tempB))->col)
					{
						val1=((Entry)get(tempA))->val;
						c1=((Entry)get(tempA))->col;
						changeEntry(temp, i, c1, val1);
						moveNext(tempA);
						temp->NNZ++; //temp's
					}
					else if(((Entry)get(tempA))->col > ((Entry)get(tempB))->col) //could have been a else but just in case
					{
						val2=((Entry)get(tempB))->val;
						c1=((Entry)get(tempB))->col;
						changeEntry(temp, i, c1, val2);
						moveNext(tempB);
						temp->NNZ++; //temp's
					}
				}
				while(index(tempA) != -1)
				{
					changeEntry(temp, i, ((Entry)get(tempA))->col, ((Entry)get(tempA))->val);
					moveNext(tempA);
					temp->NNZ++;
				}
				while(index(tempB) != -1)
				{
					changeEntry(temp, i, ((Entry)get(tempB))->col, ((Entry)get(tempB))->val);
					moveNext(tempB);
					temp->NNZ++;
				}

			}
		}
	}
	return temp;
	//free temp?
}

// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B)
{
	if(size(A) != size(B))
	{
		printf("Matrix Error: Matrices don't match.\n");
    exit(1);
	}
	Matrix temp = newMatrix(size(A));
	B = scalarMult(-1.0, B);
	temp = sum(A,B);
	return temp;
  //free(temp);

}

//Helper function to find the dot product of two lists. 
double dot(List A, List B)
{
	double product = 0.0;
	moveFront(A);
	moveFront(B);
	while(index(A) != -1 && index(B) != -1)
	{
		Entry EA = (Entry)get(A);
		Entry EB = (Entry)get(B);
		if(EB->col > EA->col)
		{
			moveNext(A);
		}
		else if(EA->col > EB->col)
		{
			moveNext(B);
		}
		else
		{
			product = product + (EA->val * EB->val);
			moveNext(A);
			moveNext(B);
		}
	}
	return product;
}

// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B)
{
	if(size(A) != size(B))
	{
		printf("Matrix Error: Matrices don't match.\n");
      	exit(1);
	}
	Matrix temp1 = newMatrix(size(A));
	Matrix tA = transpose(A);
	for(int i = 0; i < size(A); i++)
	{
		for(int j = 0; j < size(A); j++)
		{
      while(index(tA->row[i]) != -1 && index(B->row[i]) != -1)
      {
        changeEntry(temp1, i, j, dot(B->row[i], tA->row[j]) ); //trying to do temp2.row[j])
        moveNext(tA->row[i]);
        moveNext(B->row[i]);
      }
			
		}
	}
  free(tA);
	return(temp1);
	//free(temp1);
}

// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
//1: (1, 1.0) (2, 2.0) (3, 3.0)
//col: (%d, %d) (%d, %d) (%d, %d)
void printMatrix(FILE* out, Matrix M)
{
   Entry E = newEntry(0, 0.0); //must equal smth 
   int i = 0;
   while(E != NULL && i < size(M))
   {
   		E = (Entry)get(M->row[i]);
   		if(length(M->row[i]) != 0)
   		{
   			printf("%d:", i);
   		}
   		//moves to the next entry 
   		while(E != NULL && i < index(M->row[i]))
   		{
   			printf("(%d, %1f) ", E->col, E->val);
   		}
   		i++;
   		printf("\n");
      moveNext(M->row[i]);
   }
   free(E);
}