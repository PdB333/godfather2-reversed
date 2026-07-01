// FUNC_NAME: Player::handleActionInput
undefined4 __thiscall Player::handleActionInput(Player* this, int actionId)
{
    int* piVar1;
    char cVar2;
    int iVar3;
    undefined4 uVar4;
    undefined4 hintTextId; // likely a string ID or GUID
    undefined4 hintParam1;
    undefined1 hintParam2;

    if (DAT_00d876b0 < (float)this->field_0xB0) // global game time/threshold < some cooldown/state
    {
        iVar3 = FUN_00466840(); // getPrimaryAction()
        if ((actionId == iVar3) || (iVar3 = FUN_00466860(), actionId == iVar3)) // matches primary or secondary action
        {
            this->tutorialFlag = 1; // offset +0x13A4, set to 1
            piVar1 = DAT_01129924; // singleton pointer (likely GodfatherGameManager)
            if (this->inTutorial != '\0') // offset +0x13A5, check if tutorial active
            {
                hintTextId = DAT_0112ddd8; // constant hint/dialog ID
                hintParam1 = 0;
                hintParam2 = 0;
                FUN_00408a00(&hintTextId, 0); // showHintDialog()
                return 0;
            }
            if ((DAT_01129924 != (int*)0x0) && (cVar2 = FUN_009c7920(), cVar2 != '\0')) // isGameActive()
            {
                piVar1->callVtableMethod4(); // offset 0x4 virtual call on singleton
            }
            this->callVtableMethod0x2c(); // offset 0x2c virtual call on this (update)
        }
        else
        {
            if (actionId == 8)
            {
                FUN_00925470(); // handleActionPause()
                return 0;
            }
            if (actionId == 9)
            {
                uVar4 = FUN_009254a0(); // handleActionMenu()
                return uVar4;
            }
        }
    }
    return 0;
}