// FUNC_NAME: SystemManager::initializeComponents
void __thiscall SystemManager::initializeComponents(int thisPtr, int userData) {
    // If not yet initialized, perform one-time init
    if (*(char*)(thisPtr + 0xd0) == '\0') {
        *(char*)(thisPtr + 0xd0) = 1;

        int gameManager = DAT_0112a878; // Global game manager pointer
        if (gameManager != 0) {
            // Possibly increment reference or attach user data
            FUN_00424dc0(userData, gameManager, 0, 1, 1);

            // Iterate over a doubly linked list at offset 0x10 (circular with sentinel)
            for (int* node = *(int**)(thisPtr + 0x10); node != (int*)(thisPtr + 0x10); node = (int*)*node) {
                // node[2] is the stored pointer to a subobject / component
                int* dataPtr = (int*)node[2];
                if (dataPtr != 0 && dataPtr != (int*)0x48) {
                    // The stored pointer is actually offset by 0x48 from the beginning of a vtable object
                    int* vtable = (int*)((char*)dataPtr - 0x48);
                    // Call virtual function at vtable+0x38 (method index 56/4 = 14)
                    (*(void(__thiscall**)(int))(*(int*)vtable + 0x38))(gameManager + 500);
                }
            }
        }

        // Check some state: if (thisPtr+0xac == 0 || thisPtr+0xac == 0x14) and global condition
        if ((*(int*)(thisPtr + 0xac) == 0 || *(int*)(thisPtr + 0xac) == 0x14) &&
            *(int*)(DAT_01223484 + 8) != 0) {
            int result = FUN_0089b1b0(); // Possibly load/initialize something
            FUN_00899a50(result);        // Pass to another initialization function
        }

        // Finally, call a global function with address DAT_012069c4
        FUN_00408680(&DAT_012069c4);
    }
}