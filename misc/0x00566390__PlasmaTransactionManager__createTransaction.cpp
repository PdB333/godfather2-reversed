// FUNC_NAME: PlasmaTransactionManager::createTransaction
void __thiscall PlasmaTransactionManager::createTransaction(void* this, uint32_t param2, uint32_t param3, uint32_t param4, uint32_t param5, uint32_t param6, uint32_t param7)
{
    // +0x8044: pointer to function table (vtable-like for transaction operations)
    void** funcTable = *(void***)((uint8_t*)this + 0x8044);
    if (funcTable == nullptr) {
        return;
    }

    // get the Plasma system (likely singleton)
    void* plasmaSystem = getPlasmaSystem();  // FUN_00adc560
    if (plasmaSystem == nullptr) {
        return;
    }

    // get the transaction manager from the Plasma system
    void* transactionManager = getTransactionManager(plasmaSystem);  // FUN_00ad8d40
    if (transactionManager == nullptr) {
        return;
    }

    // get some intermediate object (maybe session or context) using virtual calls
    void* session = callVirtualMethod<void*>(transactionManager, 0x48);  // vtable+0x48
    if (session == nullptr) {
        return;
    }

    void* transactionContext = callVirtualMethod<void*>(session, 0x28);  // vtable+0x28
    if (transactionContext == nullptr) {
        return;
    }

    // get a transaction ID (returned as long long)
    long long transactionId = callVirtualMethod<long long>(transactionContext, 0x8);  // vtable+0x8
    if (transactionId == 0) {
        return;
    }

    // +0x8004: the transaction object (sub-object of this)
    void* transactionObj = (uint8_t*)this + 0x8004;

    // call function at index 0x24 in the function table: startCreateTransaction
    // Parameters: transactionObj, param2, param3, param4, param5, flag=1
    ((void(__thiscall*)(void*, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))funcTable[0x24 / 4])(
        transactionObj, param2, param3, param4, param5, 1);

    // check for error
    if (hasPlasmaError()) {  // FUN_00adc2d0
        const char* errorMsg = getPlasmaErrorString();  // FUN_00adc2e0
        logError(errorMsg, "Error creating Plasma transaction");  // FUN_005676d0
    }

    // call function at index 0x10 in the function table: setTimeout
    // Parameters: transactionObj, param6, param7, timeout=10000
    ((void(__thiscall*)(void*, uint32_t, uint32_t, uint32_t))funcTable[0x10 / 4])(
        transactionObj, param6, param7, 10000);
}