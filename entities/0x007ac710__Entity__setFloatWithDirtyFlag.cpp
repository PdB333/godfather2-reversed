// FUNC_NAME: Entity::setFloatWithDirtyFlag
void __thiscall Entity::setFloatWithDirtyFlag(int this, float value)
{
    // Compare with current value at offset +0x4c (float property)
    if (value != *(float *)(this + 0x4c)) {
        // Set dirty flag at offset +0x64 (byte/boolean) to 1
        *(undefined1 *)(this + 100) = 1;
        // Update the float property
        *(float *)(this + 0x4c) = value;
    }
}