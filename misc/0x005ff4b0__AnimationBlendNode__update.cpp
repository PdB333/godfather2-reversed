//FUNC_NAME: AnimationBlendNode::update
// Address: 0x005ff4b0
// This function updates the blend state of an animation blend node.
// It manages transitions between multiple animation sources (pointers at +0x7c, +0x88, +0x94)
// and computes blend weights based on positional differences.

struct AnimationBlendNode {
    // +0x00: float position[3] (or quaternion)
    float pos[3];
    // +0x60: float targetPos[3] (from source)
    float targetPos[3];
    // +0x70: int* refCountedPtr1; // reference-counted object
    int* refCountedPtr1;
    // +0x74: void* next1; // linked list pointer
    void* next1;
    // +0x78: void* prev1; // linked list pointer
    void* prev1;
    // +0x7c: int* sourceA; // first animation source
    int* sourceA;
    // +0x80: void* nextA;
    void* nextA;
    // +0x84: void* prevA;
    void* prevA;
    // +0x88: int* sourceB; // second animation source
    int* sourceB;
    // +0x8c: void* nextB;
    void* nextB;
    // +0x90: void* prevB;
    void* prevB;
    // +0x94: int* sourceC; // third animation source
    int* sourceC;
    // +0x9c: void* nextC;
    void* nextC;
    // +0xa4: void (*callback)(); // update callback
    void (*callback)();
    // +0xb0: int someInt;
    int someInt;
    // +0xb4: uint flags; // bitfield for blend control
    uint flags;
    // +0xc0: float blendWeight; // current blend weight
    float blendWeight;
    // +0xc4: float distance; // computed distance between positions
    float distance;
    // +0xe0: int state; // 1=normal, 2=transitioning
    int state;
    // +0xf4: float blendTarget1;
    float blendTarget1;
    // +0xf8: float blendTarget2;
    float blendTarget2;
    // +0xfc: float blendTarget3;
    float blendTarget3;
    // +0x100: float blendStart1;
    float blendStart1;
    // +0x104: float blendStart2;
    float blendStart2;
    // +0x108: float blendStart3;
    float blendStart3;
    // +0x118: int* someIterator;
    int* someIterator;
    // +0x120: int iteratorIndex;
    int iteratorIndex;
};

// External functions (from callees)
extern void debugPrint(int); // 0x005fea70
extern void releaseRefCounted(int*); // 0x005f7ba0
extern void assignRefCounted(int* dst, int* src); // 0x004daf90
extern void computeSomething(); // 0x005f5ce0
extern float mathSqrt(); // 0x00b9a9fa (likely sqrt)

