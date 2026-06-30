// FUNC_NAME: SerializationHelper::writeValues (0x004ea470)
// Role: Writes a set of typed values into a stream buffer, including a vtable pointer (class descriptor),
// an integer, a bool (aligned to 4-byte boundary), and four additional integer values.

void __thiscall SerializationHelper::writeValues(int* thisPtr, int valueA, bool flag, int valueB, int valueC, int valueD, int valueE)
{
    // thisPtr points to an object containing a buffer pointer at offset 0
    int* bufferBase = (int*)*thisPtr; // buffer base (e.g., a stream buffer struct)
    // The buffer struct has a current write pointer at offset 0x14
    int** writePtrField = (int**)((char*)bufferBase + 0x14);

    // Write vtable/class descriptor (constant from PTR_LAB_01124bf8)
    **(int***)writePtrField = &PTR_LAB_01124bf8; // class vtable
    (*writePtrField)++; // advance by 4 bytes

    // Write the first integer value (valueA)
    **(int**)writePtrField = valueA;
    (*writePtrField)++;

    // Write boolean flag (single byte), then align to next 4-byte boundary
    unsigned char* boolPtr = (unsigned char*)*writePtrField;
    *boolPtr = flag ? 1 : 0;
    // Align write pointer: current + 4, then mask to DWORD boundary
    *writePtrField = (int*)(((int)*writePtrField + 4) & ~3);

    // Write the remaining four integer values
    **(int**)writePtrField = valueB;
    (*writePtrField)++;
    **(int**)writePtrField = valueC;
    (*writePtrField)++;
    **(int**)writePtrField = valueD;
    (*writePtrField)++;
    **(int**)writePtrField = valueE;
    (*writePtrField)++; // final advancement
}