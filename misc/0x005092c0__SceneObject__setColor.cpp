// FUNC_NAME: SceneObject::setColor
void __thiscall SceneObject::setColor(const uint *color) {
    // color array at offset +0x10 (4 x uint32: r, g, b, a)
    this->color[0] = color[0];
    this->color[1] = color[1];
    this->color[2] = color[2];
    this->color[3] = color[3];
}