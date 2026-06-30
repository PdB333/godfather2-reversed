// FUNC_NAME: NetSession::sendPlasmaTransaction
// 0x005662a0: Creates and sends a Plasma transaction with given payload and timeout.

#include <cstdint>

class NetSession {
public:
    void sendPlasmaTransaction(void* param2, void* param3, int param4, int param5);
private:
    // +0x8004: buffer for transaction data
    char transactionBuffer[0x40];  // guessed size
    // +0x8044: pointer to a Plasma transaction manager
    void* plasmaTransactionManager;
};

// External functions from engine
extern "C" void PlasmaTransactionBegin();                           // FUN_00adc560
extern "C" void* GetPlasmaNetworkManager();                        // FUN_00ad8d40
extern "C" bool PlasmaTransactionHasError();                       // FUN_00adc2d0
extern "C" const char* PlasmaGetErrorString();                     // FUN_00adc2e0
extern "C" void LogMessage(const char* msg, const char* prefix);  // FUN_005676d0

void NetSession::sendPlasmaTransaction(void* param2, void* param3, int param4, int param5) {
    if (this->plasmaTransactionManager != nullptr) {
        PlasmaTransactionBegin();

        uint64_t transactionId = 0;  // 64-bit transaction ID
        int padding = 0;             // unused alignment

        void* networkMgr = GetPlasmaNetworkManager();
        uint64_t sessionId = 0;      // retrieved session/player ID

        if (networkMgr != nullptr) {
            // vtable +0x48: get network interface
            void* netInterface = (*(void* (__thiscall**)(void*))(*(uintptr_t*)networkMgr + 0x48))(networkMgr);
            if (netInterface != nullptr) {
                // vtable +0x28: get session object
                void* session = (*(void* (__thiscall**)(void*))(*(uintptr_t*)netInterface + 0x28))(netInterface);
                if (session != nullptr) {
                    // vtable +0x8: get unique session ID (64-bit)
                    sessionId = (*(uint64_t (__thiscall**)(void*))(*(uintptr_t*)session + 8))(session);
                }
            }
        }

        if (sessionId != 0) {
            transactionId = sessionId;

            // vtable +0x1c: send data with transaction ID and parameters
            (*(void (__thiscall**)(void*, uint64_t*, void*, void*, int, int))
                (*(uintptr_t*)this->plasmaTransactionManager + 0x1c))(
                    this->plasmaTransactionManager, &transactionId, param2, param3, 1, 0);

            // Error reporting
            if (PlasmaTransactionHasError()) {
                const char* error = PlasmaGetErrorString();
                LogMessage(error, "Error creating Plasma transaction");
            }

            // vtable +0x0: create a transaction handle
            void* transactionHandle = (*(void* (__thiscall**)(void*))
                (*(uintptr_t*)this->plasmaTransactionManager + 0x00))(this->plasmaTransactionManager);
            // vtable +0x10: commit with buffer and timeout (10000ms)
            (*(void (__thiscall**)(void*, char*, int, int, int))
                (*(uintptr_t*)transactionHandle + 0x10))(
                    transactionHandle, this->transactionBuffer, param4, param5, 10000);
        }
    }
}