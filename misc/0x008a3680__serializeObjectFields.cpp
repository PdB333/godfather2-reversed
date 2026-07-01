// FUNC_NAME: serializeObjectFields
void __fastcall serializeObjectFields(int* fieldBlock)
{
    // Field at +0x00: integer value
    writeInt(fieldBlock[0]);

    // Field at +0x04: boolean (stored as byte)
    writeInt((fieldBlock[1] & 0xFF) != 0);

    // Fields at +0x08 through +0x28 (9 integers)
    writeInt(fieldBlock[2]);
    writeInt(fieldBlock[3]);
    writeInt(fieldBlock[4]);
    writeInt(fieldBlock[5]);
    writeInt(fieldBlock[6]);
    writeInt(fieldBlock[7]);
    writeInt(fieldBlock[8]);
    writeInt(fieldBlock[9]);
    writeInt(fieldBlock[10]);

    // Sentinel zero (int)
    writeInt(0);

    // Fields at +0x2C through +0x4C (8 integers)
    writeInt(fieldBlock[0xb]);
    writeInt(fieldBlock[0xc]);
    writeInt(fieldBlock[0xd]);
    writeInt(fieldBlock[0xe]);
    writeInt(fieldBlock[0xf]);
    writeInt(fieldBlock[0x10]);
    writeInt(fieldBlock[0x11]);
    writeInt(fieldBlock[0x12]);

    // Field at +0x4C: boolean (stored as byte)
    writeInt((fieldBlock[0x13] & 0xFF) != 0);
}