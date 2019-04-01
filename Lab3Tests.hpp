#ifndef LAB3_TESTS_HPP
#define LAB3_TESTS_HPP

#define ASSERT_TRUE(T) if (!(T)) return false;
#define ASSERT_FALSE(T) if ((T)) return false;

#include "PriorityQueue.hpp"
#include "BinarySearchTree.hpp"

// Libraries needed for BinarySearchTreeTest
#include <sstream>
#include <queue>

class PriorityQueueTest
{
public:
  bool test1()
  {
    PriorityQueue q(16);
    ASSERT_TRUE( q.empty() );
    ASSERT_TRUE( !q.full() );
    ASSERT_TRUE( q.size() == 0 );
    return true;
  }

  bool test2()
  {
    PriorityQueue q(2);
    ASSERT_TRUE( q.enqueue(10) );
    ASSERT_TRUE( !q.empty() );
    ASSERT_TRUE( !q.full() );
    ASSERT_TRUE( q.size() == 1 );
    ASSERT_TRUE( q.max() == 10 );

    ASSERT_TRUE( q.dequeue() );
    ASSERT_TRUE( q.empty() );
    ASSERT_TRUE( !q.full() );
    ASSERT_TRUE( q.size() == 0 );
    return true;
  }

  bool test3()
  {
    PriorityQueue q(3);
    ASSERT_TRUE( q.enqueue(5) );
    ASSERT_TRUE( q.max() == 5 );
    ASSERT_TRUE( q.enqueue(3) );
    ASSERT_TRUE( q.max() == 5 );
    ASSERT_TRUE( q.enqueue(4) );
    ASSERT_TRUE( q.max() == 5 );
    ASSERT_TRUE( q.full() );

    ASSERT_TRUE( !q.enqueue(7) );
    ASSERT_TRUE( q.max() == 5 );
    ASSERT_TRUE( q.full() );

    ASSERT_TRUE(test4());

    return true;
  }

  bool test4() {
	  cout << endl << endl << "TEST 4" << endl;
	  PriorityQueue q(10);

	  ASSERT_TRUE(q.empty());
	  ASSERT_TRUE(q.size() == 0);
	  ASSERT_TRUE(q.enqueue(69));
	  ASSERT_TRUE(q.max() == 69);
	  ASSERT_TRUE(q.enqueue(420));
	  ASSERT_TRUE(q.enqueue(10));
	  q.print();
	  ASSERT_TRUE(q.max() == 420);
	  ASSERT_TRUE(!q.full());
	  ASSERT_TRUE(q.size() == 3);
	  ASSERT_TRUE(q.dequeue());
	  ASSERT_TRUE(q.size() == 2);
	  q.print();
	  ASSERT_TRUE(q.max() == 69);

	  for (int i = 0; i < 8; i++) {
		  ASSERT_TRUE(q.enqueue(i*10));
	  }
	  q.print();
	  ASSERT_TRUE(q.max() == 70);
	  ASSERT_TRUE(!q.enqueue(42));
	  ASSERT_TRUE(q.full());
	  ASSERT_TRUE(q.size() == 10);

	  for (int i = 0; i < 10; i++) {
		  cout << endl;
		  q.print();
		  cout << q.dequeue() << "  ";
	  }

	  ASSERT_TRUE(q.empty());

	  cout << endl << "PASS TEST 4" << endl;
	  return true;
  }
};

