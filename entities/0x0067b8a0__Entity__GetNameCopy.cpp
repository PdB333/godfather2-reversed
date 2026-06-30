// FUNC_NAME: Entity::GetNameCopy

/**
 * Function: Entity::GetNameCopy (0x0067b8a0)
 * Returns a dynamically allocated copy of the object's name string (stored at this+0xF8).
 * Uses a global memory allocator at 0x00673070 to obtain the buffer.
 * The caller is responsible for freeing the returned string.
 */
char* __fastcall Entity::GetNameCopy(void* thisPtr) {
    // Pointer to the internal name string (offset +0xF8)
    char* nameStr = *(char**)((int)thisPtr + 0xF8);
    
    // Calculate string length
    int length = 0;
    while (nameStr[length] != '\0') {
        length++;
    }
    
    // Allocate buffer (length+1 bytes) for the copy
    char* buffer = (char*)FUN_00673070(); // e.g., allocateMemory(length + 1)
    if (buffer == 0) {
        return 0;
    }
    
    // Copy the string (including null terminator) into buffer
    char* dest = buffer;
    int remaining = length + 1;
    while (remaining > 0) {
        if (*nameStr == '\0') {
            break; // safety check, though length already counts null
        }
        *dest++ = *nameStr++;
        remaining--;
    }
    *dest = '\0'; // ensure null termination
    
    return buffer;
}