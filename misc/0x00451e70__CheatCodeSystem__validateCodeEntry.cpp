// FUNC_NAME: CheatCodeSystem::validateCodeEntry
undefined1 __thiscall CheatCodeSystem::validateCodeEntry(int inputKey)
{
    // Fields at offsets +0x1a0, +0x1a4, +0x1a8, +0x1ac represent four code digits (0-32 each)
    // They are combined into a single key using base-33 (0x21) encoding:
    // key = (((digit0 * 33 + digit1) * 33 + digit2) * 33 + digit3)
    int computedKey = (((this->digit0 * 0x21 + this->digit1) * 0x21 + this->digit2) * 0x21 + this->digit3);
    if (computedKey == inputKey) {
        // Return the reward byte at +0x1c0 if the code matches
        return this->rewardByte;  // offset +0x1c0
    }
    return 0;
}