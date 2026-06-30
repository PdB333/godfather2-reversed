// FUNC_NAME: GameObject::setVTableFromType
// Function address: 0x00519140
// Purpose: Initializes the vtable pointer and type ID based on the current type field at +0x04.
// Returns this pointer for chaining, or nullptr if type is unknown (default case).
void* __thiscall GameObject::setVTableFromType() {
    switch (this->typeId) { // +0x04: type discriminator
    case 0:
        this->vtable = (void*)&__vtable_0;   // PTR_LAB_00e381d8
        this->typeId = 0;
        return this;
    case 1:
        this->vtable = (void*)&__vtable_1;   // PTR_LAB_00e381f0
        this->typeId = 1;
        return this;
    case 3:
        this->vtable = (void*)&__vtable_3;   // PTR_LAB_00e38208
        this->typeId = 3;
        return this;
    case 4:
        this->vtable = (void*)&__vtable_4;   // PTR_LAB_00e38220
        this->typeId = 4;
        return this;
    default:
        return nullptr; // Unknown type – error path
    }
}