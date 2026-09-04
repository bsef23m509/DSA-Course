#include <iostream>
using namespace std;

bool checkSum(int A[], int start, int end, int k) {

    if(start >= end) {
        return false;
    }

    for (int i = start + 1; i < end; i++)
    {
        if ((A[start] + A[i]) == k)
            return true;
        checkSum(A, start + 1, end, k);
    }
    
    return false;
}

int main()
{

    int A[5] = {8, 5, 3, 7, 2};

    cout << checkSum(A, 0, 4, 11) << endl;
    cout << checkSum(A, 0, 4, 16) << endl;
    cout << checkSum(A, 0, 4, -1) << endl;

   return 0;
}