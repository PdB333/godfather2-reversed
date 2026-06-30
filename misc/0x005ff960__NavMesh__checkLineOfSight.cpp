// FUNC_NAME: NavMesh::checkLineOfSight
// Function at 0x005ff960: Recursive line-of-sight check between two points against obstacles.
// Uses helper functions for obstacle intersection and point projection.
// Returns 1 if line is clear, 0 if obstructed.

#include <cmath>

// Forward declarations of helper functions (defined elsewhere)
int findObstacleIntersection(const float* pointA, const float* pointB, int unknown, int flag, int obstacleData);
float* getObstaclePoint(float* outPoint, const float* pointA, const float* pointB, int obstacleIndex, int flag1, int unknown, int flag2, int unknown2);

// Constants from data references (likely min/max distance thresholds)
extern const float DIST_MIN;  // DAT_00e2eff4
extern const float DIST_MAX;  // DAT_00e2b1a4

int __thiscall NavMesh::checkLineOfSight(int thisPtr, const float* pointA, const float* pointB, int obstacleIndex, const float* inputPoint, float* outputPoint, int recursionDepth, int useClosest, int flag)
{
    int obstacleIdx = findObstacleIntersection(pointA, pointB, 0, flag, *(int*)(obstacleIndex + 4));
    if (obstacleIdx == 0) {
        // No obstacle found; check if point is inside an obstacle via virtual function
        bool insideObstacle = (*(bool (__thiscall**)(int, int, const float*))(*(int*)thisPtr + 0xA8))(thisPtr, obstacleIndex, inputPoint);
        if (!insideObstacle) {
            // Copy input point to output and return success
            outputPoint[0] = inputPoint[0];
            outputPoint[1] = inputPoint[1];
            outputPoint[2] = inputPoint[2];
            outputPoint[3] = inputPoint[3];
            return 1;
        }
    }
    else if (recursionDepth > 0) {
        // Compute vector from obstacle point to pointB
        float dx = pointB[0] - *(float*)(obstacleIdx + 0x10);
        float dy = pointB[1] - *(float*)(obstacleIdx + 0x14);
        float obstacleRadiusSq = *(float*)(obstacleIdx + 0x18) * *(float*)(obstacleIdx + 0x18);
        bool pointOutsideObstacle = (dx * dx + dy * dy) >= obstacleRadiusSq;

        // Get a projected point on the obstacle
        float buffer[2]; // local_28
        float* projPoint = getObstaclePoint(buffer, pointA, pointB, obstacleIdx, flag, 0, useClosest, 0);
        float projX = projPoint[0];
        float projY = projPoint[1];

        float obstacleData = *(float*)(obstacleIndex + 4);
        float diff = (float)inputPoint[1] - obstacleData;
        if (diff > DIST_MAX || diff < DIST_MIN) {
            // Scale the distance based on ratio of distances
            float dy1 = pointA[1] - pointB[1];
            float dy2 = pointA[1] - projY;
            float dx1 = pointA[0] - pointB[0];
            float dx2 = pointA[0] - projX;
            float ratio = sqrt((dx2 * dx2 + dy2 * dy2) / (dx1 * dx1 + dy1 * dy1));
            obstacleData = ratio * diff + obstacleData;
        }

        float midX = projX;
        float midY = projY;

        // Recursively check both subsegments
        bool subResult1 = false;
        bool subResult2 = false;
        if (pointOutsideObstacle) {
            subResult1 = checkLineOfSight(thisPtr, &projX, pointB, &midX, inputPoint, outputPoint, recursionDepth - 1, (useClosest == 0), flag);
        }
        if (!subResult1) {
            subResult2 = checkLineOfSight(thisPtr, pointA, &projX, obstacleIndex, &midX, outputPoint, recursionDepth - 1, (useClosest == 0), flag);
        }

        if (!subResult1 && !subResult2) {
            // Both subsegments failed; try alternative projection
            float* altProj = getObstaclePoint(buffer, pointA, pointB, obstacleIdx, flag, 0, (useClosest == 0), 0);
            float altX = altProj[0];
            float altY = altProj[1];
            midX = altX;
            midY = altY;

            bool altSub1 = false;
            bool altSub2 = false;
            if (pointOutsideObstacle) {
                altSub1 = checkLineOfSight(thisPtr, &altX, pointB, &midX, inputPoint, outputPoint, recursionDepth - 1, useClosest, flag);
            }
            if (!altSub1) {
                altSub2 = checkLineOfSight(thisPtr, pointA, &altX, obstacleIndex, &midX, outputPoint, recursionDepth - 1, useClosest, flag);
            }
            if (!altSub1 && !altSub2) {
                return 0;
            }
        }
        return 1;
    }
    return 0;
}