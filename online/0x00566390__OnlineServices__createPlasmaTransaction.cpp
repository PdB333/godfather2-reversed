//FUNC_NAME: OnlineServices::createPlasmaTransaction
// Function address: 0x00566390
// Creates a Plasma transaction and sends it with a timeout.
// Offsets: this+0x8044 = pointer to Plasma transaction manager
//          this+0x8004 = buffer or context for transaction data

void __thiscall OnlineServices::createPlasmaTransaction(
    void* this,
    uint32_t param_2,
    uint32_t param_3,
    uint32_t param_4,
    uint32_t param_5,
    uint32_t param_6,
    uint32_t param_7)
{
    char errorFlag;
    int* pManager;
    uint32_t errorCode;
    longlong result;

    // Check if the Plasma transaction manager exists
    if (*(int*)((char*)this + 0x8044) != 0) {
        // Global initialization or context retrieval
        FUN_00adc560();

        pManager = (int*)FUN_00ad8d40();
        if (pManager != nullptr) {
            pManager = (int*)(**(code**)(*pManager + 0x48))(); // Get some subsystem
            if (pManager != nullptr) {
                pManager = (int*)(**(code**)(*pManager + 0x28))(); // Get transaction factory
                if (pManager != nullptr) {
                    result = (**(code**)(*pManager + 8))(); // Create transaction handle
                    if (result != 0) {
                        // Call transaction creation method on the manager
                        (**(code**)(**(int**)((char*)this + 0x8044) + 0x24))
                            ((char*)this + 0x8004, param_2, param_3, param_4, param_5, 1);

                        errorFlag = FUN_00adc2d0(); // Check for error
                        if (errorFlag != '\0') {
                            errorCode = FUN_00adc2e0(); // Get error code
                            FUN_005676d0(errorCode, "Error creating Plasma transaction");
                        }

                        // Send the transaction with a timeout (10000 ms)
                        pManager = (int*)(**(code**)**(undefined4**)((char*)this + 0x8044))();
                        (**(code**)(*pManager + 0x10))((char*)this + 0x8004, param_6, param_7, 10000);
                    }
                }
            }
        }
    }
}