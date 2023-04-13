/*
 * quadratic.cpp
 *
 * Data Structures & Algorithms, Project 2
 * Wendy Slattery
 * 4/7/20 (corona apocalypse)
 *
 * Implementation of simplified hash table (vector stores key only),
 * size 1,000,000 with linear, quadratic, double, and h1(k)
 * probe schemes for random values within range (-2^31, 2^31).
 *
 * compile: g++ -std=c++11 -Wall -Wextra -o quadratic.x quadratic.cpp
 */
#include <iostream>
#include <random>
#include <cmath>
#include <vector>
#include <list>


using namespace std;

// constants
const int TBL_SIZE = 1000000;
const long long MIN = pow(-2, 31);
const long long MAX = pow(2, 31);

vector<long long> table(TBL_SIZE);
long long bucket = NULL;
int collisions = 0;
int attempts = 0;
int insertions = 0;

// member functions
long long randNum(long long min, long long max);
void initializeTable();
long long hashFunc(long long key);
void quadraticInsert(long long key);



int main() {

    initializeTable();


    // stats and counters
    int inputSize = 900000;
    float loadFactor = float(inputSize)/float(TBL_SIZE);
    double predictedProbes = 1 / (1 - loadFactor);


    // generate the hash
    for (int i = 0; i < inputSize; i++){

        // create random key
        long long key = randNum(MIN, MAX);
        //cout << "key: " << key <<  endl;

        // hash keys and insert into table
        bucket = hashFunc(key);

        quadraticInsert(key);

    }
    double avgAttempts = double(attempts) / double(insertions);

    // results
    cout << "\nLoad Factor : "  << loadFactor << endl;
    cout << "Attempts : "  << attempts << endl;
    cout << "Collisions : "  << collisions << endl;
    cout << "Number Insertions: " << insertions << endl;
    cout << "Expected Probes : " << predictedProbes << endl;
    cout << "Avg Attempts to Insert: " << avgAttempts << endl;

    return 0;
}


long long randNum(long long min, long long max){
    static random_device device;
    mt19937 generator(device());
    uniform_int_distribution<long long> distribution(min, max);

    return distribution(generator);
}

void initializeTable(){
    for(int i = 0; i < TBL_SIZE; i++){
        table[i] = NULL;
    }
}

long long hashFunc(long long key){

    // offsetting negative values with mod
    return (key % TBL_SIZE + TBL_SIZE) % TBL_SIZE;
}

// hashing schemes

void quadraticInsert(long long key){
    int j = 1;
    int c1 = 1;
    int c2 = 3;

    while(table[bucket] != NULL && j < TBL_SIZE){
        //cout << "bucket " << bucket << " collision... rehash" << endl;
        collisions++;
        attempts++;
        bucket = hashFunc(key + (c1*j + c2*(j*j)));
        j++;

        if (j >= TBL_SIZE){
            j = 0;
        }
    }
    if(table[bucket] == NULL){
        attempts++;
        table[bucket] = key;
        insertions++;
        //cout << "bucket " << bucket << " filled with key " << table[bucket] << endl;
    }
}
