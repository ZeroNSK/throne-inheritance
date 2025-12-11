#include "../include/ThroneInheritance.h"
#include <stack>

ThroneInheritance::ThroneInheritance(const std::string& kingName)
    : king_(kingName) {}

void ThroneInheritance::birth(const std::string& parentName, const std::string& childName) {
    children_[parentName].push_back(childName);
    if (children_.find(childName) == children_.end()) {
        children_[childName] = {};
    }
}

void ThroneInheritance::death(const std::string& name) {
    dead_.insert(name);
}

void ThroneInheritance::dfs(const std::string& name, std::vector<std::string>& order) const {
    if (dead_.find(name) == dead_.end()) {
        order.push_back(name);
    }
    auto it = children_.find(name);
    if (it == children_.end()) return;
    for (const auto& child : it->second) {
        dfs(child, order);
    }
}

std::vector<std::string> ThroneInheritance::getInheritanceOrder() const {
    std::vector<std::string> order;
    dfs(king_, order);
    return order;
}
