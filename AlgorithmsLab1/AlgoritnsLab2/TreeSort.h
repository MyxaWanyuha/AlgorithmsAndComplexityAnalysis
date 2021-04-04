#pragma once
#include <vector>
template<typename T>
class TreeSort
{
public:
    static void treeSort(std::vector<T>& arr)
    {
        Node* root = nullptr;
        root = insert(root, arr[0]);

        const auto len = arr.size();
        for (int i = 1; i < len; i++)
            root = insert(root, arr[i]);
        
        uint32_t i = 0;
        storeSorted(root, arr, i);
        delete root;
    }
private:
    struct Node
    {
        Node(T item)
            : key(item) {};
        T key;
        Node* left = nullptr; 
        Node* right = nullptr;
        ~Node()
        {
            if (left)
                delete left;
            if (right)
                delete right;
        }
    };

    static void storeSorted(Node* root, std::vector<T>& arr, uint32_t& i)
    {
        if (root != nullptr)
        {
            storeSorted(root->left, arr, i);
            arr[i++] = root->key;
            storeSorted(root->right, arr, i);
        }
    }

    static Node* insert(Node* node, T key)
    {
        if (node == nullptr) 
            return new Node(key);

        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);

        return node;
    }
};
