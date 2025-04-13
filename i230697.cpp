/*
        Ali Akbar 23i-0697
        Rehan Ali 23i-0730
        Ahmad Kamran 23i-0622
*/


#include<iostream>
#include<fstream>
#include<direct.h>
#include<ctime>
#include<cstdio>
//#include"Repository.h"
//#include"AVLtree.h"
using namespace std;


template<typename T>
T maximumh(T a, T b)
{
    if (a > b)
        return a;
    return b;
}
int leng(const char* arr)
{
    int length = 0;
    for (int i = 0; arr[i] != '\0'; i++)
    {
        length++;
    }
    return length;
}
void copy(const char* arr1, char* arr2)
{
    int i = 0;
    for (i = 0; arr1[i] != '\0'; i++)
    {
        arr2[i] = arr1[i];
    }
    arr2[i] = '\0';
}
bool campare(const char* arr1, const char* arr2)
{
    int i = 0;
    for (i = 0; arr1[i] != 0 && arr2[i] != '\0'; i++)
    {
        if (arr1[i] != arr2[i])
            return false;
    }
    return true;
}
void concatenate(char* arr1, const char* arr2)
{
    int i = leng(arr1);
    for (int j = 0; arr2[j] != '\0'; j++)
    {
        arr1[i++] = arr2[j];
    }
    arr1[i] = '\0';
}
int asciical(const char* arr)
{
    int sum = 0;
    for (int i = 0; arr[i] != '\0'; i++)
    {
        sum += arr[i];
    }
    return sum;
}
void highertolower(char* arr)
{
    for (int i = 0; arr[i] != '\0'; i++)
    {
        if (arr[i] >= 'A' && arr[i] < 'Z')
        {
            arr[i] += 32;
        }
    }
}
bool checkint(const char* arr)
{
    cout << arr << endl;
    for (int i = 0; arr[i] != '\0'; i++)
    {
        if (arr[i] < '0' || arr[i] > '9')
        {
            return false;
        }
    }
    return true;
}
void checkslash(const char* arr, char* arr2)
{
    bool flag = false;
    int j = 0;
    for (int i = 0; arr[i] != '\0'; i++) {
        if (flag)
        {
            arr2[j++] = arr[i];
        }
        if (arr[i] == '-')
        {
            flag = true;
        }
    }

    arr2[j] = '\0';

    return;
}

int converttoint(char* arr)
{
    int result = 0;
    for (int i = 0; arr[i] != '\0'; i++)
    {
        result = result * 10 + (arr[i] - '0');
    }
    return result;
}

////////////////////////
//                    //
//     AVL NODE       //
//                    //
////////////////////////

struct Node
{
    int data;
    char filename[100];
    Node* left;
    Node* right;
    int height;
    Node(int key, char fl[])
    {
        data = key;
        height = 1;
        left = nullptr;
        right = nullptr;
        copy(fl, filename);
    }
};

int height(Node* N)
{
    return N ? N->height : 0;
}
Node* loadtreetoroot(ifstream& file)
{
    int data1;
    if (file.is_open())
    {
        file >> data1;
        if (data1 == -1)
        {
            return nullptr;
        }
        file.ignore();
        char filename1[100];
        file.getline(filename1, 100);
        Node* temp1 = new Node(data1, filename1);
        temp1->left = loadtreetoroot(file);
        temp1->right = loadtreetoroot(file);
        return temp1;
    }
    else
        cout << "Error in opening file.";
}
int capac = 35;
int cntint(char arr)
{
    if (arr < '0' || arr > '9')
    {
        return -1;
    }
    else {
        return arr - '0';
    }
}


