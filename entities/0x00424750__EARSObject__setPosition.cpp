// FUNC_NAME: EARSObject::setPosition
void __thiscall EARSObject::setPosition(void* this, int param_2) {
    // Calls engine routine with fields from this reordered
    // Offsets: this+0 (likely X or element 0), this+4 (Y), this+8 (Z)
    FUN_0056c180(param_2, *(int*)((char*)this + 4), *(int*)this, *(int*)((char*)this + 8));
}