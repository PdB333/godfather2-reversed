// FUNC_NAME: Entity::updateTransform
void __fastcall Entity::updateTransform(Entity* this)
{
    char isPaused = FUN_0040edb0(); // global pause check
    float identityScale = _DAT_00d5780c; // +0x0: identity matrix diagonal value (likely 1.0f)
    if (isPaused == '\0') {
        // Update position: newPos = velocity * globalMultiplier * timeStep + oldPos
        float newPos = *(float*)(this + 4) * DAT_012067e8 * _DAT_00d5c458 + *(float*)(this + 0xc);
        *(float*)(this + 0xc) = newPos; // store new position

        // Build identity matrix (4x4)
        float matrix[16];
        matrix[0] = identityScale;
        matrix[1] = 0.0f;
        matrix[2] = 0.0f;
        matrix[3] = 0.0f;
        matrix[4] = 0.0f;
        matrix[5] = identityScale;
        matrix[6] = 0.0f;
        matrix[7] = 0.0f;
        matrix[8] = 0.0f;
        matrix[9] = 0.0f;
        matrix[10] = identityScale;
        matrix[11] = 0.0f;
        matrix[12] = 0.0f;
        matrix[13] = 0.0f;
        matrix[14] = 0.0f;
        matrix[15] = identityScale;

        // Combine position/orientation into transform and apply
        FUN_0056c040(newPos, this + 0x10, &matrix); // orientation at +0x10
        FUN_00610040(&matrix); // set world transform
    }
}