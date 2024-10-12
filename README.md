# Sparse Matrix Operations

## Project Overview

This project involves creating a high-performance **Sparse Matrix Calculator** in C, designed to efficiently handle matrix operations with sparse matrices. A matrix is sparse when it has significantly fewer non-zero elements compared to the total number of elements. This calculator supports fundamental matrix operations such as addition, subtraction, scalar multiplication, matrix multiplication, and transposition, optimized for sparse matrices.

### Key Operations:
- **Matrix Addition & Subtraction**: Efficiently add and subtract sparse matrices.
- **Scalar Multiplication**: Multiply a matrix by a scalar value.
- **Matrix Multiplication**: Compute the product of two sparse matrices.
- **Transpose**: Generate the transpose of a matrix.
- **Efficient Storage**: Matrix elements are stored in an array of linked lists, where each list only contains non-zero entries, saving space and computation time.

## Project Structure

- **Sparse.c**: The main client program that handles input/output operations, processes the matrices, and performs calculations.
- **Matrix.c/Matrix.h**: Implementation of the Matrix Abstract Data Type (ADT) that provides matrix operations.
- **List.c/List.h**: Modified List ADT, optimized to handle sparse matrix entries.
- **MatrixTest.c & ListTest.c**: Unit tests for the Matrix and List ADTs to ensure their correctness in isolation.

### Input/Output File Format

The program reads from an input file and outputs the results of various matrix operations to a specified output file. The input file contains the size of the matrices, followed by the non-zero entries of two matrices, A and B.

Example of matrix operations included in the output:
- A, B matrices
- 1.5 * A (Scalar multiplication)
- A + B, A + A (Matrix addition)
- B - A, A - A (Matrix subtraction)
- Transpose(A)
- A * B, B * B (Matrix multiplication)

## Implementation Highlights

- **Efficient Sparse Representation**: Matrices are stored as an array of lists, where each list represents a row, storing only non-zero entries along with their column indices. This reduces both space and time complexity for operations on sparse matrices.
- **Optimized Matrix Operations**: By focusing only on non-zero elements, matrix operations skip unnecessary calculations involving zeros, drastically improving performance for large, sparse matrices.
- **Test-Driven Development**: Each ADT (Matrix and List) is thoroughly tested in isolation before integration.

## How to Compile and Run

1. **Compile the Program**: Run the following command to compile the project and create an executable.
   ```bash
   make

2. **Execute the Program**: Use the following command to run the Sparse Matrix Calculator with input and output files.
   ```bash
   ./Sparse <input_file> <output_file>

## Key Takeaways
This project demonstrates an ability to optimize algorithms for real-world efficiency, particularly in the context of handling large-scale sparse matrices. The work involves:

- Designing space- and time-efficient data structures.
- Implementing complex matrix operations using advanced data manipulation techniques.
- Writing clean, modular, and testable C code.
