#include <bits/stdc++.h>
using namespace std;

int n, k;
long long greutate[100001];

int verif(long long c) {
    int i, nr = 1;
    long long sum = 0;
    for (i = 1; i <= n; i++) {
        if (sum + greutate[i] <= c) {
            sum = sum + greutate[i];
        } else {
            nr++;
            sum = greutate[i];
        }
    }
    if (nr <= k)
        return 1;
    else
        return 0;
}

int main() {
    long long maxg = 0, suma = 0, st, dr;
    ifstream fin("feribot.in");
    fin >> n >> k;
    for (int i = 1; i <= n; i++) {
        fin >> greutate[i];
        if (greutate[i] > maxg)
            maxg = greutate[i];
        suma = suma + greutate[i];
    }
    fin.close();
    st = maxg;
    dr = suma;
    while (st < dr) {
        long long mij = (st + dr) / 2;
        if (verif(mij) == 1)
            dr = mij;
        else
            st = mij + 1;
    }

    ofstream fout("feribot.out");
    fout << st;
    fout.close();
}
