// FUNC_NAME: isTargetDataEqual (likely comparison for a target or waypoint struct)
bool __fastcall isTargetDataEqual(TargetData* self, TargetData* other) {
    // Compare ID field at +0x00
    if (self->id != other->id) {
        return false;
    }

    // Compare angle field at +0x08 with wrapping tolerance
    // Uses bitwise AND to handle angle wrapping: subtract, mask, and compare to threshold
    float angleDiff = (float)((uint32_t)(self->angle - other->angle) & ANGLE_MASK);
    if (angleDiff >= ANGLE_THRESHOLD) {
        return false;
    }

    // Compare type field at +0x0C
    if (self->type != other->type) {
        return false;
    }

    // Compare extra field at +0x10
    if (self->extra != other->extra) {
        return false;
    }

    return true;
}
// Constants: DAT_00e44680 = ANGLE_MASK (likely 0x7FFFFFFF to remove sign bit)
//            DAT_00e2e780 = ANGLE_THRESHOLD (some small angle tolerance)