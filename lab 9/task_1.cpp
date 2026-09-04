#include <iostream>
#include <fstream>
using namespace std;

class Student
{
    friend class StudentList;

private:
    int id;        // ID of the student
    string name;   // Name of the student
    float cgpa;    // CGPA of the student
    Student *next; // Pointer to the next node in the list

public:
    Student(int id, string name, float cgpa, Student *next = nullptr) // Constructor
    {
        this->id = id;
        this->name = name;
        this->cgpa = cgpa;
        this->next = next;
    }

    void studentDetails() const // Displays the student information
    {
        cout << endl;
        cout << "id: " << this->id << endl;
        cout << "name: " << this->name << endl;
        cout << "cgpa: " << this->cgpa << endl;
        cout << endl;
    }
};

class StudentList
{
private:
    Student *head;   // Start of the list
    Student *cursor; // Current item in the list

public:
    StudentList() // Constructor
    {
        this->head = nullptr;
        this->cursor = nullptr;
    }

    ~StudentList() // Destructor
    {
        if (!this->isEmpty())
        {

            Student *current = this->head;
            Student *prev = nullptr;

            while (current->next != NULL)
            {
                prev = current;
                current = current->next;
                delete prev;
            }
            delete current;
        }
    }

    // Member functions
    void insert(const Student &newStd) // Inserts a new student
    {
        if (isEmpty())
        {
            this->head = new Student(newStd.id, newStd.name, newStd.cgpa, nullptr);
            this->cursor = this->head;
        }
        else
        {

            this->cursor->next = new Student(newStd.id, newStd.name, newStd.cgpa, this->cursor->next);
            this->cursor = this->cursor->next;
        }
    }

    void remove(int id) // Removes a student by ID
    {
        if (isEmpty())
        {
            cout << "Empty List" << endl;
        }
        else if (this->head->id == id)
        {
            Student *current = this->head;

            if (current == this->head && this->head->next == NULL)
            {
                this->head = nullptr;
                this->cursor = nullptr;
            }
            else
            {

                if (this->cursor == this->head)
                {
                    this->cursor = this->head;
                }

                this->head = this->head->next;
            }

            delete current;
        }
        else
        {

            Student *current = this->head->next;
            Student *prev = this->head;

            while (current->id != id)
            {
                prev = current;

                if (current->next == NULL)
                {
                    cout << "Student with given id does not exist" << endl;
                    return;
                }

                current = current->next;
            }

            if (this->cursor == current && this->cursor->next == NULL)
            {
                this->cursor = this->head;
            }
            else if (this->cursor == current)
            {
                this->cursor = this->cursor->next;
            }
            else if (current->next == NULL)
            {
                this->cursor = this->head;
            }

            prev->next = current->next;
            delete current;
        }
    }

    void search(float cgpa) const // Searches for students by CGPA
    {
        Student *current = head;
        bool found = false;

        while (current != NULL)
        {

            if (current->cgpa == cgpa)
            {
                found = true;
                current->studentDetails();
            }

            current = current->next;
        }

        if (!found)
        {
            cout << "No Such Student(s) Found" << endl;
        }
    }

    void replace(const Student &newStd) // Replaces or appends a student
    {
        if (this->isEmpty())
        {
            this->head = new Student(newStd.id, newStd.name, newStd.cgpa, nullptr);
            this->cursor = this->head;
        }
        else if (this->head->id == newStd.id)
        {
            this->head->name = newStd.name;
            this->head->cgpa = newStd.cgpa;
            this->cursor = this->head;
        }
        else
        {

            Student *current = this->head->next;

            while (current->next != NULL)
            {

                if (current->id == newStd.id)
                {
                    current->name = newStd.name;
                    current->cgpa = newStd.cgpa;
                    this->cursor = current;
                    return;
                }

                current = current->next;
            }

            if (current->id == newStd.id)
            {
                current->name = newStd.name;
                current->cgpa = newStd.cgpa;
                this->cursor = current;
                return;
            }

            current->next = new Student(newStd.id, newStd.name, newStd.cgpa, nullptr);
            this->cursor = current->next;
        }
    }

    bool isEmpty() const // Checks if the list is empty
    {
        if (this->head == NULL)
        {
            return true;
        }
        return false;
    }

    void gotoBeginning() // Moves cursor to the beginning
    {
        this->cursor = this->head;
    }

    void gotoEnd() // Moves cursor to the end
    {
        Student *current = this->head;

        while (current->next != NULL)
        {
            current = current->next;
        }
        this->cursor = current;
    }

    bool gotoNext() // Moves cursor to the next item
    {
        if (this->cursor->next == NULL)
        {
            return false;
        }
        this->cursor = this->cursor->next;
        return true;
    }

    bool gotoPrior() // Moves cursor to the previous item
    {
        if (this->cursor == this->head)
        {
            return false;
        }
        else
        {
            Student *current = this->head;

            while (current->next != this->cursor)
            {
                current = current->next;
            }
            this->cursor = current;
            return true;
        }
    }

    Student getCursor() const // Returns the student at cursor
    {
        if (this->cursor == NULL)
        {
            return Student(-1, "", -1, nullptr);
        }

        return *(this->cursor);
    }

    void showStructure() const // Displays the list structure
    {
        if (this->isEmpty())
        {
            cout << "Empty List" << endl;
        }
        else
        {

            Student *current = this->head;

            while (current != NULL)
            {
                current->studentDetails();
                current = current->next;
            }
        }
    }
};

int main()
{

    ifstream file("input.txt");

    StudentList sl;

    int id;
    string name;
    float cgpa;

    for (int i = 0; i < 10; i++)
    {
        file >> id;
        file.ignore();
        getline(file, name, '\n');
        file >> cgpa;

        Student s(id, name, cgpa);
        sl.insert(s);
    }

    sl.showStructure();

    Student s(id, "Adil", 4.00);

    sl.replace(s);
    sl.showStructure();

    sl.remove(10);
    sl.showStructure();
    sl.replace(s);
    sl.showStructure();

    // sl.getCursor().studentDetails();

    sl.gotoBeginning();
    sl.getCursor().studentDetails();

    sl.gotoNext();
    sl.getCursor().studentDetails();

    sl.gotoEnd();
    sl.getCursor().studentDetails();

    sl.gotoPrior();
    sl.getCursor().studentDetails();

    sl.search(3.22);

    sl.remove(1);
    sl.remove(2);
    sl.remove(3);
    sl.remove(4);
    sl.remove(5);
    sl.remove(6);
    sl.remove(7);
    sl.remove(8);
    sl.remove(9);
    sl.remove(10);

    sl.showStructure();

    return 0;
}