////////////////////////
//                    //
//      HASHING       //
//                    //
////////////////////////
struct HashNode
{
    char filepath[30];
    HashNode* Next;
    char filename[30];
    HashNode(const char* filename1, char* filepath1)
    {
        copy(filename1, filename);
        copy(filepath1, filepath);
        Next = nullptr;
    }
};
class Hashing
{
    HashNode** array;
    int capacity;
public:
    Hashing(int capad)
    {
        capacity = capad;
        array = new HashNode * [capacity];
        for (int i = 0; i < capacity; i++)
        {
            array[i] = nullptr;
        }
    }
    int hash(int val)
    {
        return val % 29;
    }
    void insert(const char* ar, char* tp)
    {
        int res = 1;
        bool flagt = false;
        flagt = checkint(ar);
        if (flagt == true)
        {
            res = 1;
            for (int i = 0; ar[i] != '\0'; i++) {
                res = res * cntint(ar[i]);
            }
        }
        char tempy[50];
        char t[100];
        for (int i = 0; i < 50; i++)
        {
            tempy[i] = '\0';
        }
        checkslash(ar, tempy);
        if (tempy[0] != '\0') {
            res = 1;
            for (int i = 0; tempy[i] != '\0'; i++) {
                res = res * cntint(tempy[i]);
            }
        }
        if (flagt == false)
        {
            res = 1;
            for (int i = 0; ar[i] != '\0'; i++)
            {
                res = res * (int)ar[i];
                //cout << ar[i] << endl;
            }
        }
        res = hash(res);
        HashNode* ptr = new HashNode(ar, tp);
        if (array[res] == nullptr)
        {
            array[res] = ptr;
        }
        else
        {
            ptr->Next = array[res];
            array[res] = ptr;
        }
    }
    void remove(char* key)
    {

        int res = 1;
        bool flag = checkint(key);
        if (flag == true)
        {
            for (int i = 0; key[i] != '\0'; i++) {
                res = res * cntint(key[i]);
            }
            cout << res << endl;
        }
        else
        {
            for (int i = 0; key[i] != '\0'; i++)
            {
                res = res * static_cast<int>(key[i]);
            }
            cout << res << endl;
        }
        res = hash(res);
        HashNode* ptr = array[res];
        HashNode* prev = nullptr;
        while (ptr != nullptr)
        {
            if (campare(ptr->filename, key))
            {
                if (prev == nullptr)
                {
                    array[res] = ptr->Next;
                }
                else
                {
                    prev->Next = ptr->Next;
                }
                delete ptr;
                cout << "Key" << key << " removed." << endl;
                return;
            }
            prev = ptr;
            ptr = ptr->Next;
        }
    }
    void displayhashing()
    {
        for (int i = 0; i < capacity; i++)
        {
            HashNode* ptr = array[i];
            if (ptr != nullptr)
            {
                cout << "Index " << i << ":";
                while (ptr != nullptr)
                {
                    cout << "File: " << ptr->filename << " ,Path: " << ptr->filepath << "< " << endl;
                    ptr = ptr->Next;
                }
                cout << "Null" << endl;
            }
        }
    }
};


////////////////////////
//                    //
//     AVL CLASS      //
//                    //
////////////////////////

class AVL
{
private:
    Hashing hst{ 36 };
    Node* root;
    char foldername[100];
    bool flag = true;
public:
    char comitfilepath[100];
    AVL(char* arr)
    {
        root = nullptr;
        copy(arr, foldername);
        createfolder();
    }

