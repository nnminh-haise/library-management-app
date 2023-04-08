#include "TheDocGia.h"
#include "../Helper/Helper.h"
#include "../DataStructures/Stack.h"

#include <string>
#include <iostream>
#include <fstream>
#include <format>
#include <ctime>

MUON_TRA::MuonTra::MuonTra() {
	this->MaSach = std::string();
	this->NgayMuon = HELPER::Date();
	this->NgayTra = HELPER::Date();
	this->TrangThai = MUON_TRA::TrangThaiMuonTra::SACH_BI_MAT;
}

MUON_TRA::MuonTra::MuonTra(std::string MaSach, HELPER::Date NgayMuon, HELPER::Date NgayTra, MUON_TRA::TrangThaiMuonTra TrangThai) {
	this->MaSach = MaSach;
	this->NgayMuon = NgayMuon;
	this->NgayTra = NgayTra;
	this->TrangThai = TrangThai;
}

void MUON_TRA::MuonTra::SetMaSach(std::string MaSach) {
	this->MaSach = MaSach;
}

std::string MUON_TRA::MuonTra::GetMaSach() {
	return this->MaSach;
}

void MUON_TRA::MuonTra::SetNgayMuon(HELPER::Date NgayMuon) {
	this->NgayMuon = NgayMuon;
}

HELPER::Date MUON_TRA::MuonTra::GetNgayMuon() {
	return this->NgayMuon;
}

void MUON_TRA::MuonTra::SetNgayTra(HELPER::Date NgayTra) {
	this->NgayTra = NgayTra;
}

HELPER::Date MUON_TRA::MuonTra::GetNgayTra() {
	return this->NgayTra;
}

void MUON_TRA::MuonTra::SetTrangThai(MUON_TRA::TrangThaiMuonTra TrangThai) {
	this->TrangThai = TrangThai;
}

MUON_TRA::TrangThaiMuonTra MUON_TRA::MuonTra::GetTrangThai() {
	return this->TrangThai;
}

DOUBLE_LINKED_LIST::Node::Node() {
	this->info = MUON_TRA::MuonTra();
	this->left = this->right = nullptr;
}

DOUBLE_LINKED_LIST::Controler::Controler() {
	this->First = this->Last = nullptr;
}

void DOUBLE_LINKED_LIST::Initialize(Controler& list) {
	list.First = list.Last = nullptr;
}

bool DOUBLE_LINKED_LIST::IsEmpty(const Controler& list) {
	return list.First == nullptr;
}

THE_DOC_GIA::TheDocGia::TheDocGia() {
	this->MaThe = -1;
	this->Ho = std::string();
	this->Ten = std::string();
	this->Phai = THE_DOC_GIA::GioiTinh::NAM;
	this->TrangThai = THE_DOC_GIA::TrangThaiThe::THE_BI_KHOA;
	this->DanhSachMuonTra = DOUBLE_LINKED_LIST::Controler();
}

THE_DOC_GIA::TheDocGia::TheDocGia(int MaThe, std::string Ho, std::string Ten, THE_DOC_GIA::GioiTinh Phai, THE_DOC_GIA::TrangThaiThe TrangThai, DOUBLE_LINKED_LIST::Controler DanhSachMuonTra) {
	this->MaThe = MaThe;
	this->Ho = Ho;
	this->Ten = Ten;
	this->Phai = Phai;
	this->TrangThai = TrangThai;
	this->DanhSachMuonTra = DanhSachMuonTra;
}

void THE_DOC_GIA::TheDocGia::SetMaThe(int MaThe) {
	this->MaThe = MaThe;
}

int THE_DOC_GIA::TheDocGia::GetMaThe() {
	return this->MaThe;
}

void THE_DOC_GIA::TheDocGia::SetHo(std::string Ho) {
	this->Ho = Ho;
}

std::string THE_DOC_GIA::TheDocGia::GetHo() {
	return this->Ho;
}

void THE_DOC_GIA::TheDocGia::SetTen(std::string Ten) {
	this->Ten = Ten;
}

std::string THE_DOC_GIA::TheDocGia::GetTen() {
	return this->Ten;
}

void THE_DOC_GIA::TheDocGia::SetPhai(THE_DOC_GIA::GioiTinh Phai) {
	this->Phai = Phai;
}

THE_DOC_GIA::GioiTinh THE_DOC_GIA::TheDocGia::GetPhai() {
	return this->Phai;
}

std::string THE_DOC_GIA::TheDocGia::GetStringfyPhai() {
    return (this->Phai == THE_DOC_GIA::GioiTinh::NAM ? "NAM" : "NU");
}

void THE_DOC_GIA::TheDocGia::SetTrangThai(THE_DOC_GIA::TrangThaiThe TrangThai) {
	this->TrangThai = TrangThai;
}

THE_DOC_GIA::TrangThaiThe THE_DOC_GIA::TheDocGia::GetTrangThai() {
	return this->TrangThai;
}

std::string THE_DOC_GIA::TheDocGia::GetStringfyTrangThai() {
    return (this->TrangThai == THE_DOC_GIA::TrangThaiThe::THE_BI_KHOA ? "BI KHOA" : "HOAT DONG");
}

void THE_DOC_GIA::TheDocGia::SetDanhSachMuonTra(DOUBLE_LINKED_LIST::Controler DanhSachMuonTra) {
	this->DanhSachMuonTra = DanhSachMuonTra;
}

DOUBLE_LINKED_LIST::Controler THE_DOC_GIA::TheDocGia::GetDanhSachMuonTra() {
	return this->DanhSachMuonTra;
}

