// FUNC_NAME: Vector2::isPointInsideTriangle
// Address: 0x00522680
// Note: this method tests if the Vector2 object (this) is inside the triangle formed by the three given points.
// Uses the cross product sign test (barycentric technique) for 2D point-in-triangle.

class Vector2 {
public:
    float x;
    float y;

    bool isPointInsideTriangle(const Vector2* pA, const Vector2* pB, const Vector2* pC) const {
        // Edge vectors and point-to-vertex vectors
        // For each edge, compute cross product (edge vector cross point-to-edge-start) and compare signs.
        float ax = pA->x;
        float ay = pA->y;
        float bx = pB->x;
        float by = pB->y;
        float cx = pC->x;
        float cy = pC->y;
        float px = this->x;
        float py = this->y;

        // Cross product for edge (A->B) with (this - A): (B-A) x (this-A)
        float cross1 = (bx - ax) * (py - ay) - (by - ay) * (px - ax);
        bool sign1 = (cross1 >= 0.0f);

        // Cross product for edge (B->C) with (this - B)
        float cross2 = (cx - bx) * (py - by) - (cy - by) * (px - bx);
        bool sign2 = (cross2 >= 0.0f);

        // If the sign of the second cross doesn't match the first, point is outside
        if (sign2 != sign1) {
            return false;
        }

        // Cross product for edge (C->A) with (this - C)
        float cross3 = (ax - cx) * (py - cy) - (ay - cy) * (px - cx);
        bool sign3 = (cross3 >= 0.0f);

        // Return final sign equality
        if (sign3) {
            return sign1;
        } else {
            return !sign1;
        }
    }
};