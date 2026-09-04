#include <iostream>
using namespace std;

int rArrSum(int A[], int n) {

    if(n <= 0) {
        return A[0];
    }

    return A[n] + rArrSum(A, n - 1);

}

int arrSum(int A[], int n) {

    if(n <= 0) {
        cout << "Invalid size" << endl;
        return -1;
    }

    return rArrSum(A, n - 1);

}

int main()
{

    int A[4] = {1,2,3,4};   

    cout << arrSum(A, 4) << endl;
    cout << arrSum(A, 3) << endl;

   return 0;
}