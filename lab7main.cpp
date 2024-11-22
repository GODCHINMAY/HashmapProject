#include "makeSeuss.hpp"
#include <cstdlib>
#include <ctime>

int main() {
    srand(time(NULL)); // Seed random number generator

    // Using first hash function and first collision method
    makeSeuss seuss1("DrSeuss.txt", "Seussout1.txt", true, true);
    seuss1.printCollisionCounts();

    // Using first hash function and second collision method
    makeSeuss seuss2("DrSeuss.txt", "Seussout2.txt", true, false);
    seuss2.printCollisionCounts();

    // Using second hash function and first collision method
    makeSeuss seuss3("DrSeuss.txt", "Seussout3.txt", false, true);
    seuss3.printCollisionCounts();

    // Using second hash function and second collision method
    makeSeuss seuss4("DrSeuss.txt", "Seussout4.txt", false, false);
    seuss4.printCollisionCounts();

    return 0;
}
