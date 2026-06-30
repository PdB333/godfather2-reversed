// FUNC_NAME: ScriptReader::readHeader
void __thiscall ScriptReader::readHeader(void)
{
    int versionMajor;
    int versionMinor;
    char readFlag;
    char byteValue;
    int magic;

    FUN_00642140(); // readStart or beginRead
    versionMajor = FUN_006418b0(); // readByte
    versionMinor = versionMajor & 0xff;

    // Version upper nibble is major, lower nibble is minor
    if (0x50 < versionMinor) {
        // too new: expected at most 5.0
        FUN_00633920(*this, "%s too new: read version %d.%d; expected at most %d.%d",
                     this[4], (int)versionMinor >> 4, versionMajor & 0xf, 5, 0);
    }
    if (versionMinor < 0x50) {
        // too old: expected at least 5.0
        if ((versionMinor & 0x8000000f) != 0) {
            versionMinor = (versionMinor - 1 | 0xfffffff0) + 1;
        }
        FUN_00633920(*this, "%s too old: read version %d.%d; expected at least %d.%d",
                     this[4], (int)(versionMinor + ((int)versionMinor >> 0x1f & 0xfU)) >> 4,
                     versionMinor, 5, 0);
    }

    // Read flag
    readFlag = FUN_006418b0(); // readByte
    this[3] = (uint)(readFlag != '\x01');

    // Validate type sizes
    byteValue = FUN_006418b0();
    if (byteValue != '\x04') {
        FUN_00633920(*this, "virtual machine mismatch in %s: size of %s is %d but read %d",
                     this[4], &DAT_00e429c0, 4, byteValue);
    }
    byteValue = FUN_006418b0();
    if (byteValue != '\x04') {
        FUN_00633920(*this, "virtual machine mismatch in %s: size of %s is %d but read %d",
                     this[4], "size_t", 4, byteValue);
    }
    byteValue = FUN_006418b0();
    if (byteValue != '\x04') {
        FUN_00633920(*this, "virtual machine mismatch in %s: size of %s is %d but read %d",
                     this[4], "Instruction", 4, byteValue);
    }
    byteValue = FUN_006418b0();
    if (byteValue != '\x06') {
        FUN_00633920(*this, "virtual machine mismatch in %s: size of %s is %d but read %d",
                     this[4], &DAT_00e429d8, 6, byteValue);
    }
    byteValue = FUN_006418b0();
    if (byteValue != '\b') {
        FUN_00633920(*this, "virtual machine mismatch in %s: size of %s is %d but read %d",
                     this[4], &DAT_00e429dc, 8, byteValue);
    }
    byteValue = FUN_006418b0();
    if (byteValue != '\t') {
        FUN_00633920(*this, "virtual machine mismatch in %s: size of %s is %d but read %d",
                     this[4], &DAT_00e429e0, 9, byteValue);
    }
    byteValue = FUN_006418b0();
    if (byteValue != '\t') {
        FUN_00633920(*this, "virtual machine mismatch in %s: size of %s is %d but read %d",
                     this[4], &DAT_00e41eb4, 9, byteValue);
    }
    byteValue = FUN_006418b0();
    if (byteValue != '\x04') {
        FUN_00633920(*this, "virtual machine mismatch in %s: size of %s is %d but read %d",
                     this[4], "number", 4, byteValue);
    }

    magic = FUN_00641940(); // readInt32
    if (magic != 0x1df5e76) {
        FUN_00633920(*this, "unknown number format in %s", this[4]);
    }
}