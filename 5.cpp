#include <iostream>
#include <vector>
#include <list>
#include <array>
#include <random>
#include <chrono>
#include <iomanip>
#include <functional>


template<typename F>
double timeMs(F&& op) {
    auto start = std::chrono::steady_clock::now();
    op();
    auto end = std::chrono::steady_clock::now();
    return std::chrono::duration<double, std::milli>(end - start).count();
}


template<typename Container>
void fillRandom(Container& container, std::size_t n,
                 std::mt19937& gen, std::uniform_int_distribution<int>& dis) {
    container.clear();
    container.resize(n);
    for(std::size_t i = 0; i < n; ++i) container[i] = dis(gen);
}


template<typename T>
void fillRandom(std::list<T>& list, std::size_t n,
                 std::mt19937& gen, std::uniform_int_distribution<int>& dis) {
    list.clear();
    for(std::size_t i = 0; i < n; ++i) list.push_back(dis(gen));
}

template<typename T, std::size_t N>
void fillRandom(std::array<T, N>& array,
                 std::mt19937& gen, std::uniform_int_distribution<int>& dis) {
    for(std::size_t i = 0; i < N; ++i) array[i] = dis(gen);
}


template<typename Container>
double seqSumIndexed(const Container& container) {
    return timeMs([&]{
        long long sum = 0;
        for(std::size_t i = 0; i < container.size(); ++i) sum += container[i];
        (void)sum;
    });
}


template<typename T>
double seqSumList(const std::list<T>& list) {
    return timeMs([&]{
        long long sum = 0;
        for(auto it = list.begin(); it != list.end(); ++it) sum += *it;
        (void)sum;
    });
}



template<typename Container>
double randomAccessIndexed(const Container& container) {
    return timeMs([&]{
        volatile int x = 0;
        x ^= container[0];
        x ^= container[25000];
        x ^= container[50000];
        x ^= container[75000];
        x ^= container[99999];
        (void)x;
    });
}

template<typename T>
double randomAccessList(const std::list<T>& list) {
    auto get_at = [&](std::size_t idx) -> T {
        auto it = list.begin();
        for(std::size_t i = 0; i < idx; ++i) ++it;
        return *it;
    };

    return timeMs([&]{
        volatile T x = 0;
        x ^= get_at(0);
        x ^= get_at(25000);
        x ^= get_at(50000);
        x ^= get_at(75000);
        x ^= get_at(99999);
        (void)x;
    });
}


template<typename Container>
double pushBackContainer(Container& container,
                      std::mt19937& gen, std::uniform_int_distribution<int>& dis) {
    return timeMs([&]{
        for(int i = 0; i < 1000; ++i) container.push_back(dis(gen));
    });
}


template<typename Container>
double insert_middle_indexed(Container& container,
                             std::size_t pos,
                             std::size_t count,
                             std::mt19937& gen,
                             std::uniform_int_distribution<int>& dis) {
    return timeMs([&]{
        for(std::size_t i = container.size() - 1; i >= pos + count; --i) {
            container[i] = container[i - count];
            if(i == pos + count) break;
        }

        for(std::size_t i = 0; i < count; ++i) {
            container[pos + i] = dis(gen);
        }
    });
}


template<typename T>
double insert_middle_list(std::list<T>& list,
                          std::size_t pos,
                          std::size_t count,
                          std::mt19937& gen,
                          std::uniform_int_distribution<int>& dis) {
    return timeMs([&]{
        auto it = list.begin();
        for(std::size_t i = 0; i < pos; ++i) ++it;
        for(std::size_t j = 0; j < count; ++j) {
            list.insert(it, dis(gen));
        }
    });
}

template<typename Container>
double erase_middle_indexed(Container& container, std::size_t pos, std::size_t count) {
    return timeMs([&]{
        for(std::size_t i = pos; i + count < container.size(); ++i) {
            container[i] = container[i + count];
        }
    });
}

template<typename T>
double erase_middle_list(std::list<T>& list, std::size_t pos, std::size_t count) {
    return timeMs([&]{
        auto first = list.begin();
        for(std::size_t i = 0; i < pos; ++i) ++first;
        auto last = first;
        for(std::size_t j = 0; j < count; ++j) ++last;
        list.erase(first, last);
    });
}


int main() {
    std::cout << std::fixed << std::setprecision(3);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(-1000, 1000);

    std::cout << "Sequential access"<<std::endl;
    {
        std::vector<int> vector;
        fillRandom(vector, 100000, gen, dis);
        std::cout << "vector: " << seqSumIndexed(vector) << " ms\n";
    }
    {
        std::list<int> list;
        fillRandom(list, 100000, gen, dis);
        std::cout << "list:   " << seqSumList(list) << " ms\n";
    }
    {
        std::array<int,100000> array{};
        fillRandom(array, gen, dis);
        std::cout << "array:  " << seqSumIndexed(array) << " ms\n";
    }

    std::cout << "Random access"<<std::endl;
    {
        std::vector<int> vector(100000);
        for(std::size_t i = 0; i < vector.size(); ++i) vector[i] = static_cast<int>(i);
        std::cout << "vector: " << randomAccessIndexed(vector) << " ms\n";
    }
    {
        std::list<int> list;
        for(int i = 0; i < 100000; ++i) list.push_back(i);
        std::cout << "list:   " << randomAccessList(list) << " ms\n";
    }
    {
        std::array<int,100000> array{};
        for(std::size_t i = 0; i < array.size(); ++i) array[i] = static_cast<int>(i);
        std::cout << "array:  " << randomAccessIndexed(array) << " ms\n";
    }

    std::cout << "Push back"<<std::endl;
    {
        std::vector<int> vector;
        fillRandom(vector, 100000, gen, dis);
        std::cout << "vector: " << pushBackContainer(vector, gen, dis) << " ms\n";
    }
    {
        std::list<int> list;
        fillRandom(list, 100000, gen, dis);
        std::cout << "list:   " << pushBackContainer(list, gen, dis) << " ms\n";
    }

    std::cout << "Insert"<<std::endl;
    {
        std::vector<int> vector(100000 + 100);
        for(std::size_t i = 0; i < 100000; ++i) vector[i] = dis(gen);
        std::cout << "vector: " << insert_middle_indexed(vector, 50000, 100, gen, dis) << " ms\n";
    }
    {
        std::list<int> list;
        fillRandom(list, 100000, gen, dis);
        std::cout << "list:   " << insert_middle_list(list, 50000, 100, gen, dis) << " ms\n";
    }

    std::cout << "Erase"<<std::endl;
    {
        std::vector<int> vector(101000);
        for(std::size_t i = 0; i < vector.size(); ++i) vector[i] = dis(gen);
        std::cout << "vector: " << erase_middle_indexed(vector, 50000, 100) << " ms\n";
    }
    {
        std::list<int> list;
        fillRandom(list, 101000, gen, dis);
        std::cout << "list:   " << erase_middle_list(list, 50000, 100) << " ms\n";
    }

    return 0;
}