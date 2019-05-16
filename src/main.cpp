#include "base64.cpp"
#include "openssl/sha.h"
#include <bits/stdc++.h>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>

using namespace std;

int main(int argc, char *arv[]) {
    auto start = chrono::system_clock::now();
    // vars
    string version = "";
    string encoded = "";
    int first = 0;
    int second = 0;
    int third = 0;
    int snapshot = 0;

    int counter = 0;

    unordered_set<string> set;
    unsigned char shaBits[65];


    // loop
    do {
        counter++;
        version = to_string(first) + "." + to_string(second) + "." +
                  to_string(third) + ((snapshot == 0) ? "-SNAPSHOT" : "");

        SHA256((unsigned char *)version.c_str(), version.size(), shaBits);

        encoded = base64_encode(shaBits, 4);

        snapshot++;
        if (snapshot == 2) {
            third++;
            snapshot = 0;
            if (third == 100) {
                second++;
                third = 0;
                if (second == 100) {
                    first++;
                    second = 0;
                }
            }
        }

        //cout << version << endl;
        //cout << encoded << endl;
        //if (counter == 1) {
        //    break;
        //}
    } while (set.insert(encoded).second);
    cout << "Num of versions -- " << counter << endl;
    cout << "Duplicate -- " << encoded << endl;
    auto end = chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;

    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
}
