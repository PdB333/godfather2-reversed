// FUNC_NAME: ClassRegistry::registerNextClass
void ClassRegistry::registerNextClass(void) {
    // Global index into the static class registration table (0x00e50bc4)
    int classIndex = *(int*)0x00e50bc4;
    const int classStride = 0x14; // Each class entry occupies 20 bytes

    // Three fields of the class descriptor stored in parallel arrays
    // Field1 (8 bytes) at 0x00e50bd0 + index*stride
    uint64_t field1 = *(uint64_t*)((char*)0x00e50bd0 + classIndex * classStride);
    // Field2 (8 bytes) at 0x00e50bd8 + index*stride
    uint64_t field2 = *(uint64_t*)((char*)0x00e50bd8 + classIndex * classStride);
    // Field3 (4 bytes) at 0x00e50be0 + index*stride
    uint32_t field3 = *(uint32_t*)((char*)0x00e50be0 + classIndex * classStride);

    // +0x14 in the registry buffer (0x01206880) holds a pointer to the next vtable slot
    int** pCurrentVtableSlot = (int**)((char*)0x01206880 + 0x14);
    int* currentSlot = *pCurrentVtableSlot;

    // Write the static vtable address (PTR_LAB_00e50c5c) into the current slot
    int* vtable = (int*)&PTR_LAB_00e50c5c;
    *currentSlot = (int)vtable;

    // Advance the slot pointer to the next slot (4 bytes forward)
    *pCurrentVtableSlot = currentSlot + 1;

    // Copy/initialize the 20-byte class descriptor to a target storage
    // FUN_0049c430(source, size, flags)
    FUN_0049c430(&field1, classStride, 4);

    // Register the class with the engine using the extracted descriptor
    FUN_0069fcb0(field1, field2, field3);
}