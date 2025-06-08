// node.h
#ifndef NODE_H
#define NODE_H

#include <vector>
#include <string>
#include "box.h"
#include "const.h"

class Node {
private:
    static int counter; // 変更: mutable を削除
    static std::vector<std::string> duplication;
    Box value;
    std::vector<Node> child;

public:
    Node(const Box& box);
    
    // Static getters
    static int getCounter();
    static const std::vector<std::string>& getDuplication();
    
    // Static methods
    static bool checkDup(const std::string& hash);
    static void setDup(const std::string& hash);
    static void init();
    static std::string makeHash(const std::vector<Bottle>& box);
    
    // Instance methods
    const Box& getValue() const;
    const std::vector<Node>& getChild() const;
    
    bool add(const Node& nd, const Box& target);
    bool replace(const Node& nd, const Box& target);
    bool search(const Box& target); // 変更: const を削除
};

#endif // NODE_H
