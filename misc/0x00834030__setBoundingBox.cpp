// FUNC_NAME: setBoundingBox

class SomeObject {
public:
    // Bounding box stored at offset +0x5c (6 floats: minX, minY, minZ, maxX, maxY, maxZ)
    float m_boundingBoxData[6]; // placeholder; actual fields may be named

    void setBoundingBox(const float* src) {
        float* dest = &m_boundingBoxData[0];
        if (dest != src) {
            dest[0] = src[0];
            dest[1] = src[1];
            dest[2] = src[2];
            dest[3] = src[3];
            dest[4] = src[4];
            dest[5] = src[5];
        }
    }
};