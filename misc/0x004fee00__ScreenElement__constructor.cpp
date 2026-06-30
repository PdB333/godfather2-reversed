// FUNC_NAME: ScreenElement::constructor
ScreenElement * __thiscall ScreenElement::constructor(ScreenElement *this, ElementDescriptor *desc)
{
    float *pfVar1;
    int iVar2;
    int iVar3;
    int iVar4;
    int in_EAX;
    uint *puVar5;
    ContextInfo *context;

    baseConstructor();
    this->vtable = &ScreenElement_vtable_0x00e37b70;
    if (*(char *)(in_EAX + 0xd) == '\0') {
        this->descriptor = desc;
        this->flags = 0;
        **(uint **)(in_EAX + 4) |= 0x40000;
        **(uint **)(in_EAX + 4) |= 0x80000000;
        context = *(ContextInfo **)(__readfsdword(0x2c) + 0x2c); // get current rendering context
        applyScreenTransform(*(float *)(desc + 0x70), *(float *)(desc + 0x74), 0, this->transformData + 0x10 + context->offsetB);

        if ((desc->flags & 0x2) == 0) {
            if ((desc->flags & 0x4) != 0) {
                iVar3 = this->transformData;
                iVar4 = context->offsetB;
                *(Vector3 *)(iVar3 + 0x40 + iVar4) = desc->position;
            }
        } else {
            pfVar1 = (float *)(this->transformData + 0x40 + context->offsetB);
            *pfVar1 += desc->position.x;
            pfVar1[1] += desc->position.y;
            pfVar1[2] += desc->position.z;
        }
        if ((desc->flags & 0x1000) != 0) {
            puVar5 = (uint *)(context->offsetB + this->transformData);
            *puVar5 |= 0x100;
        }
        finalizeConstruction();
        registerElement();
        this->someState1 = 0;
        this->someState2 = 0;
        this->byteAt0x11 = 0xff;
        if ((desc->flags & 0x40) == 0) {
            if ((char)(desc->flags) < 0) {
                this->byteAt0x11 = 1;
            }
        } else {
            this->byteAt0x11 = 0;
        }
        if (((desc->flags & 0x8) != 0) && (*(char *)(desc + 0x6c) != '\0')) {
            this->someFlagAt0x0f = 2;
            return this;
        }
        this->someFlagAt0x0f = 0;
    }
    return this;
}