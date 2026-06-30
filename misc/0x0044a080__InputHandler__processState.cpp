// FUNC_NAME: InputHandler::processState
// Function address: 0x0044a080
// Role: Handles input state transitions: if state is 0 or 0x48 (maybe inactive/neutral), queries a manager interface, checks a condition, and triggers reset or update.

extern int g_bGameActive; // DAT_01223444

void __fastcall InputHandler::processState(void* thisPtr) {
    int state = *(int*)((char*)thisPtr + 0x0C); // +0x0C: current input state
    if (state == 0 || state == 0x48) {
        // Get manager pointer (e.g., an EARS input manager)
        void* manager = *(void**)((char*)thisPtr + 0x08); // +0x08: pointer to manager
        // Call virtual function at vtable offset 0x20 (index 8) on the manager's vtable
        // This function returns a pointer to an interface object
        int* (*getInterface)() = (int* (*)())*(int*)(*(int*)(*(int*)manager + 8) + 0x20);
        int* interfaceObj = getInterface();
        // Call virtual function at vtable offset 0x58 (index 22) on interfaceObj
        // Passes the pointer stored at this+0x04 (e.g., a device handle or connection)
        bool (*checkCondition)(void*) = (bool (*)(void*))(*interfaceObj + 0x58);
        bool conditionMet = checkCondition(*(void**)((char*)thisPtr + 0x04)); // +0x04: target object
        if (!conditionMet && g_bGameActive) {
            FUN_0044ae50(); // Reset input state
            return;
        }
        FUN_0044a0e0(thisPtr); // Continue update
    }
}