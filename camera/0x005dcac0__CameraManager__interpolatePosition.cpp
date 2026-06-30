// FUNC_NAME: CameraManager::interpolatePosition
bool CameraManager::interpolatePosition(float sourceX, float* outX, float* outY, float t)
{
    // FUN_005dc670 checks if interpolation is active (e.g., camera target valid)
    bool valid = this->isInterpolationEnabled();
    if (valid) {
        // FUN_005dd8a0(0, &sourceX) – likely reads a default/initial x value from ID 0
        CameraManager::getInterpolationData(0, &sourceX);
        
        // DAT_012056c0 is some global identifier for the target animation keyframe
        // FUN_005dd8a0 fills a local 3‑float vector (x, y, extra) – note: only x and y are used later
        Vector3 targetData; // local_c, local_8, local_4
        CameraManager::getInterpolationData(DAT_012056c0, &targetData.x); // writes to x, y, z
        
        // DAT_00e2b1a4 is a constant (likely 1.0f)
        float oneMinusT = DAT_00e2b1a4 - t; // (1 - t)
        *outX = oneMinusT * sourceX + targetData.x * t;
        *outY = oneMinusT * targetData.y + targetData.z * t;
    }
    return valid;
}