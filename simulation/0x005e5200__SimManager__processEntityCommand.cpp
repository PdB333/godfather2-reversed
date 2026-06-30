// FUNC_NAME: SimManager::processEntityCommand
int SimManager::processEntityCommand(void* entity, int command)
{
    // entity passed in EAX, command on stack, this in EDI
    if (entity == 0) {
        return 1;
    }

    // Array of entity data at this+0x603c (each 0x74 bytes)
    int entityArrayBase = *(int*)((char*)this + 0x603c);
    unsigned int index = ((int)entity - entityArrayBase) / 0x74;
    if (index >= 512) {
        return 1;
    }

    // Command handler array at this+0x10 (each 0x30 bytes)
    void* handlerEntry = (char*)this + 0x10 + index * 0x30;
    if (handlerEntry == 0) {
        return 1;
    }

    // Handler structure offsets:
    // +0x24: function pointer
    // +0x28: user data (context)
    // +0x2c: object pointer
    void* func = *(void**)((char*)handlerEntry + 0x24);
    void* object = *(void**)((char*)handlerEntry + 0x2c);
    void* userData = *(void**)((char*)handlerEntry + 0x28);

    if (func != 0) {
        (*(void(__thiscall*)(void*, int, void*))func)(object, command, userData);
    }

    // Call default handler
    processDefaultCommand(this, object, command);

    return 1;
}