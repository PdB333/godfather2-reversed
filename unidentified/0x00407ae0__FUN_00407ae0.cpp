#include <cstdint>

extern "C" void FUN_004abf50(int ptr);

extern "C" void FUN_00407ae0()
{
    int in_EAX;

    if (in_EAX != 0) {
        FUN_004abf50(in_EAX);
    }
}