// FUNC_NAME: DataDrivenManager::notifyListeners
void __thiscall DataDrivenManager::notifyListeners(int *this, int *notificationData)
{
    undefined4 *currentEntry;
    undefined1 *nameA;
    undefined1 *nameB;
    undefined4 *head;
    
    head = *(undefined4 **)this[9]; // +0x24: pointer to linked list head
    while(true) {
        if (head == (undefined4 *)this[9]) { // empty list
            return;
        }
        if (head == (undefined4 *)this[9]) {
            FUN_00b97aea(); // likely assertion/error
        }
        currentEntry = (undefined4 *)head[2]; // +0x08: node data pointer
        if (*notificationData == currentEntry[8]) break; // +0x20: compare notification ID
        if (head == (undefined4 *)this[9]) {
            FUN_00b97aea(); // assertion
        }
        head = (undefined4 *)*head; // +0x00: next node
    }
    nameA = (undefined1 *)currentEntry[4]; // +0x10: callback name string
    if (nameA == (undefined1 *)0x0) {
        nameA = &DAT_0120546e; // fallback empty string
    }
    nameB = (undefined1 *)*currentEntry; // +0x00: other name string
    if (nameB == (undefined1 *)0x0) {
        nameB = &DAT_0120546e; // fallback empty string
    }
    // +0x1c: pointer to callback dispatch function
    (**(code **)(*this + 0x1c))(nameB, nameA, notificationData[1]); // notificationData+0x04: additional data
    return;
}