// FUNC_NAME: Thread::run

#include <windows.h>

// EARS Thread implementation
// Expected 'this' structure layout (offsets in bytes):
// +0x00: DWORD threadHandle      // TLS handle or event handle
// +0x04: bool   active           // false while thread is running, set to true to stop
// +0x08: DWORD someTlsValue1     // copied from TLS during main loop
// +0x0C: DWORD someTlsValue2     // copied from TLS during main loop
// +0x10: int    callbackCount    // number of callbacks/objects to process
// +0x2C: (struct*) pointer to some object with offset 0x130

class Thread {
public:
    // Functions resolved from external libraries (EARS core)
    extern void FUN_00aa23a0(DWORD param1, DWORD param2);     // ThreadInit
    extern void FUN_00c6e980(void* stack[207]);                // TLSInit (exception handling)
    extern DWORD FUN_00aa28b0(DWORD handle, int mode);        // CreateHandle
    extern void FUN_00aa2360(DWORD handle, DWORD param);      // AttachHandle
    extern void FUN_00aa43c0(void* tls, int count);           // SetCallbackCount
    extern void FUN_00aad110(void);                           // EnterCriticalSection
    extern void FUN_00aad120(int mode);                       // LeaveCriticalSection
    extern DWORD FUN_009e5d50(void);                          // GetMessage
    extern void FUN_009e5d40(DWORD* msg);                     // ProcessMessage
    extern void FUN_00aa42f0(void* tls);                      // GetTLSData
    extern void FUN_00aa28e0(DWORD handle);                   // DestroyHandle
    extern void FUN_00c6e9b0(void);                           // TLSCleanup
    extern void FUN_00aa2650(void);                           // ThreadExit

    static DWORD __thiscall run(Thread* this) {
        DWORD uVar2;
        void* pvVar3;
        DWORD* puVar4;
        DWORD uStack_344;
        void* local_340[207]; // exception handler stack / cleanup list

        // Initialize thread with object at this->unk0x2C + 0x130
        FUN_00aa23a0(DAT_011397c4, *(DWORD*)(this->unk0x2C + 0x130));
        // Initialize TLS exception handling stack
        FUN_00c6e980(local_340);
        uVar2 = this->threadHandle; // save thread handle
        TlsGetValue(DAT_01139810);  // get TLS
        uVar2 = FUN_00aa28b0(uVar2, 1); // create handle from TLS
        FUN_00aa2360(uVar2, this->threadHandle); // attach handle

        if (this->callbackCount > 0) {
            pvVar3 = TlsGetValue(DAT_01139830);
            FUN_00aa43c0(pvVar3, this->callbackCount);
        }

        FUN_00aad110(); // enter critical section?

        // Main loop: run while active flag is false (i.e. running)
        while (!this->active) {
            pvVar3 = TlsGetValue(DAT_01139830);
            FUN_00aa42f0(pvVar3); // get TLS data
            uStack_344 = FUN_009e5d50(); // get next message
            FUN_009e5d40(&uStack_344);   // process message

            if (this->callbackCount > 0) {
                puVar4 = (DWORD*)TlsGetValue(DAT_01139830);
                this->someTlsValue1 = *puVar4;
                pvVar3 = TlsGetValue(DAT_01139830);
                this->someTlsValue2 = *(DWORD*)((int)pvVar3 + 4);
            }
            FUN_00aad120(1); // leave critical section
            FUN_00aad110();  // re-enter
        }

        // Cleanup
        FUN_00aa2360(0, 0);
        TlsGetValue(DAT_01139810);
        FUN_00aa28e0(uVar2);
        FUN_00c6e9b0(); // destroy TLS exception stack
        FUN_00aad120(1);
        local_340[0] = &PTR_LAB_00d996b0; // set cleanup pointer
        FUN_00aa2650(); // exit the thread
        return 0;
    }
};