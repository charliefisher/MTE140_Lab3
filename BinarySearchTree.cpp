#include "BinarySearchTree.hpp"
#include <cstdlib>
#include <iostream>

using namespace std;
typedef BinarySearchTree::DataType DataType;



BinarySearchTree::Node::Node(DataType newval)
{
	left = NULL;
	right = NULL;
	val = newval;
}

BinarySearchTree::BinarySearchTree()
{
	root_ = NULL;
	size_ = 0;
}



unsigned int BinarySearchTree::size() const
{
	return size_;
}


BinarySearchTree::~BinarySearchTree()
{
	delete root_;
	root_ = NULL;
}

bool recursiveInsert(DataType value, BinarySearchTree::Node *root)
{
	//we already checked if the value exists so we don't have to check if value == root->val
	if(value > root->val)
	{
		if(root->right == NULL)
		{
			BinarySearchTree::Node* newVal = new BinarySearchTree::Node(value);
			root->right = newVal;
			return true;
		}
		else
		{
			return recursiveInsert(value, root->right);
		}
	}
	else if(value < root->val)
	{
		if(root->left == NULL)
		{
			BinarySearchTree::Node* newVal = new BinarySearchTree::Node(value);
			root->left = newVal;
			return true;
		}
		else
		{
		return recursiveInsert(value, root->left);
		}
	}
	else{return false;}//just in case
}

bool BinarySearchTree::insert(DataType value)
{
	if(root_ == NULL)
	{
		Node* newNode = new Node(value);
		root_ = newNode;
		size_++;
		return true;
	}
	else if(exists(value) == true)
	{
		return false;
	}
	else
	{

		if(recursiveInsert(value, root_)==true)
		{
			size_++;
			return true;
		}
		else{return false;}
	}


}

bool recursiveRemove(DataType value, BinarySearchTree::Node *root_)
{
	if(root_->val == value)
	{
		if(root_->left == NULL  && root_->right == NULL) //node has no children
		{
			delete root_;
			return true;
		}
		else if (root_->left == NULL  && root_->right != NULL) //node has one child
		{
			//swap root with right
			BinarySearchTree::Node* oldRoot = root_;
			BinarySearchTree::Node* newRoot = root_->right;
			root_ = newRoot;
			delete oldRoot;
			return true;
		}
		else if (root_->left != NULL  && root_->right == NULL) //node has one child
		{
			//swap root with left
			BinarySearchTree::Node* oldRoot = root_;
			BinarySearchTree::Node* newRoot = root_->left;
			root_ = newRoot;
			delete oldRoot;
			return true;
		}
		else //node has two children
		{
			//find the smallest value in current tree's right subtree
			BinarySearchTree::Node* currNode = root_->right;
			while(currNode->left != NULL)
			{
				currNode = currNode->left;
			}

			//swap smallest value of right subtree with root
			BinarySearchTree::Node* oldRoot = root_;
			BinarySearchTree::Node* newRoot = currNode;
			root_ = newRoot;
			delete oldRoot;
			return true;
		}
	}

	else
	{
		if(value > root_->val)
		{
			if(root_->right != NULL)
			{
				return recursiveRemove(value, root_->right);
			}
			else{return false;}

		}
		if(value < root_->val)
		{
			if(root_->left != NULL)
			{
				return recursiveRemove(value, root_->left);
			}
			else{return false;}

		}
	}
}

bool BinarySearchTree::remove(DataType value)
{
	if(root_ == NULL)
	{
		return false;
	}

	else
	{
		if(recursiveRemove(value, this->root_)==true)
		{
			size_--;
			return true;
		}
		else{return false;}
	}
}

bool recursiveExists(DataType value, BinarySearchTree::Node *root_)
{
	if(value == root_->val)
	{
		return true;
	}
	else if(value > root_->val)
	{
		if(root_->right != NULL)
		{
			return recursiveExists(value, root_->right);
		}
		else{return false;}

	}

	else if(value < root_->val)
	{
		if(root_->left != NULL)
		{
			return recursiveExists(value, root_->left);
		}
		else{return false;}
	}
	else{return false;}

}

bool BinarySearchTree::exists(DataType value) const
{
	if(root_ == NULL)
	{
		return false;
	}
	else
	{
		return recursiveExists(value, this->root_);
	}
}

DataType BinarySearchTree::min() const
{
	//assume this is never called on an empty tree
	Node* currNode = root_;
	while(currNode->left != NULL)
	{
		currNode = currNode->left;
	}
	return currNode->val;
}

DataType BinarySearchTree::max() const
{
	//assume this is never called on an empty tree
		Node* currNode = root_;
		while(currNode->right != NULL)
		{
			currNode = currNode->right;
		}
		return currNode->val;
}

int BinarySearchTree::getNodeDepth(Node* tree) const
{
	if(tree == NULL)
	{
		return 0;
	}
	else if(tree->left == NULL && tree->right == NULL)
	{
		return 0;
	}
	else
	{
		return (1 + std::max(getNodeDepth(tree->left),getNodeDepth(tree->right)));
	}
}

unsigned int BinarySearchTree::depth() const
{
	//if(root_ == NULL)
	//{
	//	return 0;
	//}
	unsigned int returnVal = getNodeDepth(this->root_);
	return returnVal;
}

void recursivePrint(BinarySearchTree::Node* root, int level)
{
	if(level == 1)
	{
		cout << root->val << " ";
	}
	else if(level > 1)
	{
		recursivePrint(root->left,level-1);
		recursivePrint(root->right,level-1);
	}


}
void BinarySearchTree::print() const
{
	//print in level order

	if(root_ == NULL)
	{
		cout<< " ";
		return;
	}
	int h = getNodeDepth(root_);
	for(int i = 0; i<h;i++)
	{

		recursivePrint(root_, i);

	}


}


