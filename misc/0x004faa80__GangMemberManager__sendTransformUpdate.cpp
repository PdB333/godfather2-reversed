// FUNC_NAME: GangMemberManager::sendTransformUpdate
void __thiscall GangMemberManager::sendTransformUpdate(int playerPtr) {
    // +0x00: int id
    // +0x01: byte initializedFlag
    if (this->initializedFlag == 0) {
        FUN_00535450(0, this->id); // init some system with own ID
        this->initializedFlag = 1;
    }

    // Allocate packet buffer: pool 5, count 7, flags 0,1,0
    int* packet = (int*)FUN_0060cd00(5, 7, 0, 1, 0);
    if (packet != nullptr) {
        // playerPtr +0xe0 points to an array of 7 ints (IDs)
        int* srcId = (int*)(playerPtr + 0xe0);
        int* dest = packet;
        for (int i = 0; i < 7; ++i) {
            // Get current transform from some system
            Transform* trans = (Transform*)FUN_00414aa0(); // returns a transform pointer
            // Write packet entry: 3 zeros, ID, 4 transform components
            dest[0] = 0;
            dest[1] = 0;
            dest[2] = 0;
            dest[3] = *srcId;
            // Transform offsets: +0x70, +0x74, +0x78, +0x7c (likely quaternion or position+?)
            dest[4] = *(int*)((char*)trans + 0x70);
            dest[5] = *(int*)((char*)trans + 0x74);
            dest[6] = *(int*)((char*)trans + 0x78);
            dest[7] = *(int*)((char*)trans + 0x7c);
            dest += 8;
            ++srcId;
        }
        FUN_0060cde0(); // submit/queue the packet
    }
}