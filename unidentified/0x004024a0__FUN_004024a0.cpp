#include <windows.h>
#include <cstdint>

using undefined4 = std::uint32_t;

void FUN_00402a80();

void FUN_004024a0(void)
{
    undefined4* in_EAX;
    LARGE_INTEGER local_8;

    in_EAX[0x00] = 0;
    in_EAX[0x01] = 0;
    in_EAX[0x02] = 0;
    in_EAX[0x03] = 0;
    in_EAX[0x04] = 0;
    in_EAX[0x05] = 0;
    in_EAX[0x0b] = 0xfe16702f;
    in_EAX[0x0d] = reinterpret_cast<undefined4>(&PTR_LAB_00e2f0cc);
    in_EAX[0x0e] = 0;
    in_EAX[0x0f] = 0;
    in_EAX[0x10] = 0;
    in_EAX[0x11] = 0;

    QueryPerformanceCounter(&local_8);
    in_EAX[0x16] = static_cast<undefined4>(local_8.LowPart);
    in_EAX[0x17] = static_cast<undefined4>(local_8.HighPart);

    in_EAX[0x1d] = 0;
    in_EAX[0x3b] = 0;

    FUN_00402a80();
}