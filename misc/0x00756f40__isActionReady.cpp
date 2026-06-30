// FUNC_NAME: isActionReady
// Function at 0x00756f40: checks if bit 12 in flags at +0xa8 is set and int at +0x130 equals 3
bool __thiscall isActionReady(void *this)
{
    if (((*(uint *)((int)this + 0xa8) >> 12) & 1) != 0 &&
        (*(int *)((int)this + 0x130) == 3))
    {
        return true;
    }
    return false;
}