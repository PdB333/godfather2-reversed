// FUNC_NAME: GameActionHandler::processAction
// Address: 0x007660b0
// Handles UI/gameplay actions based on actionId (param_4).
// Constants: 0x12, 0x13, 0x14 map to specific sub-actions.
// Uses base handler FUN_0073e300 for unhandled cases.
// Class unknown but likely part of EARS UI/input system.

#include <cstdint>

// Forward declarations for called functions (addresses from callees)
int32_t FUN_00765f80();           // 0x00765f80 - unknown action sub-handler
int32_t FUN_00765ec0();           // 0x00765ec0 - returns non-zero on success
int32_t FUN_0073e300(int32_t, int32_t, int32_t, int32_t); // 0x0073e300 - base/default handler
bool FUN_007178e0();              // 0x007178e0 - returns bool
bool FUN_004ac260();              // 0x004ac260 - returns bool

class GameActionHandler {
public:
    int32_t processAction(int32_t arg1, int32_t arg2, int32_t actionId, int32_t arg3);
private:
    uint8_t _gap1[0x5C]; // +0x5C as per this use
};

int32_t GameActionHandler::processAction(int32_t arg1, int32_t arg2, int32_t actionId, int32_t arg3) {
    if (actionId == 0x12) {
        // Action ID 0x12: calls simple helper
        return FUN_00765f80();
    }
    if (actionId == 0x13) {
        // Action ID 0x13: check a flag stored at (this+0x5C)->0x21DC
        // If that flag exists, call FUN_00765ec0; return 1 on success, else 0.
        int32_t** ptr = *(int32_t**)(reinterpret_cast<uint8_t*>(this) + 0x5C);
        if (ptr && *reinterpret_cast<int32_t*>(reinterpret_cast<uint8_t*>(*ptr) + 0x21DC) != 0) {
            if (FUN_00765ec0() != 0) {
                return 1;
            }
        }
        return 0;
    }
    if (actionId != 0x14) {
        // For any other action ID, delegate to base handler
        return FUN_0073e300(arg1, arg2, actionId, arg3);
    }
    // Action ID 0x14: check two global conditions before allowing action
    bool cond1 = FUN_007178e0() != 0;
    bool cond2 = FUN_004ac260() != 0;
    if (cond2 && cond1) {
        return 1;
    }
    return 0;
}