// FUNC_NAME: RenderScene::processVisibleNodes
void RenderScene::processVisibleNodes()
{
    // +0x18: pointer to name string or descriptor
    char* nameString = *(char**)(this + 0x18);
    bool hasName = (nameString != nullptr) && (*(char*)(nameString + 0x10) != (char)0x00);

    int scratchBuffer = 0;
    if (hasName) {
        // Allocate a scratch buffer of type 0x2001 (maybe a packet or command buffer)
        scratchBuffer = FUN_004af8c0(0x2001);
    }

    // Build a descriptor structure
    // +0x00: size = 0x3e0
    // +0x04: id (from this+0xe0)
    // +0x08: flags = 0x80000000
    // +0x0c: unknown = 0
    Descriptor desc;
    desc.size = 0x3e0;
    desc.id = *(int*)(this + 0xe0);
    desc.flags = 0x80000000;
    desc.unknown = 0;

    // Begin profiling (likely)
    FUN_00a64b00(gProfilerContext);

    // Clear internal caches or buffers
    FUN_00549bf0();

    // Smart pointer management: local_130 is a vtable for a ref-counted object
    // local_70[0] was pointing to something, we dec ref and release if needed
    SmartPointer oldPtr = m_pSmartPtr;
    if (oldPtr != nullptr) {
        oldPtr->refCount--;
        if (oldPtr->refCount == 0) {
            oldPtr->vtable->release(1);
        }
    }
    // Re‑init the smart pointer to a local structure on the stack
    m_pSmartPtr = &stackSmartPtr;
    stackSmartPtr.vtable = &gSmartPtrVTable;
    if (stackSmartPtr.refCount != 0) {
        stackSmartPtr.refCount++;
    }

    // Prepare base iterator array
    // local_248 is a vtable (possibly for base array operations)
    // local_238 = negative sentinel (-0x7ffffff0) indicating no array yet
    int entryCount = 0;
    // local_54 = ((uint)&desc >> 2) | 0x40000000;  // flags for internal iteration

    // Get position from the scene object associated with this node
    // this+0x14 -> SceneObject, +0x30 -> Transform, +0x18 -> transformation matrix
    SceneObject* sceneObj = *(SceneObject**)(this + 0x14);
    Transform* transform = *(Transform**)(sceneObj + 0x30);
    float* posData = (float*)(transform + 0x18);
    Vector4 position;
    position.x = posData[0];   // +0x30
    position.y = posData[1] + gPositionOffset; // +0x34 + global offset
    position.z = posData[2];   // +0x38
    position.w = posData[3];   // +0x3C

    // Register smart pointer and base array with the rendering subsystem
    FUN_009eb910(&m_pSmartPtr, *(int*)(*(int*)(gEngineGlobal + 0x24) + 0x6c), &gBaseArrayVTable);

    // Iterate over visible entries stored in local_234 array (0x10 bytes each)
    Entry* entries = &gEntryBuffer;
    entryCount = *(int*)(this + 0x88); // example offset for count – adjust as needed
    for (int i = 0; i < entryCount; i++) {
        Entry* entry = &entries[i];
        // +0x08 in entry: pointer to a data block
        // +0x0C: additional data
        if (entry->dataPtr != nullptr && *(char*)(entry->dataPtr + 0x10) != (char)0x00) {
            int instanceAlloc = FUN_004af8c0(0x2001);
            if (instanceAlloc != 0) {
                RenderInstance* instance = (RenderInstance*)instanceAlloc;

                // Re‑fetch transform data (could be optimized out by compiler)
                Transform* transform2 = *(Transform**)(sceneObj + 0x30);
                float* posData2 = (float*)(transform2 + 0x18);

                // Build render parameters
                RenderParams params;
                params.pos = Vector4(posData2[0], posData2[1], posData2[2], posData2[3]);
                params.constant1 = gRenderConst1;     // 0x01126050
                params.constant2 = gRenderConst2;     // 0x01126054
                params.constant3 = gRenderConst3;     // 0x01126058
                params.baseOffset = *(int*)(this + 0x18) + 0x10; // from name string
                params.reserved = 0;
                params.dataFromName = *(int*)(*(int*)(this + 0x18) + 0x14);
                params.entryPtr = entry;               // pointer to current entry
                params.entryData = entry->data;

                // Call virtual function at offset 200 (0xC8) on the instance
                // Arguments: scratchBuffer, a byte from name string +0x28, and params
                instance->vtable->render(scratchBuffer, *(char*)(*(int*)(this + 0x18) + 0x28), &params);
            }
        }
    }

    // Cleanup the entry array if it was allocated (non‑negative count)
    if (entryCount >= 0) {
        TlsGetValue(gTlsSlot);
        FUN_00aa26e0(entries, entryCount << 4, 0x17); // size = count * 16, type 0x17
    }

    // Final smart pointer release
    SmartPointer finalPtr = m_pSmartPtr;
    if (finalPtr != nullptr) {
        if (finalPtr->refCount > 0) {
            finalPtr->refCount--;
            if (finalPtr->refCount == 0) {
                finalPtr->vtable->release(1);
            }
        }
    }
}