#pragma once

#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "Stack.h"
#include "LinearList.h"
#include <iostream>

template<typename VALUE_TYPE, typename KEY_TYPE = int>
class AVL_Tree
{
public:
    struct Node
    {
        Node() : key_(KEY_TYPE()), info_(VALUE_TYPE()), left_(nullptr), right_(nullptr), balanceFactor_(0), height_(1) {}

        Node(KEY_TYPE key, VALUE_TYPE info, Node* left, Node* right) : key_(key), info_(info), left_(left), right_(right), balanceFactor_(0), height_(0) {}

        KEY_TYPE key_;
        VALUE_TYPE info_;
        Node* left_;
        Node* right_;
        int balanceFactor_;
        int height_;
    };

public:
    AVL_Tree();

    bool Empty() const;

    int Size() const;

    void Remove(KEY_TYPE key);

    void Insert(KEY_TYPE key, VALUE_TYPE info);

    Node* Search(KEY_TYPE key) const;

    Node& operator[] (KEY_TYPE key);

    Node At(KEY_TYPE key) const;

    Node* GetRoot() const;

    void CastToLinearList(LinearList<Node*>& list) const;

private:
    void InOrderTraversal(Node* root);

    void NonrecursiveInOrderTraversal();

    Node* RotateLeft(Node* root);

    Node* RotateRight(Node* root);

    bool InsertAlgorithm(Node*& root, KEY_TYPE key, VALUE_TYPE info);

    Node* GetMinValueNode(Node* const& node);

    Node* RecursiveRemove(Node* root, KEY_TYPE key);

    void InterchangeLeftMostNode(Node*& root, Node*& removeNode);

private:
    Node* root_;

    int size_;
};

template<typename VALUE_TYPE, typename KEY_TYPE>
inline AVL_Tree<VALUE_TYPE, KEY_TYPE>::AVL_Tree() : root_(nullptr), size_(0) {}

template<typename VALUE_TYPE, typename KEY_TYPE>
inline bool AVL_Tree<VALUE_TYPE, KEY_TYPE>::Empty() const
{
    return this->root_ == nullptr;
}

template<typename VALUE_TYPE, typename KEY_TYPE>
inline int AVL_Tree<VALUE_TYPE, KEY_TYPE>::Size() const
{
    return this->size_;
}

template<typename VALUE_TYPE, typename KEY_TYPE>
inline void AVL_Tree<VALUE_TYPE, KEY_TYPE>::Remove(KEY_TYPE key)
{
    try {
        this->root_ = this->RecursiveRemove(this->root_, key);
    }
    catch (const std::exception& ex) {
        std::cerr << ex.what();
    }
    this->size_ -= 1;
}

template<typename VALUE_TYPE, typename KEY_TYPE>
inline void AVL_Tree<VALUE_TYPE, KEY_TYPE>::Insert(KEY_TYPE key, VALUE_TYPE info)
{
    if (this->root_ == nullptr)
    {
        this->size_ += 1;
        this->root_ = new AVL_Tree<VALUE_TYPE, KEY_TYPE>::Node(key, info, nullptr, nullptr);
    }
    else
    {
        try
        {
            this->InsertAlgorithm(this->root_, key, info);
        }
        catch (const std::exception& ex)
        {
            std::cerr << ex.what();
        }

        this->size_ += 1;
    }
}

template<typename VALUE_TYPE, typename KEY_TYPE>
inline AVL_Tree<VALUE_TYPE, KEY_TYPE>::Node* AVL_Tree<VALUE_TYPE, KEY_TYPE>::Search(KEY_TYPE key) const
{
    AVL_Tree<VALUE_TYPE, KEY_TYPE>::Node* p = this->root_;
    while (p != nullptr && p->key_ != key)
    {
        if (p->key_ < key)
        {
            p = p->right_;
        }
        else
        {
            p = p->left_;
        }
    }
    return p;
}

