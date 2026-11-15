#include <iostream>
using namespace std;
class Solution {
  public:
    int nthDay(int d, int n) {
        int save = n % 7;
        return (d - save + 7) % 7;
    }
};