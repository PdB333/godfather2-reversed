// FUNC_NAME: VectorHolder::constructFromRange
class VectorHolder {
public:
    // Layout: 5 int flags (offsets 0x00-0x10) + pointer to vector data (offset 0x14) = 24 bytes
    // Vector data structure at vectorData:
    //   +0x00: mBegin (char*)
    //   +0x04: mWritePtr (char*)
    //   +0x08: mCapacityEnd (char*)
    //   +0x0C: mGrowThreshold (int) – number of elements before reallocation

    void* __thiscall constructFromRange(void* srcBegin, void* srcEnd, void* vectorData, int destroyFlag) {
        char* it = (char*)srcBegin;
        char* end = (char*)srcEnd;

        if (it != end) {
            do {
                char* writePtr = *(char**)((int)vectorData + 4);
                if (writePtr < *(char**)((int)vectorData + 8)) {
                    // Space available: copy 4-byte element
                    *(int*)writePtr = *(int*)it;
                    *(int*)((int)vectorData + 4) += 4; // advance write pointer
                } else {
                    // Need to grow the vector
                    int capacity = *(int*)((int)vectorData + 12);
                    int usedCount = ((int)writePtr - *(int*)vectorData) >> 2;
                    if (capacity <= usedCount) {
                        // FUN_00b97aea: reallocate/grow vector (placeholder)
                        vectorGrow();
                    }
                    // Write element after potential reallocation
                    if (*(char**)((int)vectorData + 4) != nullptr) {
                        *(int*)(*(char**)((int)vectorData + 4)) = *(int*)it;
                    }
                    *(int*)((int)vectorData + 4) += 4;
                    *(int*)((int)vectorData + 8) = *(int*)((int)vectorData + 4);
                }
                it += 4;
            } while (it != end);
        }

        // Initialize the holder object: five zero fields then pointer to vector data
        *(int*)this = 0;
        *((int*)this + 1) = 0;
        *((int*)this + 2) = 0;
        *((int*)this + 3) = 0;
        *((int*)this + 4) = 0;
        *((int*)this + 5) = (int)vectorData;

        if (destroyFlag != 0) {
            // FUN_009c8eb0: possibly destroy source range or flags (placeholder)
            destroySource(destroyFlag);
        }

        return this;
    }
};