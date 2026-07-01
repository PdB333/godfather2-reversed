// FUNC_NAME: SomeClass::processMessage
// Address: 0x0086b0e0
// Role: Dispatches a message to virtual handlers, likely part of EARS messaging system.
// Uses a member at offset 0x50 (this[0x14]) as a handler table.
// Calls virtual functions at vtable offsets 0x10 and 0x18.
// The constant 0xd42a2c49 is a message type hash (e.g., kMsgTypeSomething).

void __thiscall SomeClass::processMessage(int *thisPtr, undefined4 param2, undefined4 param3, undefined4 param4)
{
    int *handlerTable; // piVar1
    undefined4 result; // uVar2
    // Local struct for message key (likely used by FUN_006215d0)
    struct {
        int field0;          // +0x00
        int hash;            // +0x04
        int *handlerTablePtr;// +0x08
    } keyStruct;
    undefined4 ignored; // uStack_8

    // Get handler table from this at offset 0x50 (this[0x14])
    handlerTable = (int *)thisPtr[0x14]; // +0x50

    // Call a virtual function on the handler table (vtable+0x24) - result ignored
    ignored = (**(code **)(*handlerTable + 0x24))();

    // Build the key struct
    keyStruct.field0 = 0;
    keyStruct.hash = 0xd42a2c49; // Message type hash
    keyStruct.handlerTablePtr = handlerTable;

    // Look up the message handler using param4 and the key
    result = FUN_006215d0(param4, &keyStruct);

    // Call virtual function at vtable offset 0x10 on this with result
    (**(code **)(*thisPtr + 0x10))(result);

    // Call virtual function at vtable offset 0x18 on this with return address, param2, and result
    // Note: unaff_retaddr is the return address of this function, used as first argument
    (**(code **)(*thisPtr + 0x18))(unaff_retaddr, param2, result);
}