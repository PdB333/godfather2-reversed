// FUNC_NAME: DataWriter::writeFixedSizePacket
// Address: 0x00597be0
// Writes a fixed 0x60-byte network packet from source object fields.
// First two words: type (0x205) and size (0x60).
// Then copies a 4-byte value, a 64-byte block, and six 4-byte ints.
// The global writer at DAT_01205590 provides a virtual write method.

typedef void (__thiscall* WriteProc)(void* self, void* dest, const void* src, int size);

int __fastcall writeFixedSizePacket(void* dest, const void* src)  // dest in ECX, src in EDX (in_EAX)
{
    // Get global writer instance
    void* writer = *(void**)DAT_01205590;
    // Vtable entry at offset 0x10 (index 4 on 32-bit pointers)
    WriteProc writeFunc = (WriteProc)(*(int**)writer)[4];

    uint16_t packetType = 0x205;
    uint16_t packetSize = 0x60;

    // Header words
    writeFunc(writer, dest, &packetType, 2);
    writeFunc(writer, (char*)dest + 2, &packetSize, 2);

    // Copy first dword from source to dest+4
    writeFunc(writer, (char*)dest + 4, src, 4);

    // Copy 64-byte block from source +0x1c to dest +8
    writeFunc(writer, (char*)dest + 8, (const char*)src + 0x1c, 0x40);

    // Copy six dwords from scattered source offsets
    writeFunc(writer, (char*)dest + 0x48, (const char*)src + 0x18, 4);
    writeFunc(writer, (char*)dest + 0x4c, (const char*)src + 0x04, 4);
    writeFunc(writer, (char*)dest + 0x50, (const char*)src + 0x08, 4);
    writeFunc(writer, (char*)dest + 0x54, (const char*)src + 0x0c, 4);
    writeFunc(writer, (char*)dest + 0x58, (const char*)src + 0x10, 4);
    writeFunc(writer, (char*)dest + 0x5c, (const char*)src + 0x14, 4);

    return 0x60;  // Total size written
}