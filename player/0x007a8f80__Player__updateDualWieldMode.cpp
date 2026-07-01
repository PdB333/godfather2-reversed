// FUNC_NAME: Player::updateDualWieldMode
void __fastcall Player::updateDualWieldMode(void* thisPtr)
{
    char cVar1;
    int iVar2;
    bool bVar3;
    undefined4 uVar4;
    undefined4 uVar5;

    cVar1 = Game::isInActiveMode(); // 0x00481620
    if (((cVar1 != '\0') && ((*(byte*)((int)thisPtr + 0x8e6) & 1) == 0)) &&
        ((*(uint*)((int)thisPtr + 0x249c) >> 1 & 1) != 0))
    {
        iVar2 = Player::getCurrentWeaponHandedness(); // 0x007a5f40
        bVar3 = iVar2 == 2;
        if ((bVar3 != *(bool*)((int)thisPtr + 0x31c8)) || (*(char*)((int)thisPtr + 0x205c) != '\0'))
        {
            if (bVar3)
            {
                uVar5 = 1;
                uVar4 = 2;
            }
            else
            {
                uVar5 = 2;
                uVar4 = 1;
            }
            Player::setWeaponMode(uVar4, uVar5); // 0x00691700
            *(bool*)((int)thisPtr + 0x31c8) = bVar3;
            *(undefined1*)((int)thisPtr + 0x205c) = 0;
        }
    }
    return;
}