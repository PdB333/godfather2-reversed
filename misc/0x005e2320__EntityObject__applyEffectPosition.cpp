// FUNC_NAME: EntityObject::applyEffectPosition
bool __thiscall EntityObject::applyEffectPosition(int this, const float* positionVec) // positionVec unused in decompiled? actually unaff_EDI
{
    // Check if effect is allowed (flag at offset 0x1744)
    if (*(char*)(this + 0x1744) != '\0')
    {
        // Get or create the effect object (returns pointer to an effect structure)
        void* effectObj = FUN_005e2150(); // likely EffectObject* getEffectObject()
        if (effectObj != (void*)0x0)
        {
            // Copy three floats from the input vector (assumed passed in EDI register)
            // Offsets: +0x288 = position.x, +0x28c = position.y, +0x290 = position.z
            *(float*)((int)effectObj + 0x288) = *(float*)(positionVec + 0);
            *(float*)((int)effectObj + 0x28c) = *(float*)(positionVec + 1);
            *(float*)((int)effectObj + 0x290) = *(float*)(positionVec + 2);
            return true;
        }
    }
    return false;
}