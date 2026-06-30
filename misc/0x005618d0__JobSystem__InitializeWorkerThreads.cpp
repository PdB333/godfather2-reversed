// FUNC_NAME: JobSystem::InitializeWorkerThreads
void __thiscall JobSystem::InitializeWorkerThreads(void)
{
    void* tlsValue;
    int i;

    tlsValue = TlsGetValue(threadLocalStorageIndex); // DAT_01139830
    ThreadLocalSetup(tlsValue, *(int*)(this + 0x0C)); // FUN_00aa43c0
    tlsValue = TlsGetValue(threadLocalStorageIndex);
    ThreadLocalFinalize(tlsValue); // FUN_00aa42f0

    i = 0;
    if (*(int*)(this + 0x04) > 0) {
        WorkerThreadDescriptor* descriptor = (WorkerThreadDescriptor*)(this + 0x18);
        do {
            descriptor->stackSize = 0x7d000;           // 512KB stack
            descriptor->threadId = *(int*)(this + 0x0C); // ID from class
            descriptor->field_0x08 = 0;
            descriptor->field_0x0C = 0;
            descriptor->field_0x10 = 0;                // byte
            descriptor->manager = this;                 // +0x24
            descriptor->index = i + 2;                  // +0x20
            StartWorkerThread(WorkerThreadEntryPoint, descriptor); // FUN_00aa64b0
            i++;
            descriptor++;
        } while (i < *(int*)(this + 0x04));
    }
}