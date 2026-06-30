// FUNC_NAME: InputManager::setInputFlagsAndPostEvent
void __thiscall InputManager::setInputFlagsAndPostEvent(int this, uint inputFlags)
{
    // TLS pointer: FS:[0x2c] points to a thread-local block
    // In Windows, FS:[0x2c] is part of TEB; here it's a custom TLS slot
    ThreadLocalBlock* tlsBlock = *(ThreadLocalBlock**)(__readfsdword(0x2C));
    
    // Get the input data object from this+0x18
    InputData* inputData = *(InputData**)(this + 0x18);
    
    // Read current state at offset 0x7c indexed by tlsBlock->index
    // +0x7c appears to be an array of uint (previous state?)
    uint stateBits = *(uint*)((int)inputData + 0x7C + tlsBlock->index) & 0xC;
    
    // Modify inputFlags based on stateBits and thread-local masks
    if (stateBits == 0) {
        // Mode 0: OR with maskOr, then AND with complement of maskAnd
        inputFlags = (tlsBlock->maskOr | inputFlags) & ~(uint)tlsBlock->maskAnd;
    }
    if (stateBits == 8) {
        // Mode 8: AND with complement of maskOr, then OR with maskAnd
        inputFlags = ~(uint)tlsBlock->maskOr & (tlsBlock->maskAnd | inputFlags);
    }
    
    // Write the processed flags to offset 0x80 indexed by tlsBlock->index (current state?)
    *(uint*)((int)inputData + 0x80 + tlsBlock->index) = inputFlags;
    uint storedFlags = *(uint*)((int)inputData + 0x80 + tlsBlock->index);
    
    // Push two values onto a global event stack (logging/notification)
    // g_eventStack at DAT_01206880 has a stack pointer at offset 0x14
    int** eventStackPtr = (int**)(DAT_01206880 + 0x14);
    **(int***)(DAT_01206880 + 0x14) = &PTR_LAB_011244c4;  // Initial stack base
    (*eventStackPtr)++;  // Skip base pointer
    int* stackTop = (int*)((uint)*eventStackPtr & ~3);  // Align to 4 bytes
    *eventStackPtr = (int)stackTop;
    *stackTop = this;  // Push 'this' (object ID)
    (*eventStackPtr)++;
    *(int*)*eventStackPtr = storedFlags;  // Push stored flags
    (*eventStackPtr)++;
}