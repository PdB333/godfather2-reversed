// FUNC_NAME: Entity::setAnimationState
void __thiscall Entity::setAnimationState(int thisPtr, int newState) {
    // thisPtr offset fields: 0x18 -> AnimationData pointer, 0xd4 -> some value, 0xe8 -> current state
    // AnimationData offset 0x2c -> packed animation state word
    uint packedWord;
    uint uVar1;
    uint uVar2;
    uint uVar3;

    *(int *)(thisPtr + 0xe8) = newState; // store new state

    if (newState != 2 && newState != 3) {
        // For non-special states, directly copy a value into the animation data
        *(uint *)(*(int *)(thisPtr + 0x18) + 0x2c) = *(uint *)(thisPtr + 0xd4);
        FUN_009e9c50(*(int *)(thisPtr + 0x18), 1); // force-update animation
        return;
    }

    // Special handling for states 2 and 3 (likely idle/walk blend states)
    uVar2 = 0x14; // initial animation index for state 3
    if (newState == 2) {
        uVar2 = 0xd; // animation index for state 2
    }

    packedWord = *(uint *)(*(int *)(thisPtr + 0x18) + 0x2c);
    uVar3 = packedWord & 0xc0000000; // top two bits

    // Decode the packed animation word based on top bits
    if (uVar3 == 0) {
        uVar1 = packedWord >> 0x10; // high 16 bits (animation ID?)
    } else if (uVar3 == 0x40000000) {
        // Read from a table at offset (packedWord*4 + 2)
        uVar1 = (uint)*(ushort *)(packedWord * 4 + 2);
    } else if (uVar3 == 0xc0000000) {
        // Read from a table at offset (packedWord*4 + 0x4e)
        uVar1 = (uint)*(ushort *)(packedWord * 4 + 0x4e);
    } else {
        uVar1 = 0;
        goto SET_PACKED;
    }
    uVar1 = uVar1 & 0xfff; // mask low 12 bits

SET_PACKED:
    *(int *)(thisPtr + 0xb0) = 0; // clear some flag
    // Build new packed word: high 16 bits from decoded uVar1, low 16 bits from uVar2 with mask 0x3e0
    *(uint *)(*(int *)(thisPtr + 0x18) + 0x2c) = (uVar1 << 0x10) | uVar2 | 0x3e0;
    FUN_009e9c50(*(int *)(thisPtr + 0x18), 0); // update animation (smooth transition)
}