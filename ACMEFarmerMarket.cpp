// ACMEFarmerMarket.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <assert.h>
#include "Node.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>

static Node<std::string>* topOfTree = nullptr;

void setupLine(const std::string& line)
{
    std::stringstream ss(line);
    std::vector<std::string> tokens;
    std::string item;
    auto backInserter = std::back_inserter(tokens);
    while (std::getline(ss, item, '|')) 
    {
        (backInserter++) = item;
    }
    std::string parentData = tokens.at(0);
    std::string childData = tokens.at(1);
    if (!parentData.empty())
    {
        Node<std::string>* parentNode = Node<std::string>::find_node_in_tree(topOfTree, parentData);
        if (parentNode == nullptr)
        {
            parentNode = new Node<std::string>(nullptr, parentData);
            topOfTree = parentNode;
        }
        parentNode->add_child(childData);
    }
    else
        topOfTree = new Node<std::string>(nullptr, childData);
}

int main(int argc, char* argv[])
{
    std::string fileName;
    if (argc != 2)
    {
        std::cout << "Enter a file name: ";
        std::cin >> fileName;
    }
    else
        fileName = argv[1];

    std::cout << "* trying to open and read: " << fileName << std::endl;
    std::ifstream fileStream(fileName);
    if (!fileStream.is_open())
    {
        perror("failed on file open");
        return 1;
    }
    std::string line;
    while (std::getline(fileStream, line))
    {
        setupLine(line);
    }
    topOfTree->PrintTree();
    std::cout << "PrintLeaves()" << std::endl;
    topOfTree->PrintLeaves();
    std::cout << "FIND()" << std::endl;
    topOfTree->Find("BANANAS");

    fileStream.close();
    return 0;
}
