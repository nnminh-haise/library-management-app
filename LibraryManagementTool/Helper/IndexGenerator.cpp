#include "IndexGenerator.h"
#include <iostream>
#include <fstream>
#include <string>
#include <format>
#include <ctime>

namespace PRIVATE_DATA_STRUCTURE
{
    AVL_Tree::Node::Node()
    {
        this->key = -1;
        this->info = 0;
        this->balanceFactor = 0;
        this->left = this->right = nullptr;
    }

    AVL_Tree::Node::Node(int key, int info, int balanceFactor, Node* left, Node* right)
    {
        this->key = key;
        this->info = info;
        this->balanceFactor = balanceFactor;
        this->left = left;
        this->right = right;
    }

    AVL_Tree::AVL_Tree()
    {
        this->root = nullptr;
    }

    AVL_Tree::~AVL_Tree()
    {
        delete this->root;
    }

    bool AVL_Tree::Empty() const
    {
        return this->root == nullptr;
    }

    void AVL_Tree::Insert(int key, int info)
    {
        if (this->root == nullptr)
        {
            this->root = new Node(key, info, 0, nullptr, nullptr);
        }
        else
        {
            try
            {
                AVL_Tree::RecursiveInsert(this->root, key, info);
            }
            catch (const std::exception& ex)
            {
                std::cout << ex.what();
            }
        }
    }

    void AVL_Tree::InterchangeLeftMostNode(Pointer& root, Pointer& removeNode)
    {
        if (root->left != nullptr)
        {
            AVL_Tree::InterchangeLeftMostNode(root->left, removeNode);
        }
        else
        {
            removeNode->key = root->key;
            removeNode->info = root->key;
            removeNode = root;
            root = removeNode->right;
        }
    }

    void AVL_Tree::RemoveNode(int key)
    {
        if (this->root == nullptr)
        {
            throw std::logic_error(std::format("[ERROR] CANNOT FIND KEY {}\n", key));
        }
        else
        {
            if (key < this->root->key)
            {
                AVL_Tree::RemoveNode(key);
            }
            else if (key > this->root->key)
            {
                AVL_Tree::RemoveNode(key);
            }
            else
            {
                AVL_Tree::Pointer removeNode = this->root;
                if (removeNode->left == nullptr)
                {
                    this->root = removeNode->right;
                }
                else if (removeNode->right == nullptr)
                {
                    this->root = removeNode->left;
                }
                else
                {
                    InterchangeLeftMostNode(this->root, removeNode);
                }
                delete removeNode;
            }
        }
    }

    AVL_Tree::Pointer AVL_Tree::Search(int key)
    {
        AVL_Tree::Pointer p = root;
        while (p != nullptr && p->key != key)
        {
            if (p->key < key)
            {
                p = p->right;
            }
            else
            {
                p = p->left;
            }
        }
        return p;
    }

    AVL_Tree::Pointer AVL_Tree::RotateLeft(AVL_Tree::Pointer root)
    {
        if (root == nullptr)
        {
            throw std::logic_error("[ERROR] TREE IS EMPTY!\n");
            return nullptr;
        }

        if (root->right == nullptr)
        {
            throw std::logic_error("[ERROR] CANNOT ROTATE LEFT BECAUSE THERE IS NO RIGHT TREE!\n");
            return nullptr;
        }

        Pointer p = root->right;
        root->right = p->left;
        p->left = root;

        return p;
    }

    AVL_Tree::Pointer AVL_Tree::RotateRight(AVL_Tree::Pointer root)
    {
        if (root == nullptr)
        {
            throw std::logic_error("[ERROR] TREE IS EMPTY!\n");
            return nullptr;
        }

        if (root->left == nullptr)
        {
            throw std::logic_error("[ERROR] CANNOT ROTATE RIGHT BECAUSE THERE IS NO LEFT TREE!\n");
            return nullptr;
        }

        Pointer s = root->left;
        root->left = s->right;
        s->right = root;
        return s;
    }

