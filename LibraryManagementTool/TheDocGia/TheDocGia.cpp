#include "TheDocGia.h"
#include "../Helper/Helper.h"
#include "../DataStructures/Stack.h"

#include <string>
#include <iostream>
#include <fstream>
#include <format>
#include <ctime>

BOOK_CIRCULATION::BookCirculation::BookCirculation() {
	this->id = std::string();
	this->borrowDate = HELPER::Date();
	this->returnDate = HELPER::Date();
	this->status = BOOK_CIRCULATION::CirculationStatus::LOSTED;
}

BOOK_CIRCULATION::BookCirculation::BookCirculation(std::string id, HELPER::Date NgayMuon, HELPER::Date NgayTra, BOOK_CIRCULATION::CirculationStatus status) {
	this->id = id;
	this->borrowDate = NgayMuon;
	this->returnDate = NgayTra;
	this->status = status;
}

void BOOK_CIRCULATION::BookCirculation::SetID(std::string id) {
	this->id = id;
}

std::string BOOK_CIRCULATION::BookCirculation::GetID() {
	return this->id;
}

void BOOK_CIRCULATION::BookCirculation::SetBorrowDate(HELPER::Date NgayMuon) {
	this->borrowDate = NgayMuon;
}

HELPER::Date BOOK_CIRCULATION::BookCirculation::GetBorrowDate() {
	return this->borrowDate;
}

void BOOK_CIRCULATION::BookCirculation::SetReturnDate(HELPER::Date NgayTra) {
	this->returnDate = NgayTra;
}

HELPER::Date BOOK_CIRCULATION::BookCirculation::GetReturnDate() {
	return this->returnDate;
}

void BOOK_CIRCULATION::BookCirculation::SetStatus(BOOK_CIRCULATION::CirculationStatus status) {
	this->status = status;
}

BOOK_CIRCULATION::CirculationStatus BOOK_CIRCULATION::BookCirculation::GetStatus() {
	return this->status;
}

DOUBLE_LINKED_LIST::Node::Node() {
	this->info = BOOK_CIRCULATION::BookCirculation();
	this->left = this->right = nullptr;
}

DOUBLE_LINKED_LIST::Controller::Controller() {
	this->First = this->Last = nullptr;
}

void DOUBLE_LINKED_LIST::Initialize(Controller& list) {
	list.First = list.Last = nullptr;
}

bool DOUBLE_LINKED_LIST::IsEmpty(const Controller& list) {
	return list.First == nullptr;
}

int DOUBLE_LINKED_LIST::Size(const Controller& list) {
    int result = 0;
    for (DOUBLE_LINKED_LIST::Pointer p = list.First; p != nullptr; p = p->left) {
        ++result;
    }
    return result;
}

void DOUBLE_LINKED_LIST::ClearList(Controller& list) {
    DOUBLE_LINKED_LIST::Pointer p = list.First;
    while (p != nullptr) {
        DOUBLE_LINKED_LIST::Pointer deleteNode = p;
        p = deleteNode->right;
        delete deleteNode;
    }
    list.First = list.Last = nullptr;
}

READER::Reader::Reader() {
	this->id = -1;
	this->firstName = std::string();
	this->lastName = std::string();
	this->sex = READER::Sex::MALE;
	this->status = READER::ReaderStatus::BANNED;
	this->borrowedBooks = DOUBLE_LINKED_LIST::Controller();
}

READER::Reader::Reader(int MaThe, std::string Ho, std::string Ten, READER::Sex Phai, READER::ReaderStatus status, DOUBLE_LINKED_LIST::Controller DanhSachMuonTra) {
	this->id = MaThe;
	this->firstName = Ho;
	this->lastName = Ten;
	this->sex = Phai;
	this->status = status;
	this->borrowedBooks = DanhSachMuonTra;
}

void READER::Reader::SetID(int MaThe) {
	this->id = MaThe;
}

int READER::Reader::GetID() {
	return this->id;
}

void READER::Reader::SetFirstName(std::string Ho) {
	this->firstName = Ho;
}

std::string READER::Reader::GetFirstName() {
	return this->firstName;
}

void READER::Reader::SetLastName(std::string Ten) {
	this->lastName = Ten;
}

