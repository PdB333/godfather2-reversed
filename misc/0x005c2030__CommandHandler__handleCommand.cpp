// FUNC_NAME: CommandHandler::handleCommand

void __thiscall CommandHandler::handleCommand(char* command)
{
    // Compare command string case-insensitively.
    // The vtable pointer is located 0x10 bytes before 'this' (likely because
    // 'this' points to a base class subobject, and the complete object's vtable
    // resides at the beginning of the complete object at offset -0x10 from this).
    int vtablePtr = *(int*)((char*)this - 0x10);

    if (_stricmp(command, "Show") == 0)
    {
        // Call virtual function at vtable + 0x28 (index 10)
        (*(void (**)(void))(vtablePtr + 0x28))();
    }

    if (_stricmp(command, "Hide") == 0)
    {
        // Call virtual function at vtable + 0x2c (index 11)
        (*(void (**)(void))(vtablePtr + 0x2c))();
    }
}