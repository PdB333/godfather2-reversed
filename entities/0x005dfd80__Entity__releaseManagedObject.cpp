// FUNC_NAME: Entity::releaseManagedObject

typedef void (__thiscall *VirtualFunc)(void*, unsigned int);

struct Entity {
    // +0x00: unknown (maybe base class data)
    // +0x04: vtable pointer
    void** vtable;
    // ... other members
    void** field_1c; // pointer to pointer (double indirection)
    void* field_20;  // another pointer
};

void __thiscall Entity::releaseManagedObject()
{
    char localBuffer[12];
    // Internal helper: possibly performing a deep copy or reference counting
    FUN_005e0410(localBuffer, this, **(void***)(this->field_1c), this, this->field_1c);
    
    // Call virtual function at index 1 (vtable[1]) to release the inner object
    ((VirtualFunc)this->vtable[1])(this->field_1c, 0x18);
    
    // Clear the two pointer fields
    this->field_1c = nullptr;
    this->field_20 = nullptr;
}