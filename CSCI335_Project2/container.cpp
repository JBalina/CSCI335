/*
Jonathan Balina
CSCI 335
Shostak
Project 2
*/

//basic constructors for node
template<class Type>
BST<Type>::Node::Node()
{
	left = nullptr;
	right = nullptr;
	height = 0;
}

template<class Type>
BST<Type>::Node::Node(const Type& new_item)
{
	item = new_item;
	left = nullptr;
	right = nullptr;
	height = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//empty tree constructor
template<class Type>
BST<Type>::BST()
{
	root = nullptr;
}

//private helper function for destructor
//recursively deletes children nodes and then itself
template<class Type>
void BST<Type>::util_clear(Node* cur)
{
	if (cur == nullptr)
		return;
	util_clear(cur->left);
	util_clear(cur->right);
	delete cur;
}

//recursively travels down the tree and records the height, takes the height of the higher subtree
template<class Type>
int BST<Type>::util_height(Node* cur) const
{
	if (cur == nullptr)
		return 0;
	int left = util_height(cur->left);
	int right = util_height(cur->right);
	if(left>right)
		return 1+left;
	else
		return 1+right;
}

//recursively counts all nodes
template<class Type>
int BST<Type>::util_size(Node* cur) const
{
	if (cur == nullptr)
		return 0;
	else
		return (util_size(cur->left) + 1 + util_size(cur->right));
}

//recursively prints left child, itself, and then right child
template<class Type>
void BST<Type>::util_print(Node* cur) const
{
	if (cur == nullptr)
		return;
	util_print(cur->left);
	std::cout << cur->item << std::endl;
	util_print(cur->right);
}

//removes an item in the tree. First recursively searches for item, then deletes it. If deleted node has two children, 
//then it is replaced by smallest node on its right subtree. If one child, then it is replaced by that child.
template<class Type>
typename BST<Type>::Node* BST<Type>::util_remove(Node* cur, const Type& value)
{
	//base case
	if(cur == nullptr)
		return cur;
	//searching for item
	else if(value < cur->item)
		cur->left = util_remove(cur->left, value);
	else if(value > cur->item)
		cur->right = util_remove(cur->right, value);
	//item is found
	else
	{
		//case 1: no children
		//just delete node
		if((cur->left == nullptr) && (cur->right == nullptr))
		{
			delete cur;
			cur = nullptr;
		}
		//case 2: one child
		//make child take place of node
		else if((cur->left == nullptr) && (cur->right != nullptr))
		{
			Node* temp = cur;
			cur = cur->right;
			delete temp;
		}
		else if((cur->left != nullptr) && (cur->right == nullptr))
		{
			Node* temp = cur;
			cur = cur->left;
			delete temp;
		}
		//case 3: two children
		//make smallest item of right subtree become Node
		else
		{
			Node* temp = cur->right;
			//find smallest item of right subtree
			while(temp->left!=nullptr)
			{
				temp = temp->left;
			}
			//cur takes values of temporary node
			cur->item = temp->item;
			cur->right = util_remove(cur->right, temp->item);
		}
	}
	return cur;
}

//recursively copies every node of another tree
template<class Type>
void BST<Type>::util_copy(Node*& this_cur, Node* other_cur)
{
	if(other_cur == nullptr)
		return;
	this_cur = new Node(other_cur->item);
	//std::cout << this_cur->item << std::endl;
	this_cur->height = other_cur->height;
	util_copy(this_cur->left, other_cur->left);
	util_copy(this_cur->right, other_cur->right);
}


//destructor
template<class Type>
BST<Type>::~BST()
{
	util_clear(root);
}

//returns height of the tree
template<class Type>
int BST<Type>::Height() const
{
	return util_height(root);
}

//returns number of nodes in the tree
template<class Type>
int BST<Type>::Size() const
{
	return util_size(root);
}

//Prints all items in order
template<class Type>
void BST<Type>::Print() const
{
	util_print(root);
}

//Returns the item given as the argument
template<class Type>/*ASSUMING THE ITEM IS ALREADY IN THE CONTAINER*/
Type& BST<Type>::operator[](const Type& search)
{
	Node* cur = root;
	while(cur!=nullptr)
	{
		if(cur->item == search)
			return cur->item;
		else if(cur->item > search)
			cur = cur->left;
		else
			cur = cur->right;
	}
	std::cout << "Item not in conatiner!" << std::endl;
	//return;
}

//inserts an item. Recursively locates the placement of the item and places it.
template<class Type>
void BST<Type>::Insert(const Type& newitem)
{
	Node* cur = root;
	if(root == nullptr)
	{
		root = new Node(newitem);
	}
	while(cur != nullptr)
	{
		//if greater then current key, go right, if less, go left
		if(cur->item > newitem)
		{
			if(cur->left != nullptr)
				cur = cur->left;
			//when nullptr found add item
			else
			{
				cur->left = new Node(newitem);
				return;
			}
		}
		else if(cur->item < newitem)
		{
			if(cur->right != nullptr)
				cur = cur->right;
			//when nullptr found add item
			else
			{
				cur->right = new Node(newitem);
				return;
			}
		}
		//if equal to do nothing
		else if(cur->item == newitem)
			return;
	}
}

//Removes an item
template<class Type>
void BST<Type>::Remove(const Type& value)
{
	util_remove(root, value);
}

//makes this tree equal to argument tree
template<class Type>
BST<Type>& BST<Type>::operator=(const BST<Type>& tree)
{
	util_clear(root);
	root = new Node;
	util_copy(root, tree.root);
	//std::cout << root->item << std::endl;
	return *this;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Single Left Rotation
template<class Type>
void AVL<Type>::LL_rotate(typename BST<Type>::Node*& k2)
{
	typename BST<Type>::Node* k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
	k2->height = std::max(NodeHeight(k2->left), NodeHeight(k2->right)) + 1;
	k1->height = std::max(NodeHeight(k1->left), NodeHeight(k2)) + 1;
	k2 = k1;
}

//Double right Rotation
template<class Type>
void AVL<Type>::RR_rotate(typename BST<Type>::Node*& k2)
{
	typename BST<Type>::Node* k1 = k2->right;
	k2->right = k1->left;
	k1->left = k2;
	k2->height = std::max(NodeHeight(k2->left), NodeHeight(k2->right)) + 1;
	k1->height = std::max(NodeHeight(k1->right), NodeHeight(k2)) + 1;
	k2 = k1;
}

//Double Left Right Rotation
template<class Type>
void AVL<Type>::LR_rotate(typename BST<Type>::Node*& k2)
{
	RR_rotate(k2->left);
	LL_rotate(k2);
}

//Double Right Left Rotation
template<class Type>
void AVL<Type>::RL_rotate(typename BST<Type>::Node*& k2)
{
	LL_rotate(k2->right);
	RR_rotate(k2);
}

//Similar to BST insert but balances after every insert
template<class Type>
void AVL<Type>::AVL_util_insert(const Type& newitem, typename BST<Type>::Node*& cur)
{
	if(cur == nullptr)
		cur = new typename BST<Type>::Node(newitem);
	else if(newitem < cur->item)
	{
		AVL_util_insert(newitem, cur->left);
		if(NodeHeight(cur->left) - NodeHeight(cur->right) == 2)
		{
			if(newitem < cur->left->item)
				LL_rotate(cur);
			else
				LR_rotate(cur);
		}
	}
	else if(cur->item < newitem)
	{
		AVL_util_insert(newitem, cur->right);
		if(NodeHeight(cur->right) - NodeHeight(cur->left) == 2)
		{
			if(cur->right->item < newitem)
				RR_rotate(cur);
			else
				RL_rotate(cur);
		}
	}
	
	cur->height = std::max(NodeHeight(cur->left), NodeHeight(cur->right)) + 1;

}

//Similar to BST remove but balances after every removal
template<class Type>
void AVL<Type>::AVL_util_remove(const Type& value, typename BST<Type>::Node*& cur)
{
	if(cur == nullptr)
		return;
	if(value < cur->item)
	{
		AVL_util_remove(value, cur->left);
		if(NodeHeight(cur->right) - NodeHeight(cur->left) == 2)
		{
			if(NodeHeight(cur->right->right) >= NodeHeight(cur->right->left))
				RR_rotate(cur);
			else
				RL_rotate(cur);
		}
	}
	else if (cur->item < value)
	{
		AVL_util_remove(value, cur->right);
		if(NodeHeight(cur->left) - NodeHeight(cur->right) == 2)
		{
			if(NodeHeight(cur->left->left) >= NodeHeight(cur->left->right))
				LL_rotate(cur);
			else
				LR_rotate(cur);
		}
	}
	else
	{		
		if((cur->left != nullptr) && (cur->right != nullptr))
		{
			typename BST<Type>::Node* temp = cur->right;
			while(temp->left!=nullptr)
			{
				temp = temp->left;
			}
			cur->item = temp->item;
			AVL_util_remove(cur->item, cur->right);
			if(NodeHeight(cur->left) - NodeHeight(cur->right) == 2)
			{
				if (NodeHeight(cur->left->left) >= NodeHeight(cur->left->right))
					LL_rotate(cur);
				else
					LR_rotate(cur);
			}
		}
		else
		{
			if(cur->right != nullptr)
			{
				typename BST<Type>::Node* temp = cur;
				cur = cur->right;
				delete temp;
			}
			else
			{
				typename BST<Type>::Node* temp = cur;
				cur = cur->left;
				delete temp;
			}
		}

	}
	if(cur != nullptr)
		cur->height = std::max(NodeHeight(cur->left), NodeHeight(cur->right)) + 1;
}

//mainly to return a value for height even when there is a nullptr
template<class Type>
int AVL<Type>::NodeHeight(typename BST<Type>::Node*& cur) const
{
	if(cur == nullptr)
		return -1;
	else
		return cur->height;
}

//Inserts a new item
template<class Type>
void AVL<Type>::Insert(const Type& newitem)
{
	AVL_util_insert(newitem, BST<Type>::root);
}

//Deletes an Item
template<class Type>
void AVL<Type>::Remove(const Type& value)
{
	AVL_util_remove(value, BST<Type>::root);
}

































