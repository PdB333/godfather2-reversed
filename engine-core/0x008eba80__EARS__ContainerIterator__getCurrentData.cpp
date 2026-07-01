// FUNC_NAME: EARS::ContainerIterator::getCurrentData
int* __fastcall ContainerIterator::getCurrentData(void* thisPtr)
{
    // Iterator structure:
    // +0x00: m_container (pointer to container)
    // +0x04: m_current  (pointer to current node)
    int* container = *(int**)thisPtr;
    int* current = *(int**)((char*)thisPtr + 4);

    // Validate iterator: container must be non-null and current must not be the end marker
    if (container == nullptr) {
        // Assertion failure / crash handler
        assertionFailure();
    }
    // End marker is stored at container+4
    if (current == *(int**)((char*)container + 4)) {
        assertionFailure();
    }
    // Data is at offset 0xC from the current node pointer
    return (int*)((char*)current + 0xC);
}