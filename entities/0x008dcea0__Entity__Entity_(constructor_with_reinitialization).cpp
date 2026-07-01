// FUNC_NAME: Entity::Entity (constructor with reinitialization)
void __thiscall Entity::Entity(Entity* thisPtr)
{
    // Set up vtable pointers for multiple inheritance/interfaces
    // Offset 0: primary vtable
    thisPtr->vtable = (VTable*)&PTR_FUN_00d7e748;
    // Offset 0x3C: secondary vtable
    thisPtr->vtable2 = (VTable*)&PTR_LAB_00d7e738;
    // Offset 0x48: tertiary vtable
    thisPtr->vtable3 = (VTable*)&PTR_LAB_00d7e734;
    // Offset 0x50: fourth vtable
    thisPtr->vtable4 = (VTable*)&PTR_LAB_00d7e730;
    // Offset 0x54: fifth vtable
    thisPtr->vtable5 = (VTable*)&PTR_LAB_00d7e6d0;
    // Offset 0x58: sixth vtable
    thisPtr->vtable6 = (VTable*)&PTR_LAB_00d7e668;

    // Initialize sub-objects at various offsets
    // Sub-object at +0x19C
    FUN_004086d0(&thisPtr->subObj1);   // placement new / raw constructor
    FUN_00408310(&thisPtr->subObj1);   // init / reset

    // Sub-object at +0x1A4
    FUN_004086d0(&thisPtr->subObj2);
    FUN_00408310(&thisPtr->subObj2);

    // Sub-object at +0x1AC
    FUN_004086d0(&thisPtr->subObj3);
    FUN_00408310(&thisPtr->subObj3);

    // Sub-object at +0x1B4 – only init (no construction)
    FUN_00408310(&thisPtr->subObj4);

    // Check pointer at +0x1BC for previous allocation
    Entity* prevAlloc = thisPtr->prevResource;  // +0x1BC
    if (prevAlloc != nullptr)
    {
        if (*(int*)((uint8_t*)prevAlloc + 8) != 0) // check field at +8
        {
            FUN_009e7530(prevAlloc); // cleanup resource
        }
        FUN_009f01a0(); // global cleanup (e.g., ref count decrement)
    }

    // Delete previous objects if they exist (offset 0x194 and 0x18C)
    if (thisPtr->oldPointer1 != nullptr) // +0x194
    {
        FUN_004daf90(&thisPtr->oldPointer1); // safe delete, sets pointer to null
    }
    if (thisPtr->oldPointer2 != nullptr) // +0x18C
    {
        FUN_004daf90(&thisPtr->oldPointer2);
    }

    // Finalize initialization (e.g., register with manager)
    FUN_0046ea20();
}