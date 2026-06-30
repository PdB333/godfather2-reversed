// FUNC_NAME: SomeClass::releaseInputBuffers
void __fastcall SomeClass::releaseInputBuffers(int this, int param_2)
{
    // +0x564: pointer to some buffer/manager (non-null when active)
    if (*(int *)(this + 0x564) != 0) {
        // local_c = 2 suggests a command/code, local_8 = 0x1000 is size or flag, local_4 = 0
        int local_c = 2;
        int local_8 = 0x1000;
        int local_4 = 0;
        // Call through vtable of object at +0x564, probably a release/process function
        (**(code **)*(undefined4 **)(this + 0x564))(param_2, &local_c);
        return;
    }
    
    // +0x568: alternative buffer/manager (e.g., fallback or different type)
    if ((*(int *)(this + 0x568) != 0) && (param_2 != 0)) {
        // Call second vtable entry (offset +4) with typical zero-fill/memset params: dest, 0, 0, 0x20, 0
        // Likely clearing 0x20 bytes (32 bytes = 256 bits) to zero
        (**(code **)(**(int **)(this + 0x568) + 4))(param_2, 0, 0, 0x20, 0);
    }
    return;
}