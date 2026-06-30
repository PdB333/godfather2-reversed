// FUNC_NAME: Object::getPropertyFloat
float __fastcall Object::getPropertyFloat(void* this) {
    // this+0x18 points to a property container, container+0x08 is the float value
    return *(float*)(*(int*)((int)this + 0x18) + 8);
}