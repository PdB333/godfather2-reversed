// FUNC_NAME: RegisteredObject::constructor
void __fastcall RegisteredObject::constructor(undefined4 param_1, RegisteredObject* thisObj)
{
    int* listHead;
    int nodePtr;

    // Set base vtable
    thisObj->vtable = &PTR_FUN_00e373b0;

    // Call base initialization three times (likely init lists, etc.)
    FUN_004ebba0();
    FUN_004ebba0();
    FUN_004ebba0();

    // Override vtable with derived vtable
    thisObj->vtable = &PTR_FUN_00e37110;

    // Check if there is a node to register (offset +0x10)
    nodePtr = thisObj->field_0x10;
    if (nodePtr != 0) {
        // Global list head at DAT_01206880 + 0x14
        listHead = (int*)(DAT_01206880 + 0x14 proiektuak);

        // Insert node into linked list (head->next = vtable, then head->data = nodePtr)
        *(void***)*listHead = &PTR_LAB_01123be8;
        *listHead = *listHead + 4;
        *(int*)*listHead = nodePtr;
        *listHead = *listHead + 4;

        // Clear the node fields in the object
        thisObj->field_0x10 = 0;
        thisObj->field_0x14 = 0;
    }
}