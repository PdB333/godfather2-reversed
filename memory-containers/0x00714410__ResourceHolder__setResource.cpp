// FUNC_NAME: ResourceHolder::setResource
void __thiscall CResourceHolder::setResource(void* pResource) {
    // Store the new resource pointer at offset +0x10
    *(void**)((char*)this + 0x10) = pResource;

    // Check flag at +0xc (bit0) – indicates whether we currently hold references to the shared resources
    if (!(*(unsigned char*)((char*)this + 0xc) & 1)) {
        // No references held yet – acquire references to both shared global resources
        acquireReference(&g_sharedResource1);
        acquireReference(&g_sharedResource2);
    } else {
        // Already held references – release them before storing the new resource
        releaseReference(&g_sharedResource1);
        releaseReference(&g_sharedResource2);
    }
}