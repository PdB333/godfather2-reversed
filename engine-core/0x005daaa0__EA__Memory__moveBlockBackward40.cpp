// FUNC_NAME: EA::Memory::moveBlockBackward40
void __thiscall EA::Memory::moveBlockBackward40(int srcEnd, int srcStart) // Note: dest pointer passed in EAX (implicit)
{
    // This function copies 40-byte blocks backward from srcEnd towards srcStart,
    // writing to a destination pointer that is also decremented.
    // It is used for overlapping memory moves when dest > src (rightward shift).
    uint8_t* pSrc = (uint8_t*)srcEnd;
    uint8_t* pDest = (uint8_t*)EAX; // EAX holds the destination end pointer
    uint8_t* pSrcStart = (uint8_t*)srcStart;

    // Copy in reverse to avoid overwriting when dest is after source
    while (pSrc != pSrcStart) {
        pSrc -= 0x28;          // Move source pointer back 40 bytes
        pDest -= 5;            // Move destination pointer back 5 * 8 = 40 bytes (in undefined8 units)

        // Copy 40 bytes (5 * 8) in one chunk
        *(uint64_t*)(pDest + 0) = *(uint64_t*)(pSrc + 0);
        *(uint64_t*)(pDest + 8) = *(uint64_t*)(pSrc + 8);
        *(uint64_t*)(pDest + 16) = *(uint64_t*)(pSrc + 16);
        *(uint64_t*)(pDest + 24) = *(uint64_t*)(pSrc + 24);
        *(uint64_t*)(pDest + 32) = *(uint64_t*)(pSrc + 32);
    }
}