    int getbalance(Node* arr)
    {
        return arr ? (height(arr->left) - height(arr->right)) : 0;
    }
    Node* rotateleft(Node* arr)
    {
        Node* temp = arr->right;
        Node* temp1 = temp->left;
        temp->left = arr;
        arr->right = temp1;
        arr->height = maximumh(height(arr->left), height(arr->right)) + 1;
        temp->height = maximumh(height(temp->left), height(temp->right)) + 1;
        return temp;
    }
    Node* rotateright(Node* arr)
    {
        Node* temp = arr->left;
        Node* temp1 = temp->right;
        temp->right = arr;
        arr->left = temp1;
        arr->height = maximumh(height(arr->left), height(arr->right)) + 1;
        temp->height = maximumh(height(temp->left), height(temp->right)) + 1;
        return temp;
    }
    Node* insert(Node* arr, int value, char fl[])
    {
        if (arr == nullptr)
        {
            // cout << fl << endl;
            arr = new Node(value, fl);
            return arr;
        }
        if (value < arr->data)
        {
            arr->left = insert(arr->left, value, fl);
        }
        else if (value > arr->data)
        {
            arr->right = insert(arr->right, value, fl);
        }
        else
            return arr;
        arr->height = maximumh(height(arr->left), height(arr->right)) + 1;
        int balance = getbalance(arr);
        if (balance > 1 && value < arr->left->data)
        {
            return rotateright(arr);
        }
        if (balance<-1 && value>arr->right->data)
        {
            return rotateleft(arr);
        }
        if (balance > 1 && value > arr->left->data)
        {
            arr->left = rotateleft(arr->left);
            return rotateright(arr);
        }
        if (balance < -1 && value < arr->right->data)
        {
            arr->right = rotateright(arr->right);
            return rotateleft(arr);
        }
        return arr;
    }
    Node* maxvalue(Node* arr)
    {
        while (arr->right != nullptr)
        {
            arr = arr->right;
        }
        return arr;
    }
    Node* minvalue(Node* arr)
    {
        while (arr->left != nullptr)
        {
            arr = arr->left;
        }
        return arr;
    }
    Node* deleteNode(Node* arr, int key, char* fildel)
    {
        if (arr == nullptr)
        {
            return arr;
        }
        if (key < arr->data)
        {
            arr->left = deleteNode(arr->left, key, fildel);
        }
        else if (key > arr->data)
        {
            arr->right = deleteNode(arr->right, key, fildel);
        }
        else {
            if (remove(arr->filename) == 0)
            {
                cout << "File deleted" << endl;
            }
            if ((arr->left == nullptr) || (arr->right == nullptr))
            {
                Node* temp = arr->left ? arr->left : arr->right;
                if (temp == nullptr)
                {
                    temp = arr;
                    arr = nullptr;
                }
                else {
                    *arr = *temp;
                }
            }
            else {
                Node* temp = minvalue(arr->right);
                arr->data = temp->data;
                copy(temp->filename, arr->filename);
                arr->right = deleteNode(arr->right, temp->data, fildel);
            }

        }
        if (arr == nullptr)
        {
            return arr;
        }
        arr->height = maximumh(height(arr->left), height(arr->right)) + 1;
        int balance = getbalance(arr);
        if (balance > 1 && getbalance(arr->left) >= 0)
        {
            return rotateright(arr);
        }
        if (balance > 1 && getbalance(arr->left) < 0)
        {
            arr->left = rotateleft(arr->left);
            return rotateright(arr);
        }
        if (balance < -1 && getbalance(arr->right) <= 0)
        {
            return rotateleft(arr);
        }
        if (balance < -1 && getbalance(arr->right)>0)
        {
            arr->right = rotateright(arr->right);
            return rotateleft(arr);
        }
        return arr;

    }
    void deleteNode(int key, char* arr)
    {
        root = deleteNode(root, key, arr);
    }
    bool searching(Node* arr, int val)
    {
        if (root == nullptr)
        {
            return false;
        }
        if (root->data == val)
        {
            return true;
        }
        else if (root->data > val)
        {
            return searching(root->left, val);
        }
        else
            return searching(root->right, val);


    }
    void insert(int key, char fil[])
    {
        root = insert(root, key, fil);
    }
    void preorder(Node* arr)
    {
        if (arr == nullptr)
        {
            return;
        }
        if (arr != nullptr)
        {
            cout << arr->filename << endl;
            ifstream file(arr->filename);
            if (file.is_open())
            {
                cout << "File content: \n";
                char line[2000];
                while (file.getline(line, 2000))
                {
                    cout << line << endl;
                }
                cout << endl;
                file.close();
            }
            else
            {
                cout << "Error in openning file." << endl;
            }
            preorder(arr->left);
            preorder(arr->right);
        }
    }
    void inorder(Node* arr)
    {
        if (arr != nullptr)
        {
            inorder(arr->left);
            cout << arr->data << " ";
            inorder(arr->right);
        }
    }
    Node* getroot()
    {
        return root;
    }


