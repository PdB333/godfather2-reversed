// FUNC_NAME: ArrayElementAccessor::getNextElement
void __fastcall ArrayElementAccessor_getNextElement(int *param_1)
{
    int elementIndex;    // The index of element to retrieve (offset +0x00 from param_1)
    int *basePtr;       // The base pointer to the array (offset +0x08 from param_1)
    int currentPtr;     // A pointer used as an offset for the next call
    int outputBuffer[1]; // A small buffer possibly used for output from the helper function

    elementIndex = *param_1;                    // param_1[0] (index)
    basePtr = (int *)(param_1[2]);             // param_1[2] (base address)
    // Calculate the address of the requested element (size 0x20 per entry)
    int elementAddr = elementIndex * 0x20 + (int)basePtr;

    // in_EAX likely represents the current iterator position or a base offset
    // that is being advanced by 0x20 to get the next element
    int nextOffset = (int)in_EAX + 0x20;

    // Call a helper function that takes an output buffer and a pointer to the next offset
    FUN_005a3480(outputBuffer, &nextOffset);
    return;
}