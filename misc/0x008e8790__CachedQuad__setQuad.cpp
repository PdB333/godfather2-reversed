// FUNC_NAME: CachedQuad::setQuad
// Function address: 0x008e8790
// Role: Sets a 4-integer quad and invalidates cached resources if changed.
// Structure offsets:
//   m_quad[0] at +0x184 (int)
//   m_quad[1] at +0x188 (int)
//   m_quad[2] at +0x18c (int)
//   m_quad[3] at +0x190 (int, offset 400 decimal)
//   m_pCachedRes1 at +0x194 (pointer, freed if non-null)
//   m_pCachedRes2 at +0x19c (pointer, freed if non-null)

void __thiscall CachedQuad::setQuad(int *newQuad)
{
    // Check if any component differs
    if (m_quad[0] != newQuad[0] ||
        m_quad[1] != newQuad[1] ||
        m_quad[2] != newQuad[2] ||
        m_quad[3] != newQuad[3])
    {
        // Free resources that depend on the quad
        if (m_pCachedRes1 != nullptr)
        {
            FUN_004daf90(m_pCachedRes1);
            m_pCachedRes1 = nullptr;
        }
        if (m_pCachedRes2 != nullptr)
        {
            FUN_004daf90(m_pCachedRes2);
            m_pCachedRes2 = nullptr;
        }
        // Copy new quad values
        m_quad[0] = newQuad[0];
        m_quad[1] = newQuad[1];
        m_quad[2] = newQuad[2];
        m_quad[3] = newQuad[3];
    }
}