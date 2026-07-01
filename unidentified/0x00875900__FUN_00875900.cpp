// FUNC_NAME: ManagerClass::removeInvalidSlots
int __fastcall ManagerClass::removeInvalidSlots(void)
{
    int removedCount = 0;
    void** slotArray = reinterpret_cast<void**>(this + 0xa4c); // +0xa4c: array of 4 object pointers
    int loopCounter = 4;

    do {
        if (*slotArray != nullptr) {
            int checkResult = isSlotValid(); // 0x00791300: returns 0 if slot is invalid/needs removal
            if (checkResult == 0) {
                removeSlotWithId(this, 0xffffffff); // 0x00791250: remove or destroy slot ( -1 as ID)
                removedCount++;
            }
        }
        slotArray++;
        loopCounter--;
    } while (loopCounter != 0);

    return removedCount;
}