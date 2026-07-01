// FUNC_NAME: PlayerCCTVariables::updateVehicleCamera
void __fastcall PlayerCCTVariables::updateVehicleCamera(int *this) {
    char cVar1;
    int iVar2;
    bool bVar3;
    float local_c; // vector component x
    float local_8; // y
    float local_4; // z

    // Check flag at sub-object offset 0x1b8c (likely vehicle relative or collision flag)
    bVar3 = *(char *)(this[0x14] + 0x1b8c) == '\0';

    // Check some global state (e.g., is player in vehicle mode?)
    cVar1 = FUN_0076ec60();

    if (cVar1 == '\0') {
        // Camera is active? Get player camera position from global function
        iVar2 = FUN_00471610(); // returns pointer to player camera state
        // Compute world-space vector from vehicle position to camera target?
        // DAT_00e44564 is likely a zero constant (0.0)
        local_c = DAT_00e44564 - ((float)this[0x1b] - *(float *)(iVar2 + 0x30));
        local_8 = DAT_00e44564 - ((float)this[0x1c] - *(float *)(iVar2 + 0x34));
        local_4 = DAT_00e44564 - ((float)this[0x1d] - *(float *)(iVar2 + 0x38));
        // Normalize or process the vector
        FUN_0046fe50(&local_c, 0);
        // Obfuscated conditional based on bVar3 (flag at +0x1b8c)
        iVar2 = (-(uint)bVar3 & 0x22278e3b) + 0xd15d386d; // likely two possible constants
    } else {
        // Camera not active? Reset position offset from vehicle
        FUN_0046ffe0(this + 0x1b, 0); // set position offset to zero?
        // Obfuscated conditional (different constants)
        iVar2 = (-(uint)bVar3 & 0xf5f70085) + 0x58884c0f;
    }

    // Set a bit flag at this+0x15 (offset 0x54) – e.g., "camera updated"?
    if ((*(byte *)(this + 0x15) & 8) == 0) {
        FUN_007f4490(1, 0, DAT_00d5ef90); // some debug/update call
        *(byte *)(this + 0x15) = *(byte *)(this + 0x15) | 8;
    }

    // Clear a state flag in the sub-object (offset 0x1e08)
    *(undefined1 *)(this[0x14] + 0x1e08) = 0;

    // Call virtual function via vtable slot 0x2c (likely "applyCameraOffset" or "updateTransform")
    (**(code **)(*this + 0x2c))(iVar2, 1, 1, 0, 0x3f800000, 0x3f800000);
    return;
}