#ifdef MAIN

#include "ABDQ.hpp"
#include "ABQ.hpp"
#include "ABS.hpp"
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include "LLDQ.hpp"
#include "LLQ.hpp"
#include "LLS.hpp"
#include <iostream>

/*
    - LEAVE THE IFDEF GUARDS TO KEEP YOUR MAIN WITHOUT CONFLICTING WITH GRADESCOPE!
    - Test your code in this main and run locally with the RunMain configuration in CLion, or
    through your own command line compilation. Make sure to add flag "-DMAIN" to your compilation so this
    main function can compile.

*/

int main() {

    ABDQ<int> deq(3);
    deq.pushFront(1);
    deq.pushFront(2);
    deq.pushFront(3);
    deq.pushFront(4);

    // deq.pushBack(2);
    // deq.pushFront(3);
    // deq.pushBack(4);

    for(size_t i = 0; i < deq.getSize(); i++) {
        std::cout << deq.popFront() << std::endl;
    }

    return 0;
}


#endif