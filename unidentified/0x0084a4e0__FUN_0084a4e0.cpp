// FUNC_NAME: SomeClass::getSubObject
int* SomeClass::getSubObject()
{
    // Check if sub-object at offset 0x2C is initialized (flag at offset 0x30)
    if (this->initialized == 0) {
        // Call initialization function with allocator from vtable+0x44 and address of sub-object
        FUN_00603330(*(int*)(this->vtable + 0x44), &this->subObject);
    }
    return &this->subObject;
}