// FUNC_NAME: VolumeControl::selectBarFromPath
char __thiscall VolumeControl::selectBarFromPath(VolumeControl *this, const char *path) {
    byte local_40[64];             // buffer for building path strings
    char result = '\0';            // return value: 0 = not found, 1 = found and selected

    // +0x50: likely a flag indicating whether the control is disabled or already in use
    if (*(int *)((int)this + 0x50) != 0) {
        return '\0';
    }

    // Iterate over bar indices 0..10 (inclusive)
    for (unsigned int barIdx = 0; barIdx <= 10; ++barIdx) {
        // Build expected path: /ctrl/content/control_%d/volume/bar_%d
        FUN_00910160((char *)local_40, "/ctrl/content/control_%d/volume/bar_%d",
                     *(int *)((int)this + 0x54), barIdx);

        // Custom string comparison (compares two bytes at a time, likely optimized by compiler)
        byte *builtPtr = local_40;
        byte *inputPtr = (byte *)path;
        int cmpResult;
        do {
            byte builtByte = *builtPtr;
            byte inputByte = *inputPtr;
            if (builtByte != inputByte) {
                cmpResult = (builtByte < inputByte) ? -1 : 1;
                goto checkEquality;
            }
            if (builtByte == 0) break;
            builtByte = builtPtr[1];
            inputByte = inputPtr[1];
            if (builtByte != inputByte) {
                cmpResult = (builtByte < inputByte) ? -1 : 1;
                goto checkEquality;
            }
            builtPtr += 2;
            inputPtr += 2;
        } while (builtByte != 0);
        cmpResult = 0;

checkEquality:
        if (cmpResult == 0) {
            // Path matched: build a second path (likely value set path) using another format string
            // DAT_00e3266c is probably "/ctrl/content/control_%d/volume/bar_%d/value" or similar
            FUN_00910160((char *)local_40, (const char *)&DAT_00e3266c, barIdx);
            // Call UI command to select the option and set its value
            // FUN_005a04a0("SelectOptionValue",0,&DAT_00d87288,1,local_40);
            FUN_005a04a0("SelectOptionValue", 0, (int)&DAT_00d87288, 1, (char *)local_40);
            result = '\x01';  // mark as found
        }

        if (result != '\0') {
            return result;  // early exit after first match
        }
    }

    return result;  // no match found
}