    /**
     * This method is written in the non-recursive way!
    */
    bool AVL_Tree::RecursiveInsert(AVL_Tree::Pointer& root, int key, int info)
    {
        /*
         * currentNode represent the node which is being manipulated.
         * currentNodeParent is the parent node of the currentNode.
         * currentNodeChild is the child of the currentNode.
         * imbalancedNode is the node before the currentNode which can be an imbalanced node in the AVL Tree.
         * imbalancedNodeParent is the parent of the imbalancedNode.
         * imbalancedNodeChild is the child node of imbalancedNode which could be imbalanced in the AVL Tree.
        */

        AVL_Tree::Pointer currentNode = root;
        AVL_Tree::Pointer currentNodeParent = nullptr;
        AVL_Tree::Pointer currentNodeChild = nullptr;
        AVL_Tree::Pointer imbalancedNode = currentNode;
        AVL_Tree::Pointer imbalancedNodeParent = nullptr;
        AVL_Tree::Pointer imbalancedNodeChild = nullptr;

        int imbalancedFactor = 0;

        /*
        * We first find the parent node of the currentNode.
        * Fint the imbalancedNode, the parent of the imbalancedNode.
        */
        while (currentNode != nullptr)
        {
            //* If the parameterized key is similar with the currentNode's key, then the parameterized key is not valid.
            if (key == currentNode->key)
            {
                throw std::logic_error("[ERROR] DUPLICATE KEY!");
                return false;
            }
            //* If the parameterized key is smaller than the currentNode's key, then we move to the left child tree of the currentNode.
            if (key < currentNode->key)
            {
                currentNodeChild = currentNode->left;
            }
            //* Otherwise we move to the right child tree of the currentNode.
            else
            {
                currentNodeChild = currentNode->right;
            }

            //! This if statement logic can be rewrite.
            if (currentNodeChild != nullptr)
            {
                //* If the currentNode's child is an imbalanced node.
                if (currentNodeChild->balanceFactor != 0)
                {
                    imbalancedNodeParent = currentNode;
                    imbalancedNode = currentNodeChild;
                }
            }

            currentNodeParent = currentNode;
            currentNode = currentNodeChild;
        }

        /*
         * Add a new node with the parameterized key and info as a child node of the currentNodeParent.
        */
        currentNodeChild = new Node(key, info, 0, nullptr, nullptr);
        currentNodeChild->left = currentNodeChild->right = nullptr;
        if (key < currentNodeParent->key)
        {
            currentNodeParent->left = currentNodeChild;
        }
        else
        {
            currentNodeParent->right = currentNodeChild;
        }

        /*
         * We modify the balance factor of all the node between the imbalenced node and the currentNodeChild.
         * If they were to the left, then all the balance factor of them are 1 and -1 in the otherhand.
        */
        if (key < imbalancedNode->key)
        {
            currentNode = imbalancedNode->left;
        }
        else
        {
            currentNode = imbalancedNode->right;
        }
        imbalancedNodeChild = currentNode;
        while (currentNode != currentNodeChild)
        {
            if (key < currentNode->key)
            {
                currentNode->balanceFactor = 1;
                currentNode = currentNode->left;
            }
            else
            {
                currentNode->balanceFactor = -1;
                currentNode = currentNode->right;
            }
        }

        /*
         * Detecting the imbalanced direction, which means that the tree is left heavy or right heavy.
        */
        if (key < imbalancedNode->key)
        {
            imbalancedFactor = 1; //* Left heavy
        }
        else
        {
            imbalancedFactor = -1; //* Right heavy
        }

        if (imbalancedNode->balanceFactor == 0)
        {
            imbalancedNode->balanceFactor = imbalancedFactor;
            return false;
        }

        if (imbalancedNode->balanceFactor != imbalancedFactor)
        {
            imbalancedNode->balanceFactor = 0;
            return false;
        }

        /*
         * After inserting a new node, if the tree is imbalanced, we will balance it again.
         * Case where we only need to rotate once.
        */
        if (imbalancedNodeChild->balanceFactor == imbalancedFactor)
        {
            //* Rotate right
            if (imbalancedFactor == 1)
            {
                currentNode = AVL_Tree::RotateRight(imbalancedNode);
            }
            //* rotate left
            else
            {
                currentNode = AVL_Tree::RotateLeft(imbalancedNode);
            }

            imbalancedNode->balanceFactor = 0;
            imbalancedNodeChild->balanceFactor = 0;
        }
        else //* Case where we need to rotate twice
        {
            if (imbalancedFactor == 1) //* Rotate Left and Right
            {
                imbalancedNode->left = AVL_Tree::RotateLeft(imbalancedNodeChild);
                currentNode = AVL_Tree::RotateRight(imbalancedNode);
            }
            else //* Rotate Right and Left
            {
                imbalancedNode->right = AVL_Tree::RotateRight(imbalancedNodeChild);
                currentNode = AVL_Tree::RotateLeft(imbalancedNode);
            }

            //* If p is the inserted node
            if (currentNode->balanceFactor == 0)
            {
                imbalancedNode->balanceFactor = 0;
                imbalancedNodeChild->balanceFactor = 0;
            }
            else
            {
                if (currentNode->balanceFactor == imbalancedFactor)
                {
                    imbalancedNode->balanceFactor = -imbalancedFactor;
                    imbalancedNodeChild->balanceFactor = 0;
                }
                else
                {
                    imbalancedNode->balanceFactor = 0;
                    imbalancedNodeChild->balanceFactor = imbalancedFactor;
                }
            }
            currentNode->balanceFactor = 0;
        }

        if (imbalancedNodeParent == nullptr)
        {
            root = currentNode;
        }
        else
        {
            if (imbalancedNode == imbalancedNodeParent->right)
            {
                imbalancedNodeParent->right = currentNode;
            }
            else
            {
                imbalancedNodeParent->left = currentNode;
            }
        }

        return true;
    }

