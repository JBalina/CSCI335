/*
Jonathan Balina
CSCI 335
Shostak
Project 1
*/

#ifndef MYMEMORY_H_INCLUDED
#define MYMEMORY_H_INCLUDED

#include<iostream>
#include<utility>

template<class Type>
class my_unique_ptr
{
private:
	Type* object;
public:
	/*Default constructor that initializes the object to point to nullptr*/
	my_unique_ptr();
	/*Constructor that takes a pointer Type * as a parameter and sets the 
	object to point there. We say that the newly created object takes 
	ownership of the pointed memory.*/
	my_unique_ptr(Type* ptr);
	/*Move constructor that takes my_unique_ptr object and constructs a new object from it.*/
	my_unique_ptr(my_unique_ptr<Type> && item);
	/*Copy constructor should be explicitly disabled/deleted*/
	my_unique_ptr(const my_unique_ptr<Type>&) = delete;
	/*Destructor that releases/deletes the block of memory pointed by the object.*/
	~my_unique_ptr();
	/*Dereference operator * that returns a reference to the item pointed by the object.*/
	Type& operator*() const;
	/*Operator -> that returns the pointer to the object. It allows 
	to use the my_unique_ptr object for class member access.*/
	Type* operator->() const;
	/*Move assignment operator*/
	my_unique_ptr<Type>& operator=(my_unique_ptr && item);
	/*Copy assignment operator must be explicitly disabled/deleted*/
	my_unique_ptr<Type>& operator=(const my_unique_ptr&) = delete;
	
};


template<class Type>
class my_shared_ptr
{
private:
	Type* object;
	int* counter;
	//std::vector<my_shared_ptr> sharedPtrs;
public:
	/*Default constructor that sets all inner pointers to nullptr*/
	my_shared_ptr();
	/*Constructor that takes Type * as a parameter and sets the object 
	to point there. The object considers itself to be the first my_shared_ptr 
	object to point to that block of memory. So the counter should be set to 1.*/
	my_shared_ptr(Type* ptr);
	/*Copy constructor. Since the original object already points to the 
	block of memory and now the newly created object points there too, 
	you must increase the counter by 1.*/
	my_shared_ptr(const my_shared_ptr<Type>& item); //not sure yet
	/*Move constructor. Since the original rvalue wont point to the block 
	of memory no more, the counter should remain the same.*/
	my_shared_ptr(my_shared_ptr<Type> && item);
	/*Destructor that releases/deletes the block of memory and the counter 
	if no other shared pointer points there.*/
	~my_shared_ptr();
	/*Dereference operator * that returns a reference to the item pointed by the object.*/
	Type& operator*() const;
	/*Operator -> that returns the pointer to the object. It allows 
	to use the my_shared_ptr object for class member access.*/
	Type* operator->() const;
	/*Copy and move assignment operators. If prior to the assignment the my_shared_ptr 
	object was already pointing somewhere, the counter for the old block of memory should 
	be decreased by 1, and if it reaches 0, the old block of memory should be released/deleted. 
	Copy assignment should also increase the counter for the newly pointed block of memory.*/
	my_shared_ptr<Type>& operator=(my_shared_ptr && item);
	my_shared_ptr<Type>& operator=(const my_shared_ptr& item);
	void printcount();

};






#include "my_memory.cpp"
#endif
