// FUNC_NAME: PacketBuffer::getPayloadPointer
int __fastcall PacketBuffer::getPayloadPointer(int *thisPtr)
{
    // Assert that the base pointer is not null
    if (thisPtr[0] == 0) {
        assertFail();
    }
    // Assert that the data pointer matches the expected value stored in the base object at offset 0x18
    if (thisPtr[1] != *(int *)(thisPtr[0] + 0x18)) {
        assertFail();
    }
    // Return pointer to the payload data (skip 8-byte header)
    return thisPtr[1] + 8;
}