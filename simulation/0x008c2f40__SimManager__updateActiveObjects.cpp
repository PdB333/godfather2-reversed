// FUNC_NAME: SimManager::updateActiveObjects
void __fastcall SimManager::updateActiveObjects(int this)
{
    uint count;
    int objectPtr;
    int objectArray;

    count = 0;
    if (*(int *)(this + 0x134) != 0) {
        objectArray = *(int *)(this + 0x130);
        do {
            objectPtr = objectArray + count * 0x1c; // +0x1c per slot
            if (*(char *)(objectPtr + 0xc) != '\0') { // slot active flag at +0x0c
                updateObject(objectPtr); // FUN_008c0ca0
            }
            count++;
        } while (count < *(uint *)(this + 0x134));
    }
}