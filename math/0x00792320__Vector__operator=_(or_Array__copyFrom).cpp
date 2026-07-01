// FUNC_NAME: Vector::operator= (or Array::copyFrom)
int* __thiscall Vector::operatorEquals(int* thisPtr, int* otherPtr)
{
    int iVar1;
    undefined4* puVar2;
    uint uVar3;

    if (thisPtr != otherPtr) {
        // If current capacity (thisPtr[2]) is less than other's size (otherPtr[1])
        if ((uint)thisPtr[2] < (uint)otherPtr[1]) {
            // Free old buffer
            FUN_009c8f10(*thisPtr); // likely operator delete[] or free
            int newCapacity = otherPtr[1];
            thisPtr[2] = newCapacity;
            if (newCapacity == 0) {
                iVar1 = 0;
            }
            else {
                iVar1 = FUN_009c8e80(newCapacity * 4); // likely operator new[] or malloc
            }
            *thisPtr = iVar1; // new buffer pointer
        }
        uVar3 = 0;
        if (otherPtr[1] != 0) {
            do {
                puVar2 = (undefined4*)(*thisPtr + uVar3 * 4);
                if (puVar2 != (undefined4*)0x0) {
                    *puVar2 = *(undefined4*)(uVar3 * 4 + *otherPtr);
                }
                uVar3 = uVar3 + 1;
            } while (uVar3 < (uint)otherPtr[1]);
        }
        thisPtr[1] = otherPtr[1]; // copy size
    }
    return thisPtr;
}