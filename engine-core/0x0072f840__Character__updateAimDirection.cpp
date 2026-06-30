// FUNC_NAME: Character::updateAimDirection
void __fastcall Character::updateAimDirection(Character* thisPtr)
{
    // Offset 0x1c78 appears to be a pointer to some animation state or controller
    // 0x48 = 72 may be a sentinel value indicating "no active state" or "dead"
    int animState = *(int*)((char*)thisPtr + 0x1c78);
    if (animState != 0 && animState != 0x48)
    {
        // FUN_00471610 likely returns a pointer to the character's movement/transform component
        int transformPtr = FUN_00471610();
        // FUN_00470250 and FUN_0046fd30 probably extract forward/up vectors or rotation angles
        // from the transform at offset +0x30 (e.g., a matrix or quaternion)
        float x = (float)FUN_00470250(transformPtr + 0x30);
        float y = (float)FUN_0046fd30(transformPtr + 0x30);
        // Store the resulting aim direction components (likely pitch/yaw or screen offsets)
        *(float*)((char*)thisPtr + 0x204c) = x;
        *(float*)((char*)thisPtr + 0x2050) = y;
    }
}