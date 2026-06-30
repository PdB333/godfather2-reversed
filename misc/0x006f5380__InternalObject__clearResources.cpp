// FUNC_NAME: InternalObject::clearResources
void __fastcall InternalObject::clearResources(int this_ptr)
{
    // Release pointer at +0x14 (e.g., audio buffer, texture data)
    if (*(void**)(this_ptr + 0x14) != nullptr) {
        deallocateBlock(*(void**)(this_ptr + 0x14));
        *(void**)(this_ptr + 0x14) = nullptr;
    }
    // Release pointer at +0x0C (e.g., sub-resource)
    if (*(void**)(this_ptr + 0x0C) != nullptr) {
        deallocateBlock(*(void**)(this_ptr + 0x0C));
        *(void**)(this_ptr + 0x0C) = nullptr;
    }
    // Clear flag or count at +0x08
    *(int*)(this_ptr + 0x08) = 0;
}