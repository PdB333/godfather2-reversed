// FUNC_NAME: CollisionTest::checkIntersection
// Address: 0x00522540
// Role: Tests for intersection between pairs of 2D points (likely line segments or rectangle edges) using multiple orientation checks.
// Uses two extra reference points stored in member variables (m_pExtra1, m_pExtra2) as additional test endpoints.

struct IntPair {
    int x;
    int y;
};

// External orientation test: returns true if the seven parameters satisfy a geometric condition (e.g., cross product sign)
extern bool __stdcall orientationTest(int a, int b, int c, int d, int e, int f, int g);

class CollisionTest {
public:
    IntPair m_selfPair;     // +0x00: first two fields of this (m_selfX, m_selfY)
    IntPair* m_pExtra1;     // +0x? : stored in ESI (used as pointer to an IntPair)
    IntPair* m_pExtra2;     // +0x? : stored in EDI (used as pointer to an IntPair)

    // Check intersection between two point pairs (pA and pB) using this object's and extra points
    bool __thiscall checkIntersection(IntPair* pA, IntPair* pB);
};

bool __thiscall CollisionTest::checkIntersection(IntPair* pA, IntPair* pB) {
    // Extract this object's own point
    int selfX = m_selfPair.x;
    int selfY = m_selfPair.y;

    // Extract points from parameters
    int pAx = pA->x;
    int pAy = pA->y;
    int pBx = pB->x;
    int pBy = pB->y;

    // Extract extra point from m_pExtra1 (stored in ESI)
    int extra1Y = m_pExtra1->y;   // offset +4 from m_pExtra1

    // Test orientation with all points, including extra1Y as first argument
    if (orientationTest(extra1Y, pBx, pBy, pAx, pAy, selfX, selfY)) {
        return true;
    }

    // Extract extra point from m_pExtra2 (stored in EDI)
    int extra2X = m_pExtra2->x;
    int extra2Y = m_pExtra2->y;

    // Second test: swap self and parameter A points
    if (orientationTest(extra1Y, pBx, pBy, selfX, selfY, extra2X, extra2Y)) {
        return true;
    }

    // Third test: use parameter A and B swapped with extra2
    if (orientationTest(extra1Y, pBx, pBy, pAx, pAy, extra2X, extra2Y)) {
        return true;
    }

    return false;
}