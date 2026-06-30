// FUN_NAME: NetSession::createPlasmaTransaction
void __thiscall NetSession::createPlasmaTransaction(void *this, undefined4 param_dataOrCallback, undefined4 param_additionalData, undefined4 param_timeoutMs, undefined4 param_unknown)
{
    char localVar;
    undefined4 errorCode;
    int *vtablePtr;
    undefined4 stackTemp;
    longlong transactionHandle; // from FUN_00566d50
    undefined8 local_18;
    undefined4 local_10;
    undefined4 local_c;

    // Check if the plasma interface pointer exists and is enabled
    // +0x8044: pointer to plasma transaction interface object
    // +0x8048: boolean flag indicating enabled
    if ((*(int *)((int)this + 0x8044) != 0) && (*(char *)((int)this + 0x8048) != '\0')) {
        // Initialize plasma system? (unclear)
        FUN_00adc560();

        // Get a transaction handle from somewhere
        transactionHandle = FUN_00566d50();
        if (transactionHandle != 0) {
            local_10 = param_additionalData;
            local_c = param_dataOrCallback;
            // Setup local structure: 1 as some type identifier
            local_18 = CONCAT44(stackTemp, 1);
            // Call virtual function at vtable+0xC on the plasma interface
            // Signature: void (PlasmaInterface::*)(void *this_plus_offset, longlong *, int)
            (**(code **)(**(int **)((int)this + 0x8044) + 0xc))((int)this + 0x8004, &transactionHandle, 1);
            // Check for errors
            localVar = FUN_00adc2d0();
            if (localVar != '\0') {
                errorCode = FUN_00adc2e0();
                // Log or handle error
                FUN_005676d0(errorCode, "Error creating Plasma transaction");
            }
            // Retrieve another vtable pointer from the interface's first virtual function (vtable+0)
            vtablePtr = (int *)(**(code **)**(undefined4 **)((int)this + 0x8044))();
            // Call a method on that object with timeout
            // Signature: void (TransactionObject::*)(void *this_plus_offset, int, int, int)
            (**(code **)(*vtablePtr + 0x10))((int)this + 0x8004, param_timeoutMs, param_unknown, 10000);
        }
    }
    return;
}