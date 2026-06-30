// FUNC_NAME: SpriteBatch::addQuad
// Address: 0x0048bab0

struct SpriteVertex {
    float x;       // +0x00
    float y;       // +0x04
    float z;       // +0x08
    uint32 color;  // +0x0C (0xRRGGBBAA)
    float u;       // +0x10
    float v;       // +0x14
};
// Total size: 0x18 (24 bytes)

// Static global vertex colors for quads (if per-vertex color enabled)
// Dat_01163d98..01163da7 (4 x uint32)
static const uint32 s_quadColors[4] = {
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF // placeholder; actual values from DAT
};

class SpriteBatch {
public:
    // +0x00: centerX (used as rotation pivot when rotation matrix supplied)
    // +0x04: centerY
    // ...
    // +0x28: screenWidth
    // +0x2C: screenHeight
    // +0x48: defaultZ
    // +0x4C: vertexBuffer (pointer to SpriteVertex array)
    // +0x50: vertexCount (number of vertices in buffer, incremented by 4 per quad)
    // +0x52: vertexCapacity (max vertices before realloc)

    void __thiscall addQuad(float x, float y, float w, float h,
                            float* uvBounds,           // array of [uMin, vMin, uMax, vMax]
                            bool perVertexColor,       // true = use s_quadColors per vertex
                            float* rotation)           // [cosθ, sinθ] or null for no rotation
    {
        // Check if we need to grow the vertex buffer (FUN_0048ba40)
        if ((uint16_t)vertexCapacity < (uint16_t)vertexCount + 4) {
            growVertexBuffer();  // calls FUN_0048ba40
        }

        // Compute opposite corner of the quad
        float right = x + w;
        float bottom = y + h;

        // Get pointer to the next vertex slot (4 vertices)
        SpriteVertex* outVerts = reinterpret_cast<SpriteVertex*>(
            reinterpret_cast<char*>(vertexBuffer) + vertexCount * sizeof(SpriteVertex)
        );

        float z = defaultZ;

        if (rotation == nullptr) {
            // No rotation – simple axis‑aligned quad
            outVerts[0].x = x;    outVerts[0].y = y;
            outVerts[1].x = x;    outVerts[1].y = bottom;
            outVerts[2].x = right; outVerts[2].y = bottom;
            outVerts[3].x = right; outVerts[3].y = y;
        } else {
            // Rotation: transform the four corners around (centerX, centerY)
            float cosθ = rotation[0];
            float sinθ = rotation[1];

            // Aspect ratio correction factor
            float aspect = screenHeight / screenWidth;  // +0x2C / +0x28
            // Constant from global: DAT_00e2b1a4 (likely 1.0f)
            float invAspect = 1.0f / aspect;

            // Compute rotated positions for each corner
            // Use center as pivot (this->centerX, this->centerY)
            float cx = reinterpret_cast<float*>(this)[0]; // centerX at +0x00
            float cy = reinterpret_cast<float*>(this)[1]; // centerY at +0x04

            float dx1 = (x - cx) * aspect;
            float dy1 = (y - cy);

            outVerts[0].x = cx + invAspect * (cosθ * dx1 - sinθ * dy1);
            outVerts[0].y = cy + sinθ * dx1 + cosθ * dy1;

            float dy2 = (bottom - cy);
            outVerts[1].x = cx + invAspect * (cosθ * dx1 - sinθ * dy2);
            outVerts[1].y = cy + sinθ * dx1 + cosθ * dy2;

            float dx2 = (right - cx) * aspect;
            outVerts[2].x = cx + invAspect * (cosθ * dx2 - sinθ * dy2);
            outVerts[2].y = cy + sinθ * dx2 + cosθ * dy2;

            outVerts[3].x = cx + invAspect * (cosθ * dx2 - sinθ * dy1);
            outVerts[3].y = cy + sinθ * dx2 + cosθ * dy1;
        }

        // Set Z for all vertices
        outVerts[0].z = z;
        outVerts[1].z = z;
        outVerts[2].z = z;
        outVerts[3].z = z;

        // Set vertex colors
        if (!perVertexColor) {
            // White color (0xFFFFFFFF) for all vertices
            for (int i = 0; i < 4; ++i) {
                // Assign 4 bytes of color at offset +0x0C
                *(uint32*)(&outVerts[i].color) = 0xFFFFFFFF;
            }
        } else {
            // Use the four global quad colors (from DAT_01163d98..01163da4)
            // These are stored as consecutive uint32 values.
            outVerts[0].color = s_quadColors[0];
            outVerts[1].color = s_quadColors[1];
            outVerts[2].color = s_quadColors[2];
            outVerts[3].color = s_quadColors[3];
        }

        // Set texture coordinates if provided
        if (uvBounds != nullptr) {
            float uMin = uvBounds[0];
            float vMin = uvBounds[1];
            float uMax = uvBounds[2];
            float vMax = uvBounds[3];

            // Vertex 0: (uMin, vMin)
            outVerts[0].u = uMin;
            outVerts[0].v = vMin;
            // Vertex 1: (uMin, vMax)
            outVerts[1].u = uMin;
            outVerts[1].v = vMax;
            // Vertex 2: (uMax, vMax)
            outVerts[2].u = uMax;
            outVerts[2].v = vMax;
            // Vertex 3: (uMax, vMin)
            outVerts[3].u = uMax;
            outVerts[3].v = vMin;
        }

        // Advance vertex count by 4
        vertexCount += 4;
    }

private:
    void growVertexBuffer(); // FUN_0048ba40

    // Offsets (incomplete; only fields used here are listed)
    // +0x00 float m_centerX;
    // +0x04 float m_centerY;
    // +0x28 float m_screenWidth;
    // +0x2C float m_screenHeight;
    // +0x48 float m_defaultZ;
    // +0x4C SpriteVertex* m_vertices;
    // +0x50 int16 m_vertexCount;
    // +0x52 int16 m_vertexCapacity;
};
```

The function reconstructs the quad addition logic from the decompiled assembly, with proper names for coordinates, texture bounds, rotation, and color handling. The global constants (DAT_) are represented as static arrays for clarity.