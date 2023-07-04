
#include "..\lab03\histogram.h"

#include <cassert>

void check_red_color() {
    bool answer = check_color("red");
    assert(answer == false);
}

void check_blue_color() {
    bool answer = check_color("blue");
    assert(answer == true);
}

int main() {
    check_red_color();
    check_blue_color();
}