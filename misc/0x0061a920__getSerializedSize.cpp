// FUNC_NAME: getSerializedSize
// Function at 0x0061a920: Returns the size (in bytes) of a serialized field based on its type ID.
// Type IDs 30-35 (0x1e-0x23) are 4 bytes, all others are 1 byte.
int __fastcall getSerializedSize(int typeId)
{
    if (typeId != 0x1e && typeId != 0x1f && typeId != 0x20 &&
        typeId != 0x21 && typeId != 0x22 && typeId != 0x23)
    {
        return 1;
    }
    return 4;
}