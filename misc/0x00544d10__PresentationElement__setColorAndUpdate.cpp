// FUNC_NAME: PresentationElement::setColorAndUpdate
void __thiscall PresentationElement::setColorAndUpdate(PresentationElement* this, Color* color)
{
    // Color struct: r, g, b, a at offsets +0x00, +0x04, +0x08, +0x0C
    int r = color->r;
    int g = color->g;
    int b = color->b;
    int a = color->a; // but we use global default alpha later

    int defaultAlpha = DAT_00e2b1a4; // Global default alpha value (likely 255)

    // Store color into this object's fields (offsets 0x100, 0x104, 0x108, 0x10C)
    this->colorR = r;   // +0x100
    this->colorG = g;   // +0x104
    this->colorB = b;   // +0x108
    this->colorA = defaultAlpha; // +0x10C (overwrites a with global default)

    // Redundant store (bug or intentional)
    this->colorA = defaultAlpha;

    // Call some global initialization or update hook
    FUN_006101b0();

    // Call virtual method at vtable+0x68 (likely "applyColor" or "update")
    this->vtable->applyColor(this);

    int someState = this->field_0x2E8; // offset 0x2E8 (param_1[0xba])

    // Check virtual method at vtable+0x19c (likely "isActive" or "isVisible")
    bool isActive = this->vtable->isActive(this);

    if (!isActive) {
        if (someState == 0) {
            goto end; // No further processing
        }
        // If not active but someState != 0, re-copy color (why?)
        r = color->r;
        g = color->g;
        b = color->b;
        a = color->a; // re-read, but overridden by defaultAlpha later
        // The re-copied values are stored in local variables but not used? Actually they are used by FUN_009f4c40 below
    } else {
        // Active branch: re-copy color and then check a child's flag
        r = color->r;
        g = color->g;
        b = color->b;
        a = color->a; // re-read, but overridden

        // Check flag at (this->m_child + 0x18)->flag at offset 0xD8
        // param_1[0xd8] is likely a pointer to a child object at offset 0x360
        ChildObject* child = *(ChildObject**)((char*)this + 0x360);
        char childFlag = *(char*)(*(int*)((char*)child + 0x18) + 0xD8);
        if (childFlag == 0x07) { // 0x07 == bell, maybe a state indicator
            FUN_009f4240(1, 1, 0); // Debug/log call
        }
    }

    // Process the color data (likely applies to graphics)
    FUN_009f4c40(&r); // Pass address of the local color (r, g, b, a on stack)

end:
    // Call virtual method at vtable+600 (offset 0x258) – maybe "postUpdate" or "finalize"
    this->vtable->postUpdate(this);
}