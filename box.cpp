// box.cpp
#include "box.h"
#include <iostream>
#include <iomanip>

// Initialize static colors map
const std::map<int, std::string> Box::colors = {
    {YELLOW, "黃色"},
    {RED, "赤色"},
    {SKY_BLUE, "水色"},
    {AQUA_GREEN, "薄緑"},
    {PINK, "桃色"},
    {MAGENTA, "赤紫"},
    {BLUE, "青色"},
    {PURPLE, "紫色"},
    {YELLOW_GREEN, "黄緑"},
    {ORANGE, "橙色"},
    {GRAY, "灰色"},
    {DARK_GREEN, "深緑"}
};

Box::Box() : bottles() {}

Box::Box(const std::vector<Bottle>& bottles) : bottles(bottles) {}

const std::map<int, std::string>& Box::getColors() { return colors; }

const std::vector<Bottle>& Box::getBottles() const { return bottles; }

std::vector<Bottle>& Box::getBottles() { return bottles; }

void Box::setBottles(const std::vector<Bottle>& bottles) { this->bottles = bottles; }

Box Box::deepCopy() const {
    std::vector<Bottle> member;
    for (const auto& b : bottles) {
        member.push_back(Bottle(b)); // コピーコンストラクタが const Bottle& を処理
    }
    Box temp(member);
    for (size_t i = 0; i < temp.bottles.size(); ++i) {
        temp.bottles[i].setComplete(bottles[i].isComplete());
    }
    return temp;
}

bool Box::check() const {
    for (const auto& b : bottles) {
        if (!b.check()) return false;
    }
    return true;
}

void Box::display() const {
    std::vector<std::string> lines(4, "");
    for (const auto& b : bottles) {
        std::string color = (b.size() > 3) ? colors.at(b[3]) : "   ";
        lines[0] += "|" + color;
        color = (b.size() > 2) ? colors.at(b[2]) : "   ";
        lines[1] += "|" + color;
        color = (b.size() > 1) ? colors.at(b[1]) : "   ";
        lines[2] += "|" + color;
        color = (b.size() > 0) ? colors.at(b[0]) : "   ";
        lines[3] += "|" + color;
    }
    std::cout << std::string(bottles.size(), '-') << std::endl;
    for (const auto& l : lines) {
        std::cout << l << "|" << std::endl;
    }
}
