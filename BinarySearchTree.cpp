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

bool recursiveRemove(DataType value, BinarySearchTree::Node *root, BinarySearchTree::Node *root_prev)
{
	if(root->val == value)
	{
		if(root->left == NULL  && root->right == NULL) //node has no children
		{

      //BinarySearchTree::Node *oldRoot = root;

      delete root;
      root_prev = NULL;
      root = NULL;
      //delete root;

			return true;
		}
		else if (root->left == NULL  && root->right != NULL) //node has one child
		{
			//swap root with right

     /*
			BinarySearchTree::Node* oldRoot = root;
			BinarySearchTree::Node* newRoot = root->right;
			root_prev = newRoot;
			delete oldRoot;
      oldRoot = NULL;
			return true;
			*/
			DataType newVal = root->right->val;
			root->val = newVal;

			delete root->right;
			root->left = NULL;


			return true;


      /*
      DataType newVal = root->right->val;
      root->val = newVal;

      delete root->right;
      root->right = NULL;
      */

      return true;
		}
		else if (root->left != NULL  && root->right == NULL) //node has one child
		{
			//swap root with left
			/*
      BinarySearchTree::Node* oldRoot = root_;
			BinarySearchTree::Node* newRoot = root_->left;
			root_ = oldRoot;

      delete oldRoot;
      oldRoot = NULL;
      */
			//BinarySearchTree::Node* oldRoot = root_;
			//BinarySearchTree::Node* newRoot = root_->left;
			//root_ = root_->left;
			//delete oldRoot;
      //oldRoot = NULL;
			//return true;

      DataType newVal = root->left->val;
      root->val = newVal;

      delete root->left;
      root->left = NULL;


      return true;

      /*
      BinarySearchTree::Node* oldRoot = root;
			BinarySearchTree::Node* newRoot = root->left;
			root_prev = root->left;
			delete oldRoot;
      //oldRoot = NULL;

			return true;
      */
		}
		else //node has two children
		{
			//find the smallest value in current tree's right subtree
			BinarySearchTree::Node* currNode = root->right;
			while(currNode->left != NULL)
			{
				currNode = currNode->left;
			}

			//swap smallest value of right subtree with root
			/*
      BinarySearchTree::Node* oldRoot = root_;
			BinarySearchTree::Node* newRoot = currNode;
			root_ = newRoot;
			delete oldRoot;
      oldRoot = NULL;
			return true;
      */
      DataType newVal = currNode->val;
      root->val = newVal;

      delete currNode;
      currNode = NULL;
		}
	}

	else
	{
		if(value > root->val)
		{
			if(root->right != NULL)
			{
				return recursiveRemove(value, root->right, root);
			}
			else{return false;}

		}
		if(value < root->val)
		{
			if(root->left != NULL)
			{
				return recursiveRemove(value, root->left, root);
			}
			else{return false;}

		}
	}
}

bool BinarySearchTree::remove(DataType value)
{
	if(exists(value) == false)
  {
    return false;
  }
  if(root_ == NULL)
	{
		return false;
	}

	else
	{
		if(recursiveRemove(value, this->root_, NULL)==true)
		{
			size_--;
			return true;
		}
		else{return false;}
	}
}

bool recursiveExists(DataType value, BinarySearchTree::Node *root_)
{
	if(root_ == NULL)
	{
		return false;
	}
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

	//if(tree == NULL)
	//{
	//	return -1;
	//}
	//if(root_ !=NULL)
	//{
	//	return 0;
	//}
	/*
	if(tree->left == NULL && tree->right == NULL)
	{
		return 1;
	}
	else
	{
		int leftTree = getNodeDepth(tree->left);
		int rightTree = getNodeDepth(tree->right);
		return (1 + std::max(rightTree, leftTree));
	}
	*/
	{
	    if (tree == NULL)
	        return -1;
	    else
	    {

	        int leftDepth = getNodeDepth(tree->left);
	        int rightDepth = getNodeDepth(tree->right);


	        if (leftDepth > rightDepth)
	            return(leftDepth + 1);
	        else return(rightDepth + 1);
	    }
	}

	/*
	if (newroot_ == nullptr)
		return -1;

	int leftDepth = getNodeDepth(newroot_->left);
	int rightDepth = getNodeDepth(newroot_->right);

	if ( leftDepth > rightDepth)
		return leftDepth + 1;
	return rightDepth + 1;
	*/

}

unsigned int BinarySearchTree::depth() const
{
	//if(size_ == 1)
		//return getNodeDepth(root_);
	//if (size_ == 1)
	//{
	//	return 0;
	//}
	return getNodeDepth(root_);
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


