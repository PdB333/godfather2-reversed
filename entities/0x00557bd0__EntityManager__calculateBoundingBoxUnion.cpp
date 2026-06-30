// FUNC_NAME: EntityManager::calculateBoundingBoxUnion

// Reconstructed from address 0x00557bd0
// Computes the axis-aligned bounding box union of all managed entities.
// Each entity at offset 0x40 has a pointer to an interface with a virtual function at vtable index 0x1c (7th function)
// that fills an array of 8 floats: minX, minY, minZ, minW, maxX, maxY, maxZ, maxW.
// The union is written to param_3 (float array of 8).

void EntityManager::calculateBoundingBoxUnion(int param_1, int param_2, float* outBounds)
{
    // this->m_pEntityArray[0] stored at +0x30; layout at +0x30: { pointer to array base, pointer to count }
    // Actually it's double indirection: *(int**)(this+0x30) gives a pointer to a structure?
    // From iteration: base = **(int**)(this+0x30), count = (*(int**)(this+0x30))[1], element size = 0x70.
    // So at this+0x30 is a pointer to a struct with: [arrayBase, arrayCount].
    int* arrayInfo = *(int**)(this + 0x30);
    int* entityArray = (int*)*arrayInfo;          // base pointer
    int numElements = (int)(arrayInfo[1]);         // number of elements

    // Initialize bounds extremes
    float minX = FLT_MAX;
    float minY = FLT_MAX;
    float minZ = FLT_MAX;
    float minW = 0.0f;
    float maxX = -FLT_MAX;
    float maxY = -FLT_MAX;
    float maxZ = -FLT_MAX;
    float maxW = 0.0f;

    // Variables to hold temporary bounding box from each entity
    float entityMinX, entityMinY, entityMinZ, entityMinW;
    float entityMaxX, entityMaxY, entityMaxZ, entityMaxW;

    // Iterate over array of entities (each 0x70 bytes)
    for (int i = 0; i < numElements; i++)
    {
        int* entity = (int*)((char*)entityArray + i * 0x70);

        // Check if entity has a bounding box interface (pointer at +0x40)
        int* bboxInterface = (int*)*(entity + 0x40 / 4); // offset 0x40
        if (bboxInterface != nullptr)
        {
            // Call virtual function at vtable offset 0x1c
            // The function signature: void (__thiscall*)(void* bboxInterface, int param_1, int param_2, float* outBounds_entity)
            typedef void (__thiscall* BBoxFunc)(void*, int, int, float*);
            BBoxFunc getBBox = (BBoxFunc)(*(int*)(*(int*)bboxInterface + 0x1c));
            getBBox(bboxInterface, param_1, param_2, &entityMinX);

            // Update min components
            if (entityMinX <= minX) minX = entityMinX;
            if (entityMinY <= minY) minY = entityMinY;
            if (entityMinZ <= minZ) minZ = entityMinZ;
            if (entityMinW <= minW) minW = entityMinW;

            // Update max components
            if (entityMaxX >= maxX) maxX = entityMaxX;
            if (entityMaxY >= maxY) maxY = entityMaxY;
            if (entityMaxZ >= maxZ) maxZ = entityMaxZ;
            if (entityMaxW >= maxW) maxW = entityMaxW;
        }
    }

    // Write output
    outBounds[0] = minX;
    outBounds[1] = minY;
    outBounds[2] = minZ;
    outBounds[3] = minW;
    outBounds[4] = maxX;
    outBounds[5] = maxY;
    outBounds[6] = maxZ;
    outBounds[7] = maxW;
}