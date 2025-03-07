#include <iostream>
#include <unordered_map>
#include <queue>
#include <chrono>
#include <thread>  

using namespace std;
using namespace std::chrono;

class TimeBasedCache {
private:
    struct CacheEntry {
        string value;
        time_point<steady_clock> expiryTime;
    };

    unordered_map<string, CacheEntry> cache;
    priority_queue<pair<time_point<steady_clock>, string>, vector<pair<time_point<steady_clock>, string>>, greater<>> expiryQueue;

    void removeExpiredKeys() {
        while (!expiryQueue.empty()) {
            auto [expiry, key] = expiryQueue.top();
            if (expiry > steady_clock::now()) break;

            expiryQueue.pop();
            cache.erase(key);
        }
    }

public:
    void set(string key, string value, int expiryTimeInSeconds) {
        removeExpiredKeys();

        time_point<steady_clock> expiry = steady_clock::now() + seconds(expiryTimeInSeconds);
        cache[key] = {value, expiry};
        expiryQueue.push({expiry, key});
    }

    string get(string key) {
        removeExpiredKeys();

        if (cache.find(key) != cache.end()) {
            return cache[key].value;
        }
        return "None";
    }

    void printCache() {
        removeExpiredKeys();
        cout << "Current Cache: ";
        for (auto& [key, entry] : cache) {
            cout << "{" << key << ": " << entry.value << "} ";
        }
        cout << endl;
    }
};

int main() {
    TimeBasedCache cache;

    cache.set("A", "100", 3);
    cache.printCache();

    this_thread::sleep_for(seconds(2));  
    cout << "Get A: " << cache.get("A") << endl;

    this_thread::sleep_for(seconds(2));
    cout << "Get A: " << cache.get("A") << endl;

    return 0;
}
