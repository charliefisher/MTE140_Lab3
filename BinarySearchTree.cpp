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
	/*
	if(root_->left != NULL && root_->right != NULL)
	{
		BinarySearchTree left;
		left.root_ = this->root_->left;
		BinarySearchTree right;
		right.root_ = this->root_->right;
		return 1 + right.size() + left.size();
	}
	else if(root_->left == NULL && root_->right != NULL)
	{
		BinarySearchTree right;
		right.root_ = this->root_->right;
		return 1 + right.size();
	}
	else if(root_->left != NULL && root_->right == NULL)
	{
		BinarySearchTree left;
		left.root_ = this->root_->left;
		return 1 + left.size();
	}
	else //both left and right are null
	{
		return 1;
	}
*/
	return size_;
}


BinarySearchTree::~BinarySearchTree()
{
	delete root_;
	root_ = NULL;
}
bool BinarySearchTree::insert(DataType value)
{
	Node* currNode = root_;
	if(root_ == NULL)
	{
		Node* newNode = new Node(value);
		root_ = newNode;
	}
	else
	{

		for(int i=size_;i>0;i--) //might want to make this a while loop
		{
			Node* left = currNode->left;
			Node* right = currNode->right;
			if(value > currNode->val && right != NULL)
			{
				currNode = right;
			}
			else if(value < currNode->val && left != NULL)
			{
				currNode = left;
			}
			else if(value > currNode->val && right != NULL)
			{
				right = new Node(value);
				size_++;
				return true;
			}
			else if(value < currNode->val && left != NULL)
			{
				right = new Node(value);
				size_++;
				return true;
			}
			else if(value = currNode->val)
			{
				return false;
			}


		}
	}


}

bool BinarySearchTree::remove(DataType val)
{

}

bool BinarySearchTree::exists(DataType val) const
{

}

DataType BinarySearchTree::min() const
{

}

DataType BinarySearchTree::max() const
{

}

unsigned int  BinarySearchTree::depth() const
{

}
void BinarySearchTree::print() const
{

}


