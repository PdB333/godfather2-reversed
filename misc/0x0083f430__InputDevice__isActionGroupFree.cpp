// FUNC_NAME: InputDevice::isActionGroupFree
bool InputDevice::isActionGroupFree(ActionGroup* group) const {
    // Must have valid this and group
    if (!this || !group)
        return true;

    // First set: actions defined by group->firstBaseIndex (uint16 at +0x10)
    // and count from group->firstCount (byte at +0x14).
    uint firstCount = group->firstCount;
    if (firstCount != 0) {
        for (uint i = 0; i < firstCount; i++) {
            // Calculate index into action state array (base at +0x24)
            uint16 idx = (group->firstBaseIndex + (uint16)i) & 0xFFFF;
            // Each state is 0x10 bytes; flags read at offset 10 from state start
            uint16 flags = *(uint16*)(this->actionStatesArrPtr + idx * 0x10 + 10);
            // Bits 0x400 (10) and 0x800 (11) indicate active/pressed state
            if (flags & 0xC00)
                return false;
        }
    }

    // Second set: base index at +0x16 (uint16), total count is
    // sum of bytes at +0x1c and +0x15 (two separate counts combined).
    uint secondCount = (uint)group->secondAdditionalByte + (uint)group->secondCount;
    if (secondCount != 0) {
        for (uint i = 0; i < secondCount; i++) {
            uint16 idx = (group->secondBaseIndex + (uint16)i) & 0xFFFF;
            // Different array at this+0x30 (analog/alt action states?)
            uint16 flags = *(uint16*)(this->otherActionStatesArrPtr + idx * 0x10 + 10);
            if (flags & 0xC00)
                return false;
        }
    }

    return true;
}