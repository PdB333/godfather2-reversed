// FUNC_NAME: SomeNode::InitFromData
uint __thiscall SomeNode::InitFromData(void *thisNode, int *dataBlock, uint8_t *extraData, float someFloat)
{
    uint result;

    result = (uint)thisNode & 0xffffff00; // Actually in_EAX, but likely this? Unclear

    if (extraData != nullptr && dataBlock != nullptr && thisNode != nullptr) {
        // Store pointer to extra data
        *(uint8_t **)((int)thisNode + 8) = extraData; // +0x08: ptr to extraData
        // Copy values from dataBlock (array of ints)
        *(int *)((int)thisNode + 0x4c) = dataBlock[0x18]; // +0x4c: value from dataBlock offset 0x60
        *(float *)((int)thisNode + 0x50) = someFloat; // +0x50: float passed via XMM0
        *(int *)((int)thisNode + 0x54) = dataBlock[0x19]; // +0x54: value from dataBlock offset 0x64
        int temp = dataBlock[0x1a]; // +0x58: value from dataBlock offset 0x68
        *(uint8_t *)((int)thisNode + 0x65) = 0; // +0x65: byte field
        *(int *)((int)thisNode + 0x58) = temp;
        *(uint8_t *)((int)thisNode + 0x66) = 0xff; // +0x66: byte field
        *(uint8_t *)((int)thisNode + 0x67) = 0xff; // +0x67: byte field
        *(int *)((int)thisNode + 0x68) = 1; // +0x68: some flag
        *(int16_t *)((int)thisNode + 0x6c) = 0; // +0x6c: short
        *(int16_t *)((int)thisNode + 0x4a) = 0; // +0x4a: short
        *(uint8_t *)((int)thisNode + 0x6e) = 0; // +0x6e: byte
        *(uint8_t *)((int)thisNode + 0x6f) = *extraData; // +0x6f: first byte of extraData

        // If dataBlock has a second pointer (offset 1), copy data from it
        if (dataBlock[1] != 0) {
            *(int *)((int)thisNode + 0x60) = *(int *)(dataBlock[1] + 4); // +0x60: copy from some sub-struct
        }

        // Magic sentinel check in extraData at +0x28 (0xdeadbeef)
        uint magicValue = *(uint *)(extraData + 0x28);
        if (magicValue != 0xdeadbeef) {
            *(uint *)((int)thisNode + 0x30) = magicValue; // +0x30: store magic value
        } else {
            *(uint *)((int)thisNode + 0x30) = 0; // Original code uses conditional assignment: -(magic != 0xdeadbeef) & magic
        }

        // If dataBlock has a valid first pointer, set up linked list / backlink
        if (*dataBlock != 0) {
            *(int **)((int)thisNode + 0x2c) = dataBlock; // +0x2c: store pointer to dataBlock
            dataBlock[2] = (int)thisNode; // link back
            uint firstVal = *(uint *)*dataBlock; // dereference dataBlock[0] (which is a pointer)
            *(uint *)((int)thisNode + 0x5c) = firstVal; // +0x5c: store value from pointed-to data
        }

        // Zero out a block of memory from +0xc to +0x2c (40 bytes? Actually 4x8=32)
        *(uint64_t *)((int)thisNode + 0xc) = 0;
        *(uint64_t *)((int)thisNode + 0x14) = 0;
        *(uint64_t *)((int)thisNode + 0x1c) = 0;
        *(uint64_t *)((int)thisNode + 0x24) = 0;

        // Build return value: originally (in_EAX & 0xffffff00) then shifted etc.
        // The result is formed as (0x01 << 8) | ((original uVar2 >> 8) & 0xFF)? Actually CONCAT31((int3)(uVar2 >> 8),1)
        // But uVar2 was from in_EAX, which we don't have. We'll approximate as 1 (the final high byte part)
        result = 0x100 | (result & 0xFF); // Simplified: set high byte to 1, low byte from original low byte?
    }

    return result;
}