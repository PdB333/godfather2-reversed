// FUNC_NAME: ObjectManager::releaseSubResources
void __thiscall ObjectManager::releaseSubResources() {
    // *in_EAX = 0; // Potential return value initialization (ignored for void)
    subRefCountAdjust(2);  // Might be reference counting or integrity check

    // Release object at (this+0x180)->0x78
    int* subObj1 = reinterpret_cast<int*>(*(int*)(*(int*)(this + 0x180) + 0x78));
    int* refData = reinterpret_cast<int*>(*(int*)(this + 4));
    if (subObj1 != nullptr) {
        // Clear the slot in the sub-object array
        *(int*)(*(int*)(refData + 0xc) + *(int*)(subObj1 - 2) * 4) = 0;
        // Decrement reference count
        --*(int*)(refData + 4);
        // Free the sub-object (including header at -0x10)
        (*DAT_01206694)(subObj1 - 4);
    }
    *(int*)(*(int*)(this + 0x180) + 0x78) = 0;

    // Release object at this+0x50
    int* subObj2 = reinterpret_cast<int*>(*(int*)(this + 0x50));
    refData = reinterpret_cast<int*>(*(int*)(this + 4));
    if (subObj2 != nullptr) {
        *(int*)(*(int*)(refData + 0xc) + *(int*)(subObj2 - 2) * 4) = 0;
        --*(int*)(refData + 4);
        (*DAT_01206694)(subObj2 - 4);
    }

    // Release object at this+0x54
    int* subObj3 = reinterpret_cast<int*>(*(int*)(this + 0x54));
    refData = reinterpret_cast<int*>(*(int*)(this + 4));
    if (subObj3 != nullptr) {
        *(int*)(*(int*)(refData + 0xc) + *(int*)(subObj3 - 2) * 4) = 0;
        --*(int*)(refData + 4);
        (*DAT_01206694)(subObj3 - 4);
    }

    // Additional cleanup calls
    FUN_00673210();  // Possibly finalize internal state
    FUN_00672fd0();  // Possibly unlock or signal

    DAT_012058ba = 0;  // Global flag reset

    // Unregister this instance from global list (max 2 instances)
    for (uint i = 0; i < 2; ++i) {
        if (g_instanceList[i] == this) {
            g_instanceFlags[i] = 0;
            return;
        }
    }
}