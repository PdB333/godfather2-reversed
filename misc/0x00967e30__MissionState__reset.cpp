// FUNC_NAME: MissionState::reset
void MissionState::reset()
{
    // +0x1F4 (500): activation flag
    *(uint8_t*)(this + 0x1F4) = 1;
    // +0x1E4: mission state counter (start at 1)
    *(int*)(this + 0x1E4) = 1;
    // +0x1E0: unknown initial zero
    *(int*)(this + 0x1E0) = 0;
    // +0x23C: another zeroed field
    *(int*)(this + 0x23C) = 0;
    // +0x1F0: copy from global timer/health base
    *(int*)(this + 0x1F0) = DAT_00d5ddec;
    // +0x1EC: set to 0x42 (66), maybe max count or id
    *(int*)(this + 0x1EC) = 0x42;
    // +0x1E8: store rounded float from global +0x14 (e.g., time value)
    float fVal = *(float*)(DAT_01129908 + 0x14);
    *(int*)(this + 0x1E8) = (int)roundf(fVal);
    // +0x1D0: max/min index derived from global minus 1
    *(int*)(this + 0x1D0) = DAT_0113082c - 1;
    // +0x1BC: another limit derived from global minus 1
    *(int*)(this + 0x1BC) = DAT_01130808 - 1;
}