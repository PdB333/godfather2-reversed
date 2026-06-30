// FUNC_NAME: UnknownClass::cleanupResource
void UnknownClass::cleanupResource(void)
{
    // Stack buffer for temporary data (e.g. struct or GUID)
    char temporaryBuffer[12];

    // Call helper function with this and two copies of the pointer at this+0x1c
    // Note: The helper likely unregisters or releases the resource
    // Parameters: temporaryBuffer, this, *(void**)(this+0x1c), this, *(void**)(this+0x1c)
    FUN_005dffe0(temporaryBuffer, this, *(void**)(this + 0x1c), this, *(void**)(this + 0x1c));

    // Call virtual function at vtable offset 4 (second entry) with the resource pointer and a release code (0x18)
    // vtable pointer is at this+4 (possible multiple inheritance or custom layout)
    (*(void (**)(void*, int))(*((int**)this + 1) + 1))(*(void**)(this + 0x1c), 0x18);

    // Null out the resource pointer and an adjacent pointer
    *(void**)(this + 0x1c) = nullptr;
    *(void**)(this + 0x20) = nullptr;
}