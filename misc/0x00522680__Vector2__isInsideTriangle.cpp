// FUNC_NAME: Vector2::isInsideTriangle
bool __thiscall Vector2::isInsideTriangle(const Vector2& a, const Vector2& b, const Vector2& c) const
{
    // Compute orientation of edge AB relative to this point (P)
    // orientation(A,B,P) = (B.x - A.x)*(P.y - A.y) - (B.y - A.y)*(P.x - A.x)
    float edgeAB_orientation = (b.y - a.y) * (a.x - this->x) - (b.x - a.x) * (a.y - this->y);
    bool pointOnSameSideAsTriangle = (edgeAB_orientation >= 0.0f);

    // Check orientation of triangle vertices C, A, B (triangle winding)
    // orientation(C,A,B) = (A.x - C.x)*(B.y - C.y) - (A.y - C.y)*(B.x - C.x)
    float triangleOrientation = (b.y - c.y) * (c.x - a.x) - (b.x - c.x) * (c.y - a.y);
    // Ensure that the point is on the same side of edge AB as the triangle interior
    if ((triangleOrientation >= 0.0f) != pointOnSameSideAsTriangle)
    {
        return false;
    }

    // Check orientation of edge CB relative to this point (P)
    // orientation(P,C,B) = (C.x - P.x)*(B.y - P.y) - (C.y - P.y)*(B.x - P.x)
    float edgeCB_orientation = (b.y - this->y) * (this->x - c.x) - (b.x - this->x) * (this->y - c.y);
    if (edgeCB_orientation >= 0.0f)
    {
        return pointOnSameSideAsTriangle;
    }
    else
    {
        return !pointOnSameSideAsTriangle;
    }
}