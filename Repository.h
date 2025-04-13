#pragma once
#include<iostream>
#include<fstream>
#include<direct.h>
#include"AVLtree.h"
#include<ctime>
#include<cstdio>



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
		tree->savetreeinfile(tree->getroot(),file2);
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
		Node* temp= loadtreetoroot(fi);
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
	void mergenode(Node* temp,const char* tar)
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
		mergenode(temp->left,tar);
		mergenode(temp->right,tar);
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
		copy(reponame,fol);
		concatenate(fol,"/");
		concatenate(fol, branchname);
		mergenode(temp,fol);
		cout << "Merge into " << branchname << " successfully." << endl;
		ofstream filou(treepath);
		tree->savetreeinfile(tree->getroot(),filou);
		filou.close();
		return;
	}
 };