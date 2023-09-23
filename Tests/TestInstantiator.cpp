#define CONFIG_CATCH_MAIN

#include "IceRoot.h"
#include "StackAllocator.h"
#include "Allocator.h"
#include "IcicleMath.h"

#include <catch2/catch_test_macros.hpp>



//TODO: header file?

/**
********************TESTS***************
* 
 *  cmake -S . in tests directory, then make all, then executable will be out/TestInstantiator
 * 
 * https://github.com/catchorg/Catch2/blob/devel/docs/tutorial.md#top
*/




//Icicle Namespace specific/white box?

namespace Icicle {

TEST_CASE("Stack Allocator") {

    std::cout << " testing things\n";

    uint8_t memory_block[10]; //is this on heap?
    StackAllocator* sa = new StackAllocator(sizeof(memory_block), memory_block);
    for (int i = 0; i < 10; i++) {
        memory_block[i] = 4;
    }

    sa->allocate(sizeof(memory_block),sizeof(uint8_t));


    //TODO: split these up into multiple tests?
    // allocating right amount of bytes;
    REQUIRE(sa->getSize() * sizeof(sa->getStart()) == 80);
    REQUIRE(sa->getStart() != nullptr); // sa is not pointing to memory_block? _start is not defined
    
}

    //template evaluation is different"
    
TEST_CASE("Template evaluation is diff") {
    printf("we're running tests");
    uint8_t memory_block[10];
    for (int i = 0; i < 10; i++) {
        memory_block[i] = 4;
    }
    StackAllocator* sa = new StackAllocator(sizeof(memory_block), memory_block);
    sa->allocate(sizeof(memory_block), 1); //1 byte for each char??

    }

TEST_CASE("Math Lib") {
    int a = 10;
    int* ptr = &a;
    Icicle::ptr_add(ptr, 10);

}
TEST_CASE("Check fopen") {
    const char* filename = "editor/textures/texture.png";
    FILE* fp = fopen(filename, "rb");
    REQUIRE(fp != NULL);
    fclose(fp);


}

#ifdef WIN32

TEST_CASE("Check fopen_s") {
    int err;
    FILE* stream;
    const char* filename = "editor/textures/texture.png";
    err = fopen_s(&stream, filename, "rb");
    if (err == 0)
    {
        printf("The file %s was opened\n", filename);
    }
    else
    {
        printf("The file %s was not opened\n", filename);
    }
    
    REQUIRE(err == 0);
    


    if (stream)
    {
        err = fclose(stream);
        if (err == 0)
        {
            printf("The file %s was closed\n", filename);
        }
        else
        {
            printf("The file %s was not closed\n", filename);
        }
    }
}
#endif // WIN32
TEST_CASE("Both top and bottom of stack initialized and freed correctly") {

}


}



//Black box tests, no namespace

TEST_CASE("Determine whether given pointer resides in stack") {
    Icicle::Root::getInstance()->startUp();
}

TEST_CASE("Render triangle where triangle is in memory manager") {
    Icicle::Root::getInstance()->startUp();


}