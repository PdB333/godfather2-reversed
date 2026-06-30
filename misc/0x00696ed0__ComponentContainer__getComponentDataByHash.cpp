// FUNC_NAME: ComponentContainer::getComponentDataByHash
void* __thiscall ComponentContainer::getComponentDataByHash(unsigned int idHash) // returns pointer to component data +0x1c
{
    int convertedId; // iVar1
    int validationResult; // iVar2
    int* foundEntry; // piVar3
    char localBuffer[8]; // local_30
    unsigned long long local_28; // local_28, alignment?
    int localStruct[3]; // local_1c
    code* cleanupFunc; // local_10
    unsigned long long local_c; // local_c
    int local_4; // local_4

    // Convert the input ID (usually a string hash) to an internal key
    convertedId = HashId(idHash);

    // Ensure the container pointer is valid
    if (this == nullptr) {
        CrashHandler(); // FUN_00b97aea
    }

    // Check if the container's type ID matches the converted ID
    if (convertedId != *(int*)(this + 4)) { // offset +0x4: containerTypeId
        // Type mismatch; try to validate the sub-component index based on convertedId+0xc
        validationResult = ValidateSubComponent(convertedId + 0xc); // FUN_004d4b20
        if (validationResult >= 0) {
            // Sub-component index valid, skip full lookup
            goto FoundComponent;
        }
    }

    // Initialize search state
    local_28 = 0;
    PrepareSearch(idHash); // FUN_004d3b50
    local_c = local_28;
    local_4 = 0;

    // Perform lookup in component list
    foundEntry = (int*)FindComponent(localBuffer, this, convertedId, localStruct); // FUN_00696a90
    this = (ComponentContainer*)foundEntry[0]; // Update this to the found component object
    convertedId = foundEntry[1]; // Update convertedId to the component's offset/index

    // If cleanup function provided, call it
    if (localStruct[0] != 0) {
        cleanupFunc = (code*)localStruct[0];
        (*cleanupFunc)(localStruct[0]);
    }

FoundComponent:
    // Verify final state: must have a valid container pointer
    if (this == nullptr) {
        CrashHandler();
    }
    // The component index must not equal the container's own type ID (likely sentinel)
    if (convertedId == *(int*)(this + 4)) {
        CrashHandler();
    }

    // Return pointer to the component's data at offset 0x1c from the component index base
    return (void*)(convertedId + 0x1c);
}