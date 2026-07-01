// FUNC_NAME: Player::canUseAbility
bool __fastcall Player::canUseAbility(int thisPtr)
{
    char cVar1;
    int uVar2;

    // Check if ability bit 2 is set in flags at +0x128
    if ((*(uint *)(thisPtr + 0x128) >> 2 & 1) != 0) {
        uVar2 = 100;
        FUN_007ab110(100); // likely some ability cost/cooldown check
        cVar1 = FUN_0054f220(uVar2); // likely checks if ability is available
        if (cVar1 == '\0') {
            return false;
        }
    }
    return true;
}