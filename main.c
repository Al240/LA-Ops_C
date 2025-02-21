/* Linear Algebra Operations: Performs basic operations used in Linear Algebra 
By: Al240 // 2/13/2025

ver.    Date        Changelog
1.2     2/20/2025   [AL] Added matrix display option, augmented matrix solver, and eigenvalue solver (beta)
1.1     2/14/2025   [AL] Menus written (fixed input bug), implemented vector stuff
1.0     2/13/2025   [AL] Initial commit, combines matrix.c and vectorProduct.c
*/
#include <stdio.h>
#include <stdlib.h>
#include "vectors.h"
#include "matrix.h"

void MainMenu(void) {
    printf("\n\n-------------------------\n");
    printf("\nLINEAR ALGEBRA OPERATIONS\n");
    printf("v1.1\n\n");
    printf("(V)ectors only\n");
    printf("(M)atrices\n");
    printf("(Q)uit Program\n");
    printf("Choose an option: ");
}

void VectorMenu(void) {
    printf("\n\nVECTOR OPERATIONS MENU\n");
    printf("(A)ddition and Subtraction (A-B)\n");
    printf("(D)ot Product (A.B)\n");
    printf("(C)ross Product (AxB)\n");
    printf("(M)agnitude & Unit Vector (A)\n");
    printf("(R)eturn to main menu\n");
    printf("Choose an option: ");
}

void MatrixMenu(void) {
    printf("\n\nMATRIX OPERATIONS MENU\n");
    printf("(0) Display Inputted Matrix\n");
    printf("(1) Row-Reduced Echelon Form (RREF)\n");
    printf("(2) Augmented Matrix Solver\n");
    printf("(3) Dimension\n");
    printf("(4) Addition and Subtraction\n");
    printf("(5) Multiplication\n");
    printf("(6) Determinant (up to 3x3)\n");
    printf("(7) EXPERIMENTAL: Eigenvalues\n");
    printf("(R)eturn to main menu\n");
    printf("Choose an option: ");
}

int main(void) {
    char userChoice, vecChoice, matChoice;
    int running, runVec, runMat;
    running = 1;
    while (running) {
        MainMenu();
        scanf(" %c", &userChoice);
        switch (userChoice) {
            // Vectors
            case 'V': case 'v':
                // Define vectors A and B
                printf("Before you continue, please define your vectors (input 0 for vector B compoments if not needed).\n");
                printf("\nVECTOR A:\n");
                Vect vecA = getVector();
                printf("\nVECTOR B:\n");
                Vect vecB = getVector();
                printf("Vectors A and B defined! Showing vector operation menu...\n");

                runVec = 1;
                while (runVec) {
                    VectorMenu();
                    scanf(" %c", &vecChoice);
                    switch (vecChoice) {
                        // Addition and Subtraction
                        case 'A': case 'a':
                            vAddSub(vecA, vecB);
                            break;
                        // Dot Product
                        case 'D': case 'd':
                            dotProduct(vecA, vecB);
                            break;
                        // Cross Product
                        case 'C': case 'c':
                            crossProduct(vecA, vecB);
                            break;
                        // Magnitude and Unit Vector
                        case 'M': case 'm':
                            while ((getchar()) != '\n') {} // clear input buffer
                            char vMagChoice;
                            printf("Perform this on vector A or B? ");
                            scanf("%c", &vMagChoice);
                            if (vMagChoice == 'A') getMagUnit(vecA);
                            else if (vMagChoice == 'B') getMagUnit(vecB);
                            break;
                        // Return to main menu
                        case 'R': case 'r':
                            printf("Returning to main menu...\n");
                            runVec = 0;
                            while ((getchar()) != '\n') {} // clear input buffer
                            break;

                        default:
                            printf("Invalid vector operation. Try again.\n"); // input validation
                            while ((getchar()) != '\n') {} // clear input buffer
                    }
                }
            break;
            
            // Matrices
            case 'M': case 'm':
                // Define matrices A and B
                printf("Before you continue, please define your matrices (input 0 for matrix B entries if not needed).\n");
                int mRow, nCol;
                printf("\nMATRIX A\n");
                printf("How many rows should matrix A have? ");
                scanf(" %d", &mRow);
                printf("How many columns should matrix B have? ");
                scanf(" %d", &nCol);
                Matrix mA = *newMatrix(mRow, nCol, 1);

                printf("\nMATRIX B\n");
                printf("How many rows should matrix B have? ");
                scanf(" %d", &mRow);
                printf("How many columns should matrix B have? ");
                scanf(" %d", &nCol);
                Matrix mB = *newMatrix(mRow, nCol, 1);


                runMat = 1;
                while (runMat) {
                    while ((getchar()) != '\n') {} // clear input buffer
                    MatrixMenu();
                    scanf(" %c", &matChoice);
                    switch (matChoice) {
                        case '0': // Show matrix
                            printf("Current matrix A: \n");
                            mDisp(&mA);
                            break;

                        case '1': // RREF(A)
                            char mRREFChoice;
                            printf("Perform this on matrix A or B? ");
                            scanf(" %c", &mRREFChoice);
                            if (mRREFChoice == 'A') {
                                mRREF(&mA);
                            }
                            else if (mRREFChoice == 'B') {
                                mRREF(&mB);
                            }
                            break;

                        case '2': // Solver
                            printf("Define the augmented part of the matrix (the B in Ax=B): \n");
                            Matrix* AugB = newMatrix(mA.rows, 1, 1);
                            Matrix mD = *AugB; 
                            printf("\nNow solving Ax=B...\n");
                            mSolver(mA, mD);
                            break;

                        case '3': // Dim(A)
                            while ((getchar()) != '\n') {} // clear input buffer
                            char mDimChoice;
                            printf("Perform this on matrix A or B? ");
                            scanf(" %c", &mDimChoice);
                            if (mDimChoice == 'A') {
                                mDim(mA);
                            }
                            else if (mDimChoice == 'B') {
                                mDim(mB);
                            }
                            break;

                        case '4': // A+B
                            mAddSub(mA, mB);
                            break;

                        case '5': // AxB
                            mMult(mA, mB);
                            break;

                        case '6': // det(A)
                            while ((getchar()) != '\n') {} // clear input buffer
                            char mDetChoice;
                            printf("Perform this on matrix A or B? ");
                            scanf(" %c", &mDetChoice);
                            if (mDetChoice == 'A') mDet(mA);
                            else if (mDetChoice == 'B') mDet(mB);
                            break;

                        case '7': // Eigenvalue solver
                            while ((getchar()) != '\n') {} // clear input buffer
                            char mEigenChoice;
                            printf("Perform this on matrix A or B? ");
                            scanf(" %c", &mEigenChoice);
                            if (mDimChoice == 'A') {
                                mEigen(mA);
                            }
                            else if (mDimChoice == 'B') {
                                mEigen(mB);
                            }
                            break;

                        case 'R': case 'r': // Return to main menu
                            printf("Returning to main menu...\n");
                            runMat = 0;
                            while ((getchar()) != '\n') {} // clear input buffer
                            break;

                        default:
                            printf("Invalid matrix operation. Try again.\n"); // input validation
                            while ((getchar()) != '\n') {} // clear input buffer
                    }
                }
            break;

            // Quit Program
            case 'Q': case 'q':
                printf("Quitting Program...\n");
                running = 0;
                getchar();
                break;

            default:
                printf("Invalid option. Try again.\n"); // input validation
                while ((getchar()) != '\n') {} // clear input buffer
        }
    }
}