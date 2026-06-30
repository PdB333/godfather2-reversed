// FUNC_NAME: Sentient::isActive
bool __thiscall Sentient::isActive(void) {
    // Check if the sentient is marked as active (flag bit 0 at +0xa8)
    // and either has a non-zero, non-invalid action state (+0xc0) 
    // or has an additional active flag set (+0xd4 bit 0)
    if ((*(byte*)(this + 0xa8) & 1) != 0 &&
        (((*(int*)(this + 0xc0) != 0 && *(int*)(this + 0xc0) != 0x48) ||
         (*(byte*)(this + 0xd4) & 1) != 0))) {
        return true;
    }
    return false;
}