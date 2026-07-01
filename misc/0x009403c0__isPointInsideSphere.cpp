// FUNC_NAME: isPointInsideSphere
// Address: 0x009403c0
// Role: Tests if a point is within a sphere defined by center and radius.
// param_1: pointer to float[4] where [0]=x, [1]=y, [2]=z, [3]=radius
// param_2: pointer to float[3] point (x,y,z)
// Returns 1 if point is inside sphere, 0 otherwise.

int isPointInsideSphere(float* sphereCenter, float* point)
{
    float dx = point[0] - sphereCenter[0];
    float dy = point[1] - sphereCenter[1];
    float dz = point[2] - sphereCenter[2];
    float distSq = dx*dx + dy*dy + dz*dz;
    float radiusSq = sphereCenter[3] * sphereCenter[3]; // radius squared
    if (distSq < radiusSq) {
        return 1;
    }
    return 0;
}