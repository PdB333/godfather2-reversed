// FUNC_NAME: MathUtils::segmentIntersect2D
bool MathUtils::segmentIntersect2D(float p1x, float p1y, float p2x, float p2y, float p3x, float p3y, float p4x, float p4y)
{
    // Check if two line segments (p1-p2) and (p3-p4) intersect in 2D space
    // Uses cross product and orientation tests
    
    float dx1 = p2x - p3x;
    float dy1 = p4y - p1y;  // Note: this is actually dy from p1 to p4
    float cross1 = (p3y - p4y) * dy1 - dx1 * (p1x - p2x);
    
    // Check if segments are collinear or nearly collinear
    if (fabsf(cross1) < EPSILON) {
        // Collinear case - check bounding box overlap
        if (fabsf(p4y - p2y) < EPSILON) {
            return false;
        }
        
        // Check x-axis overlap
        if (p1x <= p2x) {
            p1x = p2x;
        }
        if (p4y <= p3y) {
            p3y = p4y;
        }
        if (p1x <= p3y) {
            return false;
        }
        return true;
    }
    
    // Calculate intersection point
    float invCross = 1.0f / cross1;
    float det1 = p4y * p2x - p1x * p1y;
    float det2 = p2x * p4y - p3y * p3x;
    
    float t = (dx1 * det1 - dy1 * det2) * invCross;
    
    // Check if intersection point lies within first segment
    if (fabsf(dy1) >= EPSILON) {
        if (p1y <= p4y) {
            if (t < p1y || t > p4y) {
                return false;
            }
        } else {
            if (t < p4y || t > p1y) {
                return false;
            }
        }
    } else if (fabsf(p4y - t) >= EPSILON) {
        return false;
    }
    
    // Check if intersection point lies within second segment
    if (fabsf(dx1) >= EPSILON) {
        if (p3x <= p2x) {
            if (t < p3x || t > p2x) {
                return false;
            }
        } else {
            if (t < p2x || t > p3x) {
                return false;
            }
        }
    } else if (fabsf(p2x - t) >= EPSILON) {
        return false;
    }
    
    // Calculate second cross product for orientation check
    float cross2 = ((p3y - p4y) * det1 - (p1x - p2x) * det2) * invCross;
    
    // Final orientation check
    if (FUN_005222c0(cross2) && FUN_005222c0(cross2)) {
        return true;
    }
    return false;
}