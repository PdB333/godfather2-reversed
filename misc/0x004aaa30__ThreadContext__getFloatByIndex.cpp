// FUNC_NAME: ThreadContext::getFloatByIndex
float __fastcall ThreadContext::getFloatByIndex()
{
    // Retrieve TLS base pointer from TEB (FS:[0x2c])
    // FS segment register points to Thread Information Block (TIB)
    // Offset 0x2c contains the pointer to the thread-local storage array
    int** tlsArrayPtr = (int**)__readfsdword(0x2c);
    int* tlsDataBlock = *tlsArrayPtr; // First slot of TLS array holds per-thread data

    // Read integer at offset +0x8 from TLS data block, this is the base address of a float array (cast to int for arithmetic)
    int floatArrayBase = *(int*)((char*)tlsDataBlock + 8) + 0x90; 

    // Index into the float array from this object's field at offset 0x18
    int index = *(int*)((char*)this + 0x18);

    // Return the float value from the thread-local array
    return *(float*)((char*)floatArrayBase + index * sizeof(float));
}