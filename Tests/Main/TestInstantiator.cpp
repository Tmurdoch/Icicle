#define DOCTEST_CONFIG_IMPLEMENT

#include "../_deps/doctest-src/doctest/doctest.h"
#include "../../Main/src/IceRoot.h" //All we should have to include to
//implement game

/**
 * USAGE: cmake -S . in tests directory, then make all, then executable will be out/TestInstantiator
*/

int main(int argc, char** argv) {
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

TEST_CASE("vectors can be sized and resized") {
    std::vector<int> v(5);

    REQUIRE(v.size() == 5);
    REQUIRE(v.capacity() >= 5);

    SUBCASE("adding to the vector increases its size") {
        v.push_back(1);

        CHECK(v.size() == 6);
        CHECK(v.capacity() >= 6);
    }
    SUBCASE("reserving increases just the capacity") {
        v.reserve(6);

        CHECK(v.size() == 5);
        CHECK(v.capacity() >= 6);
    }
}

TEST_CASE("Stack Allocator") {

    char memory_block[10]; 
    StackAllocator* sa = new StackAllocator(sizeof(memory_block), memory_block);

    SUBCASE("allocating right amount of bytes") {
    StackAllocator *sa;
    sa->allocate(16, 4);
    CHECK(sa->getSize() == 16);
    //printf(sa->getStart());
    }
}

TEST_CASE("Memory from stack allocator is freed correctly") {
    
}

TEST_CASE("Both top and bottom of stack initialized and freed correctly") {

}

TEST_CASE("Determine whether given pointer resides in stack") {
    
}