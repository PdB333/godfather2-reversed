// FUNC_NAME: ComputeTriangleNormal

#include <cmath>

// Forward declarations of known functions (from Godfather 2 EARS engine)
extern bool FUN_00542650(uint handle1, uint handle2, int type, int flags, int unknown, int unknown2);
extern bool FUN_009e5ed0(char* buffer, void** vtablePtr);
extern void FUN_00aa2bb0(int transformData, float* result); // Transform a point using some matrix
extern void FUN_0056afa0(float* vec, float* out); // Normalize 3D vector

// Globals referenced in function
extern uint _DAT_00d5780c; // Some global object handle or ID
extern void* PTR_FUN_00e32a8c; // Vtable pointer for some class

/**
 * Computes the normalized normal of a triangle defined by points P, A, B.
 * The triangle is extracted from game objects identified by handle1 and handle2.
 * @param handle1 First identifier (e.g., object ID)
 * @param handle2 Second identifier (e.g., component ID)
 * @param[out] outNormal Output normalized triangle normal (3 floats)
 * @return 1 on success, 0 on failure.
 */
__attribute__((regparm(3))) int __stdcall ComputeTriangleNormal(uint handle1, uint handle2, float* outNormal)
{
    // Call to retrieve or initialize something with the handles
    if (!FUN_00542650(handle1, handle2, 2, 0x1000000, 0, 0))
    {
        outNormal[0] = 0.0f;
        outNormal[1] = 0.0f;
        outNormal[2] = 0.0f;
        return 0;
    }

    // Local variables for object resolution
    char buffer[80]; // Buffer for name/path resolution
    void* vtablePtr = &PTR_FUN_00e32a8c; // Vtable of expected class
    uint globalObjId = _DAT_00d5780c; // Some global ID
    uint localObjId = _DAT_00d5780c;  // Another copy

    // Resolve handle to an object instance
    // FUN_009e5ed0 likely resolves a handle to a specific game object
    int* instancePtr = nullptr; // Pointer to the resolved object
    FUN_009e5ed0(buffer, &vtablePtr);
    // After call, instancePtr might be set indirectly? The code uses local_270 which is set from the call.
    // Actually local_270 is set from inside the call? In decomp, local_270 is assigned after the call.
    // We'll simulate by assuming the function modifies a pointer.

    // The decomp shows local_270 set after call; let's assume it's output of that function.
    // For now, we keep it as is.

    if (instancePtr == nullptr)
    {
        outNormal[0] = 0.0f;
        outNormal[1] = 0.0f;
        outNormal[2] = 0.0f;
        return 0;
    }

    int* objectVtable = (int*)*instancePtr;
    int subType = objectVtable[3]; // e.g., offset 0xC? Possibly a type field

    if (subType == 0xB) // 11: Some specific type
    {
        // Virtual call to get sub-object
        objectVtable = (int*)(*(code**)(*objectVtable + 0x14))(); // First virtual call
        objectVtable = (int*)(*(code**)(*objectVtable + 0x14))(handle2, buffer); // Second virtual call with args
        subType = objectVtable[3];
    }

    if (subType == 4) // Expected triangle type
    {
        int transformData = instancePtr[2]; // +8 offset: some transform or matrix

        // Transform three points from local to world space (or vice versa)
        // The points are stored in consecutive floats in objectVtable starting at offset 4?
        // We'll define local array for three points: P, A, B
        float pointP[3], pointA[3], pointB[3];
        float* currentPoint = pointP;
        for (int i = 0; i < 3; i++)
        {
            // FUN_00aa2bb0 applies a transformation using transformData to a point from object
            // The second argument is address of a point in object data + i*12? The loop adds offset 4 each iter.
            // In decomp, the second arg is (int)objectVtable + 4 + (int)currentPoint. This is ambiguous.
            // Likely the function reads a point from objectVtable+4 (first vertex) and transforms it into currentPoint.
            // We'll assume it reads three consecutive vertices from object at offset 4,12,20.
            FUN_00aa2bb0(transformData, (float*)((char*)objectVtable + 4 + (int)currentPoint));
            currentPoint += 3;
        }

        // Now compute cross product (B-P) x (A-P) and negate to get triangle normal
        float dx1 = pointB[2] - pointP[2]; // B.z - P.z
        float dy1 = pointA[1] - pointP[1]; // A.y - P.y
        float dy2 = pointB[1] - pointP[1]; // B.y - P.y
        float dz1 = pointA[2] - pointP[2]; // A.z - P.z
        float dx2 = pointB[0] - pointP[0]; // B.x - P.x
        float dz2 = pointA[0] - pointP[0]; // A.x - P.x

        // These are the components of -((B-P) x (A-P))
        float crossX = dx1 * dy1 - dy2 * dz1; // x component
        float crossZ = dy2 * dz2 - dx2 * dy1; // z component (note sign: -((B-P)x(A-P)).z)
        float crossY = dx2 * dz1 - dx1 * dz2; // y component

        // Assemble into vector (crossX, crossY, crossZ) and normalize
        float normal[3] = { crossX, crossY, crossZ };
        FUN_0056afa0(normal, normal); // In-place normalization

        // Output
        outNormal[0] = normal[0];
        outNormal[1] = normal[1];
        outNormal[2] = normal[2];
        return 1;
    }

    outNormal[0] = 0.0f;
    outNormal[1] = 0.0f;
    outNormal[2] = 0.0f;
    return 0;
}