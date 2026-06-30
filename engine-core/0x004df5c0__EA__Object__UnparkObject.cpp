// FUNC_NAME: EA::Object::UnparkObject
void __fastcall EA::Object::UnparkObject(int* objectHandle) // param_1 is pointer to object pointer (handle)
{
    int* obj = (int*)*objectHandle; // dereference handle to get object pointer
    if (obj == nullptr) {
        return;
    }

    // Clear bit 0x20000 (bit 17) - likely "parked" or "paused" flag
    obj[0x3] = obj[0x3] & 0xfffdffff; // offset +0x0C = flags

    uint flags = obj[0x3];
    if ((flags & 0x80000) != 0) { // bit 19 - "unparking in progress" flag
        obj[0x3] = flags & 0xfff7ffff; // clear bit 19
        // If another flag (bit 0) is set and an external object's flag (at +0x14 from pointer at +0x10) has bit 29 set,
        // then set bit 31 (becomes "active" flag)
        if ((flags & 1) != 0) { // bit 0 - some condition (e.g., "was active before park"?)
            int* extObj = (int*)obj[0x4]; // +0x10 - pointer to another object (e.g., owner or parent)
            if (extObj != nullptr && (extObj[0x5] & 0x20000000) != 0) { // +0x14 - flags in external object, bit 29
                obj[0x3] = flags & 0xfff7ffff | 0x80000000; // set bit 31 (now active)
            }
        }
        // Notify state change
        FUN_0051b0b0(obj); // likely EA::Object::OnStateChange
    }
}