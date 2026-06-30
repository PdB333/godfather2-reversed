// FUNC_NAME: ParticleEmitter::loadFromStream
class ParticleEmitter {
public:
    // Offsets relative to this pointer
    // +0x14: Vector4 m_controlPoints[0] (4 floats)
    // +0x48: Vector4 m_controlPoints[1]
    // +0x7c: Vector4 m_controlPoints[2]
    // +0xb0: Vector4 m_controlPoints[3]
    // +0xe0: float m_randomValue
    // +0xe4: float m_extraFloat

    void __thiscall loadFromStream(float param_2);

private:
    // Helper functions for stream reading (names guessed from pattern)
    void streamInit(float value, int magic);  // 0x0043aff0
    bool streamHasMore();                     // 0x0043b120
    int streamReadToken();                    // 0x0043ab70
    float* streamReadVector4();               // 0x0043abc0
    int streamGetNextToken();                 // 0x0043b210
    float streamReadFloat();                  // from token+iVar4+8
    void streamAdvance();                     // 0x0043b1a0
};

void __thiscall ParticleEmitter::loadFromStream(float param_2)
{
    float minValue;
    float maxValue;
    float local_68;
    int tokenType;
    float* vecPtr;

    // Initialize the stream with a magic constant
    streamInit(param_2, 0xea432ab4);

    local_68 = _DAT_00d5780c;  // global float variable (maybe default min)
    maxValue = _DAT_00d5780c;  // initially same as min

    if (!streamHasMore()) {
        // If stream is empty, skip to random generation
    } else {
        do {
            streamGetNextToken();  // maybe read token header?
            tokenType = streamReadToken();  // actual token type
            switch (tokenType) {
            case 0:
                // Read a 4-float vector into control point 0
                streamGetNextToken();
                vecPtr = streamReadVector4();
                m_controlPoints[0] = *(Vector4*)vecPtr;  // offsets 0x14-0x20
                break;
            case 1:
                // Read vector into control point 1
                streamGetNextToken();
                vecPtr = streamReadVector4();
                m_controlPoints[1] = *(Vector4*)vecPtr;  // offsets 0x48-0x54
                break;
            case 2:
                // Read vector into control point 2
                streamGetNextToken();
                vecPtr = streamReadVector4();
                m_controlPoints[2] = *(Vector4*)vecPtr;  // offsets 0x7c-0x88
                break;
            case 3:
                // Read vector into control point 3
                streamGetNextToken();
                vecPtr = streamReadVector4();
                m_controlPoints[3] = *(Vector4*)vecPtr;  // offsets 0xb0-0xbc
                break;
            case 4:
                // Read a float value into minValue
                tokenType = streamGetNextToken();
                local_68 = streamReadFloat();  // from token data
                break;
            case 5:
                // Read a float value into maxValue
                tokenType = streamGetNextToken();
                maxValue = streamReadFloat();
                break;
            case 6:
                // Read a float into m_extraFloat
                tokenType = streamGetNextToken();
                m_extraFloat = streamReadFloat();  // offset 0xe4
                break;
            }
            streamAdvance();  // move to next token in stream
        } while (!streamHasMore());

        // Ensure min <= max
        if (maxValue < local_68) {
            maxValue = local_68;
        }
    }

    // Generate a random float within [minValue, maxValue] and store at offset 0xe0
    m_randomValue = (float)(rand() & 0x7fff) * DAT_00e44590 * (maxValue - local_68) + local_68;
}