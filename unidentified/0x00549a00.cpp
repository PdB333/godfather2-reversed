//Function address: 0x00549a00
// Role: Getter for a float property from a nested structure (likely speed or position component).
// this+0x18 points to a sub-object, and that sub-object's +0x14 is the float value.
float __thiscall Entity::getFloatProperty() {
    return *(float*)(*(int*)((char*)this + 0x18) + 0x14);
}