    int AVL_Tree::Size()
    {
        int counter = 0;
        Stack < AVL_Tree::Node* > stk;
        Pointer p = root;
        while (true)
        {
            while (p != nullptr)
            {
                stk.Push(p);
                p = p->left;
            }

            if (stk.Empty() == false)
            {
                p = stk.Pop();
                ++counter;
                p = p->right;
            }
            else
            {
                break;
            }
        }
        return counter;
    }

    void AVL_Tree::InOrderTraversal(AVL_Tree::Pointer root)
    {
        if (root != nullptr)
        {
            InOrderTraversal(root->left);
            std::cout << root->info << " ";
            InOrderTraversal(root->right);
        }
    }

    void AVL_Tree::NonrecursiveInOrderTraversal()
    {
        Stack < AVL_Tree::Node* > stk;
        Pointer p = root;
        while (true)
        {
            while (p != nullptr)
            {
                stk.Push(p);
                p = p->left;
            }

            if (stk.Empty() == false)
            {
                p = stk.Pop();
                // NODE MANIPULATION LOGIC PERFORM HERE ------

                //--------------------------------------------
                p = p->right;
            }
            else
            {
                break;
            }
        }
    }

    void AVL_Tree::ToArray(int*& arr, int& arrSize)
    {
        arrSize = this->Size();
        arr = new int[arrSize];

        Stack < AVL_Tree::Node* > stk;
        Pointer p = this->root;
        int index = 0;
        do
        {
            arr[index++] = p->info;

            if (p->right != nullptr)
            {
                stk.Push(p->right);
            }
            if (p->left != nullptr)
            {
                p = p->left;
            }
            else if (stk.Empty())
            {
                break;
            }
            else
            {
                p = stk.Pop();
            }
        } while (true);
    }

    void AVL_Tree::Print()
    {
        this->InOrderTraversal(this->root);
        std::cout << "\n";
    }
}

