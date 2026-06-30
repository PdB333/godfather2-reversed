// FUNC_NAME: CommandSystem::lookupAndExecuteCommand

int CommandSystem::lookupAndExecuteCommand(const char* commandName)
{
    CommandEntry* entry = s_commandListHead; // global DAT_01205a2c
    while (entry)
    {
        if (entry->enabled) // +0x08 flag
        {
            // Compare commandName with the command object's name at offset 0x20
            CommandObject* obj = entry->object; // +0x04
            if (strcmp(commandName, obj->name) == 0)
            {
                // Call the execution method via vtable entry at offset 4
                return obj->execute();
            }
        }
        entry = entry->next; // +0x00 next pointer
    }
    return 0; // not found
}