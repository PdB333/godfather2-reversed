// FUNC_NAME: ObjectContainer::findIndexByID
bool __thiscall ObjectContainer::findIndexByID(int this, int id, uint* outIndex)
{
    uint index = 0;
    if (*(uint*)(this + 8) != 0) {
        int** objectPtr = *(int***)(this + 4);
        while (true) {
            // If slot is empty or object pointer is null, skip
            if (*objectPtr == (int*)0x0 || **objectPtr == 0) {
                // empty slot, but still check next? Actually code checks *objectPtr first.
                // If *objectPtr is null, then **objectPtr would crash -> so safe.
                // Continue to next slot.
            } else {
                // Object exists, check its ID field at offset +0x70
                if (*(int*)(*(int*)*objectPtr + 0x70) == id) {
                    *outIndex = index;
                    return true;
                }
            }
            index++;
            objectPtr++;
            if (*(uint*)(this + 8) <= index) {
                return false;
            }
        }
    }
    return false;
}