    ////////////////////////
    //                    //
    //    Create folder   //
    //                    //
    ////////////////////////
    void createfolder()
    {
        //cout << foldername << endl;
        if (_mkdir(foldername) == 0)
        {
            cout << "Folder created." << endl;
            char fileop[100];
            copy(foldername, fileop);
            concatenate(fileop, "/commit.txt");
            copy(fileop, comitfilepath);
            ofstream fileq(fileop);
            fileq.close();
            return;
        }
        else
        {
            cout << "This folder already exist." << endl;
        }

    }
    char* getcomitfilepath()
    {
        return comitfilepath;
    }
    ////////////////////////
    //                    //
    // INITIALIZING DATA  //
    //                    //
    ////////////////////////
    void init(const char* csvfilename)
    {
        ifstream file(csvfilename);
        if (!file.is_open())
        {
            cout << "Error in opening csv file" << endl;
            return;
        }
        char line[1000];
        file.getline(line, 1000);
        cout << "Columns :" << endl;
        int start = 0;
        int count = 0;
        for (int i = 0; line[i] != '\0'; i++)
        {
            if (line[i] == ',')
            {
                line[i] = '\0';
                cout << "Columns :" << count << ": " << (line + start) << endl;
                count++;
                start = i + 1;
            }
        }
        cout << "Columns :" << count << ": " << (line + start) << endl;
        int select;
        cout << "Select the column from 0 to " << count << ".";
        cin >> select;
        filecreating(file, select);
        file.close();
    }
    void filecreating(ifstream& file, int select)
    {
        char line[1000];
        while (file.getline(line, 1000))
        {
            int start = 0; int index = 0;
            char key[100];
            char data[1000];
            copy(line, data);
            for (int i = 0; line[i] != '\0'; i++)
            {
                if (line[i] == ',')
                {
                    if (index == select)
                    {
                        line[i] = '\0';
                        copy(line + start, key);
                        break;
                    }
                    index++;
                    start = i + 1;
                }
            }
            fileinsertion(key, data);
        }
    }
    void fileinsertion(const char* key, const char* data)
    {
        char path[200];
        copy(foldername, path);
        concatenate(path, "/");
        concatenate(path, key);
        concatenate(path, ".txt");

        ofstream outputfile(path, ios::app);
        if (!outputfile.is_open())
        {
            cout << "Error in creating file: " << key << endl;
            return;
        }

        char* temp;
        int length = leng(key);
        temp = new char[length];
        copy(key, temp);
        /* for (int i = 0; temp[i] != '\0'; i++)
         {
             cout << temp[i];
         }
         cout << endl;*/
        highertolower(temp);
        int value = asciical(temp);
        outputfile << data << endl;
        outputfile.close();
        char tempy[50];
        char t[100];
        for (int i = 0; i < 50; i++)
        {
            tempy[i] = '\0';
        }
        if (checkint(temp))
        {
            value = converttoint(temp);
        }
        else
        {
            checkslash(temp, tempy);
            if (tempy[0] != '\0') {
                value = converttoint(temp);
            }
        }
        hst.insert(key, path);
        insert(value, path);
        //cout << "Inserted data into file: " << path << endl;
    }
    ////////////////////////
    //                    //
    //  ADDING NEW FILE   //
    //                    //
    ////////////////////////
    void addingnewfile(char* arr, const char* key)
    {
        char path[200];
        char data[1000];
        char line[1000];
        ifstream file(arr);
        file.getline(data, 1000);
        copy(foldername, path);
        concatenate(path, "/");
        concatenate(path, arr);
        concatenate(path, ".txt");

        char* temp;
        int length = leng(key);
        temp = new char[length];
        copy(key, temp);
        /* for (int i = 0; temp[i] != '\0'; i++)
         {
             cout << temp[i];
         }
         cout << endl;*/
        highertolower(temp);
        int value = asciical(temp);
        char tempy[50];
        char t[100];
        for (int i = 0; i < 50; i++)
        {
            tempy[i] = '\0';
        }
        if (checkint(temp))
        {
            value = converttoint(temp);
        }
        else
        {
            checkslash(temp, tempy);
            if (tempy[0] != '\0') {
                value = converttoint(temp);
            }
        }
        hst.insert(arr, path);
        insert(value, path);
        //cout << "Inserted data into file: " << path << endl;
    }


