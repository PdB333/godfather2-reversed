// Xbox PDB: EARS_Modules_RoadblockManager_RoadblockManager
// FUNC_NAME: PoliceVehicleLockController::Constructor
undefined4 * __thiscall PoliceVehicleLockController::Constructor(undefined4 *this, int maxLockableVehicles)
{
    // Initialize base or debug system (first param is 0, second is 0)
    BaseSystem::initialize(0, 0);

    // Set up vtable pointers for this object
    this[0x14] = &PTR_LAB_00d83188; // +0x50: base vtable pointer (maybe first interface)
    DAT_011298e4 = this;             // Store singleton instance globally

    this[0] = &PTR_FUN_00d831bc;    // +0x00: primary vtable (class vtable)
    this[0xf] = &PTR_LAB_00d831ac;  // +0x3C: another vtable entry
    this[0x12] = &PTR_LAB_00d831a8; // +0x48: vtable entry
    this[0x14] = &PTR_LAB_00d831a4; // +0x50: final base vtable pointer

    // Allocate memory for lock data (8 bytes per vehicle slot)
    unsigned int *lockData = (unsigned int*)FUN_009c8e80(maxLockableVehicles * 8);
    this[0x15] = lockData;          // +0x54: pointer to lock data array
    this[0x16] = 0;                 // +0x58: current lock count
    this[0x17] = maxLockableVehicles; // +0x5C: max vehicles

    // Initialize lock status arrays (offsets 0x60 to 0xA0)
    this[0x18] = 0; // +0x60
    this[0x19] = 0; // +0x64
    this[0x1a] = 0; // +0x68
    this[0x1b] = 0; // +0x6C
    this[0x1c] = 0; // +0x70
    this[0x1d] = 0; // +0x74
    this[0x1e] = 0; // +0x78
    this[0x1f] = 0; // +0x7C
    this[0x20] = 0; // +0x80
    this[0x21] = 0; // +0x84
    this[0x22] = 0; // +0x88
    this[0x23] = 0; // +0x8C
    this[0x24] = 0; // +0x90
    this[0x25] = 0; // +0x94
    this[0x26] = 0; // +0x98
    this[0x27] = 0; // +0x9C
    this[0x28] = 0; // +0xA0

    // Additional fields
    this[0x2c] = 0; // +0xB0
    this[0x2d] = 0; // +0xB4
    this[0x33] = 0; // +0xCC
    this[0x2e] = 0; // +0xB8
    this[0x2f] = 0; // +0xBC
    this[0x30] = 0; // +0xC0
    this[0x31] = 0; // +0xC4
    this[0x32] = 0; // +0xC8

    // Set magic guard values (likely for debugging / corruption detection)
    this[0x35] = 0xbeefbeef;  // +0xD4
    this[0x36] = 0xeac15a55;  // +0xD8
    this[0x37] = 0x91100911;  // +0xDC
    this[0x34] = 0xbadbadba;  // +0xD0
    this[0x38] = 0xbadbadba;  // +0xE0
    this[0x39] = 0xbeefbeef;  // +0xE4
    this[0x3a] = 0xeac15a55;  // +0xE8
    this[0x3b] = 0x91100911;  // +0xEC

    // Clear lock counter trackers
    this[0x2b] = 0; // +0xAC
    this[0x2a] = 0; // +0xA8
    this[0x29] = 0; // +0xA4

    // Register message identifier for police vehicle locking
    FUN_00408240(&DAT_0112ff74, "iMsgLockPoliceVehicle");

    // Call base class constructor (likely EARS Framework/Entity constructor)
    FUN_00446560(this);

    // Clear a flag in vtable entry (bit 29 of offset +0x14)
    this[5] = this[5] & 0xdfffffff;

    return this;
}