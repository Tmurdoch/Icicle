#include <stddef.h>
#include <cstdint>

namespace Icicle {

    //Declarations

    void* ptr_add(void* pos, size_t adjustment);
    const void* ptr_add(const void* p, size_t x);

    void* ptr_subtract(void* pos, size_t adjustment);
    const void* ptr_subtract(const void* pos, size_t adjustment);


    /**
     * calculates how much padding needs to be added before _current_pos
     *  to achieve the specified alignment while leaving space for the 
     * allocation header.
    */
    uint8_t alignForwardAdjustmentWithHeader(void* _current_pos,
                                                uint8_t alignment);



}