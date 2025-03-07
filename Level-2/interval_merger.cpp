#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class IntervalMerger {
private:
    vector<pair<int, int>> intervals;

public:
    void addInterval(int start, int end) {
        intervals.push_back({start, end});
        mergeIntervals();
    }

    void mergeIntervals() {
        if (intervals.empty()) return;

        sort(intervals.begin(), intervals.end());

        vector<pair<int, int>> merged;
        merged.push_back(intervals[0]);

        for (size_t i = 1; i < intervals.size(); i++) {
            auto& last = merged.back();
            if (intervals[i].first <= last.second) {
                last.second = max(last.second, intervals[i].second);
            } else {
                merged.push_back(intervals[i]);
            }
        }

        intervals = merged;
    }

    vector<pair<int, int>> getIntervals() {
        return intervals;
    }

    void printIntervals() {
        cout << "Merged Intervals: ";
        for (auto& interval : intervals) {
            cout << "[" << interval.first << ", " << interval.second << "] ";
        }
        cout << endl;
    }
};

int main() {
    IntervalMerger merger;

    merger.addInterval(1, 5);
    merger.printIntervals();

    merger.addInterval(6, 8);
    merger.printIntervals();

    merger.addInterval(4, 7);
    merger.printIntervals();

    merger.addInterval(10, 12);
    merger.printIntervals();

    merger.addInterval(11, 15);
    merger.printIntervals();

    return 0;
}