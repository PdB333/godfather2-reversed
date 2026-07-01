// FUNC_NAME: SomeObject::updateRotation
void __thiscall SomeObject::updateRotation(SomeObject* this)
{
    char isPaused;
    float angle;
    float deltaAngle;
    float scale;
    float matrix[16]; // 4x4 matrix, row-major

    isPaused = FUN_0040edb0(); // likely isGamePaused()
    scale = _DAT_00d5780c; // global constant, likely 1.0f

    if (isPaused == 0) {
        deltaAngle = _DAT_00d58cbc; // global delta time or angular speed
        angle = *(float*)(this + 8) + deltaAngle;
        *(float*)(this + 8) = angle;

        // Build a uniform scaling matrix (identity if scale==1.0)
        matrix[0] = scale;  matrix[1] = 0;     matrix[2] = 0;     matrix[3] = 0;
        matrix[4] = 0;      matrix[5] = scale; matrix[6] = 0;     matrix[7] = 0;
        matrix[8] = 0;      matrix[9] = 0;     matrix[10] = scale; matrix[11] = 0;
        matrix[12] = 0;     matrix[13] = 0;    matrix[14] = 0;    matrix[15] = scale;

        // Apply rotation based on angle (likely around Y or Z axis)
        FUN_0056b8a0(angle, 0, 0, matrix); // e.g., buildRotationMatrix(angle, axisX, axisY, matrix)
        FUN_00610040(matrix); // e.g., setTransform(matrix)
    }
}