// FUNC_NAME: MemPool::releaseSlotsDebug
void __thiscall MemPool::releaseSlotsDebug()
{
    uint countMinusOne = *(uint *)(this + 0x40); // +0x40: number of allocated slots minus one? (if 0 or 1 then no iter)
    if (countMinusOne != 0 && countMinusOne != 1) {
        uint *ptr = (uint *)(this + 8); // +0x08: start of slot array (each slot is 4 dwords = 16 bytes)
        for (uint i = 0; i < countMinusOne - 1; ++i) {
            // Avoid overwriting a sentinel slot? (compare to constant address 8)
            if (ptr != (uint *)8) {
                ptr[-2] = 0xbadbadba; // debug marker: slot status freed
                ptr[-1] = 0xbeefbeef;
                ptr[0] = 0xeac15a55;
                ptr[1] = 0x91100911;
            }
            ptr += 4; // advance to next 16‑byte slot
        }
        *(uint *)(this + 0x40) = 0; // reset count
    } else {
        *(uint *)(this + 0x40) = 0;
    }
}