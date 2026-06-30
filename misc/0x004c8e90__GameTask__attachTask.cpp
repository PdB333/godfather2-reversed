// FUNC_NAME: GameTask::attachTask

void __thiscall GameTask::attachTask(int param1, void* param2)
{
    // param1 passed in ECX? Actually the decompiled shows param1 in ECX (fastcall first param), param2 in EAX
    // We assume this (unaff_ESI) is the 'this' pointer from the calling convention (preserved in ESI throughout).
    // Offset 0x0c: some ID stored in this
    // Offset 0x290: pointer to attached object (set to param2)
    // Offsets 0x2b0,0x2b4,0x2b8,0x2bc,0x2c0,0x2c4: magic sentinel values for debugging/memory validation

    if ((param2 != 0) && (param1 == *(int*)(this + 0x0c))) {
        *(int*)(this + 0x290) = (int)param2;
        FUN_004d9a70(param2);   // likely processAttachedObject or similar
        FUN_005dbe70();         // likely update state or notify
        *(int*)(this + 0x2b0) = 0;
        *(int*)(this + 0x2b4) = 0xbadbadba;
        *(int*)(this + 0x2b8) = 0xbeefbeef;
        *(int*)(this + 700) = 0xeac15a55;         // offset 0x2bc
        *(int*)(this + 0x2c0) = 0x91100911;
        *(char*)(this + 0x2c4) = 0;
    }
}