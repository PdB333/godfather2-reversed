// FUNC_NAME: ExpandAABBWithTransformedRect
// Function address: 0x005bbe00
// Purpose: Expands an axis-aligned bounding box (minX, minY, maxX, maxY) 
// by transforming the four corners of another rectangle through an affine 
// 2D transform (2x2 matrix + translation) and merging the resulting extents.

struct AffineTransform2D {
    float m00; // offset +0x220
    float m10; // offset +0x224
    float m01; // offset +0x228
    float m11; // offset +0x22c
    float tx;  // offset +0x230
    float ty;  // offset +0x234
};

void __fastcall ExpandAABBWithTransformedRect(float* aabb, const float* rect, const AffineTransform2D* transform)
{
    float xMin = rect[0];
    float yMin = rect[1];
    float xMax = rect[2];
    float yMax = rect[3];

    float m00 = transform->m00;
    float m10 = transform->m10;
    float m01 = transform->m01;
    float m11 = transform->m11;
    float tx  = transform->tx;
    float ty  = transform->ty;

    // Transform all four corners of the source rectangle
    // Corner (xMin, yMin)
    float tx0 = m00 * xMin + m01 * yMin + tx;
    float ty0 = m10 * xMin + m11 * yMin + ty;
    // Corner (xMax, yMin)
    float tx1 = m00 * xMax + m01 * yMin + tx;
    float ty1 = m10 * xMax + m11 * yMin + ty;
    // Corner (xMax, yMax)
    float tx2 = m00 * xMax + m01 * yMax + tx;
    float ty2 = m10 * xMax + m11 * yMax + ty;
    // Corner (xMin, yMax)
    float tx3 = m00 * xMin + m01 * yMax + tx;
    float ty3 = m10 * xMin + m11 * yMax + ty;

    // Merge transformed points into the axis-aligned bounding box
    if (tx0 < aabb[0]) aabb[0] = tx0;
    if (tx0 > aabb[2]) aabb[2] = tx0;
    if (ty0 < aabb[1]) aabb[1] = ty0;
    if (ty0 > aabb[3]) aabb[3] = ty0;

    if (tx1 < aabb[0]) aabb[0] = tx1;
    if (tx1 > aabb[2]) aabb[2] = tx1;
    if (ty1 < aabb[1]) aabb[1] = ty1;
    if (ty1 > aabb[3]) aabb[3] = ty1;

    if (tx2 < aabb[0]) aabb[0] = tx2;
    if (tx2 > aabb[2]) aabb[2] = tx2;
    if (ty2 < aabb[1]) aabb[1] = ty2;
    if (ty2 > aabb[3]) aabb[3] = ty2;

    if (tx3 < aabb[0]) aabb[0] = tx3;
    if (tx3 > aabb[2]) aabb[2] = tx3;
    if (ty3 < aabb[1]) aabb[1] = ty3;
    if (ty3 > aabb[3]) aabb[3] = ty3;
}