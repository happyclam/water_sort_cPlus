// bottle.cpp
#include "bottle.h"
#include <algorithm>

Bottle::Bottle() : complete(false) {}

Bottle::Bottle(std::initializer_list<int> init) : std::vector<int>(init), complete(false) {}

Bottle::Bottle(const Bottle& other) : std::vector<int>(other), complete(other.complete) {}

bool Bottle::isComplete() const { return complete; }

void Bottle::setComplete(bool value) { complete = value; }

bool Bottle::pour(Bottle& bottle) {
    if (empty() || bottle.size() >= MAX_UNIT) return true;
    int org = back();
    do {
        int buf = back();
        pop_back();
        bottle.push_back(buf);
        if (empty()) break;
    } while (bottle.size() < MAX_UNIT && !empty() && back() == org);
    return true;
}

bool Bottle::monoCheck() const {
    if (empty()) return true;
    int first = front();
    return std::all_of(begin(), end(), [first](int color) { return color == first; });
}

bool Bottle::check() const {
    if (empty()) return true;
    int org = front();
    for (size_t i = 0; i < size(); ++i) {
        if (at(i) != org) return false;
        if (i + 1 == MAX_UNIT) {
            complete = true;
            return true;
        }
    }
    return false;
}

bool Bottle::operator==(const Bottle& other) const {
    return static_cast<const std::vector<int>&>(*this) == static_cast<const std::vector<int>&>(other);
}
