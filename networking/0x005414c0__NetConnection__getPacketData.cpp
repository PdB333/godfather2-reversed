// FUNC_NAME: NetConnection::getPacketData
uint __thiscall NetConnection::getPacketData(uint handle) {
    // Top 2 bits determine access type
    uint type = handle & 0xC0000000;
    
    if (type == 0) {
        // Local 32-slot array at +0x34 (offset 0x34)
        return this->slotArray[handle & 0x1f];
    }
    
    if (type != 0x40000000) {
        if (type != 0xC0000000) {
            return 0xFFFFFFFF; // Invalid type (0x80000000)
        }
        // handle is a pointer; read field at offset 0x50
        return (*(uint *)(handle + 0x50)) | 1;
    }
    
    // type == 0x40000000: handle is a pointer; read field at offset 0x04
    return (*(uint *)(handle + 0x04)) | 1;
}