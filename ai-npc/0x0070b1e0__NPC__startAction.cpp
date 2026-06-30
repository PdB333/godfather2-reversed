// FUNC_NAME: NPC::startAction
void __fastcall NPC::startAction(NPC* this)
{
    ActionData* pActionData = *(ActionData**)((char*)this + 0x1b0);
    if (pActionData != 0) {
        if (pActionData->actionState != 5) {
            pActionData->actionState = 5;
        }
        pActionData = *(ActionData**)((char*)this + 0x1b0); // reload
        int randomBase = SomeRandomFunction(); // FUN_0043b490
        int randomValue = RandomInRange(8, 21, randomBase); // FUN_00540c60
        pActionData->actionTimer = randomValue;
        pActionData->field_0x84 = *(float*)((char*)this + 0x358);
        pActionData->field_0x88 = *(float*)((char*)this + 0x354);
        pActionData->field_0x184 = *(float*)((char*)this + 0x35c);
        pActionData->field_0x188 = *(float*)((char*)this + 0x360);
        if (((*(unsigned char*)((char*)this + 0x39f) & 1) == 0) && (*(void**)((char*)this + 0x2d0) != 0)) {
            *(unsigned short*)((char*)this + 0x39e) |= 0x100;
            PlaySomeAnimation(*(void**)((char*)this + 0x2d0)); // FUN_009f1f90
            CompleteSomeAction(); // FUN_009f0190
            return;
        }
    }
}