// FUNC_NAME: Animation::isFrameInRange
// Address: 0x006330d0
// Role: Checks if a frame index is within the valid range for an animation state.
// The object has two fields describing two allowed intervals:
//   - lowBound at +0x47 (byte) for frames below 250
//   - highOffset at +0x28 (int) so that frames >= 250 must satisfy highOffset <= frame - 250.
// Returns true if frame is in either [lowBound, 249] or [250 + highOffset, ∞).

bool __thiscall Animation::isFrameInRange(int frame) const {
    uint8_t lowBound = *(uint8_t*)((uintptr_t)this + 0x47);   // +0x47: lower bound for low frames
    int highOffset  = *(int*)((uintptr_t)this + 0x28);        // +0x28: offset for high frame start

    return (lowBound <= frame) &&
           (frame < 250 || highOffset <= (frame - 250));
}