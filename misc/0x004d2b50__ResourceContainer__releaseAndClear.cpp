// FUNC_NAME: ResourceContainer::releaseAndClear
// Address: 0x004d2b50
// Role: Releases resources pointed to by the container and zeros all fields.
// Structure layout: [0] pointer to resource A, [4] some id/flag, [8] pointer to resource B
// Called function is likely a release/destructor for resource A.

void __thiscall ResourceContainer::releaseAndClear(ResourceContainer* thisPtr)
{
    // Zero the flag/status field at offset +0x04
    thisPtr->m_statusFlag = 0;

    // Release the resource at offset +0x00 by calling its destructor/free function
    if (thisPtr->m_pResourceA)
    {
        FUN_009c8f10(thisPtr->m_pResourceA);
        // FUN_009c8f10 is likely a global release function (e.g., operator delete, or object destructor)
    }

    // Zero both pointer fields at offsets +0x00 and +0x08
    thisPtr->m_pResourceA = 0;
    thisPtr->m_pResourceB = 0;
}