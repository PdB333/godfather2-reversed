// FUNC_NAME: dereferencePointer64
// Address: 0x0065c700
// Role: Trivial function that reads a 64-bit value from a pointer.
// The pointer is passed in the EAX register (non-standard calling convention).
uint64_t dereferencePointer64(uint64_t* ptr) {
    // In the original binary, this is just "mov eax, [eax]; ret"
    return *ptr;
}