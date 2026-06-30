// FUNC_NAME: LockedList::forEach
// Address: 0x0064a210
// Role: Iterates over a locked list, calling a callback for each element until the callback returns false or no more elements.
// The list is protected by a critical section (pointer at +0x1b8). The critical section must be entered before calling this function.

char __thiscall LockedList::forEach(void *this, bool (*callback)(void *item, void *userData), void *userData, int startKey)
{
    char result = '\0';
    if (callback != nullptr) {
        void *item = getFirst(this, startKey); // FUN_0064a290
        if (item != nullptr) {
            result = '\x01';
            item = getNext(this); // FUN_0064a2e0
            while (item != nullptr && result != '\0') {
                result = callback(item, userData);
                item = getNext(this);
            }
        }
        CRITICAL_SECTION *cs = *(CRITICAL_SECTION **)((char *)this + 0x1b8);
        if (cs != nullptr) {
            LeaveCriticalSection(cs);
        }
    }
    return result;
}