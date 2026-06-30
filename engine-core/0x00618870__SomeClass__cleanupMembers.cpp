// FUNC_NAME: SomeClass::cleanupMembers
void cleanupMembers(void)
{
    // +0x1c: pointer to something deallocated via specific function
    if (this->field_0x1c != 0) {
        releaseSpecificObject(this->field_0x1c, 0);
        this->field_0x1c = 0;
    }
    // +0x14: first general pointer, released via vtable slot 2 (offset 8)
    if (this->field_0x14 != 0) {
        (*(code **)(*(int *)this->field_0x14 + 8))(this->field_0x14);
        this->field_0x14 = 0;
    }
    // +0x18: second general pointer, also released via vtable slot 2
    if (this->field_0x18 != 0) {
        (*(code **)(*(int *)this->field_0x18 + 8))(this->field_0x18);
        this->field_0x18 = 0;
    }
}