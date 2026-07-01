// FUNC_NAME: ResourceHolder::releaseHandle

void ResourceHolder::releaseHandle()
{
    // Release the resource handle at +0x80 if valid
    if (m_resourceHandle != -1) {
        // Call resource release function (FUN_0090dff0)
        releaseResource(m_resourceHandle);
        // Invalidate the handle
        m_resourceHandle = -1;
    }
}