template<typename VALUE_TYPE, typename KEY_TYPE>
inline AVL_Tree<VALUE_TYPE, KEY_TYPE>::Node& AVL_Tree<VALUE_TYPE, KEY_TYPE>::operator[](KEY_TYPE key)
{
    if (this->Empty())
    {
        throw std::logic_error("[ERROR] EMPTY TREE!");
    }

    Stack<AVL_Tree<VALUE_TYPE, KEY_TYPE>::Node*> stk;
    AVL_Tree<VALUE_TYPE, KEY_TYPE>::Node* currentNode = this->root_;
    while (true)
    {
        while (currentNode != nullptr)
        {
            stk.Push(currentNode);
            currentNode = currentNode->left_;
        }

        if (stk.Empty() == false)
        {
            currentNode = stk.Pop();
            // NODE MANIPULATION LOGIC PERFORM HERE ------

            if (currentNode->key_ == key)
            {
                return *currentNode;
            }

            //--------------------------------------------
            currentNode = currentNode->right_;
        }
        else
        {
            break;
        }
    }

    throw std::logic_error("[ERROR] KEY NOT EXIST IN TREE!\n");
}

template<typename VALUE_TYPE, typename KEY_TYPE>
inline AVL_Tree<VALUE_TYPE, KEY_TYPE>::Node AVL_Tree<VALUE_TYPE, KEY_TYPE>::At(KEY_TYPE key) const
{
    if (this->Empty())
    {
        throw std::logic_error("[ERROR] EMPTY TREE!");
    }

    Stack<AVL_Tree<VALUE_TYPE, KEY_TYPE>::Node*> stk;
    AVL_Tree<VALUE_TYPE, KEY_TYPE>::Node* currentNode = this->root_;
    while (true)
    {
        while (currentNode != nullptr)
        {
            stk.Push(currentNode);
            currentNode = currentNode->left_;
        }

        if (stk.Empty() == false)
        {
            currentNode = stk.Pop();
            // NODE MANIPULATION LOGIC PERFORM HERE ------

            if (currentNode->key_ == key)
            {
                return *currentNode;
            }

            //--------------------------------------------
            currentNode = currentNode->right_;
        }
        else
        {
            break;
        }
    }

    throw std::logic_error("[ERROR] KEY NOT EXIST IN TREE!\n");
}

template<typename VALUE_TYPE, typename KEY_TYPE>
inline AVL_Tree<VALUE_TYPE, KEY_TYPE>::Node* AVL_Tree<VALUE_TYPE, KEY_TYPE>::GetRoot() const
{
    return this->root_;
}

template<typename VALUE_TYPE, typename KEY_TYPE>
inline void AVL_Tree<VALUE_TYPE, KEY_TYPE>::CastToLinearList(LinearList<AVL_Tree<VALUE_TYPE, KEY_TYPE>::Node*>& list) const
{
    try {
        Stack <AVL_Tree<VALUE_TYPE, KEY_TYPE>::Node*> stk;
        AVL_Tree<VALUE_TYPE, KEY_TYPE>::Node* p = this->root_;
        while (true)
        {
            while (p != nullptr)
            {
                stk.Push(p);
                p = p->left_;
            }

            if (stk.Empty() == false)
            {
                p = stk.Pop();
                // NODE MANIPULATION LOGIC PERFORM HERE ------
                list.PushBack(p);
                //--------------------------------------------
                p = p->right_;
            }
            else
            {
                break;
            }
        }
    }
    catch (std::exception& ex) {
        std::cout << ex.what() << "\n";
    }
}

template<typename VALUE_TYPE, typename KEY_TYPE>
inline void AVL_Tree<VALUE_TYPE, KEY_TYPE>::InOrderTraversal(AVL_Tree<VALUE_TYPE, KEY_TYPE>::Node* root)
{
    if (root != nullptr)
    {
        this->InOrderTraversal(root->left_);
        // Do the work here!

        std::cout << root->info_ << " ";

        // -----------------
        this->InOrderTraversal(root->right_);
    }
}

