// FUNC_NAME: SimManager::clearObjectArray
// Address: 0x00650d80
// Reconstructed C++ code

void __thiscall SimManager::clearObjectArray() {
    int** objects = *(int***)(this + 0x210); // Array of 1024 object pointers
    if (objects == 0) {
        return;
    }
    for (int i = 0; i < 0x400; ++i) { // 1024 entries
        int* obj = objects[i];
        if (obj != 0) {
            // Call vtable[5] (offset 0x14) – likely a cleanup/release method
            (*(void(__thiscall**)(int*))(obj[0] + 0x14))(obj);
            // Call vtable[1] (offset 4) with parameter 1 – likely a deallocation/destructor
            (*(void(__thiscall**)(int*, int))(obj[0] + 4))(obj, 1);
            objects[i] = 0;
        }
    }
}