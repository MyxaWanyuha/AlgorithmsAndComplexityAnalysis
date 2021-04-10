#pragma once
#include <string>
class TreeSortClass
{
public:
    uint32_t operator()(std::string& arr)
    {
        if (arr.size() < 2) return arr.size();

        uint32_t count = 0;
        Node* root = nullptr;
        root = insert(root, arr[0], count);

        for (size_t i = 1; i < arr.size(); i++)
            root = insert(root, arr[i], count);

        int i = 0;
        storeSorted(root, arr, i, count);
        delete root;

        return count;
    }
private:
    struct Node
    {
        Node(char item)
            : key(item) {};
        ~Node()
        {
            delete left;
            delete right;
        }
        char key;
        Node* left = nullptr;
        Node* right = nullptr;
    };
    static void storeSorted(Node* root, std::string& arr, int& i, uint32_t& count)
    {
        ++count;
        if (root != nullptr)
        {
            storeSorted(root->left, arr, i, count);
            arr[i++] = root->key;
            storeSorted(root->right, arr, i, count);
        }
    }
    static Node* insert(Node* node, char key, uint32_t& count)
    {
        ++count;
        if (node == nullptr) 
            return new Node(key);

        if (key < node->key)
            node->left = insert(node->left, key, count);
        else if (key > node->key)
            node->right = insert(node->right, key, count);

        return node;
    }
};

TreeSortClass TreeSort;
