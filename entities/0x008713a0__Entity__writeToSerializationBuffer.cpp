// FUNC_NAME: Entity::writeToSerializationBuffer
void __thiscall Entity::writeToSerializationBuffer(undefined4* buffer) {
    // buffer is a serialization buffer with a vtable at offset 0
    // The first virtual function returns a type identifier (hash)
    int typeID = (*(int (__thiscall**)(undefined4*))(*buffer))(buffer);
    
    // Check for known type hash (0x72703570 - likely "rp5p" in ASCII)
    if (typeID == 0x72703570) {
        // Copy 8 bytes from object field at +0x60 to buffer offset 0x60
        *(undefined8*)(buffer + 0x18) = *(undefined8*)((char*)this + 0x60);
        // Copy 4 bytes from object field at +0x68 to buffer offset 0x68
        buffer[0x1a] = *(undefined4*)((char*)this + 0x68);
    }
}