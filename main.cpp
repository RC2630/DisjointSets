#include <vector>
#include <iostream>
#include <utility>

#include "ansi_codes.h"

using namespace std;

struct DisjointSets {

private:

  vector<int> data;

  bool larger(int index1, int index2) const {
    return -data.at(index1) >= -data.at(index2);
  }

  friend ostream& operator << (ostream& out, const DisjointSets& ds);

public:

  DisjointSets(int size) {
    for (int i = 0; i < size; i++) {
      data.push_back(-1);
    }
  }

  int find(int index) {
    if (data.at(index) < 0) {
      return index;
    }
    data.at(index) = find(data.at(index));
    return data.at(index);
  }

  void setUnion(int index1, int index2) {
    index1 = find(index1);
    index2 = find(index2);
    if (index1 == index2) {
      return;
    }
    int newSize = data.at(index1) + data.at(index2);
    if (larger(index1, index2)) {
      data.at(index2) = index1;
      data.at(index1) = newSize;
    } else {
      data.at(index1) = index2;
      data.at(index2) = newSize;
    }
  }

};

ostream& operator << (ostream& out, const DisjointSets& ds) {
  const vector<int>& data = ds.data;
  if (data.empty()) {
    out << "(empty disjoint sets)";
    return out;
  }
  out << "[ ";
  for (int i = 0; i < data.size() - 1; i++) {
    out << ANSI_BLUE << i << ANSI_NORMAL << " : " << ANSI_GREEN << data.at(i) << ANSI_NORMAL << " , ";
  }
  out << ANSI_BLUE << (data.size() - 1) << ANSI_NORMAL << " : " << ANSI_GREEN << data.back() << ANSI_NORMAL << " ]";
  return out;
}

string displayHelper(int index1, int index2) {
  return "\nds  (after union on " + to_string(index1) + " & " + to_string(index2) + ") = ";
}

int main() {

  DisjointSets ds(10);
  cout << "\nds (before any operations) = " << ds;

  vector<pair<int, int>> pairsToUnion = {{3, 7}, {8, 1}, {2, 8}, {2, 3}, {9, 0}, {1, 2}, {4, 6}, {9, 1}, {2, 7}, {5, 4}};

  for (const auto& pair : pairsToUnion) {
    ds.setUnion(pair.first, pair.second);
    cout << displayHelper(pair.first, pair.second) << ds;
  }

  cout << "\n\n";

}