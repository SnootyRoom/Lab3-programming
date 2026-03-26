#include <iostream>
#include <array>
#include <vector>
#include <list>

using namespace std;

template <typename T>
void fillContainer(T& container){
    int value = 1;
    for (auto& item : container) item = value++;
}

template <typename T>
void printContainer(T& container){
    for (const auto& item: container) cout<<item<<" ";
}


int main(int, char**){
    const int N = 10;
    array<int, N> array;
    vector<int> vector(N);
    list<int> list(N);


    fillContainer(array);
    fillContainer(vector);
    fillContainer(list);

    cout<<"Array:"<<endl;
    printContainer(array);
    cout<<endl<<"Vector:"<<endl;
    printContainer(vector);
    cout<<endl<<"List: "<<endl;
    printContainer(list);
    
    array[5] = 100;
    vector[5] = 100;
    auto it = list.begin();
    advance(it, 5);
    *it = 5;


    // Array can not to add element, because it is static 
    int element = 11;
    vector.push_back(element);
    list.push_back(element);

    cout<<endl;
    cout<<"Size of array "<<sizeof(array)<<endl;
    cout<<"Size of vector "<<sizeof(vector)<<endl;
    cout<<"Size of list "<<sizeof(list)<<endl;

    cout<<"array[0]="<<array.front()<<" array["<<array.size() - 1<<"]="<<array.back()<<endl;
    cout<<"vector[0]="<<vector.front()<<" vector["<<array.size() - 1<<"]="<<vector.back()<<endl;
    cout<<"list[0]="<<list.front()<<" list["<<array.size() - 1<<"]="<<list.back()<<endl;


    return 0;
}
