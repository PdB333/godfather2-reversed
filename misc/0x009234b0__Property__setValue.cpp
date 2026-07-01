// FUNC_NAME: Property::setValue
void __fastcall Property::setValue(int thisPtr)
{
    int mode = *(int *)(thisPtr + 0x54); // +0x54: mode (0=direct, 1=trackPrevious, 2=other)
    int enabled = *(int *)(thisPtr + 0x58); // +0x58: enabled flag

    if (enabled == 0) {
        *(char *)(thisPtr + 0x7c) = 1; // +0x7c: dirty flag

        if (mode == 0) {
            *(int *)(thisPtr + 0x70) = *(int *)(thisPtr + 0x6c); // +0x70: currentValue = +0x6c: targetValue
            return;
        }
        if (mode == 1) {
            if (*(int *)(thisPtr + 0x74) != *(int *)(thisPtr + 0x6c)) { // +0x74: previousValue
                FUN_00402050(&DAT_011304d8, 0); // log or debug call
            }
            *(int *)(thisPtr + 0x74) = *(int *)(thisPtr + 0x6c); // previousValue = targetValue
            return;
        }
        if (mode == 2) {
            *(int *)(thisPtr + 0x78) = *(int *)(thisPtr + 0x6c); // +0x78: otherValue = targetValue
        }
    }
}