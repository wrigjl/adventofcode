#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

long handleSequence(const vector<long>& initseq, long& sum2) {
    vector<long> seq;
    vector<long> prevseq = initseq;

    long sum = 0;

    bool doMinus = false;;
    for (;;) {
        bool allZeros = true;
        seq.clear();
        for (size_t i = 1; i < prevseq.size(); i++) {
            long val = prevseq[i] - prevseq[i-1];
            allZeros = allZeros && val == 0;
            seq.push_back(val);
        }
        sum += prevseq[prevseq.size()-1];

        sum2 += (doMinus ? -prevseq.front() : prevseq.front());
        doMinus = !doMinus;

        prevseq = seq;
        if (allZeros)
            break;
    }
    return sum;
}

int main() {
    vector<long> seq;
    string line;
    long sum = 0, sum2 = 0;

    while (getline(cin, line)) {
        istringstream iss(line);
        long num;
        while (iss >> num)
            seq.push_back(num);
        sum += handleSequence(seq, sum2);
        cout << endl;
        seq.clear();
    }
    cout << "part1 " << sum << endl;
    cout << "part2 " << sum2 << endl;
}