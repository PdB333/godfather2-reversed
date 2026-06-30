// FUNC_NAME: PacketWriter::writeObject
void __thiscall PacketWriter::writeObject(PacketWriter *this, unsigned int typeId, unsigned int dataLow1, unsigned int dataHigh1, unsigned int dataLow2, unsigned int dataHigh2)
{
    // Get pointer to the underlying buffer structure
    int *bufferBase = (int *)*this; // this holds pointer to buffer struct

    // Current write position is at bufferBase offset 0x14 (5th int)
    int *writePtr = (int *)bufferBase[5];

    // Write the vtable pointer identifying the object type
    *writePtr = (int)&PTR_FUN_01124e18; // vtable for the serialized object class
    writePtr++;
    bufferBase[5] = (int)writePtr;

    // Write the type ID (4 bytes)
    *writePtr = typeId;
    writePtr++;
    bufferBase[5] = (int)writePtr;

    // Align to 4-byte boundary before writing 64-bit values
    int aligned = ((int)writePtr + 7) & 0xFFFFFFFC;
    bufferBase[5] = aligned;
    *(long long *)aligned = ((long long)dataHigh1 << 32) | (unsigned int)dataLow1;

    // Move pointer after first 64-bit value, add offset 0xB, align to 4
    int nextAligned = (bufferBase[5] + 0xB) & 0xFFFFFFFC;
    bufferBase[5] = nextAligned;
    *(long long *)nextAligned = ((long long)dataHigh2 << 32) | (unsigned int)dataLow2;

    // Advance write pointer past the second 64-bit value
    bufferBase[5] = nextAligned + 8;
}