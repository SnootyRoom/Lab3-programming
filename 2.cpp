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

    fillContainer(array);
    fillContainer(vector);
    fillContainer(list);

    array[50] = 999;
    vector.insert(vector.begin() + 50, 999);

    auto it = list.begin();
    for (int i = 0; i < 50; i++) ++it;
    list.insert(it, 999);

    it = list.begin();
    for (int i = 0; i < 50; i++) ++it;

    cout<<"Array[50]: "<<array[50]<<endl;
    cout<<"Vector[50]: "<<vector[50]<<endl;
    cout<<"List[50]: "<<*(it)<<endl;

    cout<<"Size of Array: "<<array.size()<<endl;
    cout<<"Size of Vector: "<<vector.size()<<endl;
    cout<<"Size of List: "<<list.size()<<endl;



    return 0;
}