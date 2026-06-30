// FUNC_NAME: OnlineServicesManager::CreatePlasmaTransaction
void __thiscall OnlineServicesManager::CreatePlasmaTransaction(uint this, uint arg0, uint arg1, uint arg2, uint arg3)
{
    char errorFlag;
    int *interfacePtr;
    uint errorCode;
    __int64 transactionToken;
    uint64_t local_18; // actually two 32-bit halves, but combined as 64-bit
    int local_10; // unused?

    // Check if the plasma transaction manager object exists at this+0x8044
    if (*(int *)(this + 0x8044) != 0)
    {
        // Initialize the plasma subsystem (maybe acquire a session)
        Plasma_Initialize();

        // Clear the transaction token
        local_18 = 0;
        local_10 = 0;

        // Get the plasma user context interface
        interfacePtr = (int *)Plasma_GetUserContext();
        transactionToken = 0;
        if ((interfacePtr != (int *)0x0) &&
            // Query for IPlasmaUser (vtable+0x48)
            (interfacePtr = (int *)(**(code **)(*interfacePtr + 0x48))(), transactionToken = 0, interfacePtr != (int *)0x0) &&
            // Query for IPlasmaTransaction (vtable+0x28)
            (interfacePtr = (int *)(**(code **)(*interfacePtr + 0x28))(), transactionToken = 0, interfacePtr != (int *)0x0))
        {
            // Get the transaction token (vtable+0x08)
            transactionToken = (**(code **)(*interfacePtr + 8))();
        }

        // If we got a valid token, proceed to create the transaction
        if (transactionToken != 0)
        {
            local_18 = transactionToken;
            // Send the transaction to the manager (vtable+0x1c) at this+0x8004 (buffer?)
            (**(code **)(**(int **)(this + 0x8044) + 0x1c))(this + 0x8004, &local_18, arg0, arg1, 1, 0);

            // Check for errors
            errorFlag = Plasma_CheckError();
            if (errorFlag != 0)
            {
                errorCode = Plasma_GetLastError();
                ErrorLog(errorCode, "Error creating Plasma transaction");
            }

            // Get the manager interface again
            interfacePtr = (int *)(**(code **)**(undefined4 **)(this + 0x8044))();
            // Call a method on the manager (vtable+0x10) with a timeout of 10000 ms
            (**(code **)(*interfacePtr + 0x10))(this + 0x8004, arg2, arg3, 10000);
        }
    }
    return;
}