class BinarySearchTreeTest
{
private:
  // Traverse the tree in level-order so we can check if it was constructed
  // properly. Output is as follows:
  //   "val1 val2 ... valN"
  // where vali is the value of node i, using level-order traversal.
  std::string level_order(BinarySearchTree::Node* root)
  {
    // If no nodes, return an empty string.
    if (root == NULL) {
      return "";
    }
    
    std::stringstream ss;
    std::queue<BinarySearchTree::Node*> node_queue;
    node_queue.push(root);
    while (!node_queue.empty()) {
      BinarySearchTree::Node* cur_node = node_queue.front();
      node_queue.pop();
      ss << cur_node->val << " ";
      if (cur_node->left != NULL) {
        node_queue.push(cur_node->left);
      }
      if (cur_node->right != NULL) {
        node_queue.push(cur_node->right);
      }
    }
    
    std::string level_order_str = ss.str();
    // There is a trailing space at the end of the string; return everything
    // before this.
    return level_order_str.substr(0, level_order_str.size() - 1);
  }

public:
  bool test1()
  {
    // We expect an empty tree at construction.
    std::string expected_tree_level_order = "";
    
    BinarySearchTree bst;
    ASSERT_TRUE(bst.root_ == NULL);
    ASSERT_TRUE(bst.size_ == 0 && bst.size() == 0);
    
    std::string tree_level_order = level_order(bst.root_);
    // Compare the tree's representation to the expected tree.
    ASSERT_TRUE(tree_level_order.compare(expected_tree_level_order) == 0)
    return true;
  }

  bool test2()
  {
    // We expect a single root node with value "5" after everything.
    std::string expected_tree_level_order = "5";
    
    BinarySearchTree bst;
    ASSERT_TRUE(bst.insert(5));
    ASSERT_TRUE(!bst.remove(4));
    ASSERT_TRUE(bst.exists(5));
    ASSERT_TRUE(bst.max() == bst.min() && bst.max() == 5);
    ASSERT_TRUE(bst.size() == 1);
    
    std::string tree_level_order = level_order(bst.root_);
    // Compare the tree's representation to the expected tree.
    ASSERT_TRUE(tree_level_order.compare(expected_tree_level_order) == 0)
    return true;
  }

  bool test3()
  {
    // We expect a 2-node tree at the end of this function -- root node 10 and
    // a child node with value 6.
    std::string expected_tree_level_order = "10 6";
    
    BinarySearchTree bst;
    ASSERT_TRUE(bst.insert(10));
    ASSERT_TRUE(bst.insert(8));
    ASSERT_TRUE(bst.size() == 2);
    ASSERT_TRUE(bst.insert(6));
    ASSERT_TRUE(bst.size() == 3);

    ASSERT_TRUE(bst.remove(8));
    ASSERT_TRUE(bst.size() == 2);
    
    std::string tree_level_order = level_order(bst.root_);
    // Compare the tree's representation to the expected tree.
    ASSERT_TRUE(tree_level_order.compare(expected_tree_level_order) == 0)

    ASSERT_TRUE(test4());

    return true;
  }

