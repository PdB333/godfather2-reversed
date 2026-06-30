// FUNC_NAME: checkObjectTypeId
// Function address: 0x00543050
// Compares a given type ID with the result of a virtual function at vtable offset 0x1e8.
bool __thiscall checkObjectTypeId(int* this, int typeId)
{
    // Virtual call: getTypeId() at vtable+0x1e8
    int objectType = this->getTypeId(); // (*(int (__thiscall**)(int*))(*this + 0x1e8))(this);
    return typeId == objectType;
}