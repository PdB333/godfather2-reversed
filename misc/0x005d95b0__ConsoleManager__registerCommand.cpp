// FUNC_NAME: ConsoleManager::registerCommand
// Function address: 0x005d95b0
// Reconstructed from Ghidra decompilation
// Purpose: Register a new console command; returns 0 if already registered or too long, 1 on success.
// Note: Uses EA EARS engine pattern for console variable/command registration.

__thiscall int ConsoleManager::registerCommand(char* command, uint param1, uint param2)
{
    char buffer[32]; // Stack buffer for command name (max 31 chars + null)
    int result;
    
    // Check if command already exists (FUN_005d9690 likely finds by name)
    result = findCommand(command, param1);
    if (result >= 0) {
        return 0; // Already registered, fail
    }
    
    // Compute length of command (excluding first character? Strange offset in length check)
    char* p = command;
    char* pEnd = command;
    do {
        pEnd++;
    } while (*pEnd != '\0');
    // pEnd points to null terminator; p = command; p+1 = command+1
    int len = (int)pEnd - (int)(command + 1); // strlen(command) - 1
    if (len > 0x1f) {
        return 0; // Too long (max 31 chars after first?)
    }
    
    // Copy command string into local buffer (including first character)
    // The null termination is placed at index len (which removes last character)
    // This seems intentional: maybe first character is a type prefix skipped later?
    char* src = command;
    char* dst = buffer;
    while (*src != '\0') {
        *dst = *src;
        src++;
        dst++;
    }
    // Overwrite last character with null? Actually sets buffer[len] = 0 => loses last char
    buffer[len] = '\0';
    
    // Store parameters locally (possibly for later use by the registration function)
    int local_8 = (int)param1;
    int local_4 = (int)param2;
    
    // Call actual registration routine (FUN_005d9ab0) with the truncated command name
    registerCommandInternal(buffer);
    
    return 1;
}