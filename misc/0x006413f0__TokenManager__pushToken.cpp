// FUNC_NAME: TokenManager::pushToken
void __thiscall TokenManager::pushToken(void* this, int param_1)
{
    // Offsets relative to 'this':
    // +0x04: lastToken (?)
    // +0x08: savedLastToken (copy of lastToken)
    // +0x0C: currentToken (active token)
    // +0x10: nextToken (sliding token)
    // +0x14: tokenState (0x11F = empty/marker, else holds a token)
    // +0x18: previousToken (alternate token)
    // +0x1C: pControl (pointer to a control structure, itself a pointer to an array)
    int tokenState;
    int uVar1;
    char local_28[20]; // likely a buffer for some transformation
    char local_14[20]; // another buffer

    // Save a copy of the previous lastToken
    *(int*)(this + 8) = *(int*)(this + 4);

    // Check if the token slot is empty (0x11F = 287)
    if (*(int*)(this + 0x14) == 0x11F)
    {
        // Generate a new token and store as current
        uVar1 = FUN_00639c70(this + 0x10);
        *(int*)(this + 0x0C) = uVar1;
    }
    else
    {
        // Slide tokens: current becomes next, next becomes previous,
        // and the slot is marked empty
        *(int*)(this + 0x0C) = *(int*)(this + 0x14);
        *(int*)(this + 0x10) = *(int*)(this + 0x18);
        *(int*)(this + 0x14) = 0x11F;
    }

    // Obtain a sequence/ID from a global source (maybe incrementing counter)
    uVar1 = FUN_00641390();

    // Process the new token with buffers (likely some checksum or encoding)
    FUN_0063f080(local_14, uVar1, param_1);
    FUN_00643090(local_28);

    // Store param_1 into a dynamically allocated array inside the control structure
    // The control structure at pControl points to an array; index is taken from
    // the 7th element (index 6) of that array.
    // The offset calculation: base = *(*(pControl) + 0x14)   // base address of the array's data area
    // + ( index * 4 - 4 ) // write to previous slot? (index possibly 1‑based)
    int* controlPtr = *(int**)this + 0x1C; // this->pControl? Actually this+0x1C is a pointer to a pointer
    // Simplify: let p = *(int**)(this + 0x1C) -> points to the control structure
    // The control structure's first field (offset 0) is itself a pointer to an int array
    // Field at offset 0x14 of that array is another pointer (or address)
    int* baseAddr = (int*)(**(int**)(this + 0x1C) + 0x14);
    int* indexArray = *(int**)(this + 0x1C);
    int idx = indexArray[6]; // index into the array
    *(int*)(baseAddr + idx - 1) = param_1; // offset -4 = (idx-1)*4

    return;
}