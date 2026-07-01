// FUNC_NAME: Transform::operator=
int __thiscall Transform::operator=(Transform *this, const Transform *other)
{
    if (this != other) {
        // Copy sub-object at +0x04 (e.g., Vector3 position)
        Transform::copySubObject1(&this->position, &other->position); // FUN_00827520
        // +0x10: direct 4-byte copy (e.g., float or int)
        this->field_0x10 = other->field_0x10;

        // Copy sub-object at +0x14 (e.g., Quaternion rotation)
        Transform::copySubObject2(&this->rotation, &other->rotation); // FUN_004d3e20
        // +0x24, +0x28, +0x2c, +0x30: direct copies (e.g., scale or color)
        this->field_0x24 = other->field_0x24;
        this->field_0x28 = other->field_0x28;
        this->field_0x2c = other->field_0x2c;
        this->field_0x30 = other->field_0x30;

        // +0x34 to +0x48: 6 ints / floats (may represent a bounding box or matrix)
        if ((int *)&this->field_0x34 != (int *)&other->field_0x34) {
            this->field_0x34 = other->field_0x34;
            this->field_0x38 = other->field_0x38;
            this->field_0x3c = other->field_0x3c;
            this->field_0x40 = other->field_0x40;
            this->field_0x44 = other->field_0x44;
            this->field_0x48 = other->field_0x48;
        }
    }
    return (int)this;
}