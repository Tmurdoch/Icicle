#include "IcicleMath.h"

//inline definitions

//taken from https://github.com/tiagovcosta/aquaengine/blob/aea6de9f47ba0243b90c144dee4422efb2389cc7/AquaEngine/Utilities/PointerMath.h#L4

namespace Icicle {


    void* ptr_add(void* p, size_t x) {
        return (void*)(reinterpret_cast<uintptr_t>(p)+x);
    }

    const void* ptr_add(const void* p, size_t x) {
		return (const void*)(reinterpret_cast<uintptr_t>(p)+x);
	}

    void* ptr_subtract(void* p, size_t x) {
        return (void*)(reinterpret_cast<uintptr_t>(p)-x);
    }

    const void* ptr_subtract(const void* p, size_t x) {
        return (const void*)(reinterpret_cast<uintptr_t>(p)-x);
    }

    uint8_t alignForwardAdjustment(const void* address, uint8_t alignment) {
        uint8_t adjustment = alignment - (reinterpret_cast<uintptr_t>(address)& static_cast<uintptr_t>(alignment - 1));

        if (adjustment == alignment) 
            return 0; //already aligned
        
        return adjustment;
    }

    // template<typename T>
    uint8_t alignForwardAdjustmentWithHeader(void* address, uint8_t alignment) {
        // if (__alignof(T) > alignment)
        //     alignment = __alignof(T);
        
        // uint8_t adjustment = sizeof(T) + alignForwardAdjustment(Math::ptr_add(address, sizeof(T)), alignment);
        uint8_t adjustment = alignForwardAdjustment(address, alignment);
        return adjustment;
    }

    
}