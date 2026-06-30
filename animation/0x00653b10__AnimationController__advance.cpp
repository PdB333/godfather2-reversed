// FUNC_NAME: AnimationController::advance

void __fastcall AnimationController::advance(AnimationController* this, bool isActive)
{
    Node* pNode = reinterpret_cast<Node*>(this->activeNode); // +0x11c: pointer to node
    this->activeNode = pNode->nextNode; // +0x10: next node pointer?

    if (pNode->name[0] == '\0')
    {
        if (isActive)
            goto LAB_00653b9d;
    }
    else
    {
        if (isActive)
        {
LAB_00653b9d:
            this->someId = pNode->someValue; // +0x04: store some value
            if ((this->flags & 0x0C) != 0) // +0x2e: check flags bit1/bit2
            {
                float currentTime = static_cast<float>(this->currentTime); // +0x1b8
                if (currentTime < static_cast<float>(this->duration)) // +0x1bc
                {
                    VirtualTable* vtable = reinterpret_cast<VirtualTable*>(pNode->vtable);
                    this->currentTime = static_cast<int>(currentTime + g_frameTime); // DAT_00e2b1a4
                    vtable->vfunc3c(pNode); // vfunc at +0x3c (idx 15)
                    FUN_009c8eb0(pNode); // release/decrement reference?
                    return;
                }
                if (currentTime < g_maxTime) // DAT_00e2afb8
                {
                    this->currentTime = static_cast<int>(g_frameTime / currentTime + currentTime);
                }
            }
            VirtualTable* vtable = reinterpret_cast<VirtualTable*>(pNode->vtable);
            vtable->vfunc3c(pNode);
            FUN_009c8eb0(pNode);
            return;
        }
        this->byteFlag = 1; // +0x3d: set flag
    }

    float newVal = g_minValue; // DAT_00e2b04c
    if ((this->flags & 0x0C) != 0)
    {
        float fVal = static_cast<float>(this->duration) * g_speedMultiplier; // DAT_00e2cd54
        if (fVal < g_minValue)
            fVal = g_minValue;
        this->duration = static_cast<int>(fVal);
        float timeDiff = static_cast<float>(this->currentTime) - g_frameTime;
        this->currentTime = static_cast<int>(timeDiff);
        if (timeDiff < newVal)
            this->currentTime = static_cast<int>(newVal);
    }

    VirtualTable* vtable = reinterpret_cast<VirtualTable*>(pNode->vtable);
    vtable->vfunc40(pNode); // vfunc at +0x40 (idx 16)
    FUN_009c8eb0(pNode);
}