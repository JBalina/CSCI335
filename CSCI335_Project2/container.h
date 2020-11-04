/*
Jonathan Balina
CSCI 335
Shostak
Project 2
*/

#ifndef CONTAINER_H_INCLUDED
#define CONTAINER_H_INCLUDED

#include<iostream>
#include<algorithm>

template<class Type>
class BST
{
protected:
	struct Node
	{
		Type item;
		Node* left;
		Node* right;
		int height;
		Node();
		Node(const Type& new_item);
	};
	Node* root;
private:
	void util_clear(Node* cur);
	int util_height(Node* cur) const;
	int util_size(Node* cur) const;
	void util_print(Node* cur) const;
	typename BST<Type>::Node* util_remove(Node* cur, const Type& value);
	void util_copy(Node*& this_cur, Node* other_cur);

public:
	BST();
	~BST();
	int Height() const;
	int Size() const;
	void Print() const;
	Type& operator[](const Type& search);
	void Insert(const Type& newitem);
	void Remove(const Type& value);
	BST<Type>& operator=(const BST<Type>& tree);
};



template<class Type>
class AVL:public BST<Type>
{
private:
	void LL_rotate(typename BST<Type>::Node*& k2);
	void RR_rotate(typename BST<Type>::Node*& k2);
	void LR_rotate(typename BST<Type>::Node*& k2);
	void RL_rotate(typename BST<Type>::Node*& k2);
	void AVL_util_insert(const Type& newitem, typename BST<Type>::Node*& cur);
	void AVL_util_remove(const Type& value, typename BST<Type>::Node*& cur);
	int NodeHeight(typename BST<Type>::Node*& cur) const;
public:
	void Insert(const Type& newitem);
	void Remove(const Type& value);
};







#include "container.cpp"
#endif
