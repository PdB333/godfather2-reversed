// FUNC_NAME: ResourceContainer::releaseOwnedResources
// Address: 0x00833990
// Role: Releases three owned resources by calling stored destructor function pointers.
// Offsets (in ints): +0x00 = m_pResourceA, +0x03 = m_pReleaseFuncA
//                    +0x14 = m_pResourceB, +0x17 = m_pReleaseFuncB
//                    +0x18 = m_pResourceC, +0x1b = m_pReleaseFuncC
// In bytes: 0x00, 0x0C, 0x50, 0x5C, 0x60, 0x6C

void __thiscall ResourceContainer::releaseOwnedResources(int *thisPtr)
{
    // Release resource C (highest offset)
    if (thisPtr[0x18] != 0) {
        ((void (*)(void *))thisPtr[0x1b])((void *)thisPtr[0x18]);
    }

    // Release resource B (middle offset)
    if (thisPtr[0x14] != 0) {
        ((void (*)(void *))thisPtr[0x17])((void *)thisPtr[0x14]);
    }

    // Release resource A (lowest offset)
    if (*thisPtr != 0) {
        ((void (*)(void *))thisPtr[3])((void *)*thisPtr);
    }
}