#include <atomic>
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

using namespace std;

// Publication Safety Pattern

void test() {
  vector<double> prices{10.2, 321.4, 1.3, 100.56, 124.5, 123.4, 123.2, 44.0,
                        10.2, 321.4, 1.3, 100.56, 124.5, 123.4, 123.2, 44.0,
                        10.2, 321.4, 1.3, 100.56, 124.5, 123.4, 123.2, 44.0,
                        10.2, 321.4, 1.3, 100.56, 124.5, 123.4, 123.2, 44.0};
  const auto initLength = prices.size();
  size_t length = prices.size();

  atomic<double> average = 0.0;

  atomic_flag busy = true;

  busy.clear();

  thread thread1{[&prices, &average, &busy, &length]() {
    while (1) {
      if (!busy.test_and_set()) {
        if (length = prices.size(); !length) {
          break;
        }
        cout << "t1 " << flush;
        // this_thread::sleep_for(10ms);
        const auto avg = average.load();
        average.store(prices.back() + avg);
        prices.pop_back();
        busy.clear();
      }
    }
    busy.clear();
  }};

  thread thread2{[&prices, &average, &busy, &length]() {
    while (1) {
      if (!busy.test_and_set()) {
        if (length = prices.size(); !length) {
          break;
        }
        cout << "t2 " << flush;
        // this_thread::sleep_for(10ms);
        const auto avg = average.load();
        average.store(prices.back() + avg);
        prices.pop_back();
        busy.clear();
      }
    }
    busy.clear();
  }};

  thread thread3{[&prices, &average, &busy, &length]() {
    while (1) {
      if (!busy.test_and_set()) {
        if (length = prices.size(); !length) {
          break;
        }
        cout << "t3 " << flush;
        // this_thread::sleep_for(10ms);
        const auto avg = average.load();
        average.store(prices.back() + avg);
        prices.pop_back();
        busy.clear();
      }
    }
    busy.clear();
  }};

  while (length) {
    cout << " " << flush;
    this_thread::sleep_for(10ms);
  }

  cout << '\n' << "average: " << (average.load() / initLength) << endl;

  thread1.join();
  thread2.join();
  thread3.join();
}

int main() {

    mutex mtx{};
    scoped_lock clck {mtx};


  test();
  /*
    vector<double> prices{10.2, 321.4, 1.3, 100.56, 124.5, 123.4, 123.2, 44.0};

    auto average = 0.0;

    atomic<bool> busy = true;

    cout << "is lock free: " << busy.is_lock_free() << "\n\n";

    thread thread{[&prices, &average, &busy]() {
      for (auto p : prices) {
        this_thread::sleep_for(10ms);
        average += p;
      }
      average /= prices.size();
      busy = false;
    }};

    while (busy) {
      cout << "." << flush;
      this_thread::sleep_for(10ms);
    }

    cout << '\n' << "average: " << average << endl;

    thread.join();
  */
  return 0;
}