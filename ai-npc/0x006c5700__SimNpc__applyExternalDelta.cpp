// FUNC_NAME: SimNpc::applyExternalDelta
void __fastcall SimNpc::applyExternalDelta(SimNpc* this)
{
    // Retrieve a global frame delta or similar scalar from the time manager.
    float delta = TimeManager::GetFrameDelta(); // FUN_00471610

    // Apply the delta to a 3-component vector at offset +0x29C, likely an external force or velocity.
    // This function modifies the three floats at +0x29C, +0x2A0, +0x2A4 (presumably x, y, z).
    MathUtils::Vec3ScaleAdd(delta, (float*)(this + 0x29C), (float*)(this + 0x2A0), (float*)(this + 0x2A4)); // FUN_0056c180
}