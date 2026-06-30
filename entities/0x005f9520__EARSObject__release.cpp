// FUNC_NAME: EARSObject::release
void EARSObject::release(void)
{
    // Release first sub-object (offset +0x0C) using its vtable at (+0x08)
    if (this->subObject1 != 0) {
        // Call virtual destructor at vtable[1] (offset +0x04) with delete flag 0
        (this->subObject1Vtable[1])(this->subObject1, 0);
        this->subObject1 = 0;
    }
    // Call virtual function at vtable[3] (offset +0x0C) on subObject1's vtable (cleanup?)
    (this->subObject1Vtable[3])();

    // Release second sub-object (offset +0x04) using its vtable at (+0x00)
    if (this->subObject2 != 0) {
        (this->subObject2Vtable[1])(this->subObject2, 0);
        this->subObject2 = 0;
    }
    // Call virtual function at vtable[3] (offset +0x0C) on subObject2's vtable
    (this->subObject2Vtable[3])();
}