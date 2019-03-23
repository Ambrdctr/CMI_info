#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#define TAILLE 20
using namespace std;

void fillRandom(int t[]) {
    srand(time(NULL));
    for (int i = 0; i < TAILLE; ++i) {
        t[i] = rand() % 100 + 1;
    }
}


void triInsertSeq(int t[], int i) {
    int k;
    int x;

    if (i > 1) {
        triInsertSeq(t, i-1);
        k = i-1;
        x = t[i];

        while (k >= 0 and t[k] > x) {
            t[k+1] = t[k];
            k = k-1;
        }

        t[k+1] = x;
    }
}



void triInsertSeq(int t[]) {
    auto start = chrono::system_clock::now();
    triInsertSeq(t, TAILLE-1);
    auto end = chrono::system_clock::now();
    chrono::duration<double> elapsed = end - start;
    cout << "Durée du tri : " << elapsed.count() << "s" << endl;
}



void tri3Zones(int t[], int i) {
    int a, b, min, posMin, max, posMax, current;
    a = 0;
    b = i;
    if (i > 0) {
        min = t[0];
        max = t[0];
        posMin = 0;
        posMax = 0;
    }
    while (a < b) {
        for (int k = a; k < b; ++k) {
            current = t[k];
            if (current < min) {
                min = current;
                posMin = k;
            }
            if (current > max) {
                max = current;
                posMax = k;
            }
        }
        t[posMin] = t[a + 1];
        t[a + 1] = min;
        t[posMax] = t[b - 1];
        t[b - 1] = max;
        a++;
        b--;
    }
}



void afficheTab(int t[]){
    for (int i = 0; i < TAILLE; ++i) {
        cout << " | " << t[i] ;
    }
    cout << endl;
}


int main() {
    int t[TAILLE];
    fillRandom(t);
    cout << "Tableau initial : ";
    afficheTab(t);
    //triInsertSeq(t);
    //cout << "Tri insertion sequentielle : ";
    tri3Zones(t, TAILLE-1);
    afficheTab(t);
    return 0;
}



