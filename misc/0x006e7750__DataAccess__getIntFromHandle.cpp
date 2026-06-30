// FUNC_NAME: DataAccess::getIntFromHandle
// Address: 0x006e7750
// Calls: DataAccess::getPointerFromHandle (0x006e6e40)
// Returns the first integer value stored at the pointer obtained from the handle.

int DataAccess::getIntFromHandle(int handle) {
    int* dataPtr = (int*)DataAccess::getPointerFromHandle(handle);
    if (dataPtr != nullptr) {
        return *dataPtr;
    }
    return 0;
}