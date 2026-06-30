// FUNC_NAME: CollisionUtils::lineSegmentIntersect
// Function address: 0x006d0ee0
// Role: Tests if a line segment between two points intersects a shape (likely a sphere/plane)
// Uses global collision data (e.g., from a Havok or custom physics world)
// Returns 1 if intersection found, 0 otherwise; optional output parameter for intersection distance (t)

#include <cstddef>

// Assume these are global constants (likely floats)
extern float g_Epsilon;          // _DAT_00e51108
extern float g_Zero;             // _DAT_00d5780c
extern float g_SomeConstant1;    // _DAT_00d5ccf8
extern float g_SomeConstant2;    // _DAT_00e44598
extern float g_SomeConstant3;    // _DAT_00e445dc
extern void* g_GlobalPtr;        // PTR_LAB_00dc471c  (maybe a vtable or data)

// Forward declarations (from callees)
void initSomething(float epsilon);          // FUN_00a64b00
void doSomething();                         // FUN_00a64fd0
int  allocateSomeResource(int a, int b, int c); // FUN_00540c60
int  performIntersectionTest(void* queryData, float* pointB, void* param3, void* param4); // FUN_009e7fd0
float computeDotProduct(float* a, float* b); // FUN_006d0200 (signed distance calculation)

int CollisionUtils::lineSegmentIntersect(float* pointA, float* pointB, float* outT)
{
    // Save first point components (4 floats, likely 3D position + something)
    float ax = pointA[0];
    float ay = pointA[1];
    float az = pointA[2];
    float aw = pointA[3];
    
    // Save second point components
    float bx = pointB[0];
    float by = pointB[1];
    float bz = pointB[2];
    float bw = pointB[3];
    
    initSomething(g_Epsilon);
    
    // Build a 6-float array (maybe sphere center + radius)
    float sphereData[6];
    sphereData[0] = g_Zero;          // first center component
    sphereData[1] = 0.0f;
    sphereData[2] = 0.0f;
    sphereData[3] = 0.0f;
    sphereData[4] = 0.0f;
    sphereData[5] = g_Zero;          // last component (radius?)
    
    // Build a query structure on stack (44 bytes)
    struct {
        char   pad0[4];           // 0x00 (local_30)
        int    pad1;             // 0x04
        char   pad2[4];           // 0x08
        int    someFlag;         // 0x0c (local_190 offset from local_17c?)
        float  pointAx;          // 0x10
        float  pointAy;          // 0x14
        float  pointAz;          // 0x18
        float  pointAw;          // 0x1c
        float  sphereX;          // 0x20 (from sphereData[0])
        float  sphereY;          // 0x24 (from sphereData[1])
        float  sphereZ;          // 0x28 (from sphereData[2])
        float  sphereW;          // 0x2c (from sphereData[3])
        float  sphereR;          // 0x30 (from sphereData[4])
        float  sphereUnk;        // 0x34 (from sphereData[5])
        // rest of 44 bytes...
    } queryBuffer; // size 0x2c? Actually 44 bytes = 0x2c. Let's assume custom layout.

    // Reset pointer and counters
    // Note: The decompiled code does pointer arithmetic; simplified here.
    
    // Build the query object
    // (The original code sets many fields; we just show the essence)
    queryBuffer.someFlag = 0;
    
    // Copy first point into query
    queryBuffer.pointAx = ax;
    queryBuffer.pointAy = ay;
    queryBuffer.pointAz = az;
    queryBuffer.pointAw = aw;
    
    // Sphere data set from global constants
    // (sphereData[0] initialized above)
    
    // Local variable for result
    int resultCode = 0;
    float tValue = g_SomeConstant3;  // local_f4
    float tValue2 = g_SomeConstant3; // local_11c
    
    // Call to allocate? 0xc,0x17,0 might be a string identifier (like "lineSegment")
    queryBuffer.someField = allocateSomeResource(0xc, 0x17, 0);
    
    // Another global constant
    queryBuffer.anotherField = g_SomeConstant2;
    
    // Set pointer to global data
    void* globalData = &g_GlobalPtr; // local_120
    
    // Perform the intersection test
    resultCode = performIntersectionTest(&queryBuffer, &pointB[0], &globalData, &globalData);
    
    // Check result
    if (resultCode == 0) {
        if (outT == NULL) {
            return 1; // true, but no distance needed
        }
        // If outT provided, set to zero and return true? (decompiled logic)
        *outT = g_Zero;
        return 1;
    } else {
        // resultCode != 0
        if (tValue >= 0.0f) {
            if (outT != NULL) {
                *outT = tValue;
            }
            return 0; // false? Wait: the caller expects 0 for no hit? Actually return 0 here.
        }
        // tValue < 0
        if (outT == NULL) {
            float dot = computeDotProduct(pointA, pointB);
            if (-g_Epsilon < dot * tValue) {
                return 1;
            }
            return 0;
        }
        // outT provided and tValue < 0
        *outT = g_Zero;
        return 1;
    }
}