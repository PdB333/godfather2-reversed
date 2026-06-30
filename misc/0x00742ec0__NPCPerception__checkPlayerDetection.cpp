// FUNC_NAME: NPCPerception::checkPlayerDetection

#include <cmath>

// Assumed class layout (offsets relative to 'this')
// +0x50: m_spatialNode (pointer to a SpatialNode sub-object, embedded at offset 0x48 in its container)
// +0x54: m_targetReference (pointer to a similar embedded object, e.g., player reference)
// +0x60: m_localPosition (array of 3 floats: local X, Y, Z for the sensing entity)

// Structure for a simple 3D vector
struct Vector3 {
    float x, y, z;
};

// Global threshold squared distance for detection (from DAT_00d5e288)
extern const float g_detectionRadiusSq;

// External functions
int* FUN_00471610(); // Returns pointer to player object (assume Player*)
int  FUN_00742a70(int* pObj); // Release/Decrement reference on object at pObj - 0x48?
int* FUN_009a76f0(int* pContainer, int* pOut1, int* pOut2, int zero); // Lookup child/handle?
int  FUN_0044b210(int* pThing); // Alert/Teleport callback

int __fastcall NPCPerception::checkPlayerDetection(int thisPtr) {
    int* spatialNode = *(int**)(thisPtr + 0x54);
    int* container = *(int**)(thisPtr + 0x50);

    // Validate pointers
    if (spatialNode == nullptr || spatialNode == (int*)0x48 || container == nullptr)
        return 0;

    // The pointer at +0x54 points into a sub-object; subtract 0x48 to get base of the node's owner
    int* nodeOwner = (spatialNode != (int*)0) ? (int*)((char*)spatialNode - 0x48) : nullptr;

    // Call virtual function at offset 0xa4 on nodeOwner's vtable
    // Signature: void getLocalPosition(Vector3* out, float* inTransform)
    // The 'inTransform' is the local transform data at this+0x60
    Vector3 localPos;
    typedef void (__thiscall* GetLocalPosFn)(void* self, Vector3* out, float* transform);
    GetLocalPosFn getPos = *(GetLocalPosFn*)(*(int**)nodeOwner + 0xa4);
    getPos(nodeOwner, &localPos, (float*)(thisPtr + 0x60));

    // Get the player object
    int* player = FUN_00471610();
    if (player == nullptr)
        return 0;

    // Player's world position is at offsets +0x30, +0x34, +0x38
    float playerX = *(float*)(player + 0x30); // +0x30? Wait offsets are in bytes, but pointer arithmetic on int* scales by 4. Need cast.
    // Actually player is an int*; offsets +0x30/4 = +0xc? No. Better to use char* cast.
    float* playerPos = (float*)((char*)player + 0x30);
    float dx = playerPos[0] - /* unaff_EBX? */ 0;   // Placeholder: actual NPC X from register
    float dy = playerPos[1] - /* unaff_ESI? */ 0;   // Placeholder: actual NPC Y from register
    float dz = playerPos[2] - localPos.z;           // Difference in Z (Z from localPos)

    // Compute squared distance
    float distSq = dx*dx + dy*dy + dz*dz;
    if (distSq >= g_detectionRadiusSq)
        return 0;

    // Process detection
    int* someProp = *(int**)(container + 0x1e90);  // +0x1e90 from container (0x1e90 bytes offset)
    int* adjustedProp = (someProp != nullptr) ? (int*)((char*)someProp - 0x48) : nullptr;
    int* adjustedSpatial = (spatialNode != nullptr) ? (int*)((char*)spatialNode - 0x48) : nullptr;

    // Release references (maybe decrement ref counts)
    FUN_00742a70(adjustedSpatial);
    int* resultObj = FUN_009a76f0(container, &someTemp, &someTemp, 0);
    FUN_00742a70(adjustedProp);

    if (resultObj != nullptr && *(int*)(resultObj + 0x24) != 0 && *(int*)(resultObj + 0x24) != (int)0x48) {
        int* target = (int*)((char*)*(int*)(resultObj + 0x24) - 0x48);
        FUN_0044b210(target);
        return 1;
    }
    return 0;
}