std::string READER::Reader::GetLastName() {
	return this->lastName;
}

void READER::Reader::SetSex(READER::Sex Phai) {
	this->sex = Phai;
}

READER::Sex READER::Reader::GetSex() {
	return this->sex;
}

std::string READER::Reader::GetFullName() {
    return this->firstName + " " + this->lastName;
}

std::string READER::Reader::StringfySex() {
    return (this->sex == READER::Sex::MALE ? "MALE" : "FEMALE");
}

void READER::Reader::SetStatus(READER::ReaderStatus status) {
	this->status = status;
}

READER::ReaderStatus READER::Reader::GetStatus() {
	return this->status;
}

std::string READER::Reader::StringfyStatus() {
    return (this->status == READER::ReaderStatus::BANNED ? "BI KHOA" : "HOAT DONG");
}

void READER::Reader::SetBorrowedBooks(DOUBLE_LINKED_LIST::Controller DanhSachMuonTra) {
	this->borrowedBooks = DanhSachMuonTra;
}

DOUBLE_LINKED_LIST::Controller READER::Reader::GetBorrowedBooks() {
	return this->borrowedBooks;
}

void READER::Reader::Log() {
	std::cerr << std::format("_____ THE DOC GIA _____\n");
	std::cerr << std::format("Ma the    : {}\n", this->id);
	std::cerr << std::format("firstName        : {}\n", this->firstName);
	std::cerr << std::format("lastName       : {}\n", this->lastName);
	std::cerr << std::format("sex      : {}\n", this->sex == READER::Sex::MALE ? "Nam" : "Nu");
	std::cerr << std::format("Trang thai: {}\n", this->status == READER::ReaderStatus::BANNED ? "Bi khoa" : "Hoat dong");
	if (DOUBLE_LINKED_LIST::IsEmpty(this->borrowedBooks)) {
		std::cerr << std::format("Doc gia chua muon sach!\n");
	}
	else {
		std::cerr << std::format("Doc gia co muon sach!\n");
	}
	std::cerr << std::format("-----------------------\n");
}

/*
* AVL Tree session start from below
*/

AVL_TREE::Node::Node() {
	this->info = READER::Reader();
	this->balanceFactor = 0;
	this->left = this->right = nullptr;
    this->height = 0;
}

int AVL_TREE::Node::GetKey() {
    return this->info.GetID();
}

void AVL_TREE::Node::SetKey(const int key) {
    this->info.SetID(key);
}

void AVL_TREE::Initialize(AVL_TREE::Pointer& node) {
	node = nullptr;
}

bool AVL_TREE::IsEmpty(AVL_TREE::Pointer const& node) {
	return node == nullptr;
}

void AVL_TREE::PreOrderTraversal(AVL_TREE::Pointer const& node) {
	if (node != nullptr) {
		std::cerr << node->info.GetID() << " ";
		AVL_TREE::PreOrderTraversal(node->left);
		AVL_TREE::PreOrderTraversal(node->right);
	}
}

void AVL_TREE::InOrderTraversal(AVL_TREE::Pointer const& node) {
	if (node != nullptr) {
		AVL_TREE::InOrderTraversal(node->left);
		std::cerr << node->info.GetID() << " ";
		AVL_TREE::InOrderTraversal(node->right);
	}
}

void AVL_TREE::PostOrderTraversal(AVL_TREE::Pointer const& node) {
	if (node != nullptr) {
		AVL_TREE::InOrderTraversal(node->left);
		AVL_TREE::InOrderTraversal(node->right);
		std::cerr << node->info.GetID() << " ";
	}
}

void AVL_TREE::CountNode(const AVL_TREE::Pointer& root, int& counter) {
    if (root != nullptr) {
        ++counter;
        AVL_TREE::CountNode(root->left, counter);
        AVL_TREE::CountNode(root->right, counter);
    }
}

void AVL_TREE::NonrecursiveInOrderTraversal(const AVL_TREE::Pointer& root) {
    STACK::Stack stk;
    STACK::Initialize(stk);

    AVL_TREE::Pointer p = root;

    do {
        while (p != nullptr) {
            STACK::Push(stk, p);
            p = p->left;
        }

        if (STACK::IsEmpty(stk) == false) {
            p = STACK::Pop(stk);
            p->info.Log();
            p = p->right;
        }
        else {
            break;
        }
    } while (true);
}

