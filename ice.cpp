#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <cctype>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include <iostream>

using std::begin;
using std::end;

namespace huffman {

// NOTE(nicole): these types assume an ASCII encoding

template <class Iter>
std::array<int, 128> frequency_list(Iter const first, Iter const last) {
  auto ret = std::array<int, 128>();

  /*
  for (auto it = first; it != last; ++it) {
    ret.at(*it) += 1;
  }
  */
  std::for_each(first, last,
      [&ret] (char c) { ret.at(*it) += 1; });

  return ret;
}

class codebook {
  struct node {
    int frequency;

    node(int freq): frequency(freq) {}
  };

  using node_ptr = std::unique_ptr<node const>;

  struct leaf final : node {
    char key;

    leaf(int freq, char key): node(freq), key(key) {}
  };

  struct branch final : node {
    node_ptr lhs;
    node_ptr rhs;

    branch(node_ptr lhs, node_ptr rhs) :
      node(lhs->frequency + rhs->frequency),
      lhs(std::move(lhs)),
      rhs(std::move(rhs)) {}
  };

  node_ptr top_;

public:
  template <class Iter>
  codebook(Iter const first, Iter const last) {
    auto freq = frequency_list(first, last);

    auto lst = std::vector<std::unique_ptr<node const>>();

    {
      int c = 0;
      for (auto f : freq) {
        if (f > 0) {
          lst.emplace_back(new leaf(f, char(c)));
        }
        ++c;
      }
    }
  }
};

class encoded_string {
};

}

int main() {
  std::string s = "Hello, world!";
  auto book = huffman::codebook(begin(s), end(s));
}
