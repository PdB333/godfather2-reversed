// FUNC_NAME: Building::spawnVenueSelectJobGiver

void __fastcall Building::spawnVenueSelectJobGiver(Building* this)
{
    // +0xAC: pointer to a spawned job giver object (or null)
    int* jobGiverPtr = reinterpret_cast<int*>(this + 0xAC);
    int* transformData;       // from getCameraTransform()
    undefined4 local_b0;      // position x or quaternion component
    float fStack_ac;          // position y or transformed y
    undefined4 uStack_a8;     // position z or quaternion
    undefined4 uStack_a4;     // pad/dummy
    // transform buffer for spawn
    int local_b4;             // new object handle
    undefined4 local_90;      // rotation/quaternion part
    // ... many stack locals

    // Likely a lock or reference count increment
    FUN_0097a310(0);

    // Get current camera/view transform (probably from camera manager)
    transformData = reinterpret_cast<int*>(FUN_00950b20());
    if (transformData == nullptr) {
        FUN_004df650(); // cleanup / release
        return;
    }

    // Extract transform components from camera
    local_b0 = *transformData;
    fStack_ac = DAT_00d8bbc8 + static_cast<float>(transformData[1]);
    uStack_a8 = transformData[2];
    uStack_a4 = _DAT_00d5780c; // identity constant

    FUN_004df650(); // release camera lock?

    // Build orientation data (quaternion or rotation matrix)
    FUN_00425060(&local_9c, 0);          // initialize identity quaternion
    FUN_0056b8a0(local_98, local_9c, local_94, local_50);  // multiply/quaternion operation

    // Fill rotation fields with identity (or default)
    local_90 = _DAT_00d5780c;
    uStack_8c = 0;
    uStack_88 = 0;
    uStack_84 = 0;
    local_80 = 0;
    uStack_7c = _DAT_00d5780c;
    uStack_78 = 0;
    uStack_74 = 0;
    local_70 = 0;
    uStack_6c = 0;
    uStack_68 = _DAT_00d5780c;
    uStack_64 = 0;
    // Position from camera
    local_60 = local_b0;
    fStack_5c = fStack_ac;
    uStack_58 = uStack_a8;
    uStack_54 = uStack_a4;

    // Log/load the model type for venue select job giver
    FUN_004eacb0("dv_venue_select_jobgiver");

    // Spawn a new entity with the computed transform
    FUN_004df420(&local_b4, &local_b0, &local_90, 0xFFFFFFFF, 4, 0, 0xFFFFFFFF, 0);

    // Replace previous job giver (if any) with the new one
    if (*jobGiverPtr != 0) {
        *reinterpret_cast<int*>(*jobGiverPtr + 8) = 0; // clear back reference
        *jobGiverPtr = 0;
    }
    *jobGiverPtr = local_b4;
    if (local_b4 != 0) {
        // Set self-reference in the new object (so it can point back)
        *reinterpret_cast<int**>(local_b4 + 8) = jobGiverPtr;
    }
}