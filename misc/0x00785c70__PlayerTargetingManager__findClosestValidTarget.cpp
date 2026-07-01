// FUNC_NAME: PlayerTargetingManager::findClosestValidTarget

// Reconstructed C++ from Ghidra decompilation of function at 0x00785c70
// The Godfather 2 (2008) - EA EARS engine
// Searches an array of entities/objects (e.g., NPCs, vehicles) for the first one that meets distance,
// interior, and line-of-sight criteria.

// External globals – must be defined elsewhere in the game binary
extern void* g_pLevelManager;           // DAT_012233a0 – pointer to level state (or similar)
extern float g_minInteriorDistance;     // _DAT_00d577a0 – minimum squared distance inside interiors?
extern float g_maxTargetDistance;       // DAT_00d5ccf8 – maximum valid squared distance (range)

// Forward declarations of called functions (incomplete in Ghidra, named based on usage)
int __thiscall GetPlayer();             // FUN_00471610 – returns player object pointer (likely)
bool __thiscall ShouldSkipInteriorCheck(void);  // FUN_007883e0 – returns true if this object should not be considered in certain conditions
bool __thiscall IsObjectVisibleFrom(int PlayerRef, int someViewData); // FUN_00787e20 – checks line-of-sight / visibility

// Class definition (inferred)
// Offsets:
//   +0x193c : array of pointers to objects (m_pObjectList)
//   +0x1a3c : count of objects (m_objectCount)
//   +0x2c88 : pointer to sub-object with visibility data at +0x70 (e.g., camera or transform)
class PlayerTargetingManager {
public:
    int     m_objectCount;          // at +0x1a3c (count of valid objects in list)
    void**  m_pObjectList;          // at +0x193c (array of pointers to objects, e.g., Entity*)
    void*   m_pVisibilityConfig;    // at +0x2c88 (some object containing view parameters at +0x70)
    // ... other members ...
};

// The method: param_2 = bIgnoreInteriorChecks (0 = obey interior rules, nonzero = skip them)
int __thiscall PlayerTargetingManager::findClosestValidTarget(char bIgnoreInterior) {
    float fDist;
    int   iObject;
    char  bInteriorSkip;
    int   iIdx;
    int*  pObjList;
    uint  uIdx;

    // Early exit if level state invalid
    if (*(int**)((char*)g_pLevelManager + 4) == 0 ||
        *(int**)((char*)g_pLevelManager + 4) == 0x1f30) {
        return 0;
    }

    int playerRef = GetPlayer();  // obtain player / camera reference
    uIdx = 0;
    // No objects to scan
    if (this->m_objectCount == 0) {
        return 0;
    }

    pObjList = (int*)((char*)this + 0x193c); // pointer to the object pointer array
    do {
        iObject = *pObjList;                  // current object pointer
        fDist = *(float*)(iObject + 0x20);    // object's squared distance from player/camera (or bounding sphere radius)

        if (bIgnoreInterior == 0) {
            bInteriorSkip = ShouldSkipInteriorCheck();
            if (bInteriorSkip != 0) goto checkDistance; // skip interior distance check if the object shouldn't be skipped
        }
        else { // non‑zero → ignore interior rules, always apply interior distance check
            if (g_minInteriorDistance >= *(float*)(iObject + 0x24)) {
                // interior distance check failed, skip this object
                uIdx++;
                pObjList++;
                if (this->m_objectCount <= uIdx) return 0;
                continue;
            }
        }

checkDistance:
        // Check object is within max range AND visible from player's viewpoint
        if (g_maxTargetDistance < fDist) {
            uIdx++;
            pObjList++;
            if (this->m_objectCount <= uIdx) return 0;
            continue;
        }

        // Visibility check: playerRef+0x30 likely player's eye or camera position,
        // and m_pVisibilityConfig+0x70 contains view frustum or LOD data.
        bInteriorSkip = IsObjectVisibleFrom(
            playerRef + 0x30,                                    // player viewpoint offset
            *(int*)(*(int*)((char*)this + 0x2c88) + 0x70)       // some visibility parameter from sub‑object
        );
        if (bInteriorSkip != 0) {
            return iObject;   // found a valid target
        }

        uIdx++;
        pObjList++;
    } while (this->m_objectCount > uIdx);

    return 0; // no suitable object found
}