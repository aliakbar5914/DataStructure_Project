#pragma once
#include<iostream>
#include<fstream>
#include<direct.h>
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

	cout << arr2 << endl;
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

struct Node
{
    int data;
    char filename[100];
    Node(int key=0,const char *fl="")
    {
        if (fl == nullptr)
        {
            filename[0] = '\0';
        }
        data = key;
        copy(fl, filename);
    }
};

struct BNode
{
	Node* keys;
	int degree;
	BNode** child;
	int num_key;
	char key[100];
	bool isleaf;
    BNode(int t=3, bool l=true) {
        if (t < 2) {
            cout << "Degree must be at least 2" << endl;
        }
        cout << t << endl;
        degree = t;
        isleaf = l;

        keys = new Node[2 * degree - 1];
        child = new BNode * [2 * degree];
        num_key = 0;
    }

    void traverse(int depth = 0)
    {
        for (int i = 0; i < depth; i++) cout << "  "; // Indentation for depth
        for (int i = 0; i < num_key; i++) {
            cout << "[" << keys[i].data << "]";
        }
        cout << endl;
        if (!isleaf)
        {
            for (int i = 0; i <= num_key; i++) {
                child[i]->traverse(depth + 1);
            }
        }
    }

    Node getpredecessor(int g)
    {
        BNode* nd = child[g];
        while (!nd->isleaf)
        {
            nd = nd->child[nd->num_key];
        }
        return nd->keys[nd->num_key - 1];
    }
    Node getsuccessor(int g)
    {
        BNode* nd = child[g + 1];
        while (!nd->isleaf)
        {
            nd = nd->child[0];
        }
        return nd->keys[0];
    }
    int findkey(int k)
    {
        int i = 0;
        while (i < num_key && keys[i].data < k)
        {
            i++;
        }
        return i;
    }
    void insertNonFull(Node k)
    {
        int i = num_key - 1;
        if (isleaf == true)
        {
            while (i >= 0 && keys[i].data > k.data)
            {
                keys[i + 1] = keys[i];
                i--;
            }
            keys[i + 1] = k;
            num_key = num_key + 1;
        }
        else
        {
            while (i >= 0 && keys[i].data > k.data)
            {
                i--;
            }
            if (child[i + 1]->num_key == 2 * degree - 1)
            {
                splitChild((i + 1), child[i + 1]);

                if (keys[i + 1].data < k.data)
                {
                    i++;
                }
            }
            child[i + 1]->insertNonFull(k);
        }
    }
    void splitChild(int i, BNode* y)
    {
        BNode* z = new BNode(y->degree, y->isleaf);
        z->num_key = degree - 1;
        for (int j = 0; j < degree - 1; j++)
        {
            z->keys[j] = y->keys[j + degree];
        }
        if (y->isleaf == false)
        {
            for (int k = 0; k < degree; k++)
            {
                z->child[k] = y->child[k + degree];
            }
        }
        y->num_key = degree - 1;
        for (int j = num_key; j >= i + 1; j--)
        {
            child[j + 1] = child[j];
        }
        child[i + 1] = z;
        for (int j = num_key - 1; j >= i; j--)
        {
            keys[j + 1] = keys[j];
        }
        keys[i] = y->keys[degree - 1];
        num_key += 1;
    }
    void deletion(int k)
    {
        int i = findkey(k);
        if (i < num_key && keys[i].data == k)
        {
            if (isleaf)
            {
                rl(i);
            }
            else
                rnl(i);
        }
        else
        {
            if (isleaf)
            {
                cout << "The key is not found." << endl;
                return;
            }
            bool flag = false; 
            if (i == num_key)
            {
                flag = true;
            }
            if (child[i]->num_key < degree)
            {
                fill(i);
            }
            if (flag && i > num_key)
            {
                child[i - 1]->deletion(k);
            }
            else
            {
                child[i]->deletion(k);
            }
        }
        return;
    }
    void rl(int i) {
        int j = i + 1;
        while (j < num_key)
        {
            keys[i - 1] = keys[i];
        }
        num_key--;
        return;
    }
    void rnl(int i)
    {
        Node k = keys[i];
        if (child[i]->num_key >= degree)
        {
            Node prev = getpredecessor(i);
            keys[i] = prev;
            child[i]->deletion(prev.data);
        }
        else if (child[i+1]->num_key >= degree)
        {
            Node prev = getsuccessor(i);
            keys[i] = prev;
            child[i]->deletion(prev.data);
        }
        else
        {
            merge(i);
            child[i]->deletion(k.data);
        }
        return;
    }
    void fill(int k)
    {
        if (k != 0 && child[k - 1]->num_key >= degree)
        {
            bfp(k);
        }
        else if (k != 0 && child[k + 1]->num_key >= degree)
        {
            bfn(k);
        }
        else
        {
            if (k != 0)
                merge(k);
            else
                merge(k);
        }
        return;
    }
    void bfp(int p)
    {
        BNode* ch = child[p];
        BNode* pa = child[p - 1];
        for (int i = ch->num_key - 1; i >= 0; i--)
        {
            ch->keys[i + 1] = ch->keys[i];
        }
        if (!ch->isleaf)
        {
            for (int i = ch->num_key; i >= 0; i--)
            {
                ch->child[i + 1] = ch->child[i];
            }
        }
        ch->keys[0] = keys[p - 1];
        if (!ch->isleaf)
        {
            ch->child[0] = pa->child[pa->num_key];
        }
        keys[p - 1] = pa->keys[pa->num_key - 1];
        ch->num_key += 1;
        pa->num_key -= 1;
    }
    void bfn(int p)
    {
        BNode* ch = child[p];
        BNode* pa = child[p + 1];
        if (!ch->isleaf)
        {
            ch->child[(ch->num_key) + 1] = pa->child[0];
        }
        keys[p] = pa->keys[0];
        for (int i =  1; i <pa->num_key; i++)
        {
            pa->keys[i - 1] = pa->keys[i];
        }
        if (!pa->isleaf)
        {
            for (int i = 1; i <= pa->num_key; i++)
            {
                pa->child[i - 1] = pa->child[i];
            }
        }
        ch->num_key += 1;
        pa->num_key -= 1;
    }
    void merge(int p)
    {
        BNode* ch = child[p];
        BNode* pa = child[p + 1];
        ch->keys[degree = 1] = keys[p];
        for (int i = 0; i < pa->num_key; i++)
        {
            ch->keys[i + degree] = pa->keys[i];
        }
        if (!ch->isleaf)
        {
            for(int i=0;i<=pa->num_key;i++)
            ch->child[i+degree] = pa->child[i];
        }

        for (int i = p+1; i < num_key; i++)
        {
            keys[i - 1] = keys[i];
        }
        for (int i = p + 2; i <= num_key; i++)
        {
            child[i - 1] = child[i];
        }
      
        ch->num_key = pa->num_key+ 1;
        num_key--;
        delete (pa);
        return;
    }
};
class BTree
{
    char foldername[100];
    int t;
    BNode *root;
public:
    char comitfilepath[100];

