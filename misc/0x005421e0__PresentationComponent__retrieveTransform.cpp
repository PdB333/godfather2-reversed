// FUNC_NAME: PresentationComponent::retrieveTransform
void __thiscall PresentationComponent::retrieveTransform(void* this, undefined4* outHeader, undefined4* outData)
{
    undefined4 localBuffer[4]; // 16-byte stack buffer (4*4 bytes)

    if (*(int*)((int)this + 0x260) != 0) { // Offset to presentation object pointer
        // Call virtual function at vtable offset 0x1c (index 7) on the presentation object
        void* presentationObj = *(void**)((int)this + 0x260);
        void* vtable = *(void**)presentationObj;
        ((void (*)())(*(int*)((int)vtable + 0x1c)))();

        // Fill output header: pointer to global static identity, zero, pointer to stack buffer
        *outHeader = (undefined4)&DAT_011397d0; // Global static identity matrix or constant
        outHeader[1] = 0;
        outHeader[2] = (undefined4)&localBuffer[0]; // Points to first 4 bytes of local buffer

        // Fill output data: copy remaining 12 bytes of local buffer
        outData[0] = localBuffer[1];
        outData[1] = localBuffer[2];
        outData[2] = localBuffer[3];
    } else {
        // No presentation object, zero out outputs
        outHeader[0] = 0;
        outHeader[1] = 0;
        outHeader[2] = 0;
        outData[0] = 0;
        outData[1] = 0;
        outData[2] = 0;
    }
}