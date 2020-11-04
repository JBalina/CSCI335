/*
Jonathan Balina
CSCI 335
Shostak
Project 2
*/

#include<iostream>
#include<utility>
#include<vector>
#include<cstdlib>
#include<chrono>
#include"container.h"

using namespace std;

int main()
{
	vector<int> first_test, second_test, third_test;
	for(int i = 0; i < 1000; i++)
	{
		first_test.push_back(rand());
	}
	for(int i = 0; i < 100000; i++)
	{
		second_test.push_back(rand());
	}
	for(int i = 0; i < 1000000; i++)
	{
		third_test.push_back(rand());
	}


	chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
	BST<int> BSTTest1;
	for(int i = 0; i < 1000; i++)
	{
		BSTTest1.Insert(first_test[i]);
	}
	for(int i = 0; i < 500; i++)
	{
		BSTTest1.Remove(first_test[2*i]);
	}
	chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
	cout << "Duration for BST with 1000 random Integers is " << chrono::duration_cast<chrono::milliseconds>(t2-t1).count() << " milliseconds" << endl;

	t1 = chrono::steady_clock::now();
	AVL<int> AVLTest1;
	for(int i = 0; i < 1000; i++)
	{
		AVLTest1.Insert(first_test[i]);
	}
	for(int i = 0; i < 500; i++)
	{
		AVLTest1.Remove(first_test[2*i]);
	}
	t2 = chrono::steady_clock::now();
	cout << "Duration for AVL with 1000 random Integers is " << chrono::duration_cast<chrono::milliseconds>(t2-t1).count() << " milliseconds" << endl;

	t1 = chrono::steady_clock::now();
	BST<int> BSTTest2;
	for(int i = 0; i < 100000; i++)
	{
		BSTTest2.Insert(second_test[i]);
	}
	for(int i = 0; i < 50000; i++)
	{
		BSTTest2.Remove(second_test[2*i]);
	}
	t2 = chrono::steady_clock::now();
	cout << "Duration for BST with 100000 random Integers is " << chrono::duration_cast<chrono::milliseconds>(t2-t1).count() << " milliseconds" << endl;

	t1 = chrono::steady_clock::now();
	AVL<int> AVLTest2;
	for(int i = 0; i < 100000; i++)
	{
		AVLTest2.Insert(second_test[i]);
	}
	for(int i = 0; i < 50000; i++)
	{
		AVLTest2.Remove(second_test[2*i]);
	}
	t2 = chrono::steady_clock::now();
	cout << "Duration for AVL with 100000 random Integers is " << chrono::duration_cast<chrono::milliseconds>(t2-t1).count() << " milliseconds" << endl;

	t1 = chrono::steady_clock::now();
	BST<int> BSTTest3;
	for(int i = 0; i < 1000000; i++)
	{
		BSTTest3.Insert(third_test[i]);
	}
	for(int i = 0; i < 500000; i++)
	{
		BSTTest3.Remove(third_test[2*i]);
	}
	t2 = chrono::steady_clock::now();
	cout << "Duration for BST with 1000000 random Integers is " << chrono::duration_cast<chrono::milliseconds>(t2-t1).count() << " milliseconds" << endl;

	t1 = chrono::steady_clock::now();
	AVL<int> AVLTest3;
	for(int i = 0; i < 1000000; i++)
	{
		AVLTest3.Insert(third_test[i]);
	}
	for(int i = 0; i < 500000; i++)
	{
		AVLTest3.Remove(third_test[2*i]);
	}
	t2 = chrono::steady_clock::now();
	cout << "Duration for AVL with 1000000 random Integers is " << chrono::duration_cast<chrono::milliseconds>(t2-t1).count() << " milliseconds" << endl;



	t1 = chrono::steady_clock::now();
	BST<int> BSTTestW;
	for(int i = 0; i < 10000; i++)
	{
		BSTTestW.Insert(i);
	}
	for(int i = 0; i < 5000; i++)
	{
		BSTTestW.Remove(i*2);
	}
	t2 = chrono::steady_clock::now();
	cout << "Duration for BST with worst case 10000 Integers is " << chrono::duration_cast<chrono::milliseconds>(t2-t1).count() << " milliseconds" << endl;

	t1 = chrono::steady_clock::now();
	AVL<int> AVLTestW;
	for(int i = 0; i < 10000; i++)
	{
		AVLTestW.Insert(i);
	}
	for(int i = 0; i < 5000; i++)
	{
		AVLTestW.Remove(i*2);
	}
	t2 = chrono::steady_clock::now();
	cout << "Duration for AVL with worst case 10000 Integers is " << chrono::duration_cast<chrono::milliseconds>(t2-t1).count() << " milliseconds" << endl;


	/*BST<int> test, test2;
	for(int i = 1; i <= 50; i++)
	{
		test.Insert(i);
	}
	cout << test.Size() << " " << test.Height() << " " << test[50] << endl;
	test.Print();
	for(int i = 1; i <= 25; i++)
	{
		test.Remove(i*2);
	}
	test2 = test;
	cout << test2.Size() << " " << test2.Height() << endl;
	test2.Print();
	AVL<int> Atest, Atest2;
	for(int i = 1; i <= 50; i++)
	{
		Atest.Insert(i);
	}
	cout << Atest.Size() << " " << Atest.Height() << endl;
	Atest.Print();
	for(int i = 1; i <= 25; i++)
	{
		Atest.Remove(i*2);
	}
	Atest2 = Atest;
	cout << Atest2.Size() << " " << Atest2.Height() << endl;
	Atest2.Print();*/


}
