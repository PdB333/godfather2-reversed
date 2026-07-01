//FUNC_NAME: Player::checkAndSetFlag
// Address: 0x0096dad0
// Role: Checks if a condition is met (byte at +500 non-zero, some global condition true, state == 7, and bit 18 of flags at +0x6f4 is clear), then sets bit 18 and calls another function.

void __thiscall Player::checkAndSetFlag(Player* this)
{
    char cVar1;

    // Check if the byte at offset 0x1F4 (500) is non-zero (likely an active flag)
    if (*(char*)((int)this + 0x1F4) != '\0') {
        // Call a global function that returns a boolean (likely checks some game state)
        cVar1 = isSomeConditionTrue();
        if (((cVar1 != '\0') && (*(int*)((int)this + 0xDC) == 7)) &&
            ((*(uint*)((int)this + 0x6F4) >> 0x12 & 1) == 0)) {
            // Set bit 18 (0x40000) in the flags at offset 0x6F4
            *(uint*)((int)this + 0x6F4) = *(uint*)((int)this + 0x6F4) | 0x40000;
            // Call another function to perform the action
            triggerAction();
            return;
        }
    }
    return;
}