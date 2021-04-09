#pragma once
#include <string>
class TreeSort
{
public:
    static uint32_t treeSort(std::string& arr)
    {
        if (arr.size() < 2) return arr.size();

<<<<<<< HEAD
        uint32_t count = 0;
        Node* root = insert(root, arr[0], count);

        for (int i = 1; i < arr.size(); i++)
            root = insert(root, arr[i], count);

        int i = 0;
        storeSorted(root, arr, i, count);
        delete root;

        return count;
=======
        const auto len = arr.size();
        for (int i = 1; i < len; i++)
            root = insert(root, arr[i]);
        
        uint32_t i = 0;
        storeSorted(root, arr, i);
        delete root;
>>>>>>> a5d95d9e29be46534b658b982ccb90c3d4e5a4e2
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
        ~Node()
        {
            if (left)
                delete left;
            if (right)
                delete right;
        }
    };

<<<<<<< HEAD
    static void storeSorted(Node* root, std::string& arr, int& i, uint32_t& count)
=======
    static void storeSorted(Node* root, std::vector<T>& arr, uint32_t& i)
>>>>>>> a5d95d9e29be46534b658b982ccb90c3d4e5a4e2
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
<<<<<<< HEAD
        ++count;
=======
>>>>>>> a5d95d9e29be46534b658b982ccb90c3d4e5a4e2
        if (node == nullptr) 
            return new Node(key);

        if (key < node->key)
            node->left = insert(node->left, key, count);
        else if (key > node->key)
            node->right = insert(node->right, key, count);

        return node;
    }
};
