
#include <iostream>
#include <map>

int cardRank(char c) {
    if (isdigit(c))
        return c - '0';
    if (c == 'T')
        return 10;
    if (c == 'J')
        return 11;
    if (c == 'Q')
        return 12;
    if (c == 'K')
        return 13;
    return 14;
}

bool compareHand(const std::string &a, const std::string &b) {
    for (size_t i = 0; i < a.size(); ++i) {
        auto result = cardRank(a[i]) <=> cardRank(b[i]);
        if (result < 0)
            return true;
        if (result > 0)
            return false;
    }
    return false;
}

int handRank(const std::string& hand) {
      std::map<char, u_long> counts;
      for (const auto& c : hand) {
            if (counts.count(c) == 0)
                counts.insert(std::make_pair(c, 0));
            ++counts[c];
      }

      int threes = 0;
      int pairs = 0;
      for (const auto& c : counts) {
          if (c.second == 5)
              return 10;
          if (c.second == 4)
              return 9;
          if (c.second == 3)
              threes++;
          if (c.second == 2)
              pairs++;
      }

      if (threes)
          return (pairs) ? 8 : 7;
      if (pairs == 2)
          return 6;
      if (pairs == 1)
          return 5;
      return 0;
}

struct cmpByStringRank {
    bool operator()(const std::string& a, const std::string& b) const {
        auto result = handRank(a) <=> handRank(b);
        if (result < 0)
            return true;
        if (result == 0)
            return compareHand(a, b);
        return false;
    }
};

int main() {
    std::map<std::string, u_long, cmpByStringRank> map;
    std::string card;
    u_long bid;
    while (std::cin >> card >> bid) {
        map.insert(std::make_pair(card, bid));
    }

    u_long rank = 0;
    u_long sum = 0;
    for (const auto& entry : map) {
        rank++;
        std::cout << entry.first << " " << entry.second << std::endl;
        sum += entry.second * rank;
    }
    std::cout << sum << std::endl;
}