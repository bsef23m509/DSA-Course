#include <iostream>
using namespace std;

void rReverseSubArr(int A[], int start, int end) {

    if(start >= end) {
        return;
    }

    swap(A[start], A[end]);
    rReverseSubArr(A, start + 1, end - 1);
}

void reverseSubArr(int A[], int start, int end) {

    if(start == -1) {
        cout << "Invalid Start" << endl;
        return;
    }

    rReverseSubArr(A, start, end);

}

int main()
{

    int A[6] = {1,2,3,4, 5, 6};

    for (int i = 0; i < 6; i++)
    {
        cout << A[i] << " ";
    }
    cout << endl;

    reverseSubArr(A, 1, 4);

    for (int i = 0; i < 6; i++)
    {
        cout << A[i] << " ";
    }
    cout << endl;
    

   return 0;
}