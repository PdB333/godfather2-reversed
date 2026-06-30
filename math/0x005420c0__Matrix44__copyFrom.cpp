// FUNC_NAME: Matrix44::copyFrom
void __thiscall Matrix44::copyFrom(void* thisPtr, const void* srcPtr)
{
    // Copy 64 bytes (16 dwords) from src to this
    *(uint32_t*)thisPtr = *(uint32_t*)srcPtr;
    *(uint32_t*)((uint8_t*)thisPtr + 4) = *(uint32_t*)((uint8_t*)srcPtr + 4);
    *(uint32_t*)((uint8_t*)thisPtr + 8) = *(uint32_t*)((uint8_t*)srcPtr + 8);
    *(uint32_t*)((uint8_t*)thisPtr + 12) = *(uint32_t*)((uint8_t*)srcPtr + 12);
    *(uint32_t*)((uint8_t*)thisPtr + 16) = *(uint32_t*)((uint8_t*)srcPtr + 16);
    *(uint32_t*)((uint8_t*)thisPtr + 20) = *(uint32_t*)((uint8_t*)srcPtr + 20);
    *(uint32_t*)((uint8_t*)thisPtr + 24) = *(uint32_t*)((uint8_t*)srcPtr + 24);
    *(uint32_t*)((uint8_t*)thisPtr + 28) = *(uint32_t*)((uint8_t*)srcPtr + 28);
    *(uint32_t*)((uint8_t*)thisPtr + 32) = *(uint32_t*)((uint8_t*)srcPtr + 32);
    *(uint32_t*)((uint8_t*)thisPtr + 36) = *(uint32_t*)((uint8_t*)srcPtr + 36);
    *(uint32_t*)((uint8_t*)thisPtr + 40) = *(uint32_t*)((uint8_t*)srcPtr + 40);
    *(uint32_t*)((uint8_t*)thisPtr + 44) = *(uint32_t*)((uint8_t*)srcPtr + 44);
    *(uint32_t*)((uint8_t*)thisPtr + 48) = *(uint32_t*)((uint8_t*)srcPtr + 48);
    *(uint32_t*)((uint8_t*)thisPtr + 52) = *(uint32_t*)((uint8_t*)srcPtr + 52);
    *(uint32_t*)((uint8_t*)thisPtr + 56) = *(uint32_t*)((uint8_t*)srcPtr + 56);
    *(uint32_t*)((uint8_t*)thisPtr + 60) = *(uint32_t*)((uint8_t*)srcPtr + 60);
}