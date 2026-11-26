class Solution {
public:
    bool canAliceWin(int n) {
        int stones = 10;
        int turns = 0;

        while (n >= stones) {
            n -= stones;
            stones--;
            turns++;
        }

        return turns % 2 == 1;
    }
};