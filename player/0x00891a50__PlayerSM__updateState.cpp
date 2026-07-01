// FUNC_NAME: PlayerSM::updateState
void __thiscall PlayerSM::updateState(int thisPtr, int param2)
{
    // +0x88: pointer to current action/timer – process if non-null
    if (*(int *)(thisPtr + 0x88) != 0) {
        updateAction(thisPtr); // FUN_00922ac0
    }

    // +0x170 bit1 (mask 0x2): start sound at full volume
    if ((*(uint *)(thisPtr + 0x170) >> 1) & 1) {
        playSound(*(void **)(thisPtr + 0x90), 1.0f, 0); // FUN_00894ea0
    }

    // +0x170 bit0: if clear, increment state timer; else stop sound
    if ((*(byte *)(thisPtr + 0x170) & 1) == 0) {
        (*(int *)(thisPtr + 0x174))++; // +0x174: state duration counter
    } else {
        stopSound(*(void **)(thisPtr + 0x8c)); // FUN_00894c90
    }

    // Build event packet from +0x5c and the incoming parameter
    // local_c = *(int*)(this+0x5c) typically holds a state enum or message ID
    // local_8 = param2  (delta time or event argument)
    int local_c = *(int *)(thisPtr + 0x5c);
    int local_8 = param2;
    char local_4 = 0; // padding/flag

    postEvent(&local_c, 0); // FUN_00408a00 – dispatches the constructed event
}