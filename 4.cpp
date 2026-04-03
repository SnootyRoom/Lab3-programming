#include <iostream>
#include <array>
#include <vector>
#include <list>
#include <cstdlib>
#include <ctime>
#include <random>
#include <chrono>
#include <cctype>
#include <algorithm>


template<typename T>
double timeOp(T t) {
    auto start = std::chrono::steady_clock::now();
    t();
    auto end = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / 1000000.0;
}


int randInt(int a, int b) {
    return a + rand() % (b - a + 1);
}


std::string generateRandomWord(const int &length) {
    const std::string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string word = "";
    for (int i = 0; i < length; ++i) {
        word += alphabet[rand() % alphabet.length()];
    }
    return word;
}

bool isVowel(char c) {
    c = tolower(c);
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y';
}


void fillContainers(std::array<std::string, 100>& array, std::vector<std::string>& vector, std::list<std::string>& list){
    std::string word; 
    auto it = list.begin();
    for(int i = 0; i < 100; i++){
        word = generateRandomWord(randInt(3, 15));
        array[i] = word;
        vector[i] = word;
        *it = word;
        ++it;
    }
}


int main(int, char**){
    srand(time(0));

    const int N = 100;
    std::array<std::string, N> stringsArray;
    std::vector<std::string> stringsVector(N);
    std::list<std::string> stringsList(N);

    fillContainers(stringsArray, stringsVector, stringsList);

    auto processContainer = [&N](const std::string& name, auto& container) {
        std::cout<<std::endl<<"Container "<< name <<std::endl;

        double timer1 = 0.0, timer2 = 0.0, timer3 = 0.0, timer4 = 0.0;

        auto startsWithA = [](const std::string& word) {
        return !word.empty() && (word[0] == 'A');
        };

        auto findAllWords = [&startsWithA](const auto& container) {
            std::vector<std::string> found;
            auto it = container.begin();
            while (it != container.end()) {
                it = std::find_if(it, container.end(), startsWithA);
                if (it != container.end()) {
                    found.push_back(*it);
                    ++it;
                }
            }
            return found;
        };

        timer1 = timeOp([&container, &findAllWords] {
            auto res = findAllWords(container);
            (void)res;
        });

        auto replaceVowels = [](std::string& string) {
            std::transform(string.begin(), string.end(), string.begin(),
                [](char c) { return isVowel(c) ? '*' : c; });
        };

        timer2 = timeOp([&container, &replaceVowels] {
            std::for_each(container.begin(), container.end(), replaceVowels);
        });

        timer3 = timeOp([&container] {
            auto it = std::max_element(container.begin(), container.end(),
                [](const std::string& a, const std::string& b) {
                    return a.length() < b.length();
                });
            (void)it;
        });

        std::vector<std::string> longWords;

        timer4 = timeOp([&container, &longWords] {
            longWords.clear();
            std::copy_if(container.begin(), container.end(), back_inserter(longWords),
                [](const std::string& word) { return word.length() > 7; });
        });

        std::cout << "Operation 1 (find_if, all 'A'):  " << timer1 << " ms"<<std::endl;
        std::cout << "Operation 2 (transform, vowels=*): " << timer2 << " ms"<<std::endl;
        std::cout << "Operation 3 (max_element, max len): " << timer3 << " ms"<<std::endl;
        std::cout << "Operation 4 (copy_if, >7 symbols): " << timer4 << " ms"<<std::endl;
        
    };

    processContainer("array", stringsArray);
    processContainer("vector", stringsList);
    processContainer("list", stringsList);
    

    return 0;
}