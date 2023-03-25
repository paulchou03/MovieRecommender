#ifndef TREEMULTIMAP_INCLUDED
#define TREEMULTIMAP_INCLUDED

#include <string>
#include <vector>
#include <iostream>
using namespace std;

template <typename KeyType, typename ValueType>
class TreeMultimap
{
public:
    class Iterator
    {
    public:
        Iterator()
        { //Invalid condition
            iter = nullptr;
            counter = 0;
        }
        Iterator(vector<ValueType>& itvalue)
        {
            //Valid condition
            iter = &itvalue[0]; //Sets iterator to point to the first item of the vector value list
            counter = 1;
            maxsize = itvalue.size();
        }

        ValueType& get_value() const
        {
            return (*iter);  
        }

        bool is_valid() const
        {
            if (iter == nullptr && counter == 0) //When invalid
            {
                return false;
            }
            if (counter > maxsize) //When counter is greater than the maxsize of the vector
                return false;
            else
            {
                return true;  //When valid
            }
        }

        void advance()
        {
            iter += 1; 
            counter++;
        }

    private:
        ValueType* iter;
        int counter;
        int maxsize;

    };

    TreeMultimap()
    {
        root = nullptr; //Sets root to nullptr
    }

    ~TreeMultimap()
    {
        Node* cur = root;
        deleteTree(cur); //Calls destructor helper function
        
    }

    void insert(const KeyType& key, const ValueType& value)
    {
        if (root == nullptr) //If tree is empty, make a new node and pushback the value to that node
        {
            root = new Node(key, value);
            root->itvalue.push_back(value);
            return;
        }
        Node* cur = root;
        for (;;)
        {
            if (key == cur->key) //If cur pointer points to the same key as the key of the node
            {
                cur->itvalue.push_back(value); //Add value to the vector
                return;
            }
            if (key < cur->key) //If the key is less than the key cur points to
            {
                if (cur->left != nullptr) //If left child node is not empty
                    cur = cur->left; //Set cur to left child node
                else
                {
                    cur->left = new Node(key, value); //Make a new node
                    cur->left->itvalue.push_back(value); //Push_back value to the node
                    return;
                }
            }
            else if (key > cur->key) //If the key is greater than the key cur points to
            {
                if (cur->right != nullptr) //If right child node is not empty
                    cur = cur->right; //Set cur to right child node
                else
                {
                    cur->right = new Node(key, value); //Make a new node
                    cur->right->itvalue.push_back(value); //Push_back value to the node
                    return;
                }
            }

        }
    }

    Iterator find(const KeyType& key) const
    {
        if (root == nullptr)
        {
            return Iterator(); //Invalid
        }
        Node* cur = root;
        while (cur != nullptr)
        {
            if (key == cur->key)
                return Iterator(cur->itvalue); //Valid
            if (key < cur->key)
                cur = cur->left;
            else
                cur = cur->right;
        }
        return Iterator(); //Invalid
    }

private:
    struct Node //Node initialization
    {
        Node(KeyType keyval, ValueType somevalue)
        {
            value = somevalue;
            key = keyval;
            right = nullptr;
            left = nullptr;
        }
        ValueType value;
        KeyType key;
        Node* left;
        Node* right;
        vector<ValueType> itvalue;
    };
    Node* root;

    void deleteTree(Node* cur) //Recursively deletes the nodes of the tree by doing a depth search
    {
        if (cur == nullptr)
            return;
        deleteTree(cur->left);
        deleteTree(cur->right);
        delete cur;
    }
};

#endif // TREEMULTIMAP_INCLUDED