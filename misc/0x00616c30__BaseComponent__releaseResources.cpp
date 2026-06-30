// FUNC_NAME: BaseComponent::releaseResources
// Address: 0x00616c30
// Called from destructor chain. Releases owned sub-objects and frees memory.

// Class layout (inferred offsets):
// +0x1c: pointer to a sub-object (destroyed via FUN_00617320)
// +0x20: pointer to a struct containing a pointer at offset 0 (released then freed)
// +0x24: similar to +0x20
// +0x30: pointer to another object (cleanup via FUN_006167a0 and state check)

void BaseComponent::releaseResources() {
    // Release sub-object at +0x1c
    int* subObj = *(int**)(this + 0x1c);
    if (subObj != 0) {
        destroySubObject(subObj);          // FUN_00617320
        operatorDelete(subObj);            // FUN_009c8eb0
        *(int**)(this + 0x1c) = 0;
    }

    // Release pointer container at +0x20
    int** container1 = *(int***)(this + 0x20);
    if (container1 != 0) {
        if (*container1 != 0) {
            releaseChild(*container1);     // FUN_009c8f10
        }
        operatorDelete(container1);        // FUN_009c8eb0
        *(int***)(this + 0x20) = 0;
    }

    // Release pointer container at +0x24
    int** container2 = *(int***)(this + 0x24);
    if (container2 != 0) {
        if (*container2 != 0) {
            releaseChild(*container2);     // FUN_009c8f10
        }
        operatorDelete(container2);        // FUN_009c8eb0
        *(int***)(this + 0x24) = 0;
    }

    // Handle additional object at +0x30
    int* extraObj = *(int**)(this + 0x30);
    if (extraObj != 0) {
        prepareForDestruction();           // FUN_006167a0 (call on this)
        if (*extraObj == 0) {
            handleEmptyState();            // FUN_006165e0
        }
    }
}