// FUN_NAME: CommandManager::processOutgoingMessages
void CommandManager::processOutgoingMessages() {
    int* currentItem = *(int**)(this + 0x18);  // +0x18: current command to dispatch
    if (currentItem != nullptr) {
        int** globalListHead = (int**)(DAT_012233a4 + 0x10);  // global linked list head pointer
        int* oldHead = *globalListHead;
        if (oldHead != nullptr) {
            *(int*)(oldHead + 0x9c) = currentItem;  // +0x9c: prev pointer
        }
        *(int*)(currentItem + 0xa0) = (int)oldHead;  // +0xa0: next pointer
        *globalListHead = currentItem;  // prepend to global list
    }

    FUN_0049feb0();  // likely pops next item from a queue

    // Iterate over an array of command pointers (offset 0x8c = pointer, 0x90 = count)
    int** commandArray = *(int***)(this + 0x8c);
    int commandCount = *(int*)(this + 0x90);
    if (commandArray && commandCount > 0) {
        for (int i = 0; i < commandCount; ++i) {
            int* cmd = commandArray[i];
            if ((*(byte*)(cmd + 0xb2) & 1) != 0) {  // +0xb2: flags, bit0 = ready to send
                FUN_0049fd00(this);  // prepare or allocate send buffer
                char headerBuffer[28];  // e.g., packet header
                FUN_0042cfa0(
                    *(undefined4*)(DAT_012233a8 + 4),  // some global pointer (network?)+4
                    this,
                    *(undefined4*)(cmd + 0xa0),        // +0xa0: command ID or type
                    cmd + 0x10,                        // +0x10: payload data
                    headerBuffer,                      // output header
                    *(undefined2*)(cmd + 0xb0),        // +0xb0: data size or channel
                    *(undefined4*)(this + 0xb4)        // +0xb4: some context/callback
                );
            }
        }
    }

    *(byte*)(this + 0xac) |= 2;  // +0xac: flags, set bit1 (maybe processing done)
}