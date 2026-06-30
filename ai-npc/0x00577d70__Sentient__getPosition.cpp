// FUNC_NAME: Sentient::getPosition
// Function address: 0x00577d70
// Retrieves the entity's position via internal getter, returns success.
// On success, writes three floats to output vector pointed by ESI (parameter).

bool __thiscall Sentient::getPosition(Vector3* outPosition) {
    char isValid = FUN_00577f40(); // Internal validation/getter (returns non-zero if data available)
    if (isValid) {
        // Copy three float components (local_20, local_1c, local_18) to output
        outPosition->x = reinterpret_cast<float>(local_20);  // +0x00
        outPosition->y = reinterpret_cast<float>(local_1c);  // +0x04
        outPosition->z = reinterpret_cast<float>(local_18);  // +0x08
        return true;
    }
    return false;
}