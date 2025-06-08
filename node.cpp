// node.cpp
#include "node.h"
#include <algorithm>
#include <sstream>
#include <iostream>

int Node::counter = 0;
std::vector<std::string> Node::duplication;

Node::Node(const Box& box) : value(box), child() {}

int Node::getCounter() { return counter; }

const std::vector<std::string>& Node::getDuplication() { return duplication; }

bool Node::checkDup(const std::string& hash) {
    return std::find(duplication.begin(), duplication.end(), hash) != duplication.end();
}

void Node::setDup(const std::string& hash) {
    duplication.push_back(hash);
}

void Node::init() {
    counter = 0;
    duplication.clear();
}

std::string Node::makeHash(const std::vector<Bottle>& box) {
    // ボトルをコピー
    std::vector<Bottle> rec = box;
    // ボトルを文字列化してソート（Ruby の sort_by{|r| r.to_s} を再現）
    std::sort(rec.begin(), rec.end(), [](const Bottle& a, const Bottle& b) {
        std::stringstream sa, sb;
        for (const auto& val : a) sa << val;
        for (const auto& val : b) sb << val;
        return sa.str() < sb.str();
    });
    // ソート済みのボトルを文字列化
    std::stringstream ss;
    for (const auto& b : rec) {
        for (const auto& val : b) {
            ss << val;
        }
        ss << "|"; // ボトル区切り（Ruby の to_s に相当）
    }
    return ss.str();
}

const Box& Node::getValue() const { return value; }

const std::vector<Node>& Node::getChild() const { return child; }

bool Node::add(const Node& nd, const Box& target) {
    bool ret = false;
    // std::cout << "DEBUG: Node::add, value.bottles.size() = " << value.getBottles().size()
    //           << ", target.bottles.size() = " << target.getBottles().size() << std::endl;
    if (value.getBottles() == target.getBottles()) {
        child.push_back(nd);
        ret = true;
    } else {
        for (auto& c : child) {
            if (c.getValue().getBottles() == target.getBottles()) {
                c.child.push_back(nd);
                ret = true;
                break;
            } else {
                ret = c.add(nd, target);
                if (ret) break;
            }
        }
    }
    return ret;
}

bool Node::replace(const Node& nd, const Box& target) {
    bool ret = false;
    if (value.getBottles() == target.getBottles()) {
        child.clear();
        child.push_back(nd);
        ret = true;
    } else {
        for (auto& c : child) {
            if (c.getValue().getBottles() == target.getBottles()) {
                c.child.clear();
                c.child.push_back(nd);
                ret = true;
                break;
            } else {
                ret = c.replace(nd, target);
                if (ret) break;
            }
        }
    }
    return ret;
}

bool Node::search(const Box& target) {
    bool ret = false;
    // std::cout << "DEBUG: Entering Node::search, child.size() = " << child.size()
    //           << ", target.bottles.size() = " << target.getBottles().size() << std::endl;
    for (auto& c : child) {
        // std::cout << "DEBUG: Comparing value.bottles.size() = " << c.getValue().getBottles().size()
        //           << " with target.bottles.size() = " << target.getBottles().size() << std::endl;
        if (c.getValue().getBottles() == target.getBottles()) {
            ret = true;
            counter++;
            // std::cout << "counter = " << counter << std::endl;
            c.getValue().display();
            break;
        } else {
            // std::cout << "DEBUG: Recursing into child" << std::endl;
            ret = c.search(target);
            if (ret) {
                counter++;
                // std::cout << "counter = " << counter << std::endl;
                c.getValue().display();
                break;
            }
        }
    }
    // std::cout << "DEBUG: Exiting Node::search, ret = " << ret << std::endl;
    return ret;
}