template<typename VALUE_TYPE, typename KEY_TYPE>
inline void AVL_Tree<VALUE_TYPE, KEY_TYPE>::NonrecursiveInOrderTraversal()
{
    Stack <AVL_Tree<VALUE_TYPE, KEY_TYPE>::Node*> stk;
    AVL_Tree<VALUE_TYPE, KEY_TYPE>::Node* p = this->root_;
    while (true)
    {
        while (p != nullptr)
        {
            stk.Push(p);
            p = p->left_;
        }

        if (stk.Empty() == false)
        {
            p = stk.Pop();
            // NODE MANIPULATION LOGIC PERFORM HERE ------

            //--------------------------------------------
            p = p->right_;
        }
        else
        {
            break;
        }
    }
}

template<typename VALUE_TYPE, typename KEY_TYPE>
inline AVL_Tree<VALUE_TYPE, KEY_TYPE>::Node* AVL_Tree<VALUE_TYPE, KEY_TYPE>::RotateLeft(AVL_Tree<VALUE_TYPE, KEY_TYPE>::Node* root)
{
    if (root == nullptr)
    {
        throw std::logic_error("[ERROR] TREE IS EMPTY!\n");
        return nullptr;
    }

    if (root->right_ == nullptr)
    {
        throw std::logic_error("[ERROR] CANNOT ROTATE LEFT BECAUSE THERE IS NO RIGHT TREE!\n");
        return nullptr;
    }

    AVL_Tree<VALUE_TYPE, KEY_TYPE>::Node* p = root->right_;
    root->right_ = p->left_;
    p->left_ = root;

    return p;
}

template<typename VALUE_TYPE, typename KEY_TYPE>
inline AVL_Tree<VALUE_TYPE, KEY_TYPE>::Node* AVL_Tree<VALUE_TYPE, KEY_TYPE>::RotateRight(AVL_Tree<VALUE_TYPE, KEY_TYPE>::Node* root)
{
    if (root == nullptr)
    {
        throw std::logic_error("[ERROR] TREE IS EMPTY!\n");
        return nullptr;
    }

    if (root->left_ == nullptr)
    {
        throw std::logic_error("[ERROR] CANNOT ROTATE RIGHT BECAUSE THERE IS NO LEFT TREE!\n");
        return nullptr;
    }

    AVL_Tree<VALUE_TYPE, KEY_TYPE>::Node* s = root->left_;
    root->left_ = s->right_;
    s->right_ = root;

    return s;
}

