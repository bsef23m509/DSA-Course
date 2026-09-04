#include <iostream>
using namespace std;

class Student
{
    friend class StudentMaxHeap;

private:
    int rollNo;
    double cgpa;

public:
    Student(int rollNo, double cgpa)
    {
        this->rollNo = rollNo;
        this->cgpa = cgpa;
    }

    Student()
    {
        this->rollNo = -1;
        this->cgpa = -1;
    }

    void printDetails()
    {
        cout << "Roll No: " << rollNo << " , CGPA: " << cgpa << endl;
    }
};

class StudentMaxHeap
{
private:
    Student *arr;
    int curSize;
    int maxSize;

    void maxHeapify(Student *arr, int curSize, int cur)
    {

        int left = 2 * cur + 1;
        int right = 2 * cur + 2;
        int largest = cur;

        if (left < curSize && ((arr[left].cgpa > arr[largest].cgpa)))
        {
            swap(left, largest);
        }
        if (right < curSize && ((arr[right].cgpa > arr[largest].cgpa)))
        {
            swap(right, largest);
        }

        if (left < curSize && arr[left].cgpa == arr[largest].cgpa && arr[left].rollNo < arr[largest].rollNo)
            swap(left, largest);
        if (right < curSize && arr[right].cgpa == arr[largest].cgpa && arr[right].rollNo < arr[largest].rollNo)
            swap(right, largest);

        if (cur != largest)
        {
            swap(arr[cur], arr[largest]);
            this->maxHeapify(arr, curSize, largest);
        }
    }

    void heapSort(Student *arr, int curSize)
    {

        // cout << curSize << endl;
        for (int i = curSize - 1; i >= 0; i--)
        {
            swap(arr[0], arr[--curSize]);
            this->maxHeapify(arr, curSize, 0);
        }
    }

public:
    StudentMaxHeap(int size)
    {
        this->maxSize = size;
        this->curSize = 0;
        this->arr = new Student[size];
    }

    ~StudentMaxHeap()
    {
        delete[] arr;
    }

    bool isEmpty()
    {
        return curSize == 0;
    }
    bool isFull()
    {
        return curSize == maxSize;
    }

    void insert(int rollNo, double cgpa)
    {

        if (this->isFull())
        {
            cout << "List Full" << endl;
            return;
        }

        int newPos = this->curSize;

        arr[newPos].rollNo = rollNo;
        arr[newPos].cgpa = cgpa;

        this->curSize++;

        int newPosParent = (newPos - 1) / 2;

        while (
            newPos != 0 && ((arr[newPos].cgpa > arr[newPosParent].cgpa) || (arr[newPos].cgpa == arr[newPosParent].cgpa && arr[newPos].rollNo < arr[newPosParent].rollNo)))
        {
            swap(arr[newPos], arr[newPosParent]);

            newPos = newPosParent;
            newPosParent = (newPos - 1) / 2;
        }
    }

    bool remove(int &rollNo, double &cgpa)
    {

        if (this->isEmpty())
        {
            return false;
        }

        rollNo = arr[0].rollNo;
        cgpa = arr[0].cgpa;

        arr[0] = arr[curSize - 1];

        this->curSize--;

        // maxHeapifying
        this->maxHeapify(this->arr, this->curSize, 0);

        return true;
    }

    void displayStudentList()
    {

        if (this->isEmpty())
        {
            cout << "Empty list" << endl;
            return;
        }

        Student *sortedArr = new Student[this->curSize];

        // copy data
        for (int i = 0; i < curSize; i++)
        {
            sortedArr[i] = arr[i];
        }

        // sorting
        this->heapSort(sortedArr, this->curSize);

        cout << endl;
        for (int i = this->curSize - 1; i >= 0; i--)
        {
            sortedArr[i].printDetails();
        }

        delete[] sortedArr;
    }

    void levelOrder()
    {

        if (this->isEmpty())
        {
            cout << "Empty List" << endl;
            return;
        }

        cout << endl;
        for (int i = 0; i < curSize; i++)
        {
            arr[i].printDetails();
        }
    }
};

int main()
{

    StudentMaxHeap s(5);

    s.insert(1, 3.89);
    s.insert(2, 3.56);
    s.insert(3, 3.47);
    s.insert(4, 3.97);
    s.insert(5, 3.47);

    s.levelOrder();
    s.displayStudentList();

    int rollNo;
    double cgpa;

    s.remove(rollNo, cgpa);

    Student removedStudent = Student(rollNo, cgpa);

    cout << "Removed Student" << endl;
    removedStudent.printDetails();

    s.displayStudentList();
    s.levelOrder();

    return 0;
}