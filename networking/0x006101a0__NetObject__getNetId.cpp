// FUNC_NAME: NetObject::getNetId
// Function address: 0x006101a0
// Role: Getter for the network ID / object identifier stored at offset +0x80
uint32 __thiscall NetObject::getNetId() {
    // Returns the value at this + 0x80, which likely holds a unique network ID
    return *(uint32*)(this + 0x80);
}