//FUNC_NAME: SimManager::createSimObject
void __thiscall SimManager::createSimObject(void* param2, void* param3)
{
    char isActive;
    SimObject* newObj;

    isActive = isGameActive(); // FUN_00481640 - check if game is active
    if (isActive != '\0') {
        newObj = (SimObject*)allocateMemory(0x40); // FUN_009c8e50 - allocate 64 bytes
        if (newObj != (SimObject*)0x0) {
            newObj = SimObject::SimObject(this); // FUN_0089c230 - construct SimObject with manager pointer
        }
        if (newObj != (SimObject*)0x0) {
            newObj->field_0x38 = param2; // +0x38: first parameter
            newObj->field_0x3c = param3; // +0x3c: second parameter
            registerSimObject(newObj); // FUN_00481690 - register object with manager
        }
    }
    return;
}