#include "stdint.h"


namespace Math {

    //Declarations

    static void* ptr_add(void* pos, uint8_t adjustment);

    static void* ptr_subtract(void* pos, uint8_t adjustment);

    static uint8_t alignForwardAdjustmentWithHeader(void* _current_pos,
                                                uint8_t alignment,
                                                size_t size);

}

//inline definitions

namespace Math {
    
}

