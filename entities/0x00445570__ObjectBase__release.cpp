// FUNC_NAME: ObjectBase::release
void __fastcall ObjectBase::release(ObjectBase* this)
{
    if (this == nullptr) {
        return;
    }

    // Check if this object has a sub-object or custom deallocator (bit 0x8000000 at offset 0x14)
    if (this->flags & 0x8000000) {
        // Get sub-object pointer at offset 0x3C
        ObjectBase* subObj = this->subObject; // = reinterpret_cast<ObjectBase*>( *(uint32_t*)( (uint8_t*)this + 0x3C ) );

        // Check if the sub-object has its own destructor flag (bit 2 at offset 0x40 of the sub-object)
        if (subObj->subFlags & 2) { // subObj->subFlags is at offset 0x40 relative to subObj?
            // Call function via sub-object's vtable+4 with a global parameter (DAT_012067dc)
            // This might be a deallocation callback or a custom release function
            struct LocalParam {
                int* data;       // pointer to global
                uint8_t unused;
            } localParam;
            localParam.data = &globalVar; // DAT_012067dc is a global int pointer
            localParam.unused = 0;

            // Call second vtable function on sub-object (vtable[1] = offset 4)
            subObj->vtable[1](&localParam);
        }

        // Call first vtable function on sub-object with argument 1 (vtable[0] = offset 0)
        // Typically the destructor
        subObj->vtable[0](1);
        return;
    }

    // No sub-object: call first vtable function directly (destructor)
    this->vtable[0](1);
}