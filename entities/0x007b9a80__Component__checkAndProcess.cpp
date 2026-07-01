// FUNC_NAME: Component::checkAndProcess
// Address: 0x007b9a80
// Role: checks a condition on a given object via virtual function, then processes if condition is true

int Component::checkAndProcess(void* this, int* pObject, int someArg) {
    if (pObject == nullptr) {
        return 0;
    }
    // Virtual call: vtbl[0x224] - likely a boolean check like canProcess or isActive
    bool canProcess = (**(bool (__thiscall**)(void*, int))(*(int*)pObject + 0x224))(this, someArg);
    if (canProcess) {
        // Calls a helper (FUN_007b5430) which presumably does the actual processing
        int result = FUN_007b5430(this, pObject); // see 0x007b5430
        return result;
    }
    return 0;
}