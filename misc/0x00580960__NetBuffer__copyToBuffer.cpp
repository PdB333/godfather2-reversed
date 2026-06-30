// FUNC_NAME: NetBuffer::copyToBuffer
int __thiscall NetBuffer::copyToBuffer(uint capacity, uint* dest) {
    // dest is passed in EAX (non-standard calling convention)
    // Source buffer structure at 'this':
    // +0x00: (unused in this function)
    // +0x02: byte (destination flag, set to 1)
    // +0x09: byte (cleared)
    // +0x0A: ushort count (number of elements)
    // +0x0C: int elementCount (size of data array)
    // +0x10: int data[elementCount]

    // Destination buffer structure:
    // +0x00: int (cleared)
    // +0x04: int (cleared)
    // +0x08: byte (set to 1)
    // +0x09: byte (set to 0)
    // +0x0A: ushort (set to count)
    // +0x0C: int (set to elementCount)
    // +0x10: int data[elementCount] (copied)

    ushort count = *(ushort*)((byte*)this + 0x0A); // +0x0A
    if (count <= capacity) {
        dest[0] = 0; // +0x00
        dest[1] = 0; // +0x04
        *((byte*)dest + 9) = 0; // +0x09
        *((byte*)dest + 2) = 1; // +0x08? Actually offset 2 from beginning of dest is byte, but using pointer arithmetic on *dest as int pointer, dest+2 is at offset 8.
        *((ushort*)((byte*)dest + 0x0A)) = count; // +0x0A
        int elementCount = *(int*)((byte*)this + 0x0C); // +0x0C
        dest[3] = elementCount; // +0x0C
        _memcpy(dest + 4, (void*)((byte*)this + 0x10), elementCount * 4); // copy data
        return 1;
    }
    return 0;
}