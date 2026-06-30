// FUNC_NAME: ComponentBase::~ComponentBase
void __fastcall ComponentBase::~ComponentBase(ComponentBase* this)
{
    // Set vtable pointer to base class vtable (destructor vtable switch)
    *(void**)this = &PTR_FUN_00d5f678;                           // vtable for base class
    *(void**)(reinterpret_cast<char*>(this) + 0x3C) = &PTR_LAB_00d5f668; // +0x3C: secondary vtable
    *(void**)(reinterpret_cast<char*>(this) + 0x48) = &PTR_LAB_00d5f664; // +0x48: tertiary vtable
    *(void**)(reinterpret_cast<char*>(this) + 0x50) = &PTR_LAB_00d5f660; // +0x50: quaternary vtable

    // Release owned sub-objects if still alive
    if (this->someComponent1 != nullptr) // +0x70: pointer to first owned sub-object
    {
        releaseComponent(&this->someComponent1); // FUN_004daf90 – likely calls destructor and deallocates
    }
    if (this->someComponent2 != nullptr) // +0x68: pointer to second owned sub-object
    {
        releaseComponent(&this->someComponent2);
    }

    // Final global cleanup (e.g., memory accounting or component manager flush)
    FUN_00473880();
}