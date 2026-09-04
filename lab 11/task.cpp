#include <iostream>
#include <fstream>
using namespace std;

class Student
{
    friend class StudentBST;

private:
    int id;
    string name;
    float fee;
    Student *left;
    Student *right;

public:
    /** Constructor */
    Student(int id, string name, float fee, Student *left = nullptr, Student *right = nullptr)
    {
        this->id = id;
        this->name = name;
        this->fee = fee;
        this->left = left;
        this->right = right;
    }

    void studentDetails()
    {
        cout << endl;
        cout << "id: " << this->id << endl;
        cout << "name: " << this->name << endl;
        cout << "fee: " << this->fee << endl;
        cout << endl;
    }
};

class StudentBST
{
private:
    Student *root;

    void inOrderTrav(Student *stree)
    {
        if (stree == nullptr)
            return;
        inOrderTrav(stree->left);
        stree->studentDetails();
        inOrderTrav(stree->right);
    }

    void preOrderTrav(Student *stree)
    {
        if (stree == nullptr)
            return;
        stree->studentDetails();
        preOrderTrav(stree->left);
        preOrderTrav(stree->right);
    }

    void postOrderTrav(Student *stree)
    {
        if (stree == nullptr)
            return;
        postOrderTrav(stree->left);
        postOrderTrav(stree->right);
        stree->studentDetails();
    }

    void destroy(Student *stree)
    {
        if (stree == nullptr)
            return;
        destroy(stree->left);
        destroy(stree->right);

        delete stree;
        stree = nullptr;
    }

    Student *findMinIdNode(Student *stree)
    {

        if (stree->left == nullptr)
            return stree;
        return findMinIdNode(stree->left);
    }

    Student *destroyNode(Student *node, int id)
    {
        cout << "call start" << endl;
        if (node->id > id)
        {
            node->left = destroyNode(node->left, id);
        }
        else if (node->id < id)
        {
            node->right = destroyNode(node->right, id);
        }
        else
        {
            if (node->left == nullptr && node->right == nullptr) // both node null
            {
                delete node;
                return nullptr;
            }
            else if (node->left != nullptr && node->right == nullptr) // right node null
            {
                Student *temp = node->left;
                delete node;
                return temp;
            }
            else if (node->left == nullptr && node->right != nullptr) // left node null
            {
                cout << "found" << endl;
                Student *temp = node->right;
                delete node;
                return temp;
            }
            else if (node->left != nullptr && node->right != nullptr) // both nodes exist
            {

                Student *minRightSuccessor = this->findMinIdNode(node->right);
                node->id = minRightSuccessor->id;
                node->name = minRightSuccessor->name;
                node->fee = minRightSuccessor->fee;

                destroyNode(node->right, minRightSuccessor->id);
                return node;
            }
        }
        cout << "call end" << endl;
        cout << endl;

        return node;
    }

public:
    StudentBST()
    {
        this->root = nullptr;
    }

    ~StudentBST()
    {
        destroy(this->root);
    }

    void insert(int id, string name, float fee)
    {

        if (this->root == nullptr)
        {
            Student *newNode = new Student(id, name, fee);
            this->root = newNode;
            return;
        }

        Student *parent = nullptr;
        Student *node = this->root;

        while (node != nullptr && node->id != id)
        {
            if (node->id > id)
            {
                parent = node;
                node = node->left;
            }
            else if (node->id < id)
            {
                parent = node;
                node = node->right;
            }
        }

        if (node != nullptr)
        {
            cout << "Student with this id already exists" << endl;
            return;
        }
        else
        {
            Student *newNode = new Student(id, name, fee);
            if (newNode->id < parent->id)
            {
                parent->left = newNode;
            }
            else
            {
                parent->right = newNode;
            }
        }
    }

    void search(int id)
    {

        if (this->root == nullptr)
        {
            cout << "Empty tree" << endl;
        }

        Student *node = this->root;

        while (node != nullptr && node->id != id)
        {
            if (node->id > id)
            {
                node = node->left;
            }
            else if (node->id < id)
            {
                node = node->right;
            }
        }

        if (node == nullptr)
        {
            cout << "Student with this id doesn't exist" << endl;
        }
        else
        {
            node->studentDetails();
        }
    }

    void inOrder()
    {
        if (this->root == nullptr)
        {
            cout << "Empty tree" << endl;
            return;
        }
        inOrderTrav(this->root);
    }

    void preOrder()
    {
        if (this->root == nullptr)
        {
            cout << "Empty tree" << endl;
            return;
        }

        preOrderTrav(this->root);
    }

    void postOrder()
    {
        if (this->root == nullptr)
        {
            cout << "Empty tree" << endl;
            return;
        }

        postOrderTrav(this->root);
    }

    void deleteNode(int id)
    {
        if (this->root == nullptr)
        {
            cout << "Empty tree" << endl;
            return;
        }

        Student *parent = nullptr;
        Student *node = this->root;

        while (node != nullptr && node->id != id)
        {
            if (node->id > id)
            {
                parent = node;
                node = node->left;
            }
            else if (node->id < id)
            {
                parent = node;
                node = node->right;
            }
        }

        if (node == nullptr)
        {
            cout << "Student with this id doesn't exists" << endl;
            return;
        }
        else
        {
            if (node->left == nullptr && node->right == nullptr)
            {
                delete node;
                if (parent->id > id)
                {
                    parent->left = nullptr;
                }
                else
                {
                    parent->right = nullptr;
                }
            }
        }
    }
};

int main()
{

    ifstream file("input.txt");

    StudentBST s1;

    int id;      /** ID of a book. */
    string name; /** Name of a book. */
    float fee;   /** fee of a book. */

    for (int i = 0; i < 5; i++)
    {
        file >> id;
        file >> name;
        file >> fee;

        s1.insert(id, name, fee);
    }

    // s1.preOrder();
    // s1.inOrder();
    // s1.postOrder();

    s1.insert(0, "adil", 29.2);
    // s1.preOrder();
    // s1.inOrder();
    s1.postOrder();

    // s1.search(50);
    // s1.search(2);

    // s1.deleteNode(1); // degree 0 node
    // s1.deleteNode(5); // degree 1 node
    // s1.deleteNode(6); // degree 2 node

    // s1.inOrder();

    return 0;
}