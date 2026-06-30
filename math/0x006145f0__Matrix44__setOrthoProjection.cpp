// FUNC_NAME: Matrix44::setOrthoProjection

extern const float TWO_DIV_SCREEN_WIDTH;   // DAT_00e2b04c (likely 2.0 / screenWidth)
extern const float TWO_DIV_SCREEN_HEIGHT;  // DAT_00e2b1a4 (likely 2.0 / screenHeight)
extern const float ZERO_OFFSET;            // DAT_00e44564 (likely 0.0)
extern const float SCALE_FACTOR;           // DAT_00e2cd54 (some scaling factor)

// Thread-local or global state for depth range
extern int* gDepthRangeActive;            // offset from FS segment
extern int* gDepthRangeIndex;             // index into depth triple arrays
extern float gDepthRangeTriples[];        // DAT_011f6bb8 store triples (min, max, unused)

class Matrix44 {
public:
    float m[16]; // 4x4 row-major matrix

    // Reconstructed from FUN_006145f0
    // Builds an orthographic projection matrix and optionally an auxiliary viewport matrix.
    // Parameters:
    //   outMatrix - optional output matrix (scaled by SCALE_FACTOR)
    //   left      - left clip plane (passed in XMM6 register)
    //   right     - right clip plane
    //   bottom    - bottom clip plane
    //   top       - top clip plane
    //   near      - near clip plane
    //   far       - far clip plane (passed in XMM4 register)
    void __thiscall setOrthoProjection(float *outMatrix,
                                       float left,
                                       float right,
                                       float bottom,
                                       float top,
                                       float near,
                                       float far)
    {
        float width = right - left;
        float height = top - bottom;
        float depth = far - near;

        // Determine depth range parameters (used to map [near, far] to [depthMin, depthMax])
        float depthMin, depthMax;
        uint depthIndex = 0; // index into the thread-local depth triple array
        if (gDepthRangeActive != nullptr) {
            depthIndex = (uint)(*gDepthRangeActive != 0);
        }
        int idx = gDepthRangeIndex[depthIndex];
        if (idx == -1) {
            depthMin = 0.0f;
            depthMax = TWO_DIV_SCREEN_HEIGHT; // actually stored as DAT_00e2b1a4
        } else {
            depthMin = gDepthRangeTriples[idx * 3];
            depthMax = gDepthRangeTriples[idx * 3 + 1];
        }

        // Compute the orthographic projection matrix stored in 'this'
        // Standard orthographic matrix maps:
        //   x: [left, right] -> [-1, 1]
        //   y: [bottom, top] -> [-1, 1]
        //   z: [near, far]   -> [depthMin, depthMax] (nonstandard, uses depth range)
        float invWidth = TWO_DIV_SCREEN_WIDTH / width;
        float invHeight = TWO_DIV_SCREEN_HEIGHT / height;
        float invDepth = TWO_DIV_SCREEN_HEIGHT / depth; // but later multiplied by depth range

        m[0] = invWidth;                     // scale x
        m[5] = invHeight;                    // scale y
        m[10] = TWO_DIV_SCREEN_HEIGHT;       // z scale placeholder (overridden by depth range)
        m[12] = ZERO_OFFSET - (left + right) / width;  // translate x
        m[13] = ZERO_OFFSET - (bottom + top) / height; // translate y
        m[14] = depthMin - m[10] * near;               // translate z (using depth range)
        m[15] = TWO_DIV_SCREEN_HEIGHT;                 // w? (unused)

        // Zero out unused elements (standard orthographic matrix has non-zero only on diagonal and translation)
        m[1] = m[2] = m[3] = m[4] = 0.0f;
        m[6] = m[7] = m[8] = m[9] = 0.0f;
        m[11] = 0.0f;

        // Optionally compute an auxiliary matrix (scaled version)
        if (outMatrix != nullptr) {
            float depthRange = depthMax - depthMin;
            float invDepthRange = depth / depthRange; // (far - near) / (depthMax - depthMin)
            float scale = SCALE_FACTOR; // global scale factor

            outMatrix[0] = width * scale;               // scale x
            outMatrix[5] = height * scale;              // scale y
            outMatrix[10] = invDepthRange;               // z scale (inverse of depth range)
            outMatrix[12] = (left + right) * scale;     // translate x
            outMatrix[13] = (bottom + top) * scale;     // translate y
            outMatrix[14] = near - invDepthRange * depthMin; // translate z
            outMatrix[15] = TWO_DIV_SCREEN_HEIGHT;      // w

            // Zero out unused elements
            outMatrix[1] = outMatrix[2] = outMatrix[3] = outMatrix[4] = 0.0f;
            outMatrix[6] = outMatrix[7] = outMatrix[8] = outMatrix[9] = 0.0f;
            outMatrix[11] = 0.0f;
        }
    }
};