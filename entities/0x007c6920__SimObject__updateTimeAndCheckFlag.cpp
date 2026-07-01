// FUNC_NAME: SimObject::updateTimeAndCheckFlag

// Offsets used:
// +0x128: flags (uint32 bitfield)
// +0x134: lastTime (uint32, last global time value)
// +0x138: nextTime (uint32, next scheduled time)

extern uint32 g_globalTime; // DAT_01205220

void updateGlobalTime(); // FUN_007ab120 - refresh global time

// FUN_00896ac0 - takes a size (0x20) and a pointer to uint32 (local copy of this),
// writes something into that uint32, returns a handle (int) or null
int checkHashTableEntry(int size, uint32* outValue);

class SimObject {
public:
    uint32 flags;       // +0x128
    uint32 lastTime;    // +0x134
    uint32 nextTime;    // +0x138

    void updateTimeAndCheckFlag();
};

void SimObject::updateTimeAndCheckFlag() {
    updateGlobalTime();
    uint32 uVar1 = g_globalTime;

    // If the gap since last update is more than one tick, force nextTime to current global time
    if (lastTime + 1U < g_globalTime) {
        nextTime = g_globalTime;
    }
    lastTime = uVar1;

    // Query a lookup table using our own address; outValue may be overwritten with a time
    uint32 local_this = reinterpret_cast<uint32>(this);
    int iVar2 = checkHashTableEntry(0x20, &local_this);

    // If nextTime is within range and the lookup either failed or points to an entry
    // whose secondary pointer exists and has bit 3 of its flags clear, set bit 0x800
    if (nextTime <= local_this &&
        (iVar2 == 0 ||
         (*(int*)(iVar2 + 0x24) != 0 &&
          ((*(uint*)(*(int*)(iVar2 + 0x24) + 4) & 8) == 0)))) {
        flags |= 0x800;
    }
}