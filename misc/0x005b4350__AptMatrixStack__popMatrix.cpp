//FUNC_NAME: AptMatrixStack::popMatrix

void AptMatrixStack::popMatrix(void)
{
    // Assert that stack is not empty before popping
    if (m_stackSize <= 0) {
        // Debug assertion: "nVertexMatrixStack > 0"
        // File: c:\packages001_pc\apt\0.19.optimized\source\apt\_Apt.h, line 0x1ee
        // This is a debug-only check; in release builds it's skipped.
        // The assertion mechanism uses a global flag (DAT_0112902a) and thread-local storage.
        // Simplified: assert(m_stackSize > 0);
        // For reconstruction, we keep the original logic but note it's an assert.
        // In practice, this would trigger a breakpoint or abort.
        // We'll just return without popping if assertion fails (debug behavior).
        // The original code may have a conditional breakpoint.
        // Since it's a debug check, we'll assume it's present only in debug builds.
        // For clarity, we'll use a simple assert macro.
        // assert(m_stackSize > 0);
        // But to match the decompiled code, we'll keep the structure.
        // The code below is the actual assertion logic.
        // We'll just skip the pop if the assertion fails.
        return; // In debug, this would be a breakpoint; in release, it's a no-op.
    }

    // Decrement stack size
    m_stackSize--;

    // Calculate pointer to the top element in the stack array
    // Stack array starts at offset 0x238, each element is 24 bytes (0x18)
    int topIndex = m_stackSize;
    int* stackElement = reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x238 + topIndex * 0x18);

    // Pop the three 8-byte values into the output fields at +0x220, +0x228, +0x230
    // These are likely a 3x3 matrix or a transform (quaternion + translation?)
    // The stack element is 24 bytes, copied as three 8-byte chunks.
    *reinterpret_cast<unsigned long long*>(reinterpret_cast<char*>(this) + 0x220) = *reinterpret_cast<unsigned long long*>(stackElement);
    *reinterpret_cast<unsigned long long*>(reinterpret_cast<char*>(this) + 0x228) = *reinterpret_cast<unsigned long long*>(stackElement + 2); // +8 bytes
    *reinterpret_cast<unsigned long long*>(reinterpret_cast<char*>(this) + 0x230) = *reinterpret_cast<unsigned long long*>(stackElement + 4); // +16 bytes
}