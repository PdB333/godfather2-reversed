// FUNC_NAME: SomeManager::handleEvent
void SomeManager::handleEvent(bool param_1) {
    int iVar1;
    uint uVar2;
    // Note: unaff_ESI points to 'this' (SomeManager*)
    // unaff_EDI points to an event structure: { int type; int id; }
    int* eventStruct = unaff_EDI;  // pointer to event type and id
    int* manager = unaff_ESI;      // pointer to this

    if (*eventStruct == 10) {  // event type 0xA
        // Dereference: manager[0] is a pointer to an array? Actually *manager is first field, then +0xc
        iVar1 = *(int*)(*(int*)(*manager + 0xc) + eventStruct[1] * 4);
        // Check if lower 6 bits of the byte are 0x12 (18)
        if (((byte)iVar1 & 0x3f) == 0x12) {
            // Decrement counter at offset 0x18 (index 6)
            manager[6] = manager[6] - 1;
            // Invert param_1
            param_1 = (param_1 == 0);
            // Extract 9-bit field from bits 15-23
            uVar2 = (iVar1 >> 0xf) & 0x1ff;
        }
    } else {
        // Default handler
        SomeManager::defaultHandler();  // FUN_00642d40
        if ((*eventStruct == 0xb) && (manager[0xd] <= eventStruct[1] && eventStruct[1] < 0xfa)) {
            // Decrement counter at offset 0x24 (index 9)
            manager[9] = manager[9] - 1;
        }
        uVar2 = eventStruct[1];  // use the event id
    }
    // Dispatch with type 0x18, uVar2 as parameter, and param_1 as bool
    SomeManager::dispatchEvent(0x18, uVar2, param_1);  // FUN_006424f0
}