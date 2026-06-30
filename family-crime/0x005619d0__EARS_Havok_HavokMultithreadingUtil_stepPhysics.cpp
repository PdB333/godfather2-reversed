// Xbox PDB: EARS::Havok::HavokMultithreadingUtil::stepPhysics
// FUNC_NAME: GodfatherGameManager::updateFrame
void GodfatherGameManager::updateFrame(float deltaTime)
{
    // TLS-based profiler: log a "MiTimestep" milestone with the delta time
    LPVOID tlsData = TlsGetValue(dwTlsIndex);
    char** pNext = *(char***)((char*)tlsData + 4);
    char** pEnd  = *(char***)((char*)tlsData + 0xC);
    if (pNext < pEnd)
    {
        *pNext = "MiTimestep";
        pNext[1] = (char*)(uintptr_t)deltaTime; // store value as pointer (debug profiling)
        *(char***)((char*)tlsData + 4) = pNext + 2;
    }

    // Save delta time for this frame (offset +0x134)
    this->m_frameDeltaTime = deltaTime;

    // Pre‑update phase
    preUpdate();

    // Update logic with delta time
    updateWithDelta(this->m_frameDeltaTime);

    // Update based on active object count (offset +0x4)
    updateWithObjectCount(this->m_activeObjectCount);

    // Clear temporary state
    int dummy = 0;
    clearTempState(&dummy);

    // Finalize frame update
    finalizeUpdate();

    // Update each active object
    for (int i = 0; i < this->m_activeObjectCount; ++i)
    {
        updateSingleObject();
    }
}