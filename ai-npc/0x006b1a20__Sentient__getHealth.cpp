// FUNC_NAME: Sentient::getHealth
// Function at 0x006b1a20: returns a value at +0xC8 (200), but returns 0 if +0x16C (364) is non-zero (likely death/disable flag)
int __fastcall Sentient::getHealth(Sentient* this) {
    int health = *(int*)((uintptr_t)this + 200); // +0xC8: health or state value
    if (*(int*)((uintptr_t)this + 0x16C) != 0) { // +0x16C: isDead/disabled flag
        health = 0;
    }
    return health;
}