    ////////////////////////
    //                    //
    //    MERGE BRANCH    //
    //                    //
    ////////////////////////
    void mergingnewfile(char* arr, const char* key)
    {
        char path[200];
        char data[1000];
        char line[1000];
        ifstream file(arr);
        file.getline(data, 1000);
        copy(arr, path);

        char* temp;
        int length = leng(key);
        temp = new char[length];
        copy(key, temp);
        /* for (int i = 0; temp[i] != '\0'; i++)
         {
             cout << temp[i];
         }
         cout << endl;*/
        highertolower(temp);
        int value = asciical(temp);
        char tempy[50];
        char t[100];
        for (int i = 0; i < 50; i++)
        {
            tempy[i] = '\0';
        }
        if (checkint(temp))
        {
            value = converttoint(temp);
        }
        else
        {
            checkslash(temp, tempy);
            if (tempy[0] != '\0') {
                value = converttoint(temp);
            }
        }
        insert(value, path);
        //cout << "Inserted data into file: " << path << endl;
    }
    void savetreeinfile(Node* arr, ofstream& file1)
    {
        if (arr != nullptr)
        {
            file1 << arr->data << endl << arr->filename << endl;
            savetreeinfile(arr->left, file1);
            savetreeinfile(arr->right, file1);
        }
        else
        {
            file1 << -1 << endl;
        }
    }
    void commit(const char* message, ofstream& filep, char* arr)
    {
        if (filep.is_open()) {
            time_t now = time(0);
            char timing[20];
            struct tm timeinfo;
            localtime_s(&timeinfo, &now);
            strftime(timing, sizeof(timing), "%Y%m%d%H%M%S", &timeinfo);
            int value = asciical(message);
            value += 246758585;
            filep << arr << endl;
            filep << "ID :" << value << endl;
            filep << "Commited message: " << message << endl;
            filep << "Time : " << timing << endl << endl;;
            // filep.close();
            cout << "Comiit succesfully: " << endl;
        }
        else
        {
            cout << "Error in opening commit file." << endl;
        }
    }
    void log_history()
    {
        cout << "Comit History: " << endl;
        ifstream openfile(comitfilepath);
        if (openfile.is_open())
        {
            char line[2000];
            while (openfile.getline(line, 2000))
            {
                cout << line << endl;
            }
            cout << endl;
            openfile.close();
        }
        else
        {
            cout << "Error im opening history." << endl;
        }
    }
    void setfoldername(const char* arr)
    {
        copy(arr, foldername);
    }
    void setroot(Node* temp)
    {
        root = nullptr;
        root = temp;
        return;
    }
    char* getfoldername()
    {
        if (foldername != nullptr)
        {
            return foldername;
        }
    }
    /*~AVL()
    {
        delete[] root;
        delete[] foldername;
    }*/
    void displayh()
    {
        hst.displayhashing();
    }
};


