#pragma once

#include <string>

namespace PRIVATE_DATA_STRUCTURE
{
    template < typename T >
    class Stack
    {
    public:
        Stack();

        bool Empty();

        void Push(T info);

        T Pop();

    private:
        struct Node
        {
            T info;
            Node* next;

            Node();

            Node(T info, Node* next);
        };

        Node* top_;
    };


    template < typename T >
    inline Stack < T >::Node::Node(T info, Node* next)
    {
        this->info = info;
        this->next = next;
    }

    template < typename T >
    inline Stack < T >::Stack()
    {
        this->top_ = nullptr;
    }

    template < typename T >
    inline bool Stack < T >::Empty()
    {
        return this->top_ == nullptr;
    }

    template < typename T >
    inline void Stack < T >::Push(T info)
    {
        Stack::Node* newNode = new Stack::Node(info, this->top_);
        this->top_ = newNode;
    }

    template < typename T >
    inline T Stack < T >::Pop()
    {
        if (this->Empty())
        {
            return nullptr;
        }

        Stack::Node* removeNode = this->top_;
        this->top_ = removeNode->next;
        T returnInfo = removeNode->info;
        delete removeNode;
        return returnInfo;
    }


    class AVL_Tree
    {
    public:
        struct Node
        {
            int key;
            int info;
            int balanceFactor;
            Node* left;
            Node* right;

            Node();

            Node(int key, int info, int balanceFactor, Node* left, Node* right);
        };

        typedef Node* Pointer;

        AVL_Tree();

        ~AVL_Tree();

        bool Empty() const;

        int Size();

        void RemoveNode(int key);

        void Insert(int key, int info);

        Pointer Search(int key);

        void ToArray(int*& arr, int& arrSize);

        void Print();

    private:
        void InOrderTraversal(Pointer root);

        void NonrecursiveInOrderTraversal();

        Pointer RotateLeft(Pointer root);

        Pointer RotateRight(Pointer root);

        bool RecursiveInsert(Pointer& root, int key, int info);

        void InterchangeLeftMostNode(Pointer& root, Pointer& removeNode);

    private:
        Pointer root;
    };
}

class IndexGenerator
{
public:
    IndexGenerator(int amount);

    ~IndexGenerator();

    void Generate();

    void Print();

    int operator[] (int index);

    void GetIndicies(int* indicies, int& indexCount);

    void ExportToFile(const std::string& filename);

    void ImportFromFile(const std::string& filename);

    void LogToFile(const std::string& filename);

    int FromFileGetIndexAt(const std::string& filename, int index);

private:
    int* indicies;
    int amount;
};

