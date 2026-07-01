// FUNC_NAME: NavigationPath::samplePath

// Function: 0x008f95e0
// Samples a point along a path with optional obstacle/clearance checks.
// Returns 1 on success, 0 on failure.
// param_2 (out) - sampled world position (Vec3)
// param_3 (out) - direction vector (Vec3) - tangent or perpendicular based on flags
// param_4 (out) - type: 0 = normal, 1 = perpendicular (used with flag0x4)
// param_5 - flags: 1=use alternative speed, 2=disable random variation, 4=debug/overrude

#include <cstdint>

// Forward declarations of helper functions (simplified)
extern uint32_t FUN_008f81c0();                          // returns 0 if path clear?
extern float FUN_00427180();                             // random (0..1)
extern void* FUN_007ff880();                             // get active actor?
extern void FUN_0043a210(float* v, float* result);       // normalize vector
extern float FUN_0045c4b0(void* ptr, float* vec);        // angle/dot ?
extern int FUN_005f5ec0(void* a, void* b);               // get some index
extern bool FUN_005fd340(uint16_t, uint32_t, void*);     // check property
extern void FUN_006a7fd0(void* data);                    // process
extern bool FUN_006c0050(float* point, int, int);        // collision check (returns 0 if no collision?)
extern float FUN_006bfff0(float* point);                 // distance to something
extern bool FUN_0083ce40(float* point);                 // occlusion check?
extern bool FUN_0083bb40(float* point);                 // secondary check?

// Global data (simplified)
extern uint32_t DAT_010c2678;                            // seed
extern uint32_t DAT_012054b4;                            // counter
extern float DAT_010c2680[?];                            // threshold array?
extern void* DAT_011298e4;                               // global config struct
extern float DAT_00e448a4;                               // max step count?
extern float DAT_00d812a8;                               // fallback direction (up?)
extern float DAT_00e44564;                               // constant? 0?
extern float DAT_00d813a8;                               // step size?

class NavigationPath {
public:
    // Member fields (offset from this)
    // +0x00: vtable
    // +0x04-0x58: other data
    // +0x58: float alternativeSpeed1? (used when flag&1 clear)
    // +0x60: float speedNormal
    // +0x64: float maxDist
    // +0x160: void* pathData? (pointer to another struct)
    // +0x194: void* pathSegment? (pointer to path segment geometry)
    // +0x1e0: Vec3 startPoint?
    // +0x1e8: float startPointZ?
    // +0x208: int pointCount
    // +0x20c: void** pointList (array of Vec3*)
    // +0x234: void** alternatePointList? (array of pointers)
    // +0x25c: float* cumulativeDistances (array of floats)
    // +0x284: int secondaryPointCount?
    // +0x288: void** secondaryPointList?
    // +0x2b0: float* secondaryCumulativeDistances?
    // +0x3b4: float speed1 (used when flag&1)
    // +0x3b8: float speed2 (used when flag&1 clear? actually condition)
    // +0x3c0: float randomSpeedBase
    // +0x3c4: float randomSpeedMultiplier
    // +0x3c8: float randomSpeedScale
    // +0x3cc: float distanceLimit
    // +0x3d0: float clearanceHeight?
    // +0x3d4: float maxDistanceOffset?
    // +0x3d8: float minSpeed?
    // +0x428: uint32_t flags

