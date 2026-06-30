// FUNC_NAME: EARSObject::getParentFromSubObjectPointer
int __fastcall EARSObject::getParentFromSubObjectPointer(void) {
    // Offset +0x2528 stores a pointer to a child subobject (e.g., a member at offset 0x48 in the parent)
    int subObjectPtr = *(int*)((char*)this + 0x2528);
    if (subObjectPtr != 0) {
        // Subtract 0x48 to retrieve the parent object's this pointer
        return subObjectPtr - 0x48;
    }
    return 0;
}