
#include<iostream>
#include<fstream>
#include"Repository.h"
#include"AVLtree.h"
using namespace std;
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
		cout << "\t1.Create a branch\n\t2.Remain in this Branch\n\t3.Switch to Branch\n\t4.Merge the Branch\n\t5.Delete a Branch\n\t6.Commit history\n\t7.Display its Hashing\n8.Exit\nEnter you choice: ";
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
