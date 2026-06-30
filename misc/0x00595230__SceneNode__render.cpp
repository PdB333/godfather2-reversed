// FUNC_NAME: SceneNode::render
void SceneNode::render(void* renderContext) {
    // Local transform data (likely a 4x3 matrix or similar)
    struct Transform {
        float data[11]; // 44 bytes
    } worldTransform;
    float scale = 1.0f; // 0x3f800000
    float* transformPart1; // local_34
    float* transformPart2; // local_38

    // Debug marker strings (addresses from Ghidra)
    const char* debugMarker1 = (const char*)0x59524c;
    const char* debugMarker2 = (const char*)0x595256;

    // Store the render context
    void* currentTransform = renderContext;

    // Push debug marker (likely for profiling)
    pushDebugMarker(debugMarker1);

    // Update the transform pointer to a stack variable
    currentTransform = &transformPart1; // local_3c
    pushDebugMarker(debugMarker2);

    // Query some engine state and update a flag at offset 0x7C
    bool flagResult = queryEngineState(); // FUN_00595950
    if (flagResult) {
        flags |= 0x100; // Set bit 8
    } else {
        flags &= ~0x100; // Clear bit 8
    }

    // Build the world transform with scale 1.0
    currentTransform = &worldTransform;
    worldTransform.data[0] = scale; // local_48
    worldTransform.data[1] = *transformPart1; // local_4c
    worldTransform.data[2] = *transformPart2; // local_50

    // Call renderer function with the previous transform (local_3c)
    g_rendererVtable->setTransform(transformPart1); // offset +4

    // Check if there is additional data at offset 0x14 (byte pointer)
    byte* extraData = *(byte**)(this + 0x14);
    if (extraData != nullptr && (*extraData & 4) != 0) {
        // Modify the transform using extra data
        g_rendererVtable->modifyTransform(&currentTransform, extraData + 0x10, &transformPart1); // offset +0x18
        g_rendererVtable->applyTransform(&transformPart1, &transformPart2); // offset +0x10
    }

    // Call virtual render function with the world transform
    (this->vtable[0x48])(&currentTransform); // offset +0x48

    // If flag bit 8 is set, call another virtual function (e.g., render children)
    if (flags & 0x100) {
        (this->vtable[0x3c])(); // offset +0x3c
    }
}