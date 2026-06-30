// FUNC_NAME: SimObject::setFlag
void __thiscall SimObject::setFlag(char newFlag)
{
    // +0x168: pointer to a state/flag data structure
    char *stateData = *(char **)(this + 0x168);
    // Flag is stored at offset 0x63 (99 decimal) in the state data
    if (newFlag != stateData[0x63]) {
        stateData[0x63] = newFlag;

        // +0x58: pointer to a notification/listener object with a vtable
        void *listener = *(void **)(this + 0x58);
        // Virtual function at vtable offset 0x28 (index 10, as each vtable entry is 4 bytes)
        // Signature: void __thiscall func(void* this, int arg)
        void (__thiscall *notify)(void *, int) = (void (__thiscall *)(void *, int))(*(int (**)[])(*(int *)listener))[0x28 / 4];
        notify(listener, 8); // Notify event 8 (e.g., flag set)
        if (newFlag == 0) {
            notify(listener, 2); // Also notify event 2 when clearing flag
        }
    }
}