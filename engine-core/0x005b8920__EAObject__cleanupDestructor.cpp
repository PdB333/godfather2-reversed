// FUNC_NAME: EAObject::cleanupDestructor
// Address: 0x005b8920
// This appears to be a destructor/cleanup routine for an EARS object.
// It calls sub-destructors, frees an allocated buffer if it's not the stack fallback,
// and writes a dead signature (0xbeefceec) at this+0x20 to mark free'd memory.

void EAObject::cleanupDestructor(void)
{
    // Stack buffer for potential small allocation fallback
    char stackBuffer[16];

    // Call sub-destructors (likely base class or component destructors)
    baseDestructorPart1();  // 0x005a0980
    baseDestructorPart2();  // 0x005a1060

    // local_14 is a pointer that was previously allocated. If it points to the stack buffer,
    // it was a placement new fallback and should not be freed. Otherwise free it.
    // (Decompiler may have omitted the original assignment to local_14 from member or local)
    if ((this->allocatedPtr != stackBuffer) && (this->allocatedPtr != nullptr)) {
        // Global free function pointer – likely EA's custom allocation system
        gFreeFunction(this->allocatedPtr);
    }

    // Write dead signature to identify freed memory (common EA pattern)
    this->magicSignature = 0xbeefceec;  // +0x20
}