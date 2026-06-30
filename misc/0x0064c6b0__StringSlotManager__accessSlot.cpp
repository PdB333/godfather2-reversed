// FUNC_NAME: StringSlotManager::accessSlot
void __thiscall StringSlotManager::accessSlot(char *outputString) {
    uint currentIndex = *(uint *)(this + 0x18); // +0x18: current slot index (counter)
    uint maxSlots = *(uint *)(this + 0x2c);    // +0x2c: total number of slots

    if (maxSlots < currentIndex) {
        // All slots exhausted; set overflow flag
        *(byte *)(this + 0x1c) = 1; // +0x1c: overflow flag
    } else {
        byte *bitfield = *(byte **)(this + 0xc); // +0xc: pointer to bitfield (one bit per slot)
        byte bitMask = (byte)(1 << (currentIndex & 7));
        byte bitValue = bitfield[currentIndex >> 3] & bitMask;

        // Increment slot index for next call
        *(uint *)(this + 0x18) = currentIndex + 1;

        if (bitValue != 0) {
            // Slot is occupied: read string from slot into output
            uint randomOffset = 0;
            FUN_0064b9e0(8, &randomOffset); // Get random byte (0-255) for offset? Or slot selection?
            char *slotBuffer = (char *)(this + 0x38 + (randomOffset & 0xff)); // +0x38: start of string buffer array
            FUN_0065ae90(slotBuffer); // Possibly copies string from slotBuffer to internal?
            // Copy string from slotBuffer to outputString
            char *src = (char *)(this + 0x38);
            int diff = (int)outputString - (int)src;
            char c;
            do {
                c = *src;
                src[diff] = c;
                src++;
            } while (c != '\0');
        } else {
            // Slot is free: store input string into slot
            uint thisPtr = (uint)this;
            FUN_0065ae90(outputString); // Possibly copies outputString to internal?
            // Copy string from outputString to slot buffer at this+0x38
            char *dst = (char *)(this + 0x38);
            int diff = (int)(this + 0x38) - (int)outputString;
            char c;
            do {
                c = *outputString;
                outputString[diff] = c;
                outputString++;
            } while (c != '\0');
        }
    }
}