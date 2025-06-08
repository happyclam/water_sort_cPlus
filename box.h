// box.h
#ifndef BOX_H
#define BOX_H

#include <vector>
#include <map>
#include <string>
#include "bottle.h"
#include "const.h"

class Box {
private:
    static const std::map<int, std::string> colors;
    std::vector<Bottle> bottles;

public:
    Box();
    Box(const std::vector<Bottle>& bottles);
    
    // Getter for colors
    static const std::map<int, std::string>& getColors();
    
    // Getter and setter for bottles
    const std::vector<Bottle>& getBottles() const;
    std::vector<Bottle>& getBottles(); // 非 const ゲッターを追加
    void setBottles(const std::vector<Bottle>& bottles);
    
    Box deepCopy() const;
    bool check() const;
    void display() const;
};

#endif // BOX_H
