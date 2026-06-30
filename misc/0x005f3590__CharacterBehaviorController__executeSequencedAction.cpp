// FUNC_NAME: CharacterBehaviorController::executeSequencedAction
void __thiscall CharacterBehaviorController::executeSequencedAction(int targetId)
{
    if (this == 0) return;

    // stepSize is 1 or 2 depending on a flag in the controller state (+0x08 -> +0x08 bit 0)
    char stepSize = ((*(byte*)(*(int*)(this + 0x08) + 0x08) & 1) != 0) + 1;

    // Current index into the behavior list (wrap around using count at +0x6F)
    char curIndex = *(char*)(this + 0x6E) - stepSize;
    if (curIndex < 0)
        curIndex += *(char*)(this + 0x6F);

    byte numElements = *(byte*)(this + 0x6F); // total size of list
    char processedCount = 0;

    // Search primary list (at offset +0x0C) for an element whose +0x20 matches targetId
    do {
        if ((char)numElements <= curIndex)
            curIndex -= numElements;

        int* behavior = *(int**)(this + 0x0C + curIndex * 4);
        if (behavior != 0 && *(int*)(behavior + 0x20 / 4) == targetId)
            break;

        processedCount += stepSize;
        curIndex += stepSize;
        if ((int)(uint)numElements <= processedCount)
            return;
    } while (true);

    // Found matching behavior – execute the corresponding secondary list action (at +0x10)
    int* secondaryBehavior = *(int**)(this + 0x10 + curIndex * 4);
    do {
        if (secondaryBehavior != 0 && (*(byte*)(secondaryBehavior + 0x10) & 0x40) == 0) {
            // Call global function table (DAT_01223510) offset 0x24, passing ID from behavior+0x08
            void (*fx)(unsigned short) = (void (*)(unsigned short))(*(int*)DAT_01223510 + 0x24);
            fx(*(unsigned short*)(secondaryBehavior + 0x08));

            // Then call two helper functions (likely sound/effect related)
            FUN_005dbc10(*(unsigned short*)(secondaryBehavior + 0x08), *(int*)(secondaryBehavior + 0x18));
            FUN_005f1660();
        }
        stepSize--;
        secondaryBehavior = *(int**)(this + 0x10 + curIndex * 4);
    } while (stepSize >= 0);
}