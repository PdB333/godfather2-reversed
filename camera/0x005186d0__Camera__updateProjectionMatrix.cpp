// FUNC_NAME: Camera::updateProjectionMatrix
void Camera::updateProjectionMatrix(float param_1)
{
    float fVar1;
    fVar1 = FUN_00518510(); // likely returns frame delta time or some update value
    s_previousSetting = s_currentSetting;
    s_currentSetting = s_defaultSetting;
    FUN_0052cbd0(&s_projectionMatrix, s_fov, 1.0f, 0, param_1, fVar1, s_additionalParam0, s_additionalParam1);
    return;
}