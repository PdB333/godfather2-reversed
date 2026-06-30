// FUNC_NAME: GetThreadLocalGlobalData

#include <cstdint>
#include <intrin.h>

extern uint32_t DAT_012054ec;
extern uint32_t DAT_012054f0;

// Returns one of two global values depending on a thread-specific condition.
// Reads TLS pointer from FS:[0x2C], then dereferences it and checks offset 0x34.
// If that value != 1, returns DAT_012054f0; otherwise returns DAT_012054ec.
uint32_t GetThreadLocalGlobalData()
{
    uint32_t tlsPointer = __readfsdword(0x2C);                 // FS:[0x2C] -> TLS data pointer
    uint32_t* tlsData = *reinterpret_cast<uint32_t**>(tlsPointer); // Dereference to get base of TLS data
    uint32_t checkValue = tlsData[0x34 / sizeof(uint32_t)];    // Offset 0x34 bytes (0xD dwords)
    if (static_cast<int32_t>(checkValue) != 1)
        return DAT_012054f0;
    else
        return DAT_012054ec;
}