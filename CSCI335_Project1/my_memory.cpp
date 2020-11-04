/*
Jonathan Balina
CSCI 335
Shostak
Project 1
*/

/*default constructor*/
template<class Type>
my_unique_ptr<Type>::my_unique_ptr()
{
	object = new Type;
}

/*constructor with pointer to Type as a parameter. sets my_unique_ptr
to point at object Type*/
template<class Type>
my_unique_ptr<Type>::my_unique_ptr(Type* ptr)
{
	object = new Type;
	object = ptr;
}

/*move constructor. constructs object using another my_unique_ptr*/
template<class Type>
my_unique_ptr<Type>::my_unique_ptr(my_unique_ptr<Type> && item)
{
	object = new Type;
	object = item.object;
	item.object = nullptr;
}

/*destructor, checks if pointing at nullptr, and deletes if not*/
template<class Type>
my_unique_ptr<Type>::~my_unique_ptr()
{
	if(object != nullptr)
	{
		delete object;
	}
}

/*returns reference to object*/
template<class Type>
Type& my_unique_ptr<Type>::operator*() const
{
	return *object;
}

/*returns pointer to object*/
template<class Type>
Type* my_unique_ptr<Type>::operator->() const
{
	return object;
}

/*move assignment, assigns this my_unique_ptr to another my_unique_ptr.
also deallocates the memory of the other my_unique_ptr*/
template<class Type>
my_unique_ptr<Type>& my_unique_ptr<Type>::operator=(my_unique_ptr && item)
{
	delete object;
	object = item.object;
	item.object = nullptr;
	return *this;
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////





/*default constructer with all pointers pointing to nullptr*/
template<class Type>
my_shared_ptr<Type>::my_shared_ptr()
{
	object = new Type;
	object = nullptr;
	counter = nullptr;
}

/*constructor with pointer to Type as a parameter. sets my_shared_ptr
to point at object Type and counter to 1*/
template<class Type>
my_shared_ptr<Type>::my_shared_ptr(Type* ptr)
{
	object = ptr;
	counter = new int;
	*counter = 1;
}

/*constructor that copies another my_shared_ptr. since this is another pointer for the object, the counter in incremented*/
template<class Type>
my_shared_ptr<Type>::my_shared_ptr(const my_shared_ptr<Type>& item)
{
	object = item.object;
	counter = item.counter;
	if(counter != nullptr) //in case of copied my_shared_ptr being empty
		(*counter)++;
}

/*move constructer, constructs using another my_shared_ptr and deallocates
the other my_shared_ptr*/
template<class Type>
my_shared_ptr<Type>::my_shared_ptr(my_shared_ptr<Type> && item)
{
	object = item.object;
	counter = item.counter;
	item.object = nullptr;
	item.counter = nullptr;
}

/*destructor. if this my_shared_ptr is the only thing pointing to the object
then memory is released*/
template<class Type>
my_shared_ptr<Type>::~my_shared_ptr()
{
	if((counter != nullptr) && ((*counter) <= 1))
	{
		if(object != nullptr)
			delete object;
		if(counter != nullptr)
			delete counter;
	}
}

/*returns reference to object*/
template<class Type>
Type& my_shared_ptr<Type>::operator*() const
{
	return *object;
}

/*returns pointer to object*/
template<class Type>
Type* my_shared_ptr<Type>::operator->() const
{
	return object;
}

/*move assignment, assigns this my_shared_ptr to another my_shared_ptr.
also deallocates the memory of the other my_shared_ptr. 
It decrements the counter for the object that it was pointing to before the assignment,
if it was the only pointer pointing at it, then it releases the memory*/
template<class Type>
my_shared_ptr<Type>& my_shared_ptr<Type>::operator=(my_shared_ptr && item)
{
	if(counter != nullptr)
	{
		(*counter)--;
		if((*counter) == 0)
			delete this;
	}
	object = item.object;
	counter = item.counter;
	return *this;
}

/*copy assignment, copies another my_shared_ptr and increments the counter
It decrements the counter for the object that it was pointing to before the assignment,
if it was the only pointer pointing at it, then it releases the memory*/
template<class Type>
my_shared_ptr<Type>& my_shared_ptr<Type>::operator=(const my_shared_ptr& item)
{
	if(counter != nullptr)
	{
		(*counter)--;
		if((*counter) == 0)
			delete this;
	}
	object = item.object;
	counter = item.counter;
	(*counter)++;
	return *this;
}


















