
#include <stdio.h>
#include <iostream>
#define infinity  static_cast<unsigned long>(~0);
using namespace std;
class test{
    public:
    int u;
    int v;

    test(int a, int b): u(a), v(b){}
    inline int getOtherVertex(int curr){
        if(curr ==u){
            return v;
        }else{
            return u;
        }
    }
};
int main(){
    test a = test(2, 3);
    unsigned long f = infinity;
    cout << f << endl; 

    return 0;
}