    // Method: samplePath
    // Input: outPos (Vec3), outDir (Vec3), outType, flags
    // Returns 0/1
    bool samplePath(float* outPos, float* outDir, uint8_t* outType, uint32_t flags) {
        // Check if path geometry exists
        if (*(int*)(this + 0x194) == 0 || *(short*)(*(int*)(this + 0x194) + 0xc) == 0) {
            return false;
        }

        // Override flags if internal flag bit set
        if ((*(uint32_t*)(this + 0x428) >> 2) & 1) {
            flags |= 2;
        }

        uint32_t pathData = *(uint32_t*)(this + 0x160);
        uint32_t uVar6 = *(uint32_t*)(pathData + 0x8e0) >> 4;   // some flag

        float speed, maxDist;
        if ((uVar6 & 1) == 0) {
            speed = *(float*)(this + 0x60);      // normal speed
        } else {
            speed = *(float*)(this + 0x58);      // alternative speed
        }
        maxDist = *(float*)(this + 100);            // +0x64

        float dist = 0.0f;
        bool bVar2 = false;
        float height = *(float*)(this + 0x60);     // for later
        bool bVar4 = false;
        bool bVar3 = false;
        float stepLimit = 0.0f;

        if ((flags & 4) == 0) {      // not debug mode
            if ((flags & 2) == 0) {
                // Random seed based selection for alternative speed
                uint32_t index = DAT_010c2678 & DAT_012054b4;
                DAT_012054b4 = DAT_012054b4 + 1;
                float altSpeed;
                if ((flags & 1) == 0) {
                    altSpeed = *(float*)(this + 0x3b8);
                } else {
                    altSpeed = *(float*)(this + 0x3b4);
                }
                if (DAT_010c2680[index] < altSpeed) {
                    bVar2 = true;   // use alternative path?
                }
            }

            bool clear = FUN_008f81c0();   // check if initial clear?
            if (!clear && !bVar2) {
                // Use standard path points
                int count = *(int*)(this + 0x284);   // secondary point count?
                float* dists = (float*)(this + 0x2b0);
                void** points = (void**)(this + 0x288);
                // jump to main loop
                goto main_loop;
            } else {
                // Use randomized variant
                height = *(float*)(this + 0x3d0);
                speed = *(float*)(this + 0x3c0);
                maxDist = *(float*)(this + 0x3d4);
                bVar3 = true;
                if (dist < *(float*)(this + 0x3c8)) {
                    float rand = FUN_00427180();     // random float
                    speed = rand * *(float*)(this + 0x3c8) + speed;
                }
                dist = 0.0f;
                // Apply actor speed modifier
                if (*(int*)(this + 0x160) != 0) {
                    int* actor = (int*)FUN_007ff880();
                    if (actor != nullptr) {
                        float actorSpeed = (**(float (__thiscall**)(int*))(*(int*)*actor + 0x1b0))(actor);
                        speed = actorSpeed * *(float*)(this + 0x3c4) + speed;
                    }
                    dist = 0.0f;
                }
                float diff = maxDist - *(float*)(this + 0x3d8);
                if (diff < speed) {
                    speed = diff;
                }
                stepLimit = *(float*)(this + 0x3cc) * speed;
            }
        } else {
            // Debug mode (flag 4)
            bVar4 = true;
            if ((uVar6 & 1) == 0) {
                return false;
            }
            speed = *(float*)((char*)DAT_011298e4 + 0xc0);
            maxDist = *(float*)((char*)DAT_011298e4 + 0xc4);
        }

        // Main loop: use the path defined by pointList and cumulative distances
        {
            int count = *(int*)(this + 0x208);   // point count
            void** points = (void**)(this + 0x20c);
            float* dists = (float*)(this + 0x25c);
            // fall through to main_loop label
        }

    main_loop:
        // Local variables (simplified)
        int pointCount = *(int*)(this + 0x208);
        float* cumDist = (float*)(this + 0x25c);
        void** pointArray = (void**)(this + 0x20c);
        // If alternate path used, these may be overwritten but we keep these names for clarity.

        if (pointCount == 0) {
            return false;
        }

        // Find segment index for target distance 'speed'
        int segIndex = 0;
        float accumulated = 0.0f;
        for (int i = 0; i < pointCount; ++i) {
            float segDist = cumDist[i];
            float nextAccum = accumulated + segDist;
            if (stepLimit <= accumulated && speed <= nextAccum) {
                segIndex = i;
                break;
            }
            accumulated = nextAccum;
            if (i == pointCount - 1) {
                // Fell off - use last segment (should not happen if speed < total length)
                segIndex = pointCount - 2;
                accumulated = nextAccum - segDist;
            }
        }

        // Interpolate between points at segIndex and segIndex+1
        float frac = speed - accumulated;
        Vec3* p0;
        Vec3* p1;
        if (segIndex == 0) {
            p0 = (Vec3*)(this + 0x1e0);   // start point
        } else {
            p0 = (Vec3*)pointArray[segIndex];
        }
        p1 = (Vec3*)pointArray[segIndex + 1];
        Vec3 delta;
        delta.x = p1->x - p0->x;
        delta.y = p1->y - p0->y;
        delta.z = p1->z - p0->z;
        Vec3 normDelta;
        FUN_0043a210(&delta.x, &normDelta.x);   // normalize
        Vec3 interpPos;
        interpPos.x = normDelta.x * frac + p0->x;
        interpPos.y = normDelta.y * frac + p0->y;
        interpPos.z = normDelta.z * frac + p0->z;

        // Now check segments from segIndex onward for obstacles/clearance
        for (int i = segIndex; i < pointCount - 1; ++i) {
            if (speed < maxDist) {
                bool skip = false;
                if (bVar4) {
                    // Debug mode: check some property
                    int idx = FUN_005f5ec0(pointArray[i], pointArray[i+1]);
                    if (idx != 0) {
                        uint64_t temp;
                        float local3c = 0.0f;
                        bool res = FUN_005fd340(*(uint16_t*)(idx + 8), 0xee654334, &temp);
                        if (res) {
                            FUN_006a7fd0(&local3c);
                        }
                        if (((uint32_t)local3c & 1) != 0) {
                            skip = true;
                        }
                    }
                }
                if (bVar3 && !skip) {
                    // Variant: use alternate point list
                    if (*(int*)(this + 0x234) == 0 || *(float**)(*(int*)(this + 0x234) + i*4) == nullptr) {
                        skip = true;
                    }
                }
                if (skip) goto next_segment;

                // Compute delta between consecutive points
                Vec3* q0 = (Vec3*)pointArray[i];
                Vec3* q1 = (Vec3*)pointArray[i+1];
                Vec3 segDelta;
                segDelta.x = q1->x - q0->x;
                segDelta.y = q1->y - q0->y;
                segDelta.z = q1->z - q0->z;
                if (segDelta.x == 0.0f && segDelta.y == 0.0f && segDelta.z == 0.0f) {
                    continue;
                }
                // Compute angle from start of segment
                float baseAngle;
                if (i == 0) {
                    baseAngle = FUN_0045c4b0(this + 0x1e0, (float*)pointArray[0]);  // angle from start
                } else {
                    baseAngle = 0.0f;
                }
                float segLength;
                FUN_0043a210(&segDelta.x, &segLength);
                float angleOffset = segLength - baseAngle;
                float step = 0.0f;
                for (float t = 0.0f; t < angleOffset; t += DAT_00d813a8) {
                    Vec3 samplePos;
                    samplePos.x = q0->x + (baseAngle + t) * (segDelta.x / segLength);
                    samplePos.y = q0->y + (baseAngle + t) * (segDelta.y / segLength);
                    samplePos.z = q0->z + (baseAngle + t) * (segDelta.z / segLength);
                    // Check clearance
                    bool occlusion = false;
                    if (!bVar3 || (DAT_00e448a4 <= t) ||
                        (FUN_006c0050(&samplePos.x, 0, 0) != 0 || FUN_006bfff0(&samplePos.x) < height) ||
                        FUN_0083ce40(&samplePos.x) != 0 || FUN_0083bb40(&samplePos.x) != 0) {
                        occlusion = true;
                    }
                    if (!occlusion) {
                        // Valid point found
                        outPos[0] = interpPos.x;
                        outPos[1] = interpPos.y;
                        outPos[2] = interpPos.z;
                        if (bVar4 && (flags & 4) == 0) {
                            // Compute perpendicular direction
                            outDir[0] = -segDelta.z;   // cross with (0,0,1) simplified? Actually from code: local_14 * 0.0 - local_10 etc.
                            outDir[1] = 0.0f;
                            outDir[2] = segDelta.y;    // simplified based on observed pattern
                            *outType = 1;
                        } else {
                            // Normal direction (inverse of delta)
                            outDir[0] = DAT_00e44564 - segDelta.x;
                            outDir[1] = DAT_00e44564 - segDelta.y;
                            outDir[2] = DAT_00e44564 - segDelta.z;
                            *outType = 0;
                        }
                        return true;
                    }
                }
            }
    next_segment:
            ;   // empty statement
        }

        // Fallback: if using variant and flags don't have 3, try with flag 2
        if (bVar3 && (flags & 3) == 0) {
            return samplePath(outPos, outDir, outType, flags | 2);
        }
        return false;
    }
};

// Helper structure
struct Vec3 {
    float x, y, z;
};