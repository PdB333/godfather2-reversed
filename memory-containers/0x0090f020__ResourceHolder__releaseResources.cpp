// FUNC_NAME: ResourceHolder::releaseResources
// Function address: 0x0090f020
// Releases two externally-owned sub-objects whose pointers and destructor/cleanup
// function pointers are stored in this object at fixed offsets.
//
// Field offsets (relative to thisPtr):
//   +0x04 : first sub-object pointer
//   +0x10 : cleanup function pointer for the first sub-object
//   +0x18 : second sub-object pointer
//   +0x24 : cleanup function pointer for the second sub-object

void __thiscall ResourceHolder::releaseResources(int thisPtr) {
    // Release first sub-object if it exists
    if (*(int*)(thisPtr + 0x4) != 0) {
        (**(code**)(thisPtr + 0x10))(*(int*)(thisPtr + 0x4));
    }

    // Release second sub-object if it exists
    if (*(int*)(thisPtr + 0x18) != 0) {
        (**(code**)(thisPtr + 0x24))(*(int*)(thisPtr + 0x18));
    }
}