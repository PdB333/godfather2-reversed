// FUNC_NAME: Entity::getStatus
// Function address: 0x005647f0
// Reads a 4-byte field at this+0x04 (likely an enum or status) and returns true if it is not equal to 5.
// The field value is written to the output pointer.
bool __thiscall Entity::getStatus(int* outStatus) const {
    *outStatus = *(int*)(this + 4);
    return *(int*)(this + 4) != 5;
}