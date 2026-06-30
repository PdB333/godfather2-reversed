// FUNC_NAME: playSoundEvent

void __fastcall playSoundEvent(int thisObj)
{
    uint flags = *(uint *)(thisObj + 0x3d4);
    if ((flags >> 1 & 1) != 0) {
        uint loopCount = 0;
        if (*(int *)(thisObj + 0x3d8) != 0) {
            do {
                FUN_00894c90(0x852d191); // play sound hash
                loopCount = loopCount + 1;
            } while (loopCount < *(uint *)(thisObj + 0x3d8));
        }
        float value = (float)*(int *)(thisObj + 0x3e0);
        if (*(int *)(thisObj + 0x3e0) < 0) {
            value = value + DAT_00e44578; // add float constant
        }
        FUN_00894e50(0x23ae862d, value, 0); // set sound parameter
        int* globalPtr = *(int**)(DAT_012233a0 + 4);
        int someId = *(int *)(thisObj + 0x3e0);
        if ((globalPtr != 0) && (globalPtr != (int*)0x1f30)) {
            int objPtr = FUN_008c74d0(*(undefined4 *)((int)globalPtr - 0x5c));
            if (objPtr != 0) {
                FUN_008c29a0(someId, 4); // apply effect
            }
        }
    }
}