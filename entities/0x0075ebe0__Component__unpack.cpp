// FUNC_NAME: Component::unpack

void __thiscall Component::unpack(int thisPtr, BitStream *stream)
{
    int typeHash = (*(code **)stream)(); // virtual function call to get type hash? Or stream->getTypeHash()

    if (typeHash == 0x1b2d5c51) {
        // Type A: unpack transform data
        Component::unpackInternal1(thisPtr + 0x60);
        stream[0x18] = DAT_00d651ec;  // global constant
        stream[0x1f] = *(uint *)(thisPtr + 0xf0); // copy field at +0xf0
    }
    else if (typeHash == 0x27a0f69c) {
        // Type B: unpack physics data
        uint low4 = *(uint *)(thisPtr + 0x68); // from +0x68
        uint64_t vec = *(uint64_t *)(thisPtr + 0x60); // from +0x60 (likely a Vec2)
        int temp = Component::getGlobalSomething(); // FUN_00471610
        uint64_t packed = ((uint64_t)*(uint *)(temp + 0x34) << 32) | (uint32_t)vec;
        int temp2 = Component::getGlobalSomething(); // FUN_00471610
        Component::copyToStream(&packed, temp2 + 0x20, 0, DAT_00d64c8c, 0, 1); // FUN_00754d30
    }
    return;
}