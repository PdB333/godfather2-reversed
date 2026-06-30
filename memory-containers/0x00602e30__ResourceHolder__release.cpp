// FUNC_NAME: ResourceHolder::release
void __fastcall ResourceHolder::release(void* thisPtr)
{
    ResourceHolder* self = (ResourceHolder*)thisPtr;
    // Check if resource is already released (m_bInitialized == 0)
    if (self->m_bInitialized == 0) {
        // Reset flag (redundant, but ensures consistency)
        self->m_bInitialized = 0;
        // Release the resource pointed to by m_pResource
        FUN_009c8f10(self->m_pResource);
        // Zero out pointers
        self->m_pResource = 0;
        self->m_pSomething = 0;
    }
}