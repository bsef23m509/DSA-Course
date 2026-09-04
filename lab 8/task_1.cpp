#include "iostream"
#include "fstream"

using namespace std;

// Implement the eraseObject function to modify the 2D array
void eraseObject(int **arr, int r, int c, int i, int j)
{

   if (i + 1 < r && arr[i + 1][j]) {
      arr[i + 1][j] = 0;
      eraseObject(arr, r, c, i + 1, j);
   }
   if (i - 1 >= 0 && arr[i - 1][j]) {
      arr[i - 1][j] = 0;
      eraseObject(arr, r, c, i - 1, j);
   }

   if (j + 1 < c && arr[i][j + 1]) {
      arr[i][j + 1] = 0;
      eraseObject(arr, r, c, i, j + 1);
   }
   if (j - 1 >= 0 && arr[i][j - 1]) {
      arr[i][j - 1] = 0;
      eraseObject(arr, r, c, i, j - 1);
   }
}

int main(void)
{
   // Opening the input file
   ifstream inf("input_4.txt");

   // Checking if the file opened successfully
   if (!inf.is_open())
   {
      cout << "Failed to open the file" << endl;
      exit(0);
   }

   int ROWS, COLS, p_x, p_y;

   // Reading image dimensions and target pixel coordinates from the file
   inf >> ROWS >> COLS;
   inf >> p_x >> p_y;

   // Allocating memory for a 2D array
   int **ar = new int *[ROWS];
   for (int i = 0; i < ROWS; i++)
   {
      ar[i] = new int[COLS];
   }

   // Reading the image data into the array
   for (int i = 0; i < ROWS; i++)
   {
      for (int j = 0; j < COLS; j++)
      {
         inf >> ar[i][j];
      }
   }

   // Closing the input file
   inf.close();

   if (ar[p_x][p_y]) {
      // Calling the function to process the image
      eraseObject(ar, ROWS, COLS, p_x, p_y);
   }

   // Displaying the updated image data
   for (int i = 0; i < ROWS; i++)
   {
      for (int j = 0; j < COLS; j++)
      {
         cout << ar[i][j] << " ";
      }
      cout << endl;
   }

   // Deallocating the memory for the 2D array
   for (int i = 0; i < ROWS; i++)
   {
      delete[] ar[i];
   }
   delete[] ar;

   return 0;
}