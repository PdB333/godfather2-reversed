// FUNC_NAME: SoundListenerManager::updateListener
float* __thiscall SoundListenerManager::updateListener()
{
    // Retrieve pointer to audio system from this+0x08
    AudioSystem* pAudioSystem = *(AudioSystem**)((uint8_t*)this + 0x08);
    // Call virtual function at vtable+0x04 to get current listener data
    // The vtable index 1 corresponds to a method returning a pointer to a listener struct
    ListenerState* pListenerState = (ListenerState*)pAudioSystem->getListenerState();

    // Copy position (x, y, z, w) from listener state into this object's buffer at this+0x20
    float* pDest = (float*)((uint8_t*)this + 0x20);
    pDest[0] = *(float*)((uint8_t*)pListenerState + 0x30); // x
    pDest[1] = *(float*)((uint8_t*)pListenerState + 0x34); // y
    pDest[2] = *(float*)((uint8_t*)pListenerState + 0x38); // z
    pDest[3] = *(float*)((uint8_t*)pListenerState + 0x3c); // w
    // Force w to zero (likely unused component)
    pDest[3] = 0.0f;

    // Notify all registered listeners that have the notification flag set
    int numListeners = *(int*)((uint8_t*)this + 0x6c);
    if (numListeners != 0)
    {
        ListenerEntry* pEntries = *(ListenerEntry**)((uint8_t*)this + 0x68);
        for (int i = 0; i < numListeners; i++)
        {
            // Each entry is 0x10 bytes:
            // +0x00: pointer to listener object
            // +0x04: ushort flags
            ListenerEntry& entry = pEntries[i];
            if (entry.flags & 0x100)
            {
                // Call virtual method at vtable+0x34 on the listener object,
                // passing the updated position buffer
                ListenerObject* pObj = entry.object;
                pObj->onListenerUpdate(pDest); // virtual call via vtable[0x34/4]
            }
        }
    }

    return pDest;
}