	bool test4() {
		BinarySearchTree bst;
		for (unsigned int i = 0; i < 10; i++) {
			ASSERT_TRUE(bst.insert(i * 10))
			ASSERT_TRUE(bst.depth() == i + 1);
		}
		ASSERT_TRUE(bst.root_->right == NULL);
		ASSERT_TRUE(bst.root_->left->val == 20);

		bst.print();

		ASSERT_TRUE(bst.max() == 90);
		ASSERT_TRUE(bst.min() == 0);
		ASSERT_TRUE(bst.depth() == 10);
		ASSERT_TRUE(bst.root_->val == 0);
		ASSERT_TRUE(bst.exists(20));
		ASSERT_TRUE(!bst.exists(25));
		ASSERT_TRUE(bst.getNodeDepth(bst.root_) == 1);
		ASSERT_TRUE(bst.size() == 10);
		ASSERT_TRUE(!bst.remove(45));
		ASSERT_TRUE(bst.remove(40));
		ASSERT_TRUE(!bst.exists(40));

		bst.print();

		for (int i = 0; i < 10; i++) {
			if (i != 4) {
				ASSERT_TRUE(bst.remove(i * 10));
				ASSERT_TRUE(bst.root_->val == (i + 1) * 10);
				if (i < 9) {
					ASSERT_TRUE(bst.min() == (i + 1) * 10);
					ASSERT_TRUE(bst.max() == 90);
				}
			} else {
				ASSERT_TRUE(!bst.remove(i * 10));
				ASSERT_TRUE(bst.root_->val == 50);
				ASSERT_TRUE(bst.min() == 50);
				ASSERT_TRUE(bst.max() == 90);
			}
		}
		bst.print();
		ASSERT_TRUE(bst.size() == 0);

		// increasing order now
		for (int i = 10; i >= 1; i++) {
			ASSERT_TRUE(bst.insert(i * 10))
			ASSERT_TRUE(bst.depth() == 11-i);
		}
		ASSERT_TRUE(bst.root_->left == NULL);
		ASSERT_TRUE(bst.root_->right->val == 90);
		bst.print();

		ASSERT_TRUE(bst.max() == 100);
		ASSERT_TRUE(bst.min() == 10);
		ASSERT_TRUE(bst.depth() == 10);
		ASSERT_TRUE(bst.root_->val == 100);
		ASSERT_TRUE(bst.exists(20));
		ASSERT_TRUE(!bst.exists(25));
		ASSERT_TRUE(bst.getNodeDepth(bst.root_) == 1);
		ASSERT_TRUE(bst.size() == 10);
		ASSERT_TRUE(!bst.remove(45));
		ASSERT_TRUE(bst.remove(40));
		ASSERT_TRUE(!bst.exists(40));

		for (int i = 10; i >= 1; i++) {
			if (i != 4) {
				ASSERT_TRUE(bst.remove(i * 10));
				ASSERT_TRUE(bst.root_->val == ((i-1) * 10));
				if (i > 1) {
					ASSERT_TRUE(bst.min() == 10);
					ASSERT_TRUE(bst.max() == (i-1)*10);
				}
			} else {
				ASSERT_TRUE(!bst.remove(i * 10));
				ASSERT_TRUE(bst.root_->val == 30);
				ASSERT_TRUE(bst.min() == 10);
				ASSERT_TRUE(bst.max() == 30);
			}
		}
		bst.print();
		ASSERT_TRUE(bst.size() == 0);

		// Add even tree tests now
		ASSERT_TRUE(bst.insert(41));
		ASSERT_TRUE(bst.depth() == 1);
		ASSERT_TRUE(bst.insert(20));
		ASSERT_TRUE(bst.depth() == 2);
		ASSERT_TRUE(bst.insert(11));
		ASSERT_TRUE(bst.depth() == 3);
		ASSERT_TRUE(bst.insert(29));
		ASSERT_TRUE(bst.depth() == 3);
		ASSERT_TRUE(bst.insert(32));
		ASSERT_TRUE(bst.depth() == 4);
		ASSERT_TRUE(bst.insert(65));
		ASSERT_TRUE(bst.depth() == 4);
		ASSERT_TRUE(bst.insert(50));
		ASSERT_TRUE(bst.depth() == 4);
		ASSERT_TRUE(bst.insert(91));
		ASSERT_TRUE(bst.depth() == 4);
		ASSERT_TRUE(bst.insert(72));
		ASSERT_TRUE(bst.depth() == 4);
		ASSERT_TRUE(bst.insert(99));
		ASSERT_TRUE(bst.depth() == 4);
		bst.print();

		ASSERT_TRUE(bst.size() == 10);
		ASSERT_TRUE(bst.max() == 99);
		ASSERT_TRUE(bst.min() == 11);
		ASSERT_TRUE(bst.root_->right->left->left == NULL);
		ASSERT_TRUE(bst.root_->left->left->left == NULL);
		ASSERT_TRUE(bst.remove(41));
		ASSERT_TRUE(bst.root_->val == 50);
		ASSERT_TRUE(bst.root_->right->val == 65);
		ASSERT_TRUE(bst.root_->left->val == 20);
		ASSERT_TRUE(bst.remove(50));
		ASSERT_TRUE(bst.depth == 3);
		ASSERT_TRUE(bst.root_->val == 65);
		ASSERT_TRUE(bst.root_->right->val == 91);
		ASSERT_TRUE(bst.root_->left->val == 20);
		ASSERT_TRUE(bst.root_->left->right->right->val == 32);
		ASSERT_TRUE(bst.root_->left->right->right->left == NULL);
		ASSERT_TRUE(bst.root_->left->right->right->right == NULL);
		ASSERT_TRUE(bst.getNodeDepth(bst.root_->left->right->right) == 4)

		cout << endl << endl << "PASSED TEST 4" << endl << endl;
		return true;
	}
};


#endif
