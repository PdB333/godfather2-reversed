// FUN_NAME: OnlineServices::createPlasmaTransaction
void __thiscall OnlineServices::createPlasmaTransaction(void *this, int param2, int param3, int param4, int param5, int param6, int param7, int param8)
{
    // +0x8044: pointer to a transaction manager object (e.g., IPlasmaTransactionManager)
    if (*(int*)((char*)this + 0x8044) != 0) {
        // Enter critical section to ensure thread safety (likely from EARS::Framework)
        Engine::enterCriticalSection(); // FUN_00adc560

        // Get the Plasma service singleton (e.g., IPlasmaService)
        void* plasmaService = Engine::getPlasmaService(); // FUN_00ad8d40
        if (plasmaService != nullptr) {
            // Get the transaction service from the plasma service (vtable +0x48)
            void* txnService = (*(void*(__thiscall**)(void*))(*(int*)plasmaService + 0x48))(plasmaService);
            if (txnService != nullptr) {
                // Get the transaction interface (vtable +0x28)
                void* txnInterface = (*(void*(__thiscall**)(void*))(*(int*)txnService + 0x28))(txnService);
                if (txnInterface != nullptr) {
                    // Ask the transaction interface to create a new transaction; returns a handle (64-bit)
                    long long txnHandle = (*(long long(__thiscall**)(void*))(*(int*)txnInterface + 8))(txnInterface);
                    if (txnHandle != 0) {
                        // Retrieve the transaction manager object from this
                        void* txnMgr = *(void**)((char*)this + 0x8044);
                        // Call virtual function at +0x2c on the transaction manager
                        // This likely initializes a transaction with the given parameters
                        (*(void(__thiscall*)(void*, int, int, int, int, int, int, int, int, int, int))
                            (*(int*)txnMgr + 0x2c))
                            ((char*)this + 0x8004, param2, 1, param3, param4, 1, 0, param5, param6, 0);

                        // Check if an error occurred
                        if (Engine::isError()) { // FUN_00adc2d0
                            const char* errMsg = Engine::getErrorString(); // FUN_00adc2e0
                            Engine::logError(errMsg, "Error creating Plasma transaction"); // FUN_005676d0
                        }

                        // Get the service object from the transaction manager by calling its first virtual function (offset 0)
                        void* serviceFromMgr = (*(void*(__thiscall**)(void*))(**(int**)txnMgr))(txnMgr);
                        // Call virtual function at +0x10 on that service to set a timeout (10000 ms)
                        (*(void(__thiscall*)(void*, int, int, int))
                            (*(int*)serviceFromMgr + 0x10))
                            ((char*)this + 0x8004, param7, param8, 10000);
                    }
                }
            }
        }
    }
}