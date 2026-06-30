// FUNC_NAME: BaseObject::reset
void BaseObject::reset(void) {
    // +0x00: Clears the first dword of the object (e.g., reference count, version, or flag).
    *(int*)this = 0;
}