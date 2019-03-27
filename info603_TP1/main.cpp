#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <chrono>

// #define NDEBUG
#include <assert.h>

#define TAILLE 1000

using namespace std;

void fillRandom(int t[]) {
    srand(time(NULL));
    for (int i = 0; i < TAILLE; ++i) {
        t[i] = rand() % 100 + 1;
    }
}


bool estTrie(int t[],int min, int max){
    min--;
    for (int i = min; i < max; i++) {
        if(t[i] > t[i+1]){
            return false;
        }
    }
    return true;
}



bool estSup(int t[], int min, int max, int x){
    for (int e = min; e < max; e++) {
        if(t[e] <= x){
            return false;
        }
    }
    return true;
}

bool estInf(int t[], int min, int max, int x){
    if(min == 1){
        min--;
    }
    for (int e = min; e < max; e++) {
        if(t[e] > x){
            return false;
        }
    }
    return true;
}

bool estDoublons(int a, int b){
    return (a==b);
}


void triInsertSeq(int t[], int i) {
    int k;
    int x;

    if (i > 0) {
        triInsertSeq(t, i-1);

        //t[1..i-1] trié
        assert(estTrie(t, 1, i-1));

        k = i-1;
        x = t[i];
        while (k >= 0 and t[k] > x) {

            //pour tout e E [k..i], t[e] > x et t[1..i] trié
            // OU
            //t[i-1] > t[i] et t[1..i-1] trié
            assert((estTrie(t, 1, i) and estSup(t, k, i-1, x)) or (t[i-1] > t[i] and estTrie(t, 1, i-1)));

            t[k+1] = t[k];

            //t[1..i] trié  & doublons t[k] et t[k+1]  &  pour tout e E [k..i], t[e]>x
            assert(estTrie(t, 1, i) and estDoublons(t[k], t[k+1]) and estSup(t, k, i, x));

            k = k-1;

            //t[1..i] trié  &  doublons t[k+1] et t[k+2]  &  pour tout e E [k+1..i], t[e]>x
            assert(estTrie(t, 1, i) and estDoublons(t[k+1], t[k+2]) and estSup(t, k+1, i, x));

        }

        //si k=0 => pour tout e E [1..i] alors t[e]>x et doublons t[1] et t[2] et t[1..i] trié (1)
        if(k == -1){
            assert(estSup(t, 0, i, x) and estDoublons(t[0], t[1]) and estTrie(t, 1, i));
        }
        //si i-1>k>0 => pour tout e E [1..k] alors t[e]<=x  &  pour tout e E [k+1..i], t[e]>x et doublons t[k+1] et t[k+2] et t[1..i] trié(2)
        else if(k < i-1 and k > -1){
            assert(estInf(t, 1, k, x) and estSup(t, k+1, i, x) and estDoublons(t[k+1], t[k+2]) and estTrie(t, 1, i));
        }
        //si k = i-1 => t[1..i-1] trié et pour tout e E [1..i-1], t[e] <= x (3)
        else if(k == i-1){
            assert(estTrie(t, 1, i-1) and estInf(t, 1, i-1, x));
        }

        t[k+1] = x;
    }

    //d'apres (1), (2) et (3) => t[1..i] trié
    assert(estTrie(t, 1, i));

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
    triInsertSeq(t);
    cout << "Tri insertion sequentielle : ";
    //tri3Zones(t, TAILLE-1);
    afficheTab(t);
    return 0;
}



