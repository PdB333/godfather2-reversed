// FUNC_NAME: TNLConnection::initializePacketFragment

// Function at 0x0059a060 - Initializes a packet fragment from a data buffer.
// The object at +0x8 holds buffer metadata: +0x2 (size), +0x4,0x8,0xc,0x10 (sequence bytes), +0x14 (count of sub-elements), +0x18 (data start).
// The fragment slot is allocated via FUN_00599aa0 (likely allocateFragmentSlot) using the sequence ID built from the 4 bytes.
void __fastcall TNLConnection::initializePacketFragment(void* this) // fastcall, this in ECX
{
    int bufferStatus;
    int fragmentSlot;
    int elementCount;
    short countShort;

    // Retrieve the internal buffer structure from this+0x8
    bufferStatus = *(int*)((int)this + 8);

    // Validate that the stored buffer size (uint16 at +0x2) matches the computed total size:
    // header (0x18) + elementCount * 0x14.
    if ((unsigned short)*(short*)(bufferStatus + 2) != *(int*)(bufferStatus + 0x14) * 0x14 + 0x18) {
        // Debug assertion: buffer size mismatch
        (*(code**)(*DAT_01205590 + 4))(); // calls error/assert handler
    }

    // Build a 32-bit sequence ID from four byte-sized fields at +0x4, +0x8, +0xC, +0x10
    int seqId = ((*(int*)(bufferStatus + 4) * 0x100 + *(int*)(bufferStatus + 8)) * 0x100 +
                  *(int*)(bufferStatus + 0xc)) * 0x100 + *(int*)(bufferStatus + 0x10);

    fragmentSlot = FUN_00599aa0(this, seqId); // allocateFragmentSlot(this, seqId)
    if (fragmentSlot == 0) {
        // Allocation failed – trigger assert
        (*(code**)(*DAT_01205590 + 4))();
        return;
    }

    elementCount = *(int*)(bufferStatus + 0x14);
    if (elementCount > 0xffff) {
        // Count overflow – assert
        (*(code**)(*DAT_01205590 + 4))();
    }

    countShort = (short)elementCount;
    if (countShort != 0) {
        // Initialize the fragment slot fields:
        *(int*)(fragmentSlot + 0x48) = 0;          // +0x48: flags/state? (cleared)
        *(short*)(fragmentSlot + 0x4c) = 1;        // +0x4c: fragment index? (set to 1)
        *(short*)(fragmentSlot + 0x4e) = countShort; // +0x4e: element count
        *(int*)(fragmentSlot + 0x54) = bufferStatus + 0x18; // +0x54: pointer to data payload
        *(short*)(fragmentSlot + 0x50) = 2;        // +0x50: fragment type (2 = data fragment?)
    }

    // Clear bits 0 and 2 of the slot's flags (+0x10)
    *(unsigned int*)(fragmentSlot + 0x10) &= 0xfffffffa;
    return;
}