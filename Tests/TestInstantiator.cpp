#define CONFIG_CATCH_MAIN

#include "IceRoot.h"
#include "StackAllocator.h"
#include "Allocator.h"
#include "IcicleMath.h"

#include <catch2/catch_test_macros.hpp>



typedef unsigned long size_t;
//TODO: header file?

/**
 * USAGE: cmake -S . in tests directory, then make all, then executable will be out/TestInstantiator
 * 
 * https://github.com/catchorg/Catch2/blob/devel/docs/tutorial.md#top
*/

namespace Icicle {

TEST_CASE("Determine whether given pointer resides in stack") {
   Icicle::Root::getInstance()->startUp();
    }

TEST_CASE("Stack Allocator") {

    uint8_t memory_block[10]; //is this on heap?
    StackAllocator* sa = new StackAllocator(sizeof(memory_block), memory_block);

    sa->allocate(sizeof(memory_block), )


//TODO: split these up into multiple tests?
    // allocating right amount of bytes
    CHECK(sa->getSize() == 80);
    printf(sa->getStart()); // sa is not pointing to memory_block? _start is not defined
    

    //template evaluation is different"
    uint8_t memory_block[10]; 
    StackAllocator* sa = new StackAllocator(sizeof(memory_block), memory_block);
    sa->allocate(sizeof(memory_block), 1); //1 byte for each char??
        
    }

TEST_CASE("Memory Manager") {
    //need root
    

    // allocate and free are called correctly from memorymanager") {
        //should be two print statements if this works
    

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