// FUNC_NAME: Component::getOwner
int __fastcall Component::getOwner(void* this) {
    // Offset 0xF4 stores a pointer to a sub-component embedded at offset 0x48 from the owner.
    void* subComponent = *(void**)((char*)this + 0xF4);
    if (subComponent != 0) {
        return (int)subComponent - 0x48; // Returns pointer to owner base
    }
    return 0;
}