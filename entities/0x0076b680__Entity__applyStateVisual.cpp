// FUNC_NAME: Entity::applyStateVisual
void __thiscall Entity::applyStateVisual(int *thisPtr, int propDefault, int propA, int propB, int propC, int propD)
{
    int state = thisPtr[0x1c];               // +0x70: state field
    if (state == 0 || state == 0x48) return; // only process non-zero, non-72 states

    int *secondary = (int *)thisPtr[0x17];    // +0x5c: pointer to another object (e.g. animation controller)
    int val = secondary[0x1d3];               // +0x74c
    if (val == 0 || val == 0x48 || *(char *)(val + 0x160) != 2 || ((*(uint *)(&secondary[0x238]) >> 10) & 1) == 0) {
        // First branch: secondary object does not have specific conditions
        int index = (state == 0) ? 0 : (state - 0x48);
        char byte1b8c = *(char *)(index + 0x1b8c);  // +0x1b8c: state-specific byte

        if (byte1b8c != 0 && byte1b8c != 1 && byte1b8c != 4) {
            // Use property C (propC) for unknown byte values
            (*(void (__thiscall **)(int, int, int, int, float, float))(*thisPtr + 0x2c))(thisPtr, propC, 1, 0, 0, 1.0f, 1.0f);
            return;
        }
        // Fall through to default property (propDefault)
        (*(void (__thiscall **)(int, int, int, int, float, float))(*thisPtr + 0x2c))(thisPtr, propDefault, 1, 0, 0, 1.0f, 1.0f);
    } else {
        // Second branch: secondary object meets conditions
        int index = (state == 0) ? 0 : (state - 0x48);
        char byte1b8c = *(char *)(index + 0x1b8c);  // +0x1b8c

        if (byte1b8c == 0) {
            // Use property D (propD) for byte value 0
            (*(void (__thiscall **)(int, int, int, int, float, float))(*thisPtr + 0x2c))(thisPtr, propD, 1, 0, 0, 1.0f, 1.0f);
            return;
        }
        if (byte1b8c == 1 || byte1b8c == 4) {
            // Use property E (propE) for byte values 1 or 4
            (*(void (__thiscall **)(int, int, int, int, float, float))(*thisPtr + 0x2c))(thisPtr, propE, 1, 0, 0, 1.0f, 1.0f);
            return;
        }
        // Fall through to default property for other byte values
        (*(void (__thiscall **)(int, int, int, int, float, float))(*thisPtr + 0x2c))(thisPtr, propDefault, 1, 0, 0, 1.0f, 1.0f);
    }
}