void THE_DOC_GIA::TheDocGia::Log() {
	std::cerr << std::format("_____ THE DOC GIA _____\n");
	std::cerr << std::format("Ma the    : {}\n", this->MaThe);
	std::cerr << std::format("Ho        : {}\n", this->Ho);
	std::cerr << std::format("Ten       : {}\n", this->Ten);
	std::cerr << std::format("Phai      : {}\n", this->Phai == THE_DOC_GIA::GioiTinh::NAM ? "Nam" : "Nu");
	std::cerr << std::format("Trang thai: {}\n", this->TrangThai == THE_DOC_GIA::TrangThaiThe::THE_BI_KHOA ? "Bi khoa" : "Hoat dong");
	if (DOUBLE_LINKED_LIST::IsEmpty(this->DanhSachMuonTra)) {
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
	this->info = THE_DOC_GIA::TheDocGia();
	this->balanceFactor = 0;
	this->left = this->right = nullptr;
}

int AVL_TREE::Node::GetKey() {
    return this->info.GetMaThe();
}

void AVL_TREE::Initialize(AVL_TREE::Pointer& node) {
	node = nullptr;
}

bool AVL_TREE::IsEmpty(AVL_TREE::Pointer const& node) {
	return node == nullptr;
}

void AVL_TREE::PreOrderTraversal(AVL_TREE::Pointer const& node) {
	if (node != nullptr) {
		std::cerr << node->info.GetMaThe() << " ";
		AVL_TREE::PreOrderTraversal(node->left);
		AVL_TREE::PreOrderTraversal(node->right);
	}
}

void AVL_TREE::InOrderTraversal(AVL_TREE::Pointer const& node) {
	if (node != nullptr) {
		AVL_TREE::InOrderTraversal(node->left);
		std::cerr << node->info.GetMaThe() << " ";
		AVL_TREE::InOrderTraversal(node->right);
	}
}

void AVL_TREE::PostOrderTraversal(AVL_TREE::Pointer const& node) {
	if (node != nullptr) {
		AVL_TREE::InOrderTraversal(node->left);
		AVL_TREE::InOrderTraversal(node->right);
		std::cerr << node->info.GetMaThe() << " ";
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
bool AVL_TREE::Insert(AVL_TREE::Pointer& root, THE_DOC_GIA::TheDocGia info) {

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
        if (info.GetMaThe() == currentNode->GetKey()) {
            return false;
        }

        //* If the parameterized key is smaller than the currentNode's key, then we move to the left child tree of the currentNode.
        if (info.GetMaThe() < currentNode->GetKey()) {
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
    if (info.GetMaThe() < currentNodeParent->GetKey()) {
        currentNodeParent->left = currentNodeChild;
    }
    else {
        currentNodeParent->right = currentNodeChild;
    }

    /*
     * We modify the balance factor of all the node between the imbalanced node and the currentNodeChild.
     * If they were to the left, then all the balance factor of them are 1 and -1 in the otherhand.
    */
    if (info.GetMaThe() < imbalancedNode->GetKey()) {
        currentNode = imbalancedNode->left;
    }
    else {
        currentNode = imbalancedNode->right;
    }
    imbalancedNodeChild = currentNode;

    while (currentNode != currentNodeChild) {
        if (info.GetMaThe() < currentNode->GetKey()) {
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
    if (info.GetMaThe() < imbalancedNode->GetKey()) {
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

/**
* The function will extract the data string and return an object pointer.
*/
bool THE_DOC_GIA_MODULES::TheDocGiaExtractor(std::string data, std::string separator, THE_DOC_GIA::TheDocGia& returnData) {
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
            returnData.SetMaThe(std::stoi(extractedData));
			break;
		}
		case (1): {
            returnData.SetHo(extractedData);
			break;
		}
		case (2): {
            returnData.SetTen(extractedData);
			break;
		}
		case (3): {
            returnData.SetPhai(extractedData == "0" ? THE_DOC_GIA::GioiTinh::NAM : THE_DOC_GIA::GioiTinh::NU);
			break;
		}
		case (4): {
            returnData.SetTrangThai(extractedData == "0" ? THE_DOC_GIA::TrangThaiThe::THE_BI_KHOA : THE_DOC_GIA::TrangThaiThe::THE_HOAT_DONG);
			break;
		}
		}
		data.erase(0, pos + separator.length());
	}

	if (data.length() == 0) {
        returnData.SetDanhSachMuonTra(DOUBLE_LINKED_LIST::Controler());
		return true;
	}

	int muonTraCount = std::stoi(data);
	if (muonTraCount == 0) {
        returnData.SetDanhSachMuonTra(DOUBLE_LINKED_LIST::Controler());
	}
	else {
		/**
        * Currently this session is for LOADING @DanhSachMuonTra from file based database.
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
bool THE_DOC_GIA_MODULES::LoadDanhSachTheDocGiaFromDB(std::string filename, AVL_TREE::Pointer& tree) {

    //time_t startPoint = time(0);

    std::filebuf databaseBuffer{};

	if (!databaseBuffer.open(filename, std::ios::in)) {
		std::cerr << std::format("[ERROR] Can not open file {}\n", filename);
		return false;
	}

	std::istream database(&databaseBuffer);
    bool processResult = true;
    int recordCount = 0;
	while (database) {
        std::string line{};
		std::getline(database, line);
        THE_DOC_GIA::TheDocGia newTheDocGia{};
		bool result = THE_DOC_GIA_MODULES::TheDocGiaExtractor(line, ", ", newTheDocGia);
		if (result) {
            ++recordCount;
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

