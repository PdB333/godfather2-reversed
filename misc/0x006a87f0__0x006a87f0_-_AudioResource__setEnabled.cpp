// FUNC_NAME: 0x006a87f0 - AudioResource::setEnabled
void __thiscall AudioResource::setEnabled(bool enable) {
    // If disabling and currently enabled, release the resource
    if (!enable) {
        if (m_isEnabled) {
            // Stop the resource (e.g., stop sound playback)
            if (m_pResource != nullptr) {
                stopResource(m_pResource, m_resourceId, 0, 0, 0);
            }
            // Free the resource memory
            if (m_pResource != nullptr) {
                freeResource(&m_pResource);
                m_pResource = nullptr;
            }
            // Reset state fields
            m_resourceId = 0;
            m_subState = 0;
            m_isEnabled = false;
        }
    } else {
        // Enable flag set (actual resource creation likely done elsewhere)
        m_isEnabled = true;
    }
}