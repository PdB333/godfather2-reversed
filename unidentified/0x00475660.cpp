// FUN_00475660: EARSObject::getAttribute
bool EARSObject::getAttribute(int key, int* outValue) {
    int temp = 0;
    if (this != nullptr && (flags & 0x8000000) != 0) {
        // Virtual call at vtable+0x10: bool __thiscall getAttributeFunc(int key, int* out)
        bool (__thiscall *getAttrFunc)(void*, int, int*) = *(bool (__thiscall**)(void*, int, int*))(*(void**)this + 0x10);
        if (getAttrFunc(this, key, &temp)) {
            *outValue = temp;
            return true;
        }
    }
    *outValue = 0;
    return false;
}