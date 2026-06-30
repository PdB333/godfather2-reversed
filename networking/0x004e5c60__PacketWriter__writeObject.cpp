// FUNC_NAME: PacketWriter::writeObject

struct BufferDescriptor {
    // ... other fields ...
    void* mWritePos; // +0x14: current write position within the buffer
};

class PacketWriter {
    BufferDescriptor* mBuffer; // +0x00: pointer to buffer descriptor
public:
    void __thiscall writeObject(int type, void* data);
};

void __thiscall PacketWriter::writeObject(int type, void* data) {
    BufferDescriptor* buffer = this->mBuffer;

    // Write vtable pointer for the object being serialized
    *(void**)buffer->mWritePos = &PTR_LAB_01124b44;
    buffer->mWritePos = (void*)((int)buffer->mWritePos + 4);

    // Write the type identifier (e.g., packet type or object ID)
    *(int*)buffer->mWritePos = type;
    buffer->mWritePos = (void*)((int)buffer->mWritePos + 4);

    // Align to 16-byte boundary for the payload
    buffer->mWritePos = (void*)(((int)buffer->mWritePos + 0x13) & ~0xF);

    // Copy the 32-byte payload (e.g., game event data)
    memcpy(buffer->mWritePos, data, 0x20);

    // Advance the write position past the copied data
    buffer->mWritePos = (void*)((int)buffer->mWritePos + 0x20);
}