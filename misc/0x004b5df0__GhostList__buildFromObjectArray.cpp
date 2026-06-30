// FUNC_NAME: GhostList::buildFromObjectArray
void __thiscall GhostList::buildFromObjectArray(void* thisPtr, uint32_t arg2, uint32_t arg3, GhostListSource* source)
{
    uint32_t* allocHeader;
    uint32_t* nodeArray;
    int32_t i;
    uint32_t nodeCount;
    uint32_t allocSize;
    uint32_t rawNodeAddr;
    int32_t* sourceObjPtr;
    void* objectInfo;

    nodeArray = nullptr;
    if (source != nullptr && (nodeCount = source->count, (int32_t)nodeCount > 0))
    {
        // Allocate memory for nodes: each node is 0x70 bytes, plus header
        allocSize = nodeCount * 0x70;
        allocHeader = (uint32_t*)AllocateAligned(allocSize + 0x10, 2, 0x10, 0);
        if (allocHeader != nullptr)
        {
            nodeArray = allocHeader + 4;
            *allocHeader = nodeCount;
            // Call constructor for each node (default constructor at 0x00556780)
            vector_constructor_iterator(nodeArray, 0x70, nodeCount, (void (*)(void*))0x00556780);
        }
        this->nodes = nodeArray;
        this->nodeCount = nodeCount;
        int32_t iteration = 0;
        int32_t offset = 0;
        if (nodeCount > 0)
        {
            do
            {
                sourceObjPtr = source->objectPtrArray[iteration];
                // Begin serialization context? Reset stream?
                BeginSerialization();
                InitSerializationBuffer(local_buffer_204bytes);
                objectInfo = (*(void* (**)(void))(*sourceObjPtr + 0x18))(); // Virtual call: getObjectInfo
                rawNodeAddr = (uint32_t)(this->nodes + offset);
                CopyObjectToNode(sourceObjPtr, arg3, arg2);
                *(uint32_t*)(objectInfo + 0x2C) = (rawNodeAddr >> 2) | 0xC0000000; // Store node pointer as tagged pointer
                EndSerialization();
                // If object's state is not 'alert' (0x07) and not 'dead' (0x06), set current node
                if (*(int8_t*)(objectInfo + 0xD8) != 0x07 && *(int8_t*)(objectInfo + 0xD8) != 0x06)
                {
                    this->currentNode = rawNodeAddr;
                    *(uint32_t*)(rawNodeAddr + 0x54) = 0xFFFFFFFF; // Mark node as pending?
                }
                offset += 0x70;
                iteration++;
            }
            while (iteration < (int32_t)nodeCount);
        }
    }
    return;
}