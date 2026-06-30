// FUNC_NAME: MeshInstance::renderSubmit
// Function at 0x0053ebd0: Sets up and submits a mesh instance for rendering.
// This could be part of a character body part system (like BodyPart or Destructible).
// Offsets relative to 'this' (param_1):
//  +0x10: base pointer for an array of body part data (array of structs)
//  +0x18: pointer to shared mesh data (e.g., bounding box)
//  +0x20: char - index into the body part array
//  +0x28: char - body part type (1 or 2, selects different transform source)
//  +0x70: char* - body name string (may be null, defaults to "nullBodyName")
// Globals:
//  DAT_01223480 - likely a renderer or scene manager
//  DAT_012067c4 - some object ref (maybe a debug renderer)
//  DAT_012067c8 - counter
//  DAT_0103b270, DAT_0103b274 - flags for debug/monitoring

class MeshInstance {
public:
    void renderSubmit(); // __thiscall
};

// Forward declarations of external functions
void* getResource(int* outResource, unsigned int resourceId); // FUN_004af8c0
void submitMesh(void* renderer, float* transform, const char* bodyName); // FUN_00540430
int  getDebugFlag(/*some global*/); // FUN_00402080 - checks if debug renderer is active
void resetDebugRenderer(/*some global*/, unsigned int flags); // FUN_004084d0
int  checkDebugOverlay(/*some global*/); // FUN_00ab5130 - returns -2 if inactive
void enableDebugOverlay(int enable); // FUN_00ab51e0

// Global symbols
extern char* DAT_01223480; // renderer pointer (or scene manager)
extern int DAT_012067c4;   // debug renderer object
extern int DAT_012067c8;   // debug counter
extern int DAT_0103b270;   // some debug flag
extern int DAT_0103b274;   // another debug flag
extern int DAT_00e2d728;   // unknown global

void MeshInstance::renderSubmit() {
    int iVar3;
    int iVar4;
    int iVar5;
    int local_34;
    int local_30;
    float transform[4]; // actually 4 ints but used as float[4] (e.g., bounding box or matrix)
    // local_2c..local_14 are part of transform array
    float& t0 = transform[0];
    float& t1 = transform[1];
    float& t2 = transform[2];
    float& t3 = transform[3];
    // But Ghidra shows them as undefined4; we'll treat as float[4]

    char bodyType = *(char*)(this + 0x28);
    char bodyIndex = *(char*)(this + 0x20);
    int* basePtr = (int*)(this + 0x10); // array base

    // Determine transform source based on bodyType
    if (bodyType == 1) {
        iVar3 = (int)basePtr + bodyIndex; // pointer to body part data at index
    } else {
        iVar3 = 0;
    }
    if (bodyType == 2) {
        local_34 = (int)basePtr + bodyIndex;
    } else {
        local_34 = 0;
    }

    // Attempt to get resource 0x2001 (likely a cached mesh or animation)
    if ((basePtr != 0) && ((int)basePtr + bodyIndex != 0)) {
        getResource(&local_30, 0x2001);
        iVar5 = (local_30 != 0) ? local_30 : 0;
        if (iVar5 != 0) goto LAB_0053ec62;
    }
    // Fallback to resource 0x2000
    iVar5 = 0;
    if ((basePtr != 0) && ((int)basePtr + bodyIndex != 0)) {
        getResource(&local_30, 0x2000);
        iVar5 = (local_30 != 0) ? local_30 : 0;
    }

LAB_0053ec62:
    // Read transform data from appropriate source
    if (iVar3 == 0) {
        if (local_34 == 0) {
            local_34 = (int)this; // fallback to this
        }
        // From local_34 +0x18 -> pointer to shared mesh data
        int* sharedData = *(int**)(local_34 + 0x18);
        t0 = *(float*)(sharedData + 0x30);
        t1 = *(float*)(sharedData + 0x34);
        t2 = *(float*)(sharedData + 0x38);
        t3 = *(float*)(sharedData + 0x3c);
    } else {
        // From iVar3 +0x110 (e.g., per-instance offset)
        t0 = *(float*)(iVar3 + 0x110);
        t1 = *(float*)(iVar3 + 0x114);
        t2 = *(float*)(iVar3 + 0x118);
        t3 = *(float*)(iVar3 + 0x11c);
    }

    if (iVar5 == 0) {
        // No resource obtained: use default transform values as magic sentinels
        transform[0] = 0xbadbadba; // placeholder
        transform[1] = 0xbeefbeef;
        transform[2] = 0xeac15a55;
        transform[3] = 0x91100911;

        // Check debug overlay on renderer (DAT_01223480)
        if (*(char*)(DAT_01223480 + 0x28) != '\0') {
            int debugResult = checkDebugOverlay(&DAT_00e2d728);
            if (debugResult != -2) {
                DAT_0103b270 = 0;
            }
        }

        const char* bodyName = *(const char**)(this + 0x70);
        if (bodyName == nullptr) {
            bodyName = "nullBodyName";
        }

        // Submit mesh via the renderer
        submitMesh(DAT_01223480, transform, bodyName);

        if (*(char*)(DAT_01223480 + 0x28) != '\0') {
            enableDebugOverlay(1);
            DAT_0103b274 = 0;
        }
    } else {
        // Resource obtained: call virtual render function on resource
        // The resource object's vtable at +0x8 points to a render method
        (**(code**)(*(int*)(iVar5 + 0x3c) + 8))();

        // If debug renderer is active and not yet reset, increment counter and reset it
        if ((DAT_012067c4 != 0) && (getDebugFlag(&DAT_012067c4) == '\0')) {
            DAT_012067c8 += 1;
            resetDebugRenderer(&DAT_012067c4, 0x8000);
            return;
        }
    }
    return;
}