IndexGenerator::IndexGenerator(int amount)
{
    this->amount = amount;
    this->indicies = new int[amount];

    for (int i = 0; i < this->amount; ++i)
    {
        this->indicies[i] = -1;
    }
}

IndexGenerator::~IndexGenerator()
{
    delete[] this->indicies;
}

void IndexGenerator::Generate()
{
    for (int i = 0; i < this->amount; ++i)
    {
        this->indicies[i] = i + 1;
    }

    for (int i = 0; i < this->amount; ++i)
    {
        std::swap(this->indicies[i], this->indicies[rand() % (this->amount - i) + i]);
    }

    PRIVATE_DATA_STRUCTURE::AVL_Tree tree;

    for (int i = 0; i < this->amount; ++i)
    {
        tree.Insert(this->indicies[i], this->indicies[i]);
    }

    int* arr = nullptr;
    int arrSize;
    tree.ToArray(arr, arrSize);

    for (int i = 0; i < this->amount; ++i)
    {
        this->indicies[i] = arr[i];
    }

    delete[] arr;
}

void IndexGenerator::Print()
{
    for (int i = 0; i < this->amount; ++i)
    {
        std::cout << this->indicies[i] << " ";
    }
    std::cout << std::endl;
}

int IndexGenerator::operator[](int index)
{
    if (index < 0 || index >= this->amount)
    {
        throw std::logic_error("[ERROR] Index access out of scope!\n");
        exit(1);
    }
    return this->indicies[index];
}

void IndexGenerator::GetIndicies(int* arr, int& indexCount)
{
    arr = new int[this->amount];
    indexCount = amount;

    for (int i = 0; i < this->amount; ++i)
    {
        arr[i] = this->indicies[i];
    }
    indexCount = this->amount;
}

void IndexGenerator::ExportToFile(const std::string& filename)
{
    std::ofstream fileOut(filename, std::ofstream::out);

    if (!fileOut)
    {
        throw std::logic_error(std::format("[ERROR] Cannot open {}\n", filename));
        exit(1);
    }

    for (int i = 0; i < this->amount; ++i)
    {
        fileOut << this->indicies[i] << "\n";
    }

    fileOut.close();
}

void IndexGenerator::LogToFile(const std::string& filename)
{
    std::ofstream fileOut(filename, std::ofstream::binary);

    if (!fileOut)
    {
        throw std::logic_error(std::format("[ERROR] Cannot open {}\n", filename));
        exit(1);
    }

    for (int i = 0; i < this->amount; ++i)
    {
        fileOut.write((char*)&this->indicies[i], sizeof(this->indicies[i]));
    }

    fileOut.close();
}

void IndexGenerator::ImportFromFile(const std::string& filename)
{
    std::ifstream fileIn(filename, std::ifstream::binary);

    if (!fileIn)
    {
        throw std::logic_error(std::format("[ERROR] Cannot open {}\n", filename));
        exit(1);
    }

    for (int i = 0; i < this->amount; ++i)
    {
        fileIn.read((char*)&this->indicies[i], sizeof(this->indicies[i]));
    }
    fileIn.close();
}

int IndexGenerator::FromFileGetIndexAt(const std::string& filename, int index)
{
    std::ifstream fileIn(filename, std::ifstream::binary);

    if (!fileIn.is_open())
    {
        throw std::logic_error(std::format("[ERROR] Cannot open {}\n", filename));
        exit(1);
    }

    if (index < 0 || index >= this->amount)
    {
        throw std::logic_error(std::format("[ERROR] Cannot open {}\n", filename));
        exit(1);
    }

    int result = 0;

    fileIn.seekg(0, fileIn.end);
    long long fileSize = fileIn.tellg();
    fileIn.seekg(0, fileIn.beg);
    fileIn.seekg(index * sizeof(int));
    fileIn.read((char*)&result, sizeof(int));

    fileIn.close();

    return result;
}

