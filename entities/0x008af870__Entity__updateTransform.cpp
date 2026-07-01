// FUNC_NAME: Entity::updateTransform
void __thiscall Entity::updateTransform(TransformData* transform) {
    int transformPtr = transform; // save pointer for reuse
    // +0x60: pointer to parent skeleton or physics body
    if (*(int*)(this + 0x60) != 0) {
        // +0x7c: flags field, bit 4 indicates transform needs interpolation
        if ((*(uint*)(this + 0x7c) >> 4 & 1) != 0) {
            // interpolate or copy transform from previous state
            FUN_008ab7d0(&transform, transform + 0x14);
            // +0x04: dirty flag within transform structure, clear after interpolation
            *(byte*)(transform + 4) = 0;
        }
        // apply transform to physics/collision system
        // arguments: (transform->quaternion, transform, transform->position, transform->scale?)
        FUN_004baef0(*(undefined4*)(transformPtr + 0x14), transformPtr,
                     *(undefined4*)(transformPtr + 0x10), *(undefined4*)(transformPtr + 0x18));
        // update collision bounds
        FUN_004d3b50(transformPtr);
        // update world matrix for rendering
        FUN_008ac0f0();
        // propagate to child entities
        FUN_008add00(transformPtr);
    }
}