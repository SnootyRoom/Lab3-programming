#include <iostream>
#include <array>
#include <vector>
#include <list>
#include <cstdlib>
#include <ctime>
#include <random>
#include <algorithm>
#include <iomanip>


struct Student{
    std::string name;
    int id;
    double gpa;
};

std::string generateRandomWord(const int &length) {
    const std::string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string word = "";
    for (int i = 0; i < length; ++i) {
        word += alphabet[rand() % alphabet.length()];
    }
    return word;
}

int randInt(int a, int b) {
    return a + rand() % (b - a + 1);
}


double randDouble(double a, double b) {
    std::random_device rd; 
    std::mt19937 gen(rd()); 
    std::uniform_real_distribution<double> dis(a, b);
    return dis(gen);

}

Student generateStudent(const int &id){
    Student student;
    student.name = generateRandomWord(randInt(3, 15));
    student.id = id;
    student.gpa = randDouble(0.0, 5.0);
    
    return student;
}

void sortByGpa(std::array<Student, 1000> &array, std::vector<Student> &vector, std::list<Student> &list){
    std::sort(array.begin(), std::end(array), 
        [](const Student& a, const Student&b) {
            return a.gpa > b.gpa;
        });

    std::sort(vector.begin(), std::end(vector), 
        [](const Student& a, const Student&b) {
            return a.gpa > b.gpa;
        });

    list.sort([](const Student& a, const Student& b) {
        return a.gpa > b.gpa;
    });
}

void sortById(std::array<Student, 1000> &array, std::vector<Student> &vector, std::list<Student> &list){
    std::sort(array.begin(), std::end(array), 
        [](const Student& a, const Student&b) {
            return a.id < b.id;
        });

    std::sort(vector.begin(), std::end(vector), 
        [](const Student& a, const Student&b) {
            return a.id < b.id;
        });

    list.sort([](const Student& a, const Student& b) {
        return a.id < b.id;
    });
}

void sortByName(std::array<Student, 1000> &array, std::vector<Student> &vector, std::list<Student> &list){
    std::sort(array.begin(), std::end(array), 
        [](const Student& a, const Student&b) {
            return a.name < b.name;
        });

    std::sort(vector.begin(), std::end(vector), 
        [](const Student& a, const Student&b) {
            return a.name < b.name;
        });

    list.sort([](const Student& a, const Student& b) {
        return a.name < b.name;
    });
}


void printTopStudents(const std::vector<Student> &vector){
    std::cout << std::fixed << std::setprecision(2); 
   for(int i = 0; i < 5; i++) std::cout<<vector[i].gpa<<" ";
   std::cout << std::endl;
}


int main(int, char**){
    srand(time(0));
    const int N = 1000;
    Student student;
    std::array<Student, N> studentsArray;
    std::vector<Student> studenstVector;
    std::list<Student> studentsList;

    for(int i = 0; i < N; i++){
        student = generateStudent(i);
        studentsArray[i] = student;
        studenstVector.push_back(student);
        studentsList.push_back(student);
    }


    std::cout<<"Top after sorting by gpa"<<std::endl;
    sortByGpa(studentsArray, studenstVector, studentsList);
    printTopStudents(studenstVector);

    std::cout<<std::endl<<"Top after sorting by id"<<std::endl;
    sortById(studentsArray, studenstVector, studentsList);
    printTopStudents(studenstVector);

    std::cout<<std::endl<<"Top after sorting by name"<<std::endl;
    sortByName(studentsArray, studenstVector, studentsList);
    printTopStudents(studenstVector);
    
    return 0;
}