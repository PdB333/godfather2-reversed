// FUNC_NAME: EntityManager::getEntityData
uint __fastcall EntityManager::getEntityData(int this, int index) {
    // Check for null this pointer
    if (this == 0) {
        return 0;
    }

    // Local buffer for entity data (48 bytes)
    char buffer[48];
    int flag = 1;

    // Global table of entity objects (each entry 0x10 bytes)
    // DAT_011eb8f4 is a static array of structs, first member is a pointer to an object
    int* objPtr = *(int**)(&DAT_011eb8f4 + index * 0x10);

    // Call method at offset 0x18 on the object (likely a virtual function or interface method)
    // The method takes: this (objPtr), the outer this, buffer, and flag pointer
    typedef void (__fastcall* MethodType)(int* obj, int outerThis, char* buffer, int* flag);
    MethodType method = *(MethodType*)(*(int*)objPtr + 0x18);
    method(objPtr, this, buffer, &flag);

    // Return buffer address if this is non-null, else 0
    // Equivalent to: (this != 0) ? (uint)buffer : 0
    return -(uint)(this != 0) & (uint)buffer;
}