////////////////////////
//                    //
//     Repository     //
//                    //
////////////////////////
class Repository
{
    char reponame[100];
    char branchname[100];
    char treepath[100];
public:
    AVL* tree;
    Repository(char* n)
    {
        copy(n, reponame);
        createrepo();
    }
    void createrepo()
    {
        if (_mkdir(reponame) == 0)
        {
            char foldername[100];
            cout << "Enter Main Branch name: ";
            cin.get(foldername, 100);
            cin.ignore();
            char fop[100];
            copy(reponame, fop);
            concatenate(fop, "/");
            concatenate(fop, foldername);
            copy(foldername, branchname);
            tree = new AVL(fop);
        }
    }
    ////////////////////////
    //                    //
    //  INITIALIZING AVl  //
    //                    //
    ////////////////////////
    void init(const char* csvfilename)
    {
        tree->init(csvfilename);
        char fil1[100];
        copy(reponame, fil1);
        concatenate(fil1, "/");
        concatenate(fil1, branchname);
        concatenate(fil1, "/treestate.txt");
        copy(fil1, treepath);
        ofstream file2(fil1);
        tree->savetreeinfile(tree->getroot(), file2);
        file2.close();
    }
    AVL* gettree()
    {
        return tree;
    }

    void updation()
    {

        ////// For Deletion /////
        int choice;
        bool flag = true;
        char comit[100];
        ofstream comith(tree->comitfilepath);
        while (flag) {
            cout << "\n>>>>>>>>>>> Tree Menu <<<<<<<<\n";
            cout << "\t1.Add a file\n\t2.Delete a file\n\t3.Update the file name\n\t4.Exit\n\nEnter you choice: ";
            cin >> choice;
            if (choice < 1 && choice>4)
            {
                continue;
            }
            switch (choice)
            {
            case 1:
            {
                char newf[100];
                cin.ignore();
                cout << "Enter name of file for adding in form(name): ";
                cin.get(newf, 100);
                char key[100];
                copy(newf, key);
                tree->addingnewfile(newf, key);
                cin.ignore();
                cout << "Enter the message for commit and changes that you make: ";
                cin.get(comit, 100);
                tree->commit(comit, comith, newf);
                break;
            }
            case 2:
            {
                char fildel[100];
                cin.ignore();
                cout << "Enter name of file for deletion : ";
                cin.get(fildel, 100);
                highertolower(fildel);
                int value = asciical(fildel);
                char* temp;
                int length = leng(fildel);
                temp = new char[length];
                copy(fildel, temp);
                char tempy[50];
                char t[100];
                for (int i = 0; i < 50; i++)
                {
                    tempy[i] = '\0';
                }
                if (checkint(temp))
                {
                    value = converttoint(temp);
                }
                else
                {
                    checkslash(temp, tempy);
                    if (tempy[0] != '\0') {
                        value = converttoint(temp);
                    }
                }
                tree->deleteNode(value, fildel);
                cin.ignore();
                cout << "Enter the message for commit and changes that you make: ";
                cin.get(comit, 100);
                tree->commit(comit, comith, fildel);
                break;
            }
            case 4:
            {
                flag = false;
                break;
            }
            default:
            {
                cout << "Invalid input." << endl;
                break;
            }
            }
        }
        comith.close();
        char fil1[100];
        copy(treepath, fil1);
        ofstream file2(treepath);
        tree->savetreeinfile(tree->getroot(), file2);
        file2.close();
    }
    void newBranch()
    {
        settonull();
        char foldername[100];
        cin.ignore();
        cout << "Enter new Branch name: ";
        cin.get(foldername, 100);
        char fop[100];
        copy(reponame, fop);
        concatenate(fop, "/");
        concatenate(fop, foldername);
        copy(foldername, branchname);
        tree = new AVL(fop);
        return;
    }
    void settonull()
    {
        tree = nullptr;
        for (int i = 0; i < 100; i++)
        {
            branchname[i] = '\0';
            treepath[i] = '\0';
        }
    }
    ////////////////////////
    //                    //
    //    Branches NAME   //
    //                    //
    ////////////////////////
    void branchnames(ofstream& fil)
    {
        if (branchname != nullptr) {
            fil << branchname << endl;
        }
        return;
    }
    void displayBranches(ifstream& f)
    {
        cout << "Branches: " << endl;
        if (f.is_open())
        {
            char line[2000];
            while (f.getline(line, 2000))
            {
                cout << line << endl;
            }
            cout << endl;
            f.close();
        }
        else
        {
            cout << "Error in opening history." << endl;
        }
    }