template<typename VALUE_TYPE, typename KEY_TYPE>
inline bool AVL_Tree<VALUE_TYPE, KEY_TYPE>::InsertAlgorithm(AVL_Tree<VALUE_TYPE, KEY_TYPE>::Node*& root, KEY_TYPE key, VALUE_TYPE info)
{
    /*
     * currentNode represent the node which is being manipulated.
     * currentNodeParent is the parent node of the currentNode.
     * currentNodeChild is the child of the currentNode.
     * imbalancedNode is the node before the currentNode which can be an imbalanced node in the AVL Tree.
     * imbalancedNodeParent is the parent of the imbalancedNode.
     * imbalancedNodeChild is the child node of imbalancedNode which could be imbalanced in the AVL Tree.
    */

    AVL_Tree<VALUE_TYPE, KEY_TYPE>::Node* currentNode = root;
    AVL_Tree<VALUE_TYPE, KEY_TYPE>::Node* currentNodeParent = nullptr;
    AVL_Tree<VALUE_TYPE, KEY_TYPE>::Node* currentNodeChild = nullptr;
    AVL_Tree<VALUE_TYPE, KEY_TYPE>::Node* imbalancedNode = currentNode;
    AVL_Tree<VALUE_TYPE, KEY_TYPE>::Node* imbalancedNodeParent = nullptr;
    AVL_Tree<VALUE_TYPE, KEY_TYPE>::Node* imbalancedNodeChild = nullptr;

    int imbalancedFactor = 0;

    /*
    * We first find the parent node of the currentNode.
    * Fint the imbalancedNode, the parent of the imbalancedNode.
    */
    while (currentNode != nullptr)
    {
        //* If the parameterized key is similar with the currentNode's key, then the parameterized key is not valid.
        if (key == currentNode->key_)
        {
            throw std::logic_error("[ERROR] DUPLICATE KEY!");
            return false;
        }
        //* If the parameterized key is smaller than the currentNode's key, then we move to the left child tree of the currentNode.
        if (key < currentNode->key_)
        {
            currentNodeChild = currentNode->left_;
        }
        //* Otherwise we move to the right child tree of the currentNode.
        else
        {
            currentNodeChild = currentNode->right_;
        }

        //! This if statement logic can be rewrite.
        if (currentNodeChild != nullptr)
        {
            //* If the currentNode's child is an imbalanced node.
            if (currentNodeChild->balanceFactor_ != 0)
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
    currentNodeChild = new AVL_Tree<VALUE_TYPE, KEY_TYPE>::Node(key, info, nullptr, nullptr);
    currentNodeChild->left_ = currentNodeChild->right_ = nullptr;
    if (key < currentNodeParent->key_)
    {
        currentNodeParent->left_ = currentNodeChild;
    }
    else
    {
        currentNodeParent->right_ = currentNodeChild;
    }

    /*
     * We modify the balance factor of all the node between the imbalenced node and the currentNodeChild.
     * If they were to the left, then all the balance factor of them are 1 and -1 in the otherhand.
    */
    if (key < imbalancedNode->key_)
    {
        currentNode = imbalancedNode->left_;
    }
    else
    {
        currentNode = imbalancedNode->right_;
    }
    imbalancedNodeChild = currentNode;
    while (currentNode != currentNodeChild)
    {
        if (key < currentNode->key_)
        {
            currentNode->balanceFactor_ = 1;
            currentNode = currentNode->left_;
        }
        else
        {
            currentNode->balanceFactor_ = -1;
            currentNode = currentNode->right_;
        }
    }

    /*
     * Detecting the imbalanced direction, which means that the tree is left heavy or right heavy.
    */
    if (key < imbalancedNode->key_)
    {
        imbalancedFactor = 1; //* Left heavy
    }
    else
    {
        imbalancedFactor = -1; //* Right heavy
    }

    if (imbalancedNode->balanceFactor_ == 0)
    {
        imbalancedNode->balanceFactor_ = imbalancedFactor;
        return false;
    }

    if (imbalancedNode->balanceFactor_ != imbalancedFactor)
    {
        imbalancedNode->balanceFactor_ = 0;
        return false;
    }

    /*
     * After inserting a new node, if the tree is imbalanced, we will balance it again.
     * Case where we only need to rotate once.
    */
    if (imbalancedNodeChild->balanceFactor_ == imbalancedFactor)
    {
        //* Rotate right
        if (imbalancedFactor == 1)
        {
            currentNode = this->RotateRight(imbalancedNode);
        }
        //* rotate left
        else
        {
            currentNode = this->RotateLeft(imbalancedNode);
        }

        imbalancedNode->balanceFactor_ = 0;
        imbalancedNodeChild->balanceFactor_ = 0;
    }
    else //* Case where we need to rotate twice
    {
        if (imbalancedFactor == 1) //* Rotate Left and Right
        {
            imbalancedNode->left_ = this->RotateLeft(imbalancedNodeChild);
            currentNode = this->RotateRight(imbalancedNode);
        }
        else //* Rotate Right and Left
        {
            imbalancedNode->right_ = this->RotateRight(imbalancedNodeChild);
            currentNode = this->RotateLeft(imbalancedNode);
        }

        //* If p is the inserted node
        if (currentNode->balanceFactor_ == 0)
        {
            imbalancedNode->balanceFactor_ = 0;
            imbalancedNodeChild->balanceFactor_ = 0;
        }
        else
        {
            if (currentNode->balanceFactor_ == imbalancedFactor)
            {
                imbalancedNode->balanceFactor_ = -imbalancedFactor;
                imbalancedNodeChild->balanceFactor_ = 0;
            }
            else
            {
                imbalancedNode->balanceFactor_ = 0;
                imbalancedNodeChild->balanceFactor_ = imbalancedFactor;
            }
        }
        currentNode->balanceFactor_ = 0;
    }

    if (imbalancedNodeParent == nullptr)
    {
        root = currentNode;
    }
    else
    {
        if (imbalancedNode == imbalancedNodeParent->right_)
        {
            imbalancedNodeParent->right_ = currentNode;
        }
        else
        {
            imbalancedNodeParent->left_ = currentNode;
        }
    }

    return true;
}

template<typename VALUE_TYPE, typename KEY_TYPE>
inline AVL_Tree<VALUE_TYPE, KEY_TYPE>::Node* AVL_Tree<VALUE_TYPE, KEY_TYPE>::GetMinValueNode(AVL_Tree<VALUE_TYPE, KEY_TYPE>::Node* const& node)
{
    if (node == nullptr || node->left_ == nullptr)
    {
        return node;
    }

    return this->GetMinValueNode(node->left_);
}

template<typename VALUE_TYPE, typename KEY_TYPE>
inline AVL_Tree<VALUE_TYPE, KEY_TYPE>::Node* AVL_Tree<VALUE_TYPE, KEY_TYPE>::RecursiveRemove(AVL_Tree<VALUE_TYPE, KEY_TYPE>::Node* node, KEY_TYPE key)
{
    if (node == nullptr)
    {
        return node;
    }

    if (key < node->key_)
    {
        node->left_ = this->RecursiveRemove(node->left_, key);
    }
    else if (key > node->key_)
    {
        node->right_ = this->RecursiveRemove(node->right_, key);
    }
    else
    {
        if (node->left_ == nullptr)
        {
            AVL_Tree<VALUE_TYPE, KEY_TYPE>::Node* temp = node->right_;
            delete node;
            return temp;
        }
        else if (node->right_ == nullptr)
        {
            AVL_Tree<VALUE_TYPE, KEY_TYPE>::Node* temp = node->left_;
            delete node;
            return temp;
        }
        AVL_Tree<VALUE_TYPE, KEY_TYPE>::Node* temp = this->GetMinValueNode(node->right_);
        node->key_ = temp->key_;
        node->right_ = this->RecursiveRemove(node->right_, temp->key_);
    }

    if (node == nullptr)
    {
        return node;
    }

    if (node->left_ != nullptr && node->right_ != nullptr)
    {
        node->height_ = 1 + (node->left_->height_ > node->right_->height_ ? node->left_->height_ : node->right_->height_);
    }
    else if (node->left_ != nullptr && node->right_ == nullptr)
    {
        node->height_ = 1 + node->left_->height_;
    }
    else if (node->left_ == nullptr && node->right_ != nullptr)
    {
        node->height_ = 1 + node->right_->height_;
    }
    else
    {
        node->height_ = 1;
    }

    /*node->height_ = 1 + std::max(
        (node->left_ != nullptr ? node->left_->height_ : 0),
        (node->right_ != nullptr ? node->right_->height_ : 0)
    );*/

    if (node->balanceFactor_ > 1 && node->left_->balanceFactor_ >= 0)
    {
        return this->RotateRight(node);
    }

    if (node->balanceFactor_ < -1 && node->right_->balanceFactor_ <= 0)
    {
        return this->RotateLeft(node);
    }

    if (node->balanceFactor_ > 1 && node->left_->balanceFactor_ < 0)
    {
        node->left_ = this->RotateLeft(node->left_);
        return this->RotateRight(node);
    }

    if (node->balanceFactor_ < -1 && node->right_->balanceFactor_ > 0)
    {
        node->right_ = this->RotateRight(node->right_);
        return this->RotateLeft(node);
    }

    return node;
}

template<typename VALUE_TYPE, typename KEY_TYPE>
inline void AVL_Tree<VALUE_TYPE, KEY_TYPE>::InterchangeLeftMostNode(AVL_Tree<VALUE_TYPE, KEY_TYPE>::Node*& root, AVL_Tree<VALUE_TYPE, KEY_TYPE>::Node*& removeNode)
{
    if (root->left_ != nullptr)
    {
        this->InterchangeLeftMostNode(root->left_, removeNode);
    }
    else
    {
        removeNode->key_ = root->key_;
        removeNode->info_ = root->key_;
        removeNode = root;
        root = removeNode->right_;
    }
}


#endif // !AVL_TREE_H
