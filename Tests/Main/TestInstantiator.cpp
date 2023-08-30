#define DOCTEST_CONFIG_IMPLEMENT

// #include "../doctest.h"
// #include "../../Main/src/IceRoot.h" 
// #include "../../Main/Memory/StackAllocator.h"
// #include "../../Main/Memory/Allocator.h"
// #include "../../Main/Math/IcicleMath.h"

#include "../doctest.h"
#include "IceRoot.h"
#include "StackAllocator.h"
#include "Allocator.h"
#include "IcicleMath.h"

namespace Icicle{
/**
 * USAGE: cmake -S . in tests directory, then make all, then executable will be out/TestInstantiator
 * 
 * https://github.com/doctest/doctest/blob/master/doc/markdown/tutorial.md
*/

int main(int argc, char* argv[]) {
    doctest::Context ctx;
    ctx.setOption("abort-after", 5);  // default - stop after 5 failed asserts
    ctx.applyCommandLine(argc, argv); // apply command line - argc / argv
    ctx.setOption("no-breaks", true); // override - don't break in the debugger
    int res = ctx.run();              // run test cases unless with --no-run
    if(ctx.shouldExit())              // query flags (and --exit) rely on this
        return res;                   // propagate the result of the tests
    // your actual program execution goes here - only if we haven't exited

    //Root iceroot = iceroot.getInstance();


    return res; // + your_program_res
}

TEST_CASE("Determine whether given pointer resides in stack") {
    Icicle::Root::getInstance()->startUp();
}

TEST_CASE("Stack Allocator") {

    uint8_t memory_block[10]; 
    StackAllocator* sa = new StackAllocator(sizeof(memory_block), memory_block);

    SUBCASE("allocating right amount of bytes") {
    
    // sa->allocate(16, 4); //not the way to do this
    // CHECK(sa->getSize() == 16);
    //printf(sa->getStart());
    }

    SUBCASE("template evaluation is different") {
        uint8_t memory_block[10]; 
        StackAllocator* sa = new StackAllocator(sizeof(memory_block), memory_block);
        sa->allocate(sizeof(memory_block), 1); //1 byte for each char??
        
    }
}
TEST_CASE("Memory Manager") {
    //need root
    

    SUBCASE("allocate and free are called correctly from memorymanager") {
        //should be two print statements if this works
    }

}

TEST_CASE("Math Lib") {
    int a = 10;
    int* ptr = &a;
    Icicle::ptr_add(ptr, 10);

}
TEST_CASE("Memory from stack allocator is freed correctly") {
    
}

TEST_CASE("Both top and bottom of stack initialized and freed correctly") {

}


}