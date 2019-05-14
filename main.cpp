#include "base64.cpp"
#include "picosha2.h"
#include <bits/stdc++.h>
#include <iomanip>
#include <iostream>

using namespace std;

int main(int argc, char *arv[]) {
    cout << "Hello World" << endl;

    // vars
    string hash = "";
    string version = "";
    string encoded = "";
    int first = 0;
    int second = 0;
    int third = 0;
    int snapshot = 0;

    int counter = 0;

    unordered_set<string> set;

    // loop
    while (set.insert(encoded).second) {
        counter++;
        version = to_string(first) + "." + to_string(second) + "." +
                  to_string(third) + ((!snapshot) ? "-SNAPSHOT" : "");

        hash = picosha2::hash256_hex_string(version).substr(0, 8);
        encoded = base64_encode(reinterpret_cast<const unsigned char*>(hash.c_str()), hash.length());


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

        cout << encoded << endl;
        /*if (counter == 50) {
            break;
            }*/
    }
    cout << "Num of versions -- " << counter << endl;
    cout << "Duplicate -- " << encoded << endl;
}
