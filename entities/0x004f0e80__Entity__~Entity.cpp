// FUNC_NAME: Entity::~Entity

void Entity::~Entity()
{
    // Set vtable to base class destructor vtable (for virtual calls)
    *(this->vtablePtr) = &PTR_FUN_00e37440;

    if (this->field_0x28 != 0)
    {
        // Call something on the object pointed by field_0x28 using its vtable at offset 4
        (**(code **)(*(this->field_0x28) + 4))(this->field_0x24, &this->field_0x30);
        if (this->field_0x2C != '\0')
        {
            // Add to deletion queue in global memory manager
            int* pDeferQueue = (int*)(gMemoryManager + 0x14);
            **(int***)(gMemoryManager + 0x14) = &PTR_LAB_01124d50;  // deferred destructor label
            *pDeferQueue = *pDeferQueue + 4;
            *(void**)*pDeferQueue = this;                           // queue this object
            *pDeferQueue = *pDeferQueue + 4;
        }
    }

    // Set vtable to final destructor vtable
    *(this->vtablePtr) = &PTR_FUN_00e37110;

    if (this->field_0x10 != 0)
    {
        // Deallocate via same deletion queue
        int* pDeferQueue = (int*)(gMemoryManager + 0x14);
        **(int***)(gMemoryManager + 0x14) = &PTR_LAB_01123be8;  // different deferred destructor label
        *pDeferQueue = *pDeferQueue + 4;
        *(int*)*pDeferQueue = this->field_0x10;                 // queue the field pointer
        *pDeferQueue = *pDeferQueue + 4;

        this->field_0x10 = 0;
        this->field_0x14 = 0;
    }
}