    ////////////////////////
    //                    //
    //  SWITCHING BRANCH  //
    //                    //
    ////////////////////////
    void SwitchBranch(const char* arr)
    {
        for (int i = 0; i < 100; i++)
        {
            branchname[i] = '\0';
            treepath[i] = '\0';
        }
        cin.ignore();
        char fop[100];
        copy(reponame, fop);
        concatenate(fop, "/");
        concatenate(fop, arr);
        copy(arr, branchname);
        tree->setfoldername(fop);
        char fill[100];
        copy(fop, fill);
        concatenate(fill, "/treestate.txt");
        ifstream fi(fill);
        if (!fi.is_open())
        {
            cout << "This branch does not exist." << endl;
        }
        Node* temp = loadtreetoroot(fi);
        tree->setroot(temp);
        cout << "Switched to Branch " << arr << endl;
        return;
    }
    void DeleteBranch(char* arr)
    {
        char tpo[100];
        bool flage;
        if (campare(branchname, arr))
        {
            cout << arr << " is current branch so it cannot be deleted." << endl;
            return;
        }
        ifstream filee1("Branches.txt");
        if (filee1.is_open())
        {
            while (filee1.getline(tpo, 100))
            {
                if (campare(tpo, arr))
                {
                    flage = true;
                    break;
                }
            }

        }
        else
        {
            cout << "Error in opening Branch file" << endl;
        }
        if (flage == false)
        {
            cout << "Branch " << arr << " doesnot exist." << endl;
            return;
        }
        char fop[100];
        copy(reponame, fop);
        concatenate(fop, "/");
        concatenate(fop, arr);
        cout << fop << endl;
        char data[200];
        ofstream filpo("Bran.txt");
        ifstream filo("Branches.txt");
        if (filo.is_open())
        {
            while (filo.getline(data, 100))
            {
                if (!campare(data, arr))
                {
                    filpo << data << endl;
                }
            }
        }
        else
        {
            cout << "Error in opening Branch file" << endl;
        }
        char tmp[100];
        filpo.close();
        ifstream kl("Bran.txt");
        ofstream sa("Branches.txt");
        if (kl.is_open())
        {
            while (kl.getline(tmp, 100))
            {
                sa << tmp << endl;
            }
        }
        kl.close();
        sa.close();
        if (remove("Bran.txt") == 0)
        {
            return;
        }
        else
        {
            cout << "Error in deleting Bran.txt." << endl;
            return;
        }

    }

