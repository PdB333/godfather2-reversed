// FUNC_NAME: Container::forEachItem
char Container::forEachItem(code *callback, int userData, int filter)
{
    char result = 0;
    if (callback != (code *)0x0) {
        int current = this->beginIteration(filter); // FUN_0064a290 - acquires critical section, returns first item
        if (current != 0) {
            result = 1;
            current = this->getNextItem();           // FUN_0064a2e0 - gets next item
            while ((current != 0) && (result != 0)) {
                result = (*callback)(current, userData);
                current = this->getNextItem();
            }
        }
        LPCRITICAL_SECTION cs = *(LPCRITICAL_SECTION *)(this + 0x1b8); // critical section handle
        if (cs != (LPCRITICAL_SECTION)0x0) {
            LeaveCriticalSection(cs);
        }
    }
    return result;
}