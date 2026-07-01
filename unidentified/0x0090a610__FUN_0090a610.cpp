// FUNC_NAME: UnknownClass::setLinkedObject
void __thiscall UnknownClass::setLinkedObject(UnknownClass* this, void* linkedObject) {
    // Store the linked object at offset +0x10
    *(void**)(this + 0x10) = linkedObject;

    // Check if the object type at offset +0x8 is valid (non-null and not a special sentinel 0x48)
    int type = *(int*)(this + 0x8);
    if (type != 0 && type != 0x48) {
        // Additional global state checks (likely a manager or system readiness)
        if (FUN_00791300() != 0) {
            // Check global singleton at DAT_01131040
            if (FUN_0043b870(DAT_01131040) != 0) {
                // Trigger some action using the linked object
                FUN_009b1b80(linkedObject);
            }
        }
    }
}