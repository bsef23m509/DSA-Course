#include <iostream>
#include <fstream>
using namespace std;

class Book
{
    friend class BookList;

private:
    int id;       /** ID of a book. */
    string title; /** Name of a book. */
    float price;  /** Price of a book. */
    Book *next;   /** Address of the next node. */
    Book *pre;    /** Address of the previous node. */

public:
    /** Constructor */
    Book(int id, string title, float price, Book *next = nullptr, Book *pre = nullptr)
    {
        this->id = id;
        this->title = title;
        this->price = price;
        this->next = next;
        this->pre = pre;
    }

    void bookDetails()
    {
        cout << endl;
        cout << "id: " << this->id << endl;
        cout << "title: " << this->title << endl;
        cout << "price: " << this->price << endl;
        cout << endl;
    }
};

class BookList
{
private:
    Book *head;
    Book *cursor;
    Book *last;

public:
    BookList()
    {
        this->head = nullptr;
        this->last = nullptr;
        this->cursor = nullptr;
    }
    ~BookList()
    {
        if (!this->isEmpty())
        {

            Book *current = this->head;
            Book *prev = nullptr;

            while (current->next != NULL)
            {
                prev = current;
                current = current->next;
                delete prev;
            }
            delete current;
        }
    }

    void insert(const Book &newItem)
    {
        if (isEmpty())
        {
            this->head = new Book(newItem.id, newItem.title, newItem.price);
            this->last = this->head;
            this->cursor = this->head;
        }
        else
        {
            Book *temp = new Book(newItem.id, newItem.title, newItem.price, this->cursor->next, this->cursor);
            this->cursor->next = temp;

            if (this->last == this->cursor)
            {
                this->last = this->cursor->next;
            }
            this->cursor = this->cursor->next;
        }
    }

    void remove()
    {
        if (isEmpty())
        {
            cout << "Empty List" << endl;
        }
        else if (this->cursor == this->head && this->head->next == nullptr)
        {
            Book *temp = this->head;
            this->head = nullptr;
            this->last = nullptr;
            this->cursor = nullptr;
            delete temp;
        }
        else if (this->cursor == this->last)
        {
            this->last->pre->next = nullptr;
            this->cursor = this->head;
            Book *temp = this->last;
            this->last = this->last->pre;
            delete temp;
        }
        else if (this->cursor == this->head)
        {
            Book *temp = this->head;
            this->head = this->head->next;
            this->head->pre = nullptr;
            this->cursor = this->head;

            delete temp;
        }
        else
        {
            Book *temp = this->cursor;
            this->cursor = this->cursor->next;
            this->cursor->pre = temp->pre;
            temp->pre->next = this->cursor;

            delete temp;
        }
    }

    void search(string title)
    {
        Book *current = this->head;
        bool found = false;

        while (current != NULL)
        {
            if (current->title == title)
            {
                found = true;
                current->bookDetails();
            }

            current = current->next;
        }

        if (!found)
        {
            cout << "No Such Student(s) Found" << endl;
        }
    }

    void replace(const Book &newItem)
    {
        if (this->isEmpty())
        {
            this->head = new Book(newItem.id, newItem.title, newItem.price);
            this->last = this->head;
            this->cursor = this->head;
        }
        else if (this->head->id == newItem.id)
        {
            this->head->title = newItem.title;
            this->head->price = newItem.price;
            this->cursor = this->head;
        }
        else
        {
            Book *current = this->head->next;

            while (current->next != NULL)
            {

                if (current->id == newItem.id)
                {
                    current->title = newItem.title;
                    current->price = newItem.price;
                    this->cursor = current;
                    return;
                }

                current = current->next;
            }

            if (current->id == newItem.id)
            {
                current->title = newItem.title;
                current->price = newItem.price;
                this->cursor = current;
                return;
            }

            current->next = new Book(newItem.id, newItem.title, newItem.price, nullptr, current);
            this->cursor = current->next;
            this->last = this->cursor;
        }
    }

    bool isEmpty() const
    {
        return this->head == nullptr;
    }

    void gotoBeginning()
    {
        this->cursor = this->head;
    }

    void gotoEnd()
    {
        this->cursor = this->last;
    }

    bool gotoNext()
    {
        if (this->cursor->next == nullptr)
            return false;

        this->cursor = this->cursor->next;
        return true;
    }

    bool gotoPrior()
    {
        if (this->cursor->pre == nullptr)
            return false;

        this->cursor = this->cursor->pre;
        return true;
    }

    Book getCursor() const
    {
        if (this->cursor == nullptr)
        {
            Book temp = Book(-1, "", 0.00);
            return temp;
        }

        return *(this->cursor);
    }

    void showStructureForward() const
    {
        if (this->isEmpty())
        {
            cout << "Empty List" << endl;
        }
        else
        {
            Book *current = this->head;

            while (current != NULL)
            {
                current->bookDetails();
                current = current->next;
            }
        }
    }

    void showStructureReverse() const
    {
        if (this->isEmpty())
        {
            cout << "Empty List" << endl;
        }
        else
        {
            Book *current = this->last;

            while (current != NULL)
            {
                current->bookDetails();
                current = current->pre;
            }
        }
    }
};

int main()
{

    ifstream file("input.txt");

    BookList b1;

    int id;       /** ID of a book. */
    string title; /** Name of a book. */
    float price;  /** Price of a book. */

    for (int i = 0; i < 10; i++)
    {
        file >> id;
        file.ignore();
        getline(file, title, '\n');
        file >> price;

        Book b(id, title, price);
        b1.insert(b);
    }

    // b1.getCursor().bookDetails();
    // b1.gotoBeginning();
    // b1.getCursor().bookDetails();
    // b1.gotoEnd();
    // b1.getCursor().bookDetails();

    b1.showStructureReverse();
    b1.gotoBeginning();


    Book b(11, "Adil", 14.00);
    b1.insert(b);

    b1.showStructureForward();

    // b1.replace(b);
    // b1.showStructureForward();

    // b1.remove();
    // b1.showStructureForward();
    // b1.replace(b);
    // b1.showStructureForward();

    // // b1.getCursor().bookDetails();

    // b1.gotoBeginning();
    // b1.getCursor().bookDetails();

    // b1.gotoNext();
    // b1.getCursor().bookDetails();

    // b1.gotoEnd();
    // b1.getCursor().bookDetails();

    // b1.gotoPrior();
    // b1.getCursor().bookDetails();

    // b1.search("Adil");

    // b1.remove();
    // b1.remove();
    // b1.remove();
    // b1.remove();
    // b1.remove();
    // b1.remove();
    // b1.remove();
    // b1.remove();
    // b1.remove();
    // b1.remove();

    // b1.showStructureReverse();

    return 0;
}