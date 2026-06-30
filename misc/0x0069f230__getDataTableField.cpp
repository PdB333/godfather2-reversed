// FUNC_NAME: getDataTableField

// Function at 0x0069f230: Extracts a field from a global array of 20-byte structs.
// param_1: field index (0-9: byte fields, 10-11: uint fields)
// param_2: entry index (multiplied by 20 internally)
// Returns the field value as uint (bytes zero-extended).
// The global arrays are interleaved: each field's data starts at a fixed offset from the base,
// with stride 0x14 (20) per entry.
// Layout of each 20-byte entry:
//   +0x00: byte field0
//   +0x01: byte field1
//   ...
//   +0x09: byte field9
//   +0x0A: padding (2 bytes)
//   +0x0C: uint field10
//   +0x10: uint field11

uint getDataTableField(int fieldIndex, int entryIndex)
{
    int offset = entryIndex * 0x14;  // stride per entry

    if (fieldIndex == 0)
        return (uint)(byte)(*(byte*)(0x00e50bd0 + offset));
    if (fieldIndex == 1)
        return (uint)(byte)(*(byte*)(0x00e50bd1 + offset));
    if (fieldIndex == 2)
        return (uint)(byte)(*(byte*)(0x00e50bd2 + offset));
    if (fieldIndex == 3)
        return (uint)(byte)(*(byte*)(0x00e50bd3 + offset));
    if (fieldIndex == 4)
        return (uint)(byte)(*(byte*)(0x00e50bd4 + offset));
    if (fieldIndex == 5)
        return (uint)(byte)(*(byte*)(0x00e50bd5 + offset));
    if (fieldIndex == 6)
        return (uint)(byte)(*(byte*)(0x00e50bd6 + offset));
    if (fieldIndex == 7)
        return (uint)(byte)(*(byte*)(0x00e50bd7 + offset));
    if (fieldIndex == 8)
        return (uint)(byte)(*(byte*)(0x00e50bd8 + offset));
    if (fieldIndex == 9)
        return (uint)(byte)(*(byte*)(0x00e50bd9 + offset));
    if (fieldIndex == 10)
        return *(uint*)(0x00e50bdc + offset);   // +0x0C within entry
    if (fieldIndex == 11)
        return *(uint*)(0x00e50be0 + offset);   // +0x10 within entry

    return 0;
}