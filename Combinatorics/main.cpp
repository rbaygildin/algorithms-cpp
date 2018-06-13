#include <iostream>

using namespace std;

long fact(long);
void ex1(long, long, long&, long&, long&);
void ex2(long);

int main() {
    long n = 6;
    long k = 2;
    long p, a, c;
    p = 0;
    a = 0;
    c = 0;
    ex1(n, k, p, a, c);
    cout << p << " " <<  a << " " << c << endl;
    ex2(10);
    return 0;
}

void ex1(long n, long k, long& p, long& a, long& c){
    p = fact(n);
    a = fact(n)/fact(n - k);
    c = fact(n)/(fact(n - k) * fact(k));
}

void ex2(long n){
    long *p = new long[n];
    for(int k = 0; k < n; k++)
        p[k] = k + 1;
    long last = 0;
    for(int k = 1; k <= n; k++)
        last = last * 10 + k;
    long current = 0;
    while(current != last){
        long i = n;
        while(i > 2 && p[i - 1] < p[i - 2])
            i--;
        long j = n;
        while(p[j - 1] < p[i - 2])
            j--;
        swap(p[j - 1], p[i - 2]);
        for(j = 0; j <= (n - i + 1)/2 - 1; j++)
            swap(p[i + j - 1], p[n - j - 1]);
        for(int k = 0; k < n; k++)
            current = current * 10 + p[k];
        cout << current << endl;
    }
    delete[] p;
}
long fact(long n){
    long p = 1;
    while(n > 0) {
        p *= n;
        n--;
    }
    return p;
}