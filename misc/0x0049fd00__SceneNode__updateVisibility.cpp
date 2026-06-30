// FUNC_NAME: SceneNode::updateVisibility

// Address: 0x0049fd00
// Role: Computes aggregated AABB from child objects, expands it, and performs frustum culling.
//       Updates visibility state stored in low 4 bits of +0xb0.

// Constants from data section (global floats)
const float kAABB_MIN_INIT = 0x00e2e50c; // +infinity or large positive
const float kAABB_MAX_INIT = 0x00e44758; // -infinity or large negative
const float kAABB_MARGIN   = 0x00e2cd48; // expansion distance

// Assumed class layouts (offsets in hex)
struct MeshObject {
    float aabbMin[4]; // +0xa0 (x,y,z,w)
    float aabbMax[4]; // +0xb0 (x,y,z,w)
};

struct SceneNode {
    // +0x8c: pointer to array of child pointers
    SceneNode** childArray;   // 0x8c
    // +0x90: number of children
    int childCount;           // 0x90
    // +0xb0: visibility state (low 4 bits: 1=visible? 2=hidden? toggles)
    unsigned int visibilityFlags; // 0xb0
    // ... other members ...
};

// External function: frustum culling of AABB
// Returns 0 if fully outside, non-zero if visible.
extern "C" int __stdcall frustumCullAABB(float min[4], float max[4]);

// Possibly a debug/profiling call (does nothing in release)
void FUN_0049fb40() {
    // Empty in analyzed build
}

void SceneNode::updateVisibility() {
    // Extract low 4 bits of visibilityFlags
    unsigned int state = (visibilityFlags << 28) >> 28; // mask to low nibble
    // Only proceed if state is 1 or 2 (i.e., state - 1 < 2)
    if ((state - 1) < 2) {
        // Initialize AABB with extreme values
        float aabbMin[4];
        float aabbMax[4];
        aabbMin[0] = aabbMin[1] = aabbMin[2] = aabbMin[3] = kAABB_MIN_INIT; // should be +inf
        aabbMax[0] = aabbMax[1] = aabbMax[2] = aabbMax[3] = kAABB_MAX_INIT; // should be -inf

        // Iterate over all children
        SceneNode** iter = childArray;
        SceneNode** end = childArray + childCount;
        while (iter != end) {
            SceneNode* child = *iter;
            MeshObject* mesh = *(MeshObject**)((char*)child + 0xa0); // assume offset 0xa0 is a pointer to mesh
            // Read min/max from mesh (two 4-float vectors)
            float childMin[4];
            childMin[0] = mesh->aabbMin[0];
            childMin[1] = mesh->aabbMin[1];
            childMin[2] = mesh->aabbMin[2];
            childMin[3] = mesh->aabbMin[3];
            float childMax[4];
            childMax[0] = mesh->aabbMax[0];
            childMax[1] = mesh->aabbMax[1];
            childMax[2] = mesh->aabbMax[2];
            childMax[3] = mesh->aabbMax[3];

            // Possibly debug/profiling hook
            FUN_0049fb40();

            // Use SSE min/max instructions (emulated here)
            aabbMin[0] = (childMin[0] < aabbMin[0]) ? childMin[0] : aabbMin[0];
            aabbMin[1] = (childMin[1] < aabbMin[1]) ? childMin[1] : aabbMin[1];
            aabbMin[2] = (childMin[2] < aabbMin[2]) ? childMin[2] : aabbMin[2];
            aabbMin[3] = (childMin[3] < aabbMin[3]) ? childMin[3] : aabbMin[3];
            aabbMax[0] = (childMax[0] > aabbMax[0]) ? childMax[0] : aabbMax[0];
            aabbMax[1] = (childMax[1] > aabbMax[1]) ? childMax[1] : aabbMax[1];
            aabbMax[2] = (childMax[2] > aabbMax[2]) ? childMax[2] : aabbMax[2];
            aabbMax[3] = (childMax[3] > aabbMax[3]) ? childMax[3] : aabbMax[3];

            ++iter;
        }

        // Expand AABB by margin (x and z only, y and w unchanged)
        aabbMin[0] -= kAABB_MARGIN;
        aabbMin[1] -= 0.0f;
        aabbMin[2] -= kAABB_MARGIN;
        aabbMin[3] -= 0.0f;
        aabbMax[0] += kAABB_MARGIN;
        aabbMax[1] += 0.0f;
        aabbMax[2] += kAABB_MARGIN;
        aabbMax[3] += 0.0f;

        // Perform frustum culling
        int visible = frustumCullAABB(aabbMin, aabbMax);

        // Update visibility state (toggle between visible/hidden)
        // Formula: newFlags = oldFlags ^ ( (visible+2) ^ oldFlags ) & 0xF
        unsigned int mask = (visible != 0) + 2; // 3 if visible, 2 if not
        unsigned int lowBits = (mask ^ visibilityFlags) & 0xF;
        visibilityFlags ^= lowBits;
    }
}