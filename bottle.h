// bottle.h
#ifndef BOTTLE_H
#define BOTTLE_H

#include <vector>
#include <initializer_list>
#include "const.h"

class Bottle : public std::vector<int> {
private:
    mutable bool complete;

public:
    Bottle();
    Bottle(std::initializer_list<int> init);
    Bottle(const Bottle& other);
    
    // Getter and setter for complete
    bool isComplete() const;
    void setComplete(bool value);

    bool pour(Bottle& bottle);
    bool monoCheck() const;
    bool check() const;

    // 追加: 比較演算子
    bool operator==(const Bottle& other) const;
};

#endif // BOTTLE_H
