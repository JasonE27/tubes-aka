#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>
#include <chrono>

using namespace boost::multiprecision;
using namespace std;
using namespace chrono;
typedef cpp_int bigInt;

bigInt factorialItr(int n){
    bigInt result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

bigInt factorialRec(int n){
    if (n == 0 || n == 1) return 1;
    return n * factorialRec(n - 1);
}

template <typename Func>
double execTime(Func func, int n){
    auto start = chrono::high_resolution_clock::now();
    func(n);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::duration<double, micro>>(end - start).count();
    return duration;
}

void avgSpeed(int arrayN[10], int size, int test){
    cout << "\nRata-Rata Kecepatan:\n";

    for (int i = 0; i < size; ++i){
        int n = arrayN[i];
        double totalItrTime = 0;
        double totalRecTime = 0;

        for (int j = 0; j < test; ++j) {
            totalItrTime += execTime(factorialItr, n);
            totalRecTime += execTime(factorialRec, n);
        }

        double avgItrTime = totalItrTime/test;
        double avgRecTime = totalRecTime/test;

        cout << "n = " << n << " -> ";
        if (avgItrTime < avgRecTime){
            double dif = avgRecTime - avgItrTime;
            cout << "Iteratif lebih cepat ";
            if (dif >= 1000000){
                cout << dif/1000000 << " detik\n";
            } else if (dif >= 1000){
                cout << dif/1000 << " milidetik\n";
            } else {
                cout << dif << " mikrodetik\n";
            }
        } else {
            double dif = avgItrTime - avgRecTime;
            cout << "Rekursif lebih cepat ";
            if (dif >= 1000000){
                cout << dif/1000000 << " detik\n";
            } else if (dif >= 1000){
                cout << dif/1000 << " milidetik\n";
            } else{
                cout << dif << " mikrodetik\n";
            }
        }
    }
}

void speedPerTest(int arrayN[10], int size, int test){
    cout << "\nPerbandingan Kecepatan:\n";

    for (int i = 0; i < size; ++i){
        int n = arrayN[i];
        int itrFast = 0;
        int recFast = 0;

        for (int j = 0; j < test; ++j){
            double itrT = execTime(factorialItr, n);
            double recT = execTime(factorialRec, n);

            if (itrT < recT){
                ++itrFast;
            } else {
                ++recFast;
            }
        }
        cout << "n = " << n << " -> Iteratif lebih cepat " << itrFast << " kali | Rekursif lebih cepat " << recFast << " kali\n";
    }
}

int main(){
    // test n besar -> int arrayN[10] = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000};
    int arrayN[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    const int test = 20;

    cout << "Iteratif\n";
    for (int i = 0; i < 10; ++i){
        int n = arrayN[i];
        double ttlTime = 0;

        for (int j = 0; j < test; ++j){
            ttlTime += execTime(factorialItr, n);
        }

        double avgTime = ttlTime/test;
        if (avgTime >= 1000000){
            cout << "n = " << n << " -> " << avgTime/1000000 << " detik\n";
        } else if (avgTime >= 1000) {
            cout << "n = " << n << " -> " << avgTime/1000 << " milidetik\n";
        } else {
            cout << "n = " << n << " -> " << avgTime << " mikrodetik\n";
        }
    }

    cout << "\nRekursif\n";
    for (int i = 0; i < 10; ++i){
        int n = arrayN[i];
        double ttlTime = 0;

        for (int j = 0; j < test; ++j){
            ttlTime += execTime(factorialRec, n);
        }

        double avgTime = ttlTime/test;
        if (avgTime >= 1000000){
            cout << "n = " << n << " -> " << avgTime/1000000 << " detik\n";
        } else if (avgTime >= 1000){
            cout << "n = " << n << " -> " << avgTime/1000 << " millidetik\n";
        } else{
            cout << "n = " << n << " -> " << avgTime << " mikrodetik\n";
        }
    }
    avgSpeed(arrayN, 10, test);
    speedPerTest(arrayN, 10, test);
}
