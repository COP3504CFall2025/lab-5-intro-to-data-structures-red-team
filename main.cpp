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

    LLDQ<int> sta;
    sta.pushBack(1);
    sta.pushBack(2);
    sta.pushBack(3);
    sta.pushBack(4);
    sta.pushBack(5);
    // sta.pop();
    // deq.pushFront(1);
    // deq.pushFront(2);
    // deq.pushFront(3);
    // deq.pushFront(4);
    // std::cout << sta.front() << std::endl;

    // deq.pushBack(2);
    // deq.pushFront(3);
    // deq.pushBack(4);

    // std::cout << sta.getSize() << std::endl;
    while(sta.getSize() > 0) {
        // std::cout << sta.getSize() << std::endl;
        std::cout << sta.popBack() << std::endl;
    }

    return 0;
}


#endif