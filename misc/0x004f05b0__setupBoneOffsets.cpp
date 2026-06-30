// FUNC_NAME: setupBoneOffsets
// Function address: 0x004f05b0
// Role: Passes three constant offsets (0x18, 0x28, 0x38) to another function, likely for bone or animation setup.
void setupBoneOffsets(void* thisPtr, int someParam) {
    int offsets[3] = {0x18, 0x28, 0x38}; // Offsets into a structure (e.g., bone indices or transform components)
    FUN_004eba90(thisPtr, someParam, offsets, 3); // Process the three offsets
}