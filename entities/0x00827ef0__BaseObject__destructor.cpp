// FUNC_NAME: BaseObject::destructor
void __fastcall BaseObject::destructor(BaseObject* this)
{
    // +0x00: vtable pointer (PTR_FUN_00d73594)
    this->vtable = &PTR_FUN_00d73594;

    // +0x1C: pointer to a sub-object (7*4 = 0x1C)
    if (this->field_0x1C != 0)
    {
        // Deallocate or destruct the sub-object
        destructSubObject(this->field_0x1C);
    }

    // Global or internal cleanup routine
    finalizeCleanup();
}