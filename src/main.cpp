#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cctype>
#include "../include/ThroneInheritance.h"

using namespace std;

static void printOrder(const vector<string>& order) {
    cout << "[";
    for (size_t i = 0; i < order.size(); ++i) {
        cout << order[i];
        if (i + 1 < order.size()) cout << ", ";
    }
    cout << "]\n";
}

static string readAllStdin() {
    ostringstream ss;
    ss << cin.rdbuf();
    return ss.str();
}

static vector<string> parseOps(const string& s) {
    vector<string> res;
    bool inQuote = false;
    string cur;
    for (size_t i = 0; i < s.size(); ++i) {
        char c = s[i];
        if (c == '"') {
            inQuote = !inQuote;
            if (!inQuote) { 
                res.push_back(cur);
                cur.clear();
            }
            continue;
        }
        if (inQuote) cur.push_back(c);
    }
    return res;
}


static vector<vector<string>> parseArgs(const string& s) {
    vector<vector<string>> res;
    size_t i = 0;
    while (i < s.size() && s[i] != '[') ++i;
    if (i == s.size()) return res;
    while (i < s.size()) {
        if (s[i] == '[') {
            ++i;
            vector<string> group;
            bool done = false;
            while (i < s.size() && !done) {
                while (i < s.size() && isspace((unsigned char)s[i])) ++i;
                if (i >= s.size()) break;
                if (s[i] == '"') {
                    ++i;
                    string cur;
                    while (i < s.size() && s[i] != '"') { cur.push_back(s[i]); ++i; }
                    if (i < s.size() && s[i] == '"') ++i;
                    group.push_back(cur);
                } else if (s.compare(i, 4, "null") == 0) {
                    i += 4;
                } else if (s[i] == ']') {
                    ++i;
                    done = true;
                    break;
                } else if (s[i] == ',') {
                    ++i; 
                } else {
                    ++i;
                }
            }
            res.push_back(group);
        } else {
            ++i;
        }
    }
    return res;
}

int main() {
    string stdinAll = readAllStdin();
    if (stdinAll.empty()) {
        ThroneInheritance t("king");
        t.birth("king", "andy");
        t.birth("king", "bob");
        t.birth("king", "catherine");
        t.birth("andy", "matthew");
        t.birth("bob", "alex");
        t.birth("bob", "asha");

        auto order1 = t.getInheritanceOrder();
        printOrder(order1);

        t.death("bob");
        auto order2 = t.getInheritanceOrder();
        printOrder(order2);
        return 0;
    }

    istringstream in(stdinAll);
    string line1, line2;
    if (!getline(in, line1)) return 0;
    if (!getline(in, line2)) return 0;

    auto ops = parseOps(line1);
    auto args = parseArgs(line2);

    ThroneInheritance* t = nullptr;
    for (size_t i = 0; i < ops.size(); ++i) {
        const string& op = ops[i];
        const vector<string> a = (i < args.size() ? args[i] : vector<string>{});
        if (op == "ThroneInheritance") {
            if (a.size() >= 1) {
                delete t;
                t = new ThroneInheritance(a[0]);
                cout << "null\n";
            }
        } else if (op == "birth") {
            if (t && a.size() >= 2) {
                t->birth(a[0], a[1]);
                cout << "null\n";
            }
        } else if (op == "death") {
            if (t && a.size() >= 1) {
                t->death(a[0]);
                cout << "null\n";
            }
        } else if (op == "getInheritanceOrder") {
            if (t) {
                auto order = t->getInheritanceOrder();
                cout << "[";
                for (size_t j = 0; j < order.size(); ++j) {
                    cout << '"' << order[j] << '"';
                    if (j + 1 < order.size()) cout << ", ";
                }
                cout << "]\n";
            }
        } else {
            cout << "null\n";
        }
    }

    delete t;
    return 0;
}