AVL_TREE::Pointer AVL_TREE::RotateLeft(AVL_TREE::Pointer root) {
    if (root == nullptr) {
        std::cerr << "[ERROR] TREE IS EMPTY!\n";
        return nullptr;
    }

    if (root->right == nullptr) {
        std::cerr << "[ERROR] CANNOT ROTATE LEFT BECAUSE THERE IS NO RIGHT TREE!\n";
        return nullptr;
    }

    AVL_TREE::Pointer p = root->right;
    root->right = p->left;
    p->left = root;

    return p;
}

AVL_TREE::Pointer AVL_TREE::RotateRight(AVL_TREE::Pointer root) {
    if (root == nullptr) {
        std::cerr << "[ERROR] TREE IS EMPTY!\n";
        return nullptr;
    }

    if (root->left == nullptr) {
        std::cerr << "[ERROR] CANNOT ROTATE RIGHT BECAUSE THERE IS NO LEFT TREE!\n";
        return nullptr;
    }

    AVL_TREE::Pointer s = root->left;
    root->left = s->right;
    s->right = root;
    return s;
}

/**
 * This method is written in the non-recursive way!
*/
bool AVL_TREE::Insert(AVL_TREE::Pointer& root, READER::Reader info) {

    /*
     * currentNode represent the node which is being manipulated.
     * currentNodeParent is the parent node of the currentNode.
     * currentNodeChild is the child of the currentNode.
     * imbalancedNode is the node before the currentNode which can be an imbalanced node in the AVL Tree.
     * imbalancedNodeParent is the parent of the imbalancedNode.
     * imbalancedNodeChild is the child node of imbalancedNode which could be imbalanced in the AVL Tree.
    */

    AVL_TREE::Pointer currentNode = root;
    AVL_TREE::Pointer currentNodeParent = nullptr;
    AVL_TREE::Pointer currentNodeChild = nullptr;
    AVL_TREE::Pointer imbalancedNode = currentNode;
    AVL_TREE::Pointer imbalancedNodeParent = nullptr;
    AVL_TREE::Pointer imbalancedNodeChild = nullptr;

    int imbalancedFactor = 0;

    /*
    * We first find the parent node of the currentNode.
    * Fint the imbalancedNode, the parent of the imbalancedNode.
    */
    while (currentNode != nullptr) {

        //* If the parameterized key is similar with the currentNode's key, then the parameterized key is not valid.
        if (info.GetID() == currentNode->GetKey()) {
            return false;
        }

        //* If the parameterized key is smaller than the currentNode's key, then we move to the left child tree of the currentNode.
        if (info.GetID() < currentNode->GetKey()) {
            currentNodeChild = currentNode->left;
        }
        //* Otherwise we move to the right child tree of the currentNode.
        else {
            currentNodeChild = currentNode->right;
        }

        //! This if statement logic can be rewrite.
        if (currentNodeChild != nullptr) {
            //* If the currentNode's child is an imbalanced node.
            if (currentNodeChild->balanceFactor != 0) {
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
    currentNodeChild = new AVL_TREE::Node;
    currentNodeChild->info = info;
    currentNodeChild->left = currentNodeChild->right = nullptr;
    if (info.GetID() < currentNodeParent->GetKey()) {
        currentNodeParent->left = currentNodeChild;
    }
    else {
        currentNodeParent->right = currentNodeChild;
    }

    /*
     * We modify the balance factor of all the node between the imbalanced node and the currentNodeChild.
     * If they were to the left, then all the balance factor of them are 1 and -1 in the otherhand.
    */
    if (info.GetID() < imbalancedNode->GetKey()) {
        currentNode = imbalancedNode->left;
    }
    else {
        currentNode = imbalancedNode->right;
    }
    imbalancedNodeChild = currentNode;

    while (currentNode != currentNodeChild) {
        if (info.GetID() < currentNode->GetKey()) {
            currentNode->balanceFactor = 1;
            currentNode = currentNode->left;
        }
        else {
            currentNode->balanceFactor = -1;
            currentNode = currentNode->right;
        }
    }

    /*
     * Detecting the imbalanced direction, which means that the tree is left heavy or right heavy.
    */
    if (info.GetID() < imbalancedNode->GetKey()) {
        imbalancedFactor = 1; //* Left heavy
    }
    else {
        imbalancedFactor = -1; //* Right heavy
    }

    if (imbalancedNode->balanceFactor == 0) {
        imbalancedNode->balanceFactor = imbalancedFactor;
        return false;
    }

    if (imbalancedNode->balanceFactor != imbalancedFactor) {
        imbalancedNode->balanceFactor = 0;
        return false;
    }

    /*
     * After inserting a new node, if the tree is imbalanced, we will balance it again.
     * Case where we only need to rotate once.
    */
    if (imbalancedNodeChild->balanceFactor == imbalancedFactor) {

        //* Rotate right
        if (imbalancedFactor == 1) {
            currentNode = AVL_TREE::RotateRight(imbalancedNode);
        }
        //* rotate left
        else {
            currentNode = AVL_TREE::RotateLeft(imbalancedNode);
        }

        imbalancedNode->balanceFactor = 0;
        imbalancedNodeChild->balanceFactor = 0;
    }
    //* Case where we need to rotate twice
    else {
        //* Rotate Left and Right
        if (imbalancedFactor == 1) {
            imbalancedNode->left = AVL_TREE::RotateLeft(imbalancedNodeChild);
            currentNode = AVL_TREE::RotateRight(imbalancedNode);
        }
        //* Rotate Right and Left
        else {
            imbalancedNode->right = AVL_TREE::RotateRight(imbalancedNodeChild);
            currentNode = AVL_TREE::RotateLeft(imbalancedNode);
        }

        //* If p is the inserted node
        if (currentNode->balanceFactor == 0) {
            imbalancedNode->balanceFactor = 0;
            imbalancedNodeChild->balanceFactor = 0;
        }
        else {
            if (currentNode->balanceFactor == imbalancedFactor) {
                imbalancedNode->balanceFactor = -imbalancedFactor;
                imbalancedNodeChild->balanceFactor = 0;
            }
            else {
                imbalancedNode->balanceFactor = 0;
                imbalancedNodeChild->balanceFactor = imbalancedFactor;
            }
        }
        currentNode->balanceFactor = 0;
    }

    if (imbalancedNodeParent == nullptr) {
        root = currentNode;
    }
    else {
        if (imbalancedNode == imbalancedNodeParent->right) {
            imbalancedNodeParent->right = currentNode;
        }
        else {
            imbalancedNodeParent->left = currentNode;
        }
    }

    return true;
}

AVL_TREE::Pointer AVL_TREE::SearchByKey(const AVL_TREE::Pointer& root, const int& key) {
    AVL_TREE::Pointer p = root;

    while (p != nullptr && p->GetKey() != key) {
        if (p->GetKey() < key) {
            p = p->right;
        }
        else {
            p = p->left;
        }
    }
    return p;
}

AVL_TREE::Pointer AVL_TREE::GetMinValueNode(AVL_TREE::Pointer const& node) {
    if (node == nullptr || node->left == nullptr) {
        return node;
    }

    return AVL_TREE::GetMinValueNode(node->left);
}

AVL_TREE::Pointer AVL_TREE::RemoveNode(AVL_TREE::Pointer& node, const int& key) {
    if (node == nullptr) {
        return node;
    }

    if (key < node->GetKey()) {
        node->left = AVL_TREE::RemoveNode(node->left, key);
    }
    else if (key > node->GetKey()) {
        node->right = AVL_TREE::RemoveNode(node->right, key);
    }
    else {
        if (node->left == nullptr) {
            AVL_TREE::Pointer temp = node->right;
            delete node;
            return temp;
        }
        else if (node->right == nullptr) {
            AVL_TREE::Pointer temp = node->left;
            delete node;
            return temp;
        }
        AVL_TREE::Pointer temp = AVL_TREE::GetMinValueNode(node->right);
        node->SetKey(temp->GetKey());
        node->right = AVL_TREE::RemoveNode(node->right, temp->GetKey());
    }

    if (node == nullptr) {
        return node;
    }

    node->height = 1 + max(
        (node->left != nullptr ? node->left->height : 0),
        (node->right != nullptr ? node->right->height : 0)
    );

    if (node->balanceFactor > 1 && node->left->balanceFactor >= 0) {
        return AVL_TREE::RotateRight(node);
    }

    if (node->balanceFactor < -1 && node->right->balanceFactor <= 0) {
        return AVL_TREE::RotateLeft(node);
    }

    if (node->balanceFactor > 1 && node->left->balanceFactor < 0) {
        node->left = AVL_TREE::RotateLeft(node->left);
        return AVL_TREE::RotateRight(node);
    }

    if (node->balanceFactor < -1 && node->right->balanceFactor > 0) {
        node->right = AVL_TREE::RotateRight(node->right);
        return AVL_TREE::RotateLeft(node);
    }

    return node;
}

/**
* The function will extract the data string and return an object pointer.
*/
bool READER_MODULES::TheDocGiaExtractor(std::string data, std::string separator, READER::Reader& returnData) {
	if (data.length() == 0) {
		return false;
	}

	int indicator = 0;
	size_t pos = 0;

	while ((pos = data.find(separator)) != std::string::npos) {
		std::string extractedData = data.substr(0, pos);
		if (extractedData.length() == 0) {
			continue;
		}

		switch (indicator++) {
		case (0): {
            returnData.SetID(std::stoi(extractedData));
			break;
		}
		case (1): {
            returnData.SetFirstName(extractedData);
			break;
		}
		case (2): {
            returnData.SetLastName(extractedData);
			break;
		}
		case (3): {
            returnData.SetSex(extractedData == "0" ? READER::Sex::MALE : READER::Sex::FEMALE);
			break;
		}
		case (4): {
            returnData.SetStatus(extractedData == "0" ? READER::ReaderStatus::BANNED : READER::ReaderStatus::ACTIVE);
			break;
		}
		}
		data.erase(0, pos + separator.length());
	}

	if (data.length() == 0) {
        returnData.SetBorrowedBooks(DOUBLE_LINKED_LIST::Controller());
		return true;
	}

	int muonTraCount = std::stoi(data);
	if (muonTraCount == 0) {
        returnData.SetBorrowedBooks(DOUBLE_LINKED_LIST::Controller());
	}
	else {
		/**
        * Currently this session is for LOADING @borrowedBooks from file based database.
        * todo: update database and write these code.
        */
	}

	return true;
}

/**
* READ DATA FROM FILE BASED DATABASE!
*
* 1. Create a file buffer reader.
* 2. Filter out the case where we cannot open the file!
*/
bool READER_MODULES::LoadDanhSachTheDocGiaFromDB(std::string filename, AVL_TREE::Pointer& tree) {

    //time_t startPoint = time(0);

    std::filebuf databaseBuffer{};

	if (!databaseBuffer.open(filename, std::ios::in)) {
		std::cerr << std::format("[ERROR] Can not open file {}\n", filename);
		return false;
	}

	std::istream database(&databaseBuffer);
    bool processResult = true;
    int attributeCount = 0;
	while (database) {
        std::string line{};
		std::getline(database, line);
        READER::Reader newTheDocGia{};
		bool result = READER_MODULES::TheDocGiaExtractor(line, ", ", newTheDocGia);
		if (result) {
            ++attributeCount;
            //newTheDocGia.Log();

            //* If the tree is empty, then directly insert to the tree
            if (AVL_TREE::IsEmpty(tree)) {
                AVL_TREE::Pointer firstNode = new AVL_TREE::Node();
                firstNode->info = newTheDocGia;
                tree = firstNode;
            }
            //* Otherwise, we use the algorithm to insert a new Node to the tree and balanced the tree.
            else {
                AVL_TREE::Insert(tree, newTheDocGia);
            }
		}
	}
	databaseBuffer.close();

    //time_t endPoint = time(0);
    //std::cerr << std::format("Record count: {}\n", recordCount);
    //std::cerr << std::format("performance : {}s\n", ((double)(endPoint - startPoint)) / CLOCKS_PER_SEC);

	return processResult;
}

bool READER_MODULES::UpdateListToDatabase(const std::string& filename, AVL_TREE::Pointer& tree) {

    std::filebuf databaseBuffer{};

    if (!databaseBuffer.open(filename, std::ios::out)) {
        std::cerr << std::format("[ERROR] Can not open file {}\n", filename);
        return false;
    }

    std::ostream database(&databaseBuffer);

    STACK::Stack stk;
    STACK::Initialize(stk);

    AVL_TREE::Pointer p = tree;

    do {
        while (p != nullptr) {
            STACK::Push(stk, p);
            p = p->left;
        }

        if (STACK::IsEmpty(stk) == false) {
            p = STACK::Pop(stk);
            
            database << p->info.GetID() << ", ";
            database << p->info.GetFirstName() << ", ";
            database << p->info.GetLastName() << ", ";
            database << (p->info.StringfySex() == "MALE" ? 0 : 1) << ", ";
            database << (p->info.StringfyStatus() == "THE BI KHOA" ? 0 : 1) << ", ";

            if (DOUBLE_LINKED_LIST::IsEmpty(p->info.GetBorrowedBooks())) {
                database << 0;
            }
            else {
                int listSize = DOUBLE_LINKED_LIST::Size(p->info.GetBorrowedBooks());
                database << listSize;
            }
            database << "\n";

            p = p->right;
        }
        else {
            break;
        }
    } while (true);

    databaseBuffer.close();
    return true;
}

int READER_MODULES::GetIndex(const std::string& filename, AVL_TREE::Pointer& tree) {
    std::filebuf databaseBuffer{};

    if (!databaseBuffer.open(filename, std::ios::in)) {
        std::cerr << std::format("[ERROR] Can not open file {}\n", filename);
        return false;
    }

    int attributeCount = 0;
    AVL_TREE::CountNode(tree, attributeCount);
    std::istream database(&databaseBuffer);

    for (int i = 0, tmp = 0; i < attributeCount; ++i, database >> tmp);
    std::string nextIndex{};
    database >> nextIndex;

    databaseBuffer.close();
    return std::stoi(nextIndex);
}

/*
* The algorithm is that we first create an array contains the pointer of all the node of the tree.
* Then we sort the array by comparing the value which the pointer pointed to and interchange the position of the element in the array
* without changing the positon of the node of the tree.
* 
! Currently, Selection sort is used! Therefore the time complexcity if very high!
*/
void READER_MODULES::SortByName(AVL_TREE::Pointer const& node, AVL_TREE::Pointer*& pointerArr, int& arrSize) {
    
    //* If the array is empty at first, then create the array.
    AVL_TREE::CountNode(node, arrSize);
    pointerArr = new AVL_TREE::Pointer[arrSize];

    //* Create an array containing the pointer.
    STACK::Stack stk;
    STACK::Initialize(stk);
    AVL_TREE::Pointer p = node;
    int index = 0;
    do {
        while (p != nullptr) {
            STACK::Push(stk, p);
            p = p->left;
        }

        if (STACK::IsEmpty(stk) == false) {
            p = STACK::Pop(stk);
            pointerArr[index++] = p;
            p = p->right;
        }
        else {
            break;
        }
    } while (true);

    for (int i = 0; i < arrSize - 1; ++i) {
        for (int j = i + 1; j < arrSize; ++j) {
            const std::string& valueA = pointerArr[i]->info.GetLastName() + pointerArr[i]->info.GetFirstName();
            const std::string& valueB = pointerArr[j]->info.GetLastName() + pointerArr[j]->info.GetFirstName();

            if (valueA.compare(valueB) > 0) {
                std::swap(pointerArr[i], pointerArr[j]);
            }
        }
    }
}

int BOOK_CIRCULATION_MODULES::CountBorrowedBooks(const DOUBLE_LINKED_LIST::Controller& list) {
    int counter = 0;
    for (DOUBLE_LINKED_LIST::Pointer p = list.First; p != nullptr; p = p->right) {
        if (p->info.GetStatus() == BOOK_CIRCULATION::CirculationStatus::BORROWED) {
            ++counter;
        }
    }
    return counter;
}
