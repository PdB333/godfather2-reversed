// FUNC_NAME: NetConnection::sendPacket
uint __thiscall NetConnection::sendPacket(uint sequenceNum, NetConnection *this, int param3, undefined4 param4, int param5)
{
    uint result;
    int *managerPtr;
    int *vtablePtr;
    int threadId;
    int localVar5;
    int *someManager;
    int flushResult;
    uint retVal;
    int *packetFunc;

    // Get global manager singleton
    managerPtr = (int *)GetAudioEngine(); // FUN_00ad8d40 - likely EARS::AudioEngine
    if (managerPtr == nullptr) return 0xFFFFFFFF;

    vtablePtr = (int *)(**(code **)(*managerPtr + 0x34))(); // Get some system component
    if (vtablePtr == nullptr) return 0xFFFFFFFF;

    vtablePtr = (int *)(**(code **)(*vtablePtr + 0x24))(); // Get another component
    if (vtablePtr == nullptr) return 0xFFFFFFFF;

    vtablePtr = (int *)(**(code **)(*vtablePtr + 8))(); // Get network manager
    if (vtablePtr == nullptr) return 0xFFFFFFFF;

    threadId = (**(code **)(*vtablePtr + 0xc))(); // Get current thread ID
    if (this->threadId != threadId) {
        // Different thread: delegate via packet send
        return delegateSendPacket(this, sequenceNum, param3, param4, param5);
    }

    // Same thread: process directly
    EnterCriticalSection(&this->sendCritSec); // +0x0C
    FlushSendQueue(this); // FUN_0065d730
    LeaveCriticalSection(&this->sendCritSec);

    someManager = (int *)GetNetworkSendManager(); // FUN_0065d3a0
    if (someManager == nullptr) return 0;

    // Check for reliable packet path
    if (this->reliableQueue != nullptr && sequenceNum > 199) {
        // Allocate stack space for sending reliable packet
        packetFunc = (int *)(*(int *)(this->reliableQueue + 0x6C));
        // ... complex alloca logic for packet buffer
        // The original code uses alloca_probe to allocate space for the packet
        // and calls virtual functions to send it
        // Reconstructed simplified:
        uint allocatedSize = (**(code **)(*packetFunc + 0xC))(); // Get required size
        char *buffer = (char *)alloca(allocatedSize + 0x14); // Actual size based on alloca
        *(undefined4 *)buffer = 0x65d2fb; // Return address stub
        *(int *)(buffer + 0x4) = param3;
        *(uint *)(buffer + 0x8) = sequenceNum;
        *(int *)(buffer + 0xC) = param3; // duplicate?
        // Call virtual send function
        retVal = (*(code *)(*(int **)(this->reliableQueue))[0x0])(); // vtable[0] = send?
        if (retVal < sequenceNum) {
            // Need more: call vtable[0x28] to process more
            retVal = (*(code *)(*someManager + 0x28))(retVal, &buffer);
            return retVal;
        } else {
            retVal = (*(code *)(*someManager + 0x28))(sequenceNum, param3);
            return retVal;
        }
    } else {
        // Unreliable packet path
        int paramCopy = param5;
        int paramCopy2 = param3;
        return (**(code **)(*someManager + 0x28))(sequenceNum, param3, param5);
    }
}