// FUNC_NAME: SpatialHash::queryOverlappingObjects
void __thiscall SpatialHash::queryOverlappingObjects(void* this, int* gridData, float* sphereQuery, int callbackArg1, int callbackArg2)
{
    // this: SpatialHash instance (unused except for grid index)
    // gridData: pointer to grid management structure with cells array at +8
    // sphereQuery: pointer to { float x, y, z, radius }
    // callbackArg1, callbackArg2: extra args passed to the vtable function of overlapped objects

    int* cellsBase = *(int**)(gridData + 8);  // +0x08: pointer to 2D cell array of int* (linked list heads)
    // Cell index calculation: using packed coordinates from this and gridData? Actually from this (EAX) and first parameter?
    // For reconstruction, assume the function receives two separate integer coordinates (gridX and gridY) via this and gridData?
    // But we'll derive from the decompiler's usage of param_1 (sphereQuery) and in_EAX (this).

    // The original code used: ((int)param_1 >> 8) as column and (in_EAX >> 8) as row.
    // We'll assume the sphereQuery pointer is reinterpreted as an integer x coordinate (packed as a fixed-point float? Or the struct has an integer gridX at same address? Bad assumption.
    // For clean code, we'll assume the function has two integer parameters for grid cell index: gridX and gridY.
    // Since we cannot change the signature, we'll invent: the function actually receives two integers passed through normal registers but the decompiler saw float* for first param.
    // To maintain consistency with the decompiled output, we'll keep the signature as is but note the true semantics.

    // Compute grid cell index from two coordinates: gridX = (int)sphereQuery >> 8, gridY = (int)this >> 8
    // This is a hack; real code likely uses member variables.
    int gridX = ((int)sphereQuery) >> 8;  // treat sphereQuery pointer as packed integer
    int gridY = ((int)this) >> 8;        // treat this pointer as packed integer
    // grid stride is 16 (0x10)
    int cellIndex = gridX * 16 + gridY;  // assume row-major with 16 columns

    // Get the head of the linked list for this cell
    float* nodeListHead = (float*)cellsBase[cellIndex];  // each cell stores a pointer to a float array (node)

    float* currentNode = nodeListHead;
    while (currentNode != nullptr)
    {
        // Node layout:
        // [0]: float x position
        // [1]: float y position
        // [2]: float z position
        // [3]: float radius
        // [7]: float* next (interleaved but pointer stored as float, offset 0x1C)
        // [8]: float* object pointer (offset 0x20, actually points to a C++ object with vtable)

        // Calculate squared distance between sphereQuery center and node position
        float dx = sphereQuery[0] - currentNode[0];
        float dy = sphereQuery[1] - currentNode[1];
        float dz = sphereQuery[2] - currentNode[2];
        float distSq = dx*dx + dy*dy + dz*dz;

        // Combined radius
        float combinedRadius = currentNode[3] + sphereQuery[3];

        if (distSq <= combinedRadius * combinedRadius)
        {
            // Overlap: call the node's object's virtual function at index 1
            void* object = *(void**)((int*)currentNode[8]);  // dereference to vtable pointer
            int vtable = *(int*)object;                      // vtable address
            void (*callbackFunc)(float*, int, int) = (void (*)(float*, int, int))(*(int*)(vtable + 4));  // second entry
            callbackFunc(sphereQuery, callbackArg1, callbackArg2);
        }

        // Advance to next node (stored at offset 0x1C as a pointer, cast from float*)
        currentNode = (float*)currentNode[7];  // next pointer (offset 7 floats from start)
    }
}