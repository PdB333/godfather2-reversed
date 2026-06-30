// FUNC_NAME: serializeObjectToStream
// Function at 0x00597b40 writes a 0x1C-byte structured data packet to a stream.
// The destination stream object (first arg) must have a vtable with a `write` method at offset 0x10.
// The source object pointer is passed in EAX (likely this pointer of the caller).
// Offsets in source object: +0x20 (4 bytes), +0x10 (16 bytes), +0x40 (4 bytes).

int __fastcall serializeObjectToStream(void* stream, void* sourceObject)
{
    // Predefined constant header: type 0x0204, size 0x001C
    unsigned short type = 0x204;
    unsigned short size = 0x1C;

    // Get the stream's vtable (global pointer DAT_01205590 points to the vtable)
    // Virtual write method at offset 0x10: write(void* stream, const void* data, int size)
    typedef void (__thiscall* WriteFunc)(void* self, const void* data, int size);
    WriteFunc write = (WriteFunc)(*((int*)DAT_01205590) + 0x10);

    // Write header: type (2 bytes)
    write(stream, &type, 2);
    // Write total size (2 bytes)
    write(stream, &size, 2);
    // Write 4 bytes from source offset 0x20
    write(stream, (char*)sourceObject + 0x20, 4);
    // Write 16 bytes from source offset 0x10 (e.g., a quaternion or 4 floats)
    write(stream, (char*)sourceObject + 0x10, 0x10);
    // Write 4 bytes from source offset 0x40
    write(stream, (char*)sourceObject + 0x40, 4);

    return 0x1C; // total bytes written
}