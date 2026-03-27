#include <iostream>
#include <array>
#include <vector>
#include <list>
#include <cstdlib>
#include <time.h>

using namespace std;

const int A = 1;
const int B = 1000;

int randInt(int a, int b) {
    return a + rand() % (b - a + 1);
}

template <typename T>
void fillContainer(T& container){
    for (auto& item : container) item = randInt(A, B);
}


int main(int, char**){
    srand(time(0));

    const int N = 100;
    array<int, N> array;
    vector<int> vector(N);
    list<int> list(N);

    //fill containers
    fillContainer(array);
    fillContainer(vector);
    fillContainer(list);

    // insertion
    vector.insert(vector.begin() + 50, 999);

    auto it = list.begin();
    for (int i = 0; i < 50; i++) ++it;
    list.insert(it, 999);

    //erase index 25
    vector.erase(vector.begin() + 25);

    it = list.begin();
    for(int i = 0; i < 25; i++) ++it;
    list.erase(it);

    // erase elements > 500
    int i = 0;
    for(auto elem: vector){
        if (elem > 500)
        {
            vector.erase(vector.begin() + i);
            i--;
        } 
        i++;
    }

    it = list.begin();
    while (it != list.end()) {
        if (*it > 500) {
            it = list.erase(it);  // erase возвращает следующий итератор
        } else {
            ++it;
        }
    }

    cout<<"Size of Array: "<<array.size()<<endl;
    cout<<"Size of Vector: "<<vector.size()<<endl;
    cout<<"Size of List: "<<list.size()<<endl;



    return 0;
}