// FUNC_NAME: StreamManager::updateLoadFlags
char __thiscall StreamManager::updateLoadFlags(StreamManager *this, byte flags)
{
    char anyLoaded = '\0';
    
    if ((flags & 1) != 0) {
        if (!StreamManager::isResourceLoaded((void*)&gResourcePtrA) && gResourcePtrA != 0) {
            StreamManager::loadBlock(this->m_buffer + 0x3c, &gResourcePtrA, 0x8000);
            anyLoaded = '\x01';
        }
    }
    
    if ((flags & 2) != 0) {
        if (!StreamManager::isResourceLoaded((void*)&gResourcePtrB) && gResourcePtrB != 0) {
            StreamManager::loadBlock(this->m_buffer + 0x3c, &gResourcePtrB, 0x8000);
            anyLoaded = '\x01';
        }
    }
    
    if ((flags & 4) != 0) {
        if (!StreamManager::isResourceLoaded((void*)&gResourcePtrC)) {
            if (gResourcePtrC == 0) {
                return '\x01'; // Resource not present, return success?
            }
            StreamManager::loadBlock(this->m_buffer + 0x3c, &gResourcePtrC, 0x8000);
            return '\x01';
        }
    }
    
    if (anyLoaded == '\0') {
        StreamManager::flushBuffer(this->m_buffer + 0x3c); // Finalize when nothing loaded
    }
    
    return anyLoaded;
}