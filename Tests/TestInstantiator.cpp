#define CONFIG_CATCH_MAIN

#include "IceRoot.hpp"
#include "StackAllocator.hpp"
#include "Allocator.hpp"
#include "IcicleMath.hpp"

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

	TEST_CASE("initialize") {
		Icicle::Root::getInstance()->startUp();
		Icicle::Root::getInstance()->run();


		SECTION("Test case while running") {
			REQUIRE(Icicle::Root::getInstance()->window->isInstanceInitialized() == true);
		}
	}

	TEST_CASE("Render Image") {

	}

	TEST_CASE("Stack Allocator") {

		std::cout << " testing things\n";

		uint8_t memory_block[10]; //is this on heap?
		StackAllocator* sa = new StackAllocator(sizeof(memory_block), memory_block);
		for (int i = 0; i < 10; i++) {
			memory_block[i] = 4;
		}

		sa->allocate(sizeof(memory_block), sizeof(uint8_t));


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

}


//Black box tests, no namespace

