// FUNC_NAME: RefCountedHolder::constructor
int RefCountedHolder::constructor(int thisPtr, int* objectPtr, int attachmentData)
{
    int* currentObj = objectPtr;
    // Call virtual function at vtable +0x8 (likely AddRef)
    (*(void (**)(int*))(*(int*)currentObj + 8))(currentObj);

    int copiedData;
    if (attachmentData == 0) {
        copiedData = 0;
    } else {
        // Duplicate or assign attachmentData into the object
        copiedData = copyAttachmentData(attachmentData, currentObj);
    }

    // Initialize internal state with the object and copied data
    initializeWithData(currentObj, copiedData);

    // Store the object pointer at offset +0x14 (m_object)
    *(int**)(thisPtr + 0x14) = objectPtr;

    // Second call to vtable +0x8 (perhaps another AddRef or GetRefCount)
    (*(void (**)(void))(*(int*)objectPtr + 8))();

    if (attachmentData != 0) {
        // Re-copy attachment data using the stored object
        copiedData = copyAttachmentData(attachmentData, *(int*)(thisPtr + 0x14));
        *(int*)(thisPtr + 0x18) = copiedData; // Store at offset +0x18 (m_data)
        // Call vtable +0x4 (likely Release or Set) with attachmentData and 0
        (*(void (**)(int, int))(*(int*)objectPtr + 4))(attachmentData, 0);
        // Finalize with vtable +0xc
        (*(void (**)(void))(*(int*)objectPtr + 0xc))();
    } else {
        *(int*)(thisPtr + 0x18) = 0;
        (*(void (**)(void))(*(int*)objectPtr + 0xc))();
    }
    return thisPtr;
}