    BTree(int t1,char* arr)
    {
        t = t1;
        copy(arr, foldername);
        createfolder();
    }

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
    void Traversal()
    {
        if (root != NULL)
        {
            root->traverse();
        }
    }
    void insert(Node k)
    {
        if (root == nullptr)
        {
            root = new BNode(t, true);
            root->keys[0] = k;
            root->num_key = 1;
        }
        else
        {
            if (root->num_key == 2 * t - 1)
            {
                BNode* temp = new BNode(t, false);
                temp->child[0] = root;
                temp->splitChild(0, root);
                int i = 0;
                if (temp->keys[0].data < k.data)
                {
                    i++;
                }
                temp->child[i]->insertNonFull(k);
                root = temp;
            }
            else
            {
                root->insertNonFull(k);
            }
        }
    }
    void deletion(int l)
    {
        if (!root)
        {
            cout << "Tree is empty" << endl; return;
        }
        root->deletion(l);
        if (root->num_key == 0)
        {
            BNode* temp = root;
            if (root->isleaf)
            {
                root = nullptr;
            }
            else
            {
                root = root->child[0];
            }
            delete temp;
        }
        return;
    }
    char* getcomitfilepath()
    {
        return comitfilepath;
    }
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

        Node tempw{ value, path };
      // hst.insert(key, path);
        insert(tempw);
        //cout << "Inserted data into file: " << path << endl;
    }
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

      //  hst.insert(arr, path);
        //insert(value, path);
        //cout << "Inserted data into file: " << path << endl;
    }
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
        cout << key << endl;
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
        //insert(value, path);
        //cout << "Inserted data into file: " << path << endl;
    }
    /*void savetreeinfile(Node* arr, ofstream& file1)
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
    }*/
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
    
    char* getfoldername()
    {
        if (foldername != nullptr)
        {
            return foldername;
        }
    }
    
    void displayh()
    {
      //  hst.displayhashing();
    }
};