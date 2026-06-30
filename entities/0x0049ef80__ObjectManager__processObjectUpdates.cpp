// FUNC_NAME: ObjectManager::processObjectUpdates
void __thiscall ObjectManager::processObjectUpdates(void)
{
    // +0x18: pointer to a child object (maybe a root or sceneNode)
    if (this->m_pRootObject != 0)
    {
        g_sceneManager->update(); // call to FUN_004503d0 with global DAT_012233a4
    }

    // +0x8c: pointer to an array of object pointers (list of active objects)
    // +0x90: size of the array (count)
    Object** ppObjects = this->m_pActiveObjects;
    int count = this->m_nActiveObjectCount;
    Object** ppEnd = ppObjects + count;

    for (; ppObjects < ppEnd; ++ppObjects)
    {
        Object* pObj = *ppObjects;
        // +0xb2: flags byte, bit 0 = object has pending update
        if ((pObj->m_flags & 0x01) != 0)
        {
            // +0xa8: function pointer (callback) called before processing
            if (this->m_pPreProcessCallback != 0)
            {
                this->m_pPreProcessCallback();
            }
            // Dispatch event: pass global event dispatcher (DAT_012233a8+4) and object's event ID (from +0xa0)
            g_eventDispatcher->dispatchEvent(pObj->m_eventId);
        }
    }

    // +0xb0: state flags (4 bytes), low nibble compared to 3
    if ((this->m_state & 0x0F) == 3)
    {
        g_someManager->reset(); // FUN_00428d00() – clears dirty flags or resets state
        this->m_state = (this->m_state & 0xFFFFFFF0) | 1; // set low nibble to 1
    }

    // +0xac: byte flags, clear bit 1 (0x02) – marks update complete or ready
    this->m_updateFlags &= 0xFD;
}