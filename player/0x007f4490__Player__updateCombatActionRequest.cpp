// FUNC_NAME: Player::updateCombatActionRequest
// Address: 0x007f4490
// Manages reference-counted activation of a sub-action (type A/B) with associated data.
// Bitfields at +0x1b94: bit8=0x100 (actionA), bit9=0x200 (actionB), bit14=0x4000 (dirty/pending)
// Counter at +0x1eb0: ref count for current action
// Data at +0x1eac: parameter (e.g., target ID) from activation call
// Data at +0x1ea4, +0x1ea8: cleared when ref count reaches zero

void __thiscall Player::updateCombatActionRequest(Player* this, char enable, char type, uint someData)
{
    uint* flags = (uint*)((int)this + 0x1b94);
    int* refCount = (int*)((int)this + 0x1eb0);

    if (enable != '\0') {
        // Activate: set the appropriate flag based on sub-type
        if (type == '\0') {
            *flags = *flags | 0x100;  // bit8
        } else {
            *flags = *flags | 0x200;  // bit9
        }
        *refCount = *refCount + 1;
        *(uint*)((int)this + 0x1eac) = someData;
        *flags = *flags & 0xffffbfff;  // clear bit14 (0x4000)
        return;
    }

    // Deactivate: decrement ref count if positive
    if (0 < *refCount) {
        *refCount = *refCount - 1;
    }

    // If ref count reached zero, clear the appropriate flag and reset related fields
    if (*refCount == 0) {
        if (type == '\0') {
            *flags = *flags & 0xfffffeff;  // clear bit8
        } else {
            *flags = *flags & 0xfffffdff;  // clear bit9
        }
        *(uint*)((int)this + 0x1ea4) = 0;
        *(uint*)((int)this + 0x1ea8) = 0;
    }

    *flags = *flags & 0xffffbfff;  // clear bit14 always
    return;
}