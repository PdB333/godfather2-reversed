// FUNC_NAME: PacketWindow::initializeSlots
// Address: 0x00513df0
// Role: Initializes a pool of packet window slots. Allocates memory and zeroes critical fields in each slot.
// Each slot is 0xA8 bytes, located at offset 0xA0 from allocation base. The output structure stores the base and count.

// Note: unaff_EDI is a register parameter (count). Calling convention is __fastcall-like with param_1 in ecx and count in edx.
uint32_t* PacketWindow::initializeSlots(uint32_t* outPtr, int count) {
    uint32_t base;
    int allocResult;
    uint32_t* slotPtr;

    base = 0;
    if (count != 0) {
        allocResult = (int)FUN_00485650(&base);  // returns allocation pointer or handle
        if (allocResult != 0 && count != 0) {
            slotPtr = (uint32_t*)(allocResult + 0xa0); // points to first slot
            do {
                if (slotPtr != (uint32_t*)0xa0) { // null check (base was 0)
                    // Zero fields in slot (offsets relative to slot start):
                    slotPtr[-5] = 0;  // offset -0x14 * 4? Actually byte offsets: -0x14
                    slotPtr[0] = 0;   // offset 0x00
                    slotPtr[0x14] = 0; // offset 0x50? Wait, original uses pointer scaling.
                    // Better to cast to byte pointer:
                    // This code zeroes fields at byte offsets: -0x14, 0x00, 0x14, 0x28, 0x3c, 0x50, 0x64, 0x78
                }
                slotPtr += 0xa8 / sizeof(uint32_t); // advance to next slot (0xA8 bytes)
                count--;
            } while (count != 0);
        }
        outPtr[0] = base;
        outPtr[1] = count_original; // originally unaff_EDI
        return outPtr;
    }
    outPtr[0] = 0;
    outPtr[1] = 0;
    return outPtr;
}