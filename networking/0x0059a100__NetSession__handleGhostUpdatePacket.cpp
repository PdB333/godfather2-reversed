// FUNC_NAME: NetSession::handleGhostUpdatePacket
// Address: 0x0059a100
// This function processes a network packet of type 0xCC (ghost update?).
// It reads a timestamp, position, rotation, flags, and applies them to a ghosted object via the SimManager singleton.

void __thiscall NetSession::handleGhostUpdatePacket(void* thisPtr, NetPacket* packet)
{
    // packet->dataBuffer is at offset +8 (packet[2])
    byte* dataBuffer = *(byte**)((int*)packet + 2);

    // Validate packet type: expect 0xCC at offset +2
    if (*(short*)(dataBuffer + 2) != 0xCC) {
        // Unknown packet type -> call error handler
        // DAT_01205590 is a vtable pointer for some error handling function
        (**(code**)(*DAT_01205590 + 4))();
    }

    // Build 32-bit timestamp from bytes at offsets 4,8,0xC,0x10 (big-endian? little-endian combination)
    uint timestamp = ( (*(int*)(dataBuffer + 4) * 0x100 + *(int*)(dataBuffer + 8)) * 0x100 + *(int*)(dataBuffer + 0xC) ) * 0x100 + *(int*)(dataBuffer + 0x10);

    // Local variable to hold pointer to dataBuffer+0x78 (used later)
    byte* updateDataPtr = dataBuffer + 0x78;

    // Get the singleton SimManager
    SimManager* simMgr = (SimManager*)FUN_00599aa0(); // likely SimManager::getInstance()
    if (simMgr == nullptr) {
        (**(code**)(*DAT_01205590 + 4))();
        return;
    }

    int unknownValue = *(int*)(dataBuffer + 0x68); // some data

    // Begin ghost state update (vtable offset 0x2C = 11th virtual function)
    (**(code**)(simMgr->vtable + 0x2C))();

    // Write consecutive fields into simMgr's internal buffer (offsets 0x4E*4=0x138, etc.)
    simMgr->field_0x138 = *(int*)(dataBuffer + 0x74);
    simMgr->field_0x13C = *(int*)((int)thisPtr + 0x44); // unaff_EBX is the 'this' pointer of the NetSession
    simMgr->field_0x140 = *(int*)((int)thisPtr + 0x48);
    simMgr->field_0x144 = (uint)*(byte*)(dataBuffer + 0x24);
    simMgr->field_0x148 = (uint)*(byte*)(dataBuffer + 0x25);

    // Retrieve model/template pointer from dataBuffer+0x18
    int* modelPtr = *(int**)(dataBuffer + 0x18);

    // Call a function to set position/scale (DAT_012055a8+4) - parameters: x, modelPtr?, z, 1.0f
    (**(code**)(*(int*)DAT_012055a8 + 4))( *(float*)(dataBuffer + 0x14), modelPtr, *(float*)(dataBuffer + 0x1C), 1.0f );

    // Call a function to transform? (DAT_012055a8+0x10) with pointer to stack and updateData?
    (**(code**)(*(int*)DAT_012055a8 + 0x10))(&updateDataPtr, /* stack address? */);

    // Build a local update structure to pass to subsequent functions
    struct GhostUpdateData {
        float rotX;      // at +0x5C
        float rotY;      // +0x58
        float rotZ;      // +0x54
        uint flag1;      // +0x50 (byte from +0x21)
        uint flag2;      // +0x4C (byte from +0x22)
        int modelField1; // +0x44 (from modelPtr+0x4C)
        int modelField2; // +0x40 (from modelPtr+0x50)
        bool flagA;      // +0x3C (byte from +0x20)
        bool flagB;      // +0x3B (byte from +0x23)
        bool flagC;      // +0x3A (byte from +0x26)
        bool flagD;      // +0x39 (byte from +0x27)
        int* extraData;  // +0x60 (pointer to dataBuffer+0x28)
        int* modelRef;   // +0x48 (modelPtr)
    } update;

    update.rotX = *(float*)(dataBuffer + 0x68);
    update.rotY = *(float*)(dataBuffer + 0x6C);
    update.rotZ = *(float*)(dataBuffer + 0x70);
    update.flag1 = (uint)*(byte*)(dataBuffer + 0x21);
    update.flag2 = (uint)*(byte*)(dataBuffer + 0x22);
    update.modelField1 = *(int*)((int)modelPtr + 0x4C);
    update.modelField2 = *(int*)((int)modelPtr + 0x50);
    update.flagA = *(char*)(dataBuffer + 0x20) != 0;
    update.flagB = *(char*)(dataBuffer + 0x23) != 0;
    update.flagC = *(char*)(dataBuffer + 0x26) != 0;
    update.flagD = *(char*)(dataBuffer + 0x27) != 0;
    update.extraData = (int*)(dataBuffer + 0x28);
    update.modelRef = modelPtr;

    // Call utility functions to finalize update
    FUN_005945a0(0); // likely debug/logging
    FUN_00594890();  // likely state machine update

    // End ghost state update (same virtual function)
    (**(code**)(simMgr->vtable + 0x2C))(*(int*)((int)modelPtr + 0x40));
}