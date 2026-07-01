// FUNC_NAME: ResourceManager::createFromTemplate
void ResourceManager::createFromTemplate(unsigned int resourceId, const float data[4], unsigned int paramId)
{
    // TLS thread safety
    TlsGetValue(gTlsIndex); // DAT_01139810

    // Allocate a new resource object (size 0x30, class ID 0x27)
    int newResource = allocObject(0x30, 0x27); // FUN_00aa2680
    *(short *)(newResource + 4) = 0x30; // Set size field at +0x04

    // Retrieve the source resource from global manager
    SomeResource *source = (SomeResource *)getResourceFromManager(resourceId, gResourceManager); // FUN_00a66df0

    // Copy incoming 16-byte data block into local stack (e.g., transform or color data)
    float dataCopy[4];
    dataCopy[0] = data[0];
    dataCopy[1] = data[1];
    dataCopy[2] = data[2];
    dataCopy[3] = data[3];

    // Process the parameter ID (e.g., resolve into actual data)
    char buffer[48];
    processParameter(paramId, buffer); // FUN_004b59d0

    // Call virtual function on 'this' (vtable index 3, offset +0x0C) with source resource
    (this->vtable[3])(source);

    // Release temporary stack buffer
    releaseTemporaryStack(buffer); // FUN_009f17c0

    // Decrement reference count on source
    if (*(short *)((char *)source + 4) != 0)
    {
        if (--*(short *)((char *)source + 6) == 0)
        {
            // When refcount reaches zero, call virtual release function
            source->release(1); // (**(code**)*source)(1)
        }
    }
}