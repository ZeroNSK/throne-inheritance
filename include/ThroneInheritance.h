#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

class ThroneInheritance {
public:
    explicit ThroneInheritance(const std::string& kingName);
    void birth(const std::string& parentName, const std::string& childName);
    void death(const std::string& name);
    std::vector<std::string> getInheritanceOrder() const;

private:
    std::string king_;
    std::unordered_map<std::string, std::vector<std::string>> children_;
    std::unordered_set<std::string> dead_;

    void dfs(const std::string& name, std::vector<std::string>& order) const;
};