int AnimationBlendNode::update(float* outputWeight)
{
    // Check if sourceA and sourceC are both non-null
    if ((sourceA == 0) || (sourceC == 0)) {
        debugPrint(0);
        if ((sourceA == 0) || (sourceC == 0)) {
            // Use sourceB as fallback
            float* fallbackPos;
            if (sourceB == 0) {
                fallbackPos = 0;
            } else {
                fallbackPos = (float*)prevB; // +0x90? Actually prevB is at +0x90, but here it's used as pointer to data
            }
            // Copy position from fallback
            pos[0] = fallbackPos[0];
            pos[1] = fallbackPos[1];
            pos[2] = fallbackPos[2];
            blendWeight = 0.0f;
            // Release reference-counted objects
            releaseRefCounted(sourceA);
            releaseRefCounted(sourceB);
            releaseRefCounted(sourceC);
            // If sourceA is non-null, copy targetPos from its data
            if ((sourceA != 0) && (prevA != 0)) {
                targetPos[0] = ((float*)prevA)[0];
                targetPos[1] = ((float*)prevA)[1];
                targetPos[2] = ((float*)prevA)[2];
            }
            flags |= 0x4001;
            someInt = 0;
            if (callback != 0) {
                callback();
            }
            return 3; // Status: fallback used
        }
    } else {
        // Both sourceA and sourceC are non-null
        uint f = flags;
        if (((f >> 3) & 1) == 0 && state == 1) {
            state = 2; // Start transition
        } else {
            if (((f >> 5) & 1) == 0) {
                float val = (float)blendStart3; // +0x108
                if ((float)blendStart2 != val) {
                    blendStart1 = val;
                    blendStart2 = val;
                }
            }
            if (((f >> 6) & 1) == 0) {
                float val = (float)blendTarget3; // +0xfc
                if ((float)blendTarget2 != val) {
                    blendTarget1 = val;
                    blendTarget2 = val;
                }
            }
        }
    }

    // Check if bit 7 of flags is set and sourceA equals sourceC, and sourceA is non-null, and prevA equals prevC, and bit 6 is clear
    if ((((flags >> 7) & 1) != 0) && (sourceA == sourceC) &&
        ((sourceA == 0) || (prevA == prevC)) && (((flags >> 6) & 1) == 0)) {
        // Compute distance between sourceC's position and sourceB's position
        float* posC;
        if (sourceC == 0) {
            posC = 0;
        } else {
            posC = (float*)prevC; // +0x9c? Actually prevC is at +0x9c, but here it's used as data pointer
        }
        float* posB;
        if (sourceB == 0) {
            posB = 0;
        } else {
            posB = (float*)prevB;
        }
        double dx = (double)(posC[0] - posB[0]);
        mathSqrt(); // This function might compute something else, but we assume it's sqrt
        float diff = (float)dx;
        blendTarget3 = diff;
        blendTarget1 = diff;
        blendTarget2 = diff;
    }

    // Manage linked list of sourceA (refCountedPtr1)
    int* listHead = &sourceA; // +0x7c
    int* listEntry = &refCountedPtr1; // +0x70
    if (listEntry != listHead) {
        int newVal = *listHead;
        if (*listEntry != newVal) {
            if (*listEntry != 0) {
                assignRefCounted(listEntry, 0); // Release old
            }
            refCountedPtr1 = newVal;
            if (newVal != 0) {
                next1 = *(void**)(newVal + 4);
                *(int**)(newVal + 4) = listEntry;
            }
        }
    }

    // Manage linked list for sourceB
    listEntry = &sourceB; // +0x88
    prevA = prevB; // +0x84 = +0x90? Actually prevA is at +0x84, prevB at +0x90
    if (listHead != listEntry) {
        int newVal = *listEntry;
        if (*listHead != newVal) {
            if (*listHead != 0) {
                assignRefCounted(listHead, 0);
            }
            *listHead = newVal;
            if (newVal != 0) {
                nextA = *(void**)(newVal + 4);
                *(int**)(newVal + 4) = listHead;
            }
        }
    }
    prevA = prevB; // +0x84 = +0x90

    // Manage linked list for sourceC
    listEntry = &sourceC; // +0x94
    if (&sourceB != listEntry) {
        int newVal = *listEntry;
        if (*listEntry != newVal) {
            if (*listEntry != 0) {
                assignRefCounted(listEntry, 0);
            }
            *listEntry = newVal;
            if (newVal != 0) {
                nextB = *(void**)(newVal + 4);
                *(int**)(newVal + 4) = listEntry;
            }
        }
    }
    prevB = prevC; // +0x90 = +0x9c

    computeSomething();

    // Compute output weight as difference between blendWeight and distance
    *outputWeight = (float)blendWeight - (float)distance;

    // Copy targetPos from sourceA's data
    float* srcData;
    if (sourceA == 0) {
        srcData = 0;
    } else {
        srcData = (float*)prevA;
    }
    targetPos[0] = srcData[0];
    targetPos[1] = srcData[1];
    targetPos[2] = srcData[2];

    // Compute distance between targetPos and sourceB's position
    float* posB2;
    if (sourceB == 0) {
        posB2 = 0;
    } else {
        posB2 = (float*)prevB;
    }
    float dx2 = targetPos[0] - posB2[0];
    float dy2 = targetPos[1] - posB2[1];
    float dz2 = targetPos[2] - posB2[2];
    distance = sqrt(dx2*dx2 + dy2*dy2 + dz2*dz2);
    blendWeight = 0.0f;

    // Advance iterator if present
    if (someIterator != 0) {
        uint idx = iteratorIndex;
        int count = (**(int (__thiscall**)(int*))someIterator)(someIterator); // virtual function call
        if (idx < (uint)(count - 1)) {
            iteratorIndex = idx + 1;
        }
    }

    if (callback != 0) {
        callback();
    }

    return 1; // Status: normal update
}