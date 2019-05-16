#include "base64.cpp"
#include "picosha2.h"
#include <bits/stdc++.h>
#include <iomanip>
#include <iostream>

using namespace std;

int main(int argc, char *arv[]) {
    // vars

    string version = "";
    string encoded = "";
    int first = 0;
    int second = 0;
    int third = 0;
    int snapshot = 0;

    int counter = 0;

    unordered_set<string> set;

    vector<unsigned char> hash(picosha2::k_digest_size);

    // loop
    while (set.insert(encoded).second) {
        counter++;
        version = to_string(first) + "." + to_string(second) + "." +
                  to_string(third) + ((snapshot == 0) ? "-SNAPSHOT" : "");

        picosha2::hash256(version.begin(), version.end(), hash.begin(),
                          hash.end());
        hash.resize(5);
        string foo(hash.begin(), hash.end());

        encoded = base64_encode(
            reinterpret_cast<const unsigned char *>(foo.c_str()), foo.length());

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

        //cout << encoded << endl;
    }
    cout << "Num of versions -- " << counter << endl;
    cout << "Duplicate -- " << encoded << endl;
}
