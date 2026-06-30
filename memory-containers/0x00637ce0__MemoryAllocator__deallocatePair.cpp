// FUNC_NAME: MemoryAllocator::deallocatePair
void MemoryAllocator::deallocatePair(int param_1)
{
    int *counterPtr;
    byte  flagOrShift = *(byte *)(this + 7); // +0x07: flags or shift amount
    int  size1 = *(int *)(this + 0x1c);      // +0x1c: second resource size

    if (*(int *)(this + 0x10) != 0) {       // +0x10: first resource pointer
        (*DAT_012059e0)(*(int *)(this + 0x10)); // free first resource
        if (param_1 != 0) {
            counterPtr = (int *)(*(int *)(param_1 + 0x10) + 0x24);
            *counterPtr += (1 << (flagOrShift & 0x1f)) * -0x14; // adjust counter by -0x14 * (1 << shift)
        }
    }

    if (*(int *)(this + 0xc) != 0) {        // +0x0c: second resource pointer
        (*DAT_012059e0)(*(int *)(this + 0xc)); // free second resource
        if (param_1 != 0) {
            counterPtr = (int *)(*(int *)(param_1 + 0x10) + 0x24);
            *counterPtr += size1 * -8;          // adjust counter by -8 * size1
        }
    }

    (*DAT_012059e0)(); // additional cleanup (no argument)

    if (param_1 != 0) {
        counterPtr = (int *)(*(int *)(param_1 + 0x10) + 0x24);
        *counterPtr += -0x20; // final fixed adjustment to counter
    }
}