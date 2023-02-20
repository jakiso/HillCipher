/*=============================================================================
| Assignment: HW 01 – Encrypting a plaintext file using the Hill cipher in the key file
|
| Author: Jade Soto
| Language: C
|
| To Compile: gcc hw1.c
|
| To Execute: ./a.out hillcipherkey.txt plaintextfile.txt
| where the files in the command line are in the current directory.
| The key text contains a single digit on the first line defining the size of the key
| while the remaining lines define the key, for example:
| 3
| 1 2 3
| 4 5 6
| 7 8 9
| The plain text file contains the plain text in mixed case with spaces & punctuation.
|
| Class: CIS3360 - Security in Computing - Fall 2020
| Instructor: McAlpin
| Due Date: per assignment
|
+=============================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Multiply key by plain text vector
int dotproduct(int matrixlength, int rowmatrix,int i, int matrix[rowmatrix][matrixlength], int avalue[1][matrixlength])
{
  int j = 0;
  int k = 0;
  int result = 0;
  for(j = 0; j < matrixlength; j++)
  {
      result += matrix[rowmatrix][j]*avalue[i][j];
  }
  // Mod it by the amount of letters in the alphabet
  return result%26;
}
int main (int argc, char **argv)
{
  int i = 0;
  int j = 0;
  char parse[1];
  int atoitype;
  char letter;
  int row = 0;
  int ciphert;
  int index = 0;
  int counter = 0;
  // Read command line arguments and open the files
  FILE *keyfile = fopen(argv[1], "r");
  FILE *ptfile = fopen(argv[2],"r");
  char readlength[1];
  // Read first line of keyfile to get matrix length
  fscanf(keyfile,"%s", readlength);
  int matrixlength = atoi(readlength);
  int vector [matrixlength][1];
  int matrix[matrixlength][matrixlength];
  int avalue[10000][matrixlength];
  printf("\n\nKey matrix:\n\n");
  for(i = 0; i < matrixlength; i++)
  {
    for(j = 0; j < matrixlength; j++)
    {
      fscanf(keyfile,"%s", parse);
      // Set parse to integer and put it in integer array
      matrix[i][j] = atoi(parse);
      printf("%d ", matrix[i][j]);
      if(j + 1 == matrixlength)
      {
        // Prints a new line for new row
        printf("\n");
      }
    }
  }
  printf("\n\n");
  printf("Plaintext:\n\n");
  while(fscanf(ptfile, " %c", parse) != EOF)
  {
    // Makes sure that the parse is from [a-z] or [A-Z]
    if(parse[0] >= 'a' && parse[0] <= 'z' || parse[0] >= 'A' && parse[0] <= 'Z')
    {
      printf("%c", tolower(parse[0]));
      // Counts how many letters are printed
      counter++;
      // Sets char to a value [0-26] to represent alphabet
      atoitype = (tolower(parse[0]) - 97);
      avalue[row][index] = atoitype;
      index++;
      // Sets new row
      if(index == matrixlength)
      {
        index = 0;
        row++;
      }
      // Prints max 80 characters per row
      if(counter == 80)
      {
        printf("\n");
        counter -= 80;
      }
    }
    else
    {
      continue;
    }
  }
  // Prevents extra row if index can be perfectly divided by matrixlength
  if(index % matrixlength == 0)
  {
    row--;
  }
  // Adds x to the end of avalue if index is not perfectly divided by matrixlegth
  while(index % matrixlength != 0)
  {
    printf("x");
    avalue[row][index] = 23;
    index++;
  }
  printf("\n\n\n");
  printf("Ciphertext:\n\n");
  index = 0;
  i = 0;
  counter = 0;
  while(i != row + 1)
  {
    ciphert = 0;
    for (j = 0; j < matrixlength; j++)
    {
      ciphert = dotproduct(matrixlength,j,i, matrix,avalue);
      // Sets value to proper ASCII number
      letter = (ciphert + 97);
      printf("%c", letter);
      counter++;
      // Prints max 80 characters per row
      if(counter == 80)
      {
        printf("\n");
        counter-=80;
      }
    }
    i++;
  }
  printf("\n");
// END
}

/*=============================================================================
| I Jade Soto (ja348052)) affirm that this program entirely my own work and that I have neither developed my code together with
| any another person, nor copied any code from any other person, nor permitted
| my code to be copied or otherwise used by any other person, nor have I
| copied, modified, or otherwise used programs created by others. I acknowledge
| that any violation of the above terms will be treated as academic dishonesty.
+=============================================================================*/
