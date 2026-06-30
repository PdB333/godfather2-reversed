// FUNC_NAME: EARSObject::checkState6Or7
void __thiscall EARSObject::checkState6Or7(int this, bool *outResult) {
    // +0xd8: state byte - values 0x06 and 0x07 indicate a specific condition (e.g., active/loading)
    char state = *(char *)(this + 0xd8);
    *outResult = (state == 0x06 || state == 0x07);
}