// FUNC_NAME: EntityController::applyMovement
// Function address: 0x0050d5e0
// Updates entity position using movement data and delta time, then writes position to transform buffer.

void __thiscall EntityController::applyMovement(float deltaTime)
{
    // this offsets:
    // +0x24 : MovementData* (pointer to velocity/force data)
    // +0x34 : position.x (float)
    // +0x38 : position.y (float)
    // +0x10 : index into transform array (int)

    MovementData* movement = *(MovementData**)(this + 0x24);
    // TLS global pointer (FS:0x2c) to scene/object manager
    int** globalPtr = *(int***)__readfsdword(0x2c);
    int* manager = *globalPtr; // pointer to manager struct
    // manager+8 is base of transform array, each entry is ??
    int* transformBase = *(int**)(manager + 8);
    // compute target transform slot: base + 0x10 (header?) + this->index
    int* targetTransform = (int*)((char*)transformBase + 0x10 + *(int*)(this + 0x10));

    // euler integration: position += velocity * deltaTime
    float newX = movement->velocityX * deltaTime + *(float*)(this + 0x34);
    float newY = movement->velocityY * deltaTime + *(float*)(this + 0x38);
    *(float*)(this + 0x34) = newX;
    *(float*)(this + 0x38) = newY;

    // push new position into transform buffer (called function likely sets world matrix)
    FUN_0056b8a0(newX, newY, *(float*)(movement + 0xf4), targetTransform);
}