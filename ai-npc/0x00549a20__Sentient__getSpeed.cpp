// FUNC_NAME: Sentient::getSpeed
// Function at 0x00549a20: returns a float from a sub-object at this+0x18, offset +8.
// Likely retrieves the current scalar speed from a movement/physics component.
float Sentient::getSpeed() const {
    // Dereference the pointer at this+0x18 to get the movement component,
    // then read the float at component+0x08.
    return *(float*)(*(int*)(reinterpret_cast<const unsigned char*>(this) + 0x18) + 8);
}