    ////////////////////////
    //                    //
    //For Merging Branches//
    //                    //
    ////////////////////////
    void extract(const char* arr, char* res)
    {
        int length = 0;
        while (arr[length] != '\0')
        {
            length++;
        }
        int op = -1;
        for (int i = 0; i < length; i++)
        {
            if (arr[i] == '/')
            {
                op = i;
            }
        }
        int rf = 0;
        if (op != -1)
        {
            for (int i = op + 1; i < length; i++)
            {
                res[rf++] = arr[i];
            }
        }
        else
        {
            for (int i = 0; i < length; i++)
            {
                res[rf++] = arr[i];
            }
        }
        res[rf] = '\0';
    }
    void copycontent(const char* t1, const char* t2)
    {
        ifstream sf(t1);
        ofstream dt(t2);
        if (!sf.is_open() || !dt.is_open())
        {
            cout << "Error in opening file." << endl;
            return;
        }
        dt << sf.rdbuf();
        sf.close();
        dt.close();
    }
    void mergenode(Node* temp, const char* tar)
    {
        if (temp == nullptr)
        {
            return;
        }
        char key1[100];
        extract(temp->filename, key1);
        char newpath[200];
        int i = 0;
        while (tar[i] != '\0')
        {
            newpath[i] = tar[i];
            i++;
        }
        newpath[i++] = '/';
        int j = 0;
        while (key1[j] != '\0')
        {
            newpath[i++] = key1[j++];
        }
        newpath[i] = '\0';
        copycontent(temp->filename, newpath);
        tree->mergingnewfile(newpath, key1);
        mergenode(temp->left, tar);
        mergenode(temp->right, tar);
    }
    void mergebranches(char* arr1)
    {
        char temp1[100];
        copy(reponame, temp1);
        concatenate(temp1, "/");
        concatenate(temp1, arr1);
        concatenate(temp1, "/treestate.txt");
        //cout << temp1 << endl;
        ifstream filer(temp1);

        if (!filer.is_open())
        {
            cout << "Error in opening branch for merging." << endl;
            return;
        }
        Node* temp = loadtreetoroot(filer);
        filer.close();
        if (temp == nullptr)
        {
            cout << "Tree is empty" << endl;
            return;
        }
        char fol[100];
        copy(reponame, fol);
        concatenate(fol, "/");
        concatenate(fol, branchname);
        mergenode(temp, fol);
        cout << "Merge into " << branchname << " successfully." << endl;
        ofstream filou(treepath);
        tree->savetreeinfile(tree->getroot(), filou);
        filou.close();
        return;
    }
};

int main()
{
    ofstream filing("Branches.txt");
    char reponame[100];
    cout << "Enter Repo name: ";
    cin.get(reponame, 100);
    cin.ignore();
    Repository bt(reponame);
    bt.init("Example Data.csv");
    bt.gettree()->preorder(bt.gettree()->getroot());
    bt.branchnames(filing);
    bt.updation();
    ifstream ft("Branches.txt");
    int choice;
    bool flag = true;
    while (flag)
    {
        cout << "\n>>>>>>>>>>> Branched Menu <<<<<<<<\n";
        cout << "\t1.Create a branch\n\t2.Remain in this Branch\n\t3.Switch to Branch\n\t4.Merge the Branch\n\t5.Delete a Branch\n\t6.Commit history\n\t7.Display its Hashing\n\t8.Exit\nEnter you choice: ";
        cin >> choice;
        if (choice < 1 && choice>7)
        {
            continue;
        }
        switch (choice)
        {
        case 1:
        {
            bt.newBranch();
            bt.init("Example Data.csv");
            bt.branchnames(filing);
            bt.gettree()->preorder(bt.gettree()->getroot());
            bt.updation();
            break;
        }
        case 2:
        {
            bt.updation();
            break;
        }
        case 3:
        {
            char fi[100];
            cin.ignore();
            cout << "Enter the branch name: ";
            cin.get(fi, 100);
            bt.SwitchBranch(fi);
            bt.updation();
            break;
        }
        case 4:
        {
            char fiw[100];
            cin.ignore();
            cout << "Enter the branch name for merging: ";
            cin.get(fiw, 100);
            bt.mergebranches(fiw);
            bt.gettree()->preorder(bt.gettree()->getroot());
            bt.updation();
            break;
        }
        case 5:
        {
            char filo[100];
            cin.ignore();
            cout << "Enter the branch name for deletion: ";
            cin.get(filo, 100);
            bt.DeleteBranch(filo);
            char teo[100];
            for (int i = 0; i < 100; i++)
            {
                teo[i] = '\0';
            }
            ft >> teo;
            if (teo[0] == '\0')
            {
                cout << "All Branches are deleted." << endl;
            }
            else {
                bt.SwitchBranch(filo);
            }
            break;
        }
        case 6:
        {
            bt.tree->log_history();
            break;
        }
        case 7:
        {
            bt.tree->displayh();
            break;
        }
        case 8:
        {
            flag = false;
            break;
        }
        default:
        {
            cout << "Invalid input." << endl;
            break;
        }
        }
    }
    filing.close();
    return 0;
}