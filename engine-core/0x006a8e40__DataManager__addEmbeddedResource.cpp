// FUNC_NAME: DataManager::addEmbeddedResource
void __thiscall DataManager::addEmbeddedResource(DataManager* this, int id, int extraInfo)
{
    // Member offsets:
    // +0x48: pointer to ring buffer array (int*)
    // +0x4C: capacity of the ring buffer (max elements)
    // +0x50: base index within the ring buffer (start offset)
    // +0x54: current write index (incremented each call)
    int* ringBuffer = *(int**)((char*)this + 0x48);
    int capacity = *(int*)((char*)this + 0x4C);
    int baseIndex = *(int*)((char*)this + 0x50);
    int writeIndex = *(int*)((char*)this + 0x54);

    // Register the id as "embedded" resource (e.g., asset type)
    FUN_00603130(id, extraInfo, "embedded");

    // Calculate the target slot; wrap using subtraction when exceeding capacity
    int currentSlot = baseIndex + writeIndex;
    *(int*)((char*)this + 0x54) = writeIndex + 1;

    if (capacity <= currentSlot) {
        // Wrap around: subtract capacity to stay within array bounds
        ringBuffer[currentSlot - capacity] = id;
    } else {
        ringBuffer[currentSlot] = id;
    }
}