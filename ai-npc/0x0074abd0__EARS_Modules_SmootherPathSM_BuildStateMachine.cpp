// Xbox PDB: EARS::Modules::SmootherPathSM::BuildStateMachine
// FUNC_NAME: FollowPathStateMachine::processEvent
// Function address: 0x0074abd0
// Role: Handles path-related events for the FollowPathStateMachine (FSM), transitioning states between FollowPathST and SmootherPathST.

#include <cstdint>

// Forward declarations (stubs based on called functions)
bool __thiscall canReachTarget(uint64_t pathInfo, int someFlag); // 0x0074a400
uint32_t __thiscall defaultEventHandler(uint32_t param2, uint32_t param3, uint32_t param4, int eventType, uint32_t param6); // 0x0073e610
uint32_t __cdecl getSomeValue(); // 0x0072d160
void __fastcall clearPathRequest(int pathRequestHandle); // 0x00460300
void __cdecl setPathFindingMode(int mode); // 0x00624ca0
int __cdecl getPathType(); // 0x0077dd80
bool __thiscall isPathValid(void* pathPtr); // 0x00749eb0
const char* __thiscall AllocString(const char* str); // 0x00621520

// Vtable offsets (assuming class layout)
// +0x00: vtable pointer
// +0x20: virtual method "setState" (takes this, param2, param3, const char* stateName)
// +0x2c: virtual method "renderDebug" (takes this, ...)

class FollowPathStateMachine {
public:
    // Field offsets (relative to this pointer):
    // +0x1d (0x74): pathInfo (64-bit struct or double)
    // +0x1f (0x7C): someInt
    // +0x1c (0x70): flags (bit 0 = path usable?)
    // +0x20 (0x80): pathRequestHandle

    uint32_t processEvent(uint32_t param2, uint32_t param3, uint32_t param4, int eventType, uint32_t param6) {
        // eventType == 0x23: check path condition and set flag
        if (eventType == 0x23) {
            uint64_t pathInfo = *(uint64_t*)(this + 0x1d); // double or struct at +0x74
            int someInt = *(int*)(this + 0x1f); // +0x7C
            bool canReach = canReachTarget(pathInfo, someInt);
            if (canReach) {
                *(uint32_t*)(this + 0x1c) |= 1; // set bit 0
            } else {
                *(uint32_t*)(this + 0x1c) &= ~1; // clear bit 0
            }
            return 1;
        }

        // eventType == 0x24: decide path state (FollowPathST or SmootherPathST)
        if (eventType == 0x24) {
            setPathFindingMode(1); // enable path finding
            int pathType = getPathType();
            if (pathType == 2 || pathType == 3) {
                void* pathPtr = (void*)(this + 0x1d); // +0x74
                if (isPathValid(pathPtr)) {
                    // Transition to FollowPathST state
                    const char* stateName = AllocString("FollowPathST");
                    (*(void(__thiscall**)(FollowPathStateMachine*, uint32_t, uint32_t, const char*))(*(uint32_t*)this + 0x20))(
                        this, param2, param3, stateName);
                    return 1;
                }
            }
            // Default: transition to SmootherPathST
            const char* stateName = AllocString("SmootherPathST");
            (*(void(__thiscall**)(FollowPathStateMachine*, uint32_t, uint32_t, const char*))(*(uint32_t*)this + 0x20))(
                this, param2, param3, stateName);
            return 1;
        }

        // eventType == 0x25: debug render and clear path request
        if (eventType == 0x25) {
            uint32_t debugVal = getSomeValue();
            (*(void(__thiscall**)(FollowPathStateMachine*, uint32_t, int, int, float, float))(*(uint32_t*)this + 0x2c))(
                this, debugVal, 1, 0, 1.0f, 1.0f); // 0x3f800000 = 1.0f
            int pathHandle = *(int*)(this + 0x20); // +0x80
            clearPathRequest(pathHandle);
            return 1;
        }

        // Default: pass to generic event handler
        return defaultEventHandler(param2, param3, param4, eventType, param6);
    }
};