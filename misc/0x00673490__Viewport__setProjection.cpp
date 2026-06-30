// FUNC_NAME: Viewport::setProjection
// Function address: 0x00673490
// Role: Sets an orthographic projection matrix for a 2D viewport, updates dimensions, and tracks changes.

#include <cstdint>

class Viewport {
public:
    // Fixed-point representation (1.0 = 0x10000)
    static const int kFixedPointOne = 0x10000;

    // +0x08: 2x2 projection matrix (row-major: m00, m01, m10, m11) in fixed-point 16.16
    int m_00; // +0x08
    int m_01; // +0x0C
    int m_10; // +0x10
    int m_11; // +0x14

    // +0x1C: flag set to 1 if matrix is identity (all zeros except m00=m11=1.0)
    int m_isIdentity; // +0x1C

    // +0x124: current viewport width (pixels)
    int m_width; // +0x124
    // +0x128: current viewport height (pixels)
    int m_height; // +0x128

    // +0x168: previous viewport width (used for change detection)
    int m_prevWidth; // +0x168
    // +0x16C: previous viewport height
    int m_prevHeight; // +0x16C

    /**
     * Sets a 2D projection matrix and viewport dimensions.
     * 
     * @param matrix Pointer to a 4-element array representing a 2x2 matrix in fixed-point 16.16.
     * @param updateFlag Non-zero if the previous dimensions should be updated when they change.
     * @param width New viewport width.
     * @param height New viewport height.
     */
    void setProjection(const int* matrix, int updateFlag, int width, int height) {
        // Read matrix elements
        int m00 = matrix[0];
        int m01 = matrix[1];
        int m10 = matrix[2];
        int m11 = matrix[3];

        // Store matrix into member fields
        m_00 = m00;
        m_01 = m01;
        m_10 = m10;
        m_11 = m11;

        // Check if the matrix is the identity matrix (1.0, 0, 0, 1.0)
        m_isIdentity = (m00 == kFixedPointOne && m01 == 0 && m10 == 0 && m11 == kFixedPointOne) ? 1 : 0;

        // Always store the new dimensions
        m_width = width;
        m_height = height;

        // If the update flag is set and the dimensions have changed,
        // update the "previous" dimensions (likely used for dirty tracking)
        if (updateFlag != 0 && (m_prevWidth != width || m_prevHeight != height)) {
            m_prevWidth = width;
            m_prevHeight = height;
        }
    }
};