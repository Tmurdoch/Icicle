#ifndef DEBUG_H
#define DEBUG_H

#include <stdlib.h>

namespace Icicle {

#define ASSERTIONS_ENABLED 1
#define _DEBUG 1

#if ASSERTIONS_ENABLED == 1
#include <assert.h>
#endif


}
#endif