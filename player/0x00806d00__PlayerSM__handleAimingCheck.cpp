// FUNC_NAME: PlayerSM::handleAimingCheck
void __fastcall PlayerSM::handleAimingCheck(void* thisPtr)
{
    char cVar1;
    int* pMatrixRow1;
    int* pMatrixRow2;
    int* pMatrixRow3;

    pMatrixRow1 = (int*)getMatrixRowPointer();   // FUN_00471610
    pMatrixRow2 = (int*)getMatrixRowPointer();   // FUN_00471610
    pMatrixRow3 = (int*)getMatrixRowPointer();   // FUN_00471610

    // Dot product of player's forward direction (from this+0x1c6c,0x1c70,0x1c74) with axes from the matrix
    float dotProduct = *(float*)((char*)thisPtr + 0x1c70) * *(float*)((char*)pMatrixRow2 + 0x24) +
                       *(float*)((char*)thisPtr + 0x1c6c) * *(float*)((char*)pMatrixRow1 + 0x20) +
                       *(float*)((char*)thisPtr + 0x1c74) * *(float*)((char*)pMatrixRow3 + 0x28);

    if (DAT_00d723c8 <= dotProduct)  // threshold cos angle
    {
        uint32_t weaponSlotCount = *(uint32_t*)((char*)thisPtr + 0x7a0);
        if (weaponSlotCount < 8)
        {
            int* weaponArray = (int*)((char*)thisPtr + 0x75c);
            if (weaponArray[weaponSlotCount * 2] == 0)  // weapon at slot is empty?
            {
                fallbackAction(); // FUN_00800670
                return;
            }
        }
        else
        {
            uint32_t flags = *(uint32_t*)((char*)thisPtr + 0x81c);
            if ((flags >> 9 & 1) == 0)
            {
                if ((flags >> 11 & 1) == 0)
                    goto LAB_00806d64;
                pMatrixRow1 = *(int**)((char*)thisPtr + 0x7a4);
            }
            else
            {
                pMatrixRow1 = *(int**)((char*)thisPtr + 0x7a8);
            }
            if (pMatrixRow1 == 0)
                goto LAB_00806d64;
        }
        cVar1 = checkAimActivation(thisPtr, 0); // FUN_008c9a80
        if (cVar1 != '\0')
        {
            return;
        }
        fallbackAction(); // FUN_00800670
        return;
    }
LAB_00806d64:
    fallbackAction(); // FUN_00800670
    return;
}