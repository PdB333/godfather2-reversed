// FUNC_NAME: PropertyContainer::deserializeProperties
// Function: 0x006d6ba0
// Role: Deserializes a property bag from a binary stream (EARS serialization).
// Fields stored: name, 10 ints (0xa0-0xc8), 3 floats scaled by DAT_00e445c8 (0xcc-0xd4),
//               2 ints (0xd8,0xdc), 1 int (0xe0), a vector3 (0xe4-0xec),
//               and 6 others (0x68-0x8c) with conditional logic for 0x18-0x1c.
// Stream functions: FUN_0043b120 (hasMore), FUN_0043ab70 (getTokenType),
//                   FUN_0043b210 (readToken), FUN_0043b1a0 (nextToken),
//                   FUN_004738b0 (setStream), FUN_0043aff0 (readMagic),
//                   FUN_0043abe0 (readVector3).

#include <cstdint>

// External constants used in property scaling
extern float DAT_00e445c8; // Scale factor (e.g., degree/radian conversion)
extern float _DAT_00d5780c; // Upper bound clamp value

class PropertyContainer {
public:
    void deserializeProperties(void *stream);

private:
    // Offsets known from decompilation:
    char *mName; // +0x58 (string pointer)
    // +0x68, 0x6c, 0x70, 0x74, 0x78, 0x7c, 0x80, 0x84, 0x88, 0x8c (10 fields, conditional)
    uint32_t mInt0; // +0x68
    uint32_t mInt1; // +0x6c
    uint32_t mInt2; // +0x70
    uint32_t mInt3; // +0x74
    uint32_t mInt4; // +0x78
    float mFloat0; // +0x7c
    float mFloat1; // +0x80
    float mFloat2; // +0x84
    uint32_t mInt5; // +0x88
    uint32_t mInt6; // +0x8c
    // +0xa0 to 0xc8: 10 ints (0xa0,0xa4,0xa8,0xac,0xb0,0xb4,0xb8,0xbc,0xc0,0xc4)
    uint32_t mPropertyList[10]; // +0xa0 (indexed by case 1-0xb)
    // +0xcc,0xd0,0xd4: 3 floats scaled by DAT_00e445c8
    float mScaledFloat0; // +0xcc
    float mScaledFloat1; // +0xd0
    float mScaledFloat2; // +0xd4
    // +0xd8,0xdc,0xe0: 3 ints (case 0xf,0x10,0x11)
    uint32_t mInt7; // +0xd8
    uint32_t mInt8; // +0xdc
    uint32_t mInt9; // +0xe0
    // +0xe4,0xe8,0xec: vector3
    float mVec3[3]; // +0xe4
};

// These are stubs for the decompiled stream functions.
// In the original code they are likely part of an EA stream library.
namespace Stream {
    void setStream(void *stream); // FUN_004738b0
    void readMagic(void *stream, uint32_t magic); // FUN_0043aff0
    bool hasMore(); // FUN_0043b120 - returns true when stream is exhausted (non-zero means done)
    void *readToken(); // FUN_0043b210 - returns pointer to token structure
    void *readToken(void *dest); // overload for case 0 (string read)
    uint32_t getTokenType(); // FUN_0043ab70 - returns token type index
    void advanceToNext(); // FUN_0043b1a0
    void *readVector3(); // FUN_0043abe0 - returns pointer to three floats
    // string read functions for case 0:
    void readString(void *dest); // FUN_0043ad10?
    uint32_t findString(void *str, int mode); // FUN_00445ff0? (mode=0)
    void *findObject(uint32_t id, uint32_t hash, void *param); // FUN_00475660? (used with nameHash)
};

void PropertyContainer::deserializeProperties(void *stream) {
    uint32_t tokenType;
    void *token;
    void *dest;
    uint32_t uVar2;
    float fVar5;
    
    // Initialize stream reading
    Stream::setStream(stream);
    Stream::readMagic(stream, 0x8e19a048); // Magic number for property version
    
    // Loop until end of stream
    while (!Stream::hasMore()) {
        Stream::advanceToNext();
        tokenType = Stream::getTokenType();
        
        switch (tokenType) {
        case 0: { // Name/title property
            dest = reinterpret_cast<void*>(reinterpret_cast<uint32_t>(this) + 0x58);
            Stream::readToken(dest); // read string pointer into mName
            Stream::readString(dest); // likely reads the string data
            uint32_t nameHash = Stream::findString(dest, 0); // hash or lookup name
            uVar2 = reinterpret_cast<uint32_t>(Stream::findObject(nameHash, 0x38523fc3, &uVar2));
            // findObject may return some object reference, stored into param_2? (not used?)
            break;
        }
        case 1: // Property list index 0
            token = Stream::readToken();
            reinterpret_cast<uint32_t*>(this)[0xa0/4] = *reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(token) + 8);
            break;
        case 2: // Property list index 1
            token = Stream::readToken();
            reinterpret_cast<uint32_t*>(this)[0xa4/4] = *reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(token) + 8);
            break;
        case 3: // index 2
            token = Stream::readToken();
            reinterpret_cast<uint32_t*>(this)[0xa8/4] = *reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(token) + 8);
            break;
        case 4: // index 3
            token = Stream::readToken();
            reinterpret_cast<uint32_t*>(this)[0xac/4] = *reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(token) + 8);
            break;
        case 5: // index 4
            token = Stream::readToken();
            reinterpret_cast<uint32_t*>(this)[0xb0/4] = *reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(token) + 8);
            break;
        case 6: // index 5
            token = Stream::readToken();
            reinterpret_cast<uint32_t*>(this)[0xb4/4] = *reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(token) + 8);
            break;
        case 7: // index 6
            token = Stream::readToken();
            reinterpret_cast<uint32_t*>(this)[0xb8/4] = *reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(token) + 8);
            break;
        case 8: // index 7
            token = Stream::readToken();
            reinterpret_cast<uint32_t*>(this)[0xbc/4] = *reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(token) + 8);
            break;
        case 9: // index 8
            token = Stream::readToken();
            reinterpret_cast<uint32_t*>(this)[0xc0/4] = *reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(token) + 8);
            break;
        case 10: // index 9
            token = Stream::readToken();
            reinterpret_cast<uint32_t*>(this)[0xc4/4] = *reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(token) + 8);
            break;
        case 11: // index 10? Actually +200 = 0xc8, but list goes to 0xc4, so maybe +0xc8 is separate? 
            token = Stream::readToken();
            reinterpret_cast<uint32_t*>(this)[0xc8/4] = *reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(token) + 8);
            break;
        case 12: // Scaled float 0
            token = Stream::readToken();
            reinterpret_cast<float*>(this)[0xcc/4] = *reinterpret_cast<float*>(reinterpret_cast<char*>(token) + 8) * DAT_00e445c8;
            break;
        case 13: // Scaled float 1
            token = Stream::readToken();
            reinterpret_cast<float*>(this)[0xd0/4] = *reinterpret_cast<float*>(reinterpret_cast<char*>(token) + 8) * DAT_00e445c8;
            break;
        case 14: // Scaled float 2
            token = Stream::readToken();
            reinterpret_cast<float*>(this)[0xd4/4] = *reinterpret_cast<float*>(reinterpret_cast<char*>(token) + 8) * DAT_00e445c8;
            break;
        case 15: // Int at +0xd8
            token = Stream::readToken();
            reinterpret_cast<uint32_t*>(this)[0xd8/4] = *reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(token) + 8);
            break;
        case 16: // Int at +0xdc
            token = Stream::readToken();
            reinterpret_cast<uint32_t*>(this)[0xdc/4] = *reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(token) + 8);
            break;
        case 17: // Int at +0xe0
            token = Stream::readToken();
            reinterpret_cast<uint32_t*>(this)[0xe0/4] = *reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(token) + 8);
            break;
        case 18: { // Vector3 (e.g., position/color)
            void *vecPtr = Stream::readVector3(); // returns pointer to 3 floats
            float *vec = reinterpret_cast<float*>(vecPtr);
            reinterpret_cast<float*>(this)[0xe4/4] = vec[0];
            reinterpret_cast<float*>(this)[0xe8/4] = vec[1];
            reinterpret_cast<float*>(this)[0xec/4] = vec[2];
            break;
        }
        case 19: // Int at +0x68
            token = Stream::readToken();
            reinterpret_cast<uint32_t*>(this)[0x68/4] = *reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(token) + 8);
            break;
        case 20: // Int at +0x70
            token = Stream::readToken();
            reinterpret_cast<uint32_t*>(this)[0x70/4] = *reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(token) + 8);
            break;
        case 21: // Int at +0x6c
            token = Stream::readToken();
            reinterpret_cast<uint32_t*>(this)[0x6c/4] = *reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(token) + 8);
            break;
        case 22: // Int at +0x74
            token = Stream::readToken();
            reinterpret_cast<uint32_t*>(this)[0x74/4] = *reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(token) + 8);
            break;
        case 23: // Int at +0x78
            token = Stream::readToken();
            reinterpret_cast<uint32_t*>(this)[0x78/4] = *reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(token) + 8);
            break;
        case 24: { // Float at +0x7c with clamping
            token = Stream::readToken();
            fVar5 = 0.0f;
            float val1 = *reinterpret_cast<float*>(reinterpret_cast<char*>(token) + 8);
            if (val1 > 0.0f) {
                token = Stream::readToken();
                float val2 = *reinterpret_cast<float*>(reinterpret_cast<char*>(token) + 8);
                if (val2 < _DAT_00d5780c) {
                    token = Stream::readToken();
                    fVar5 = *reinterpret_cast<float*>(reinterpret_cast<char*>(token) + 8);
                } else {
                    fVar5 = _DAT_00d5780c;
                }
            }
            reinterpret_cast<float*>(this)[0x7c/4] = fVar5;
            break;
        }
        case 25: { // Float at +0x80 with different clamp
            token = Stream::readToken();
            fVar5 = _DAT_00d5780c;
            if (*reinterpret_cast<float*>(reinterpret_cast<char*>(token) + 8) > _DAT_00d5780c) {
                token = Stream::readToken();
                fVar5 = *reinterpret_cast<float*>(reinterpret_cast<char*>(token) + 8);
            }
            reinterpret_cast<float*>(this)[0x80/4] = fVar5;
            break;
        }
        case 26: { // Float at +0x84, similar to case 24
            token = Stream::readToken();
            fVar5 = 0.0f;
            float val1 = *reinterpret_cast<float*>(reinterpret_cast<char*>(token) + 8);
            if (val1 > 0.0f) {
                token = Stream::readToken();
                float val2 = *reinterpret_cast<float*>(reinterpret_cast<char*>(token) + 8);
                if (val2 < _DAT_00d5780c) {
                    token = Stream::readToken();
                    fVar5 = *reinterpret_cast<float*>(reinterpret_cast<char*>(token) + 8);
                } else {
                    fVar5 = _DAT_00d5780c;
                }
            }
            reinterpret_cast<float*>(this)[0x84/4] = fVar5;
            break;
        }
        case 27: { // Int at +0x88 with condition
            token = Stream::readToken();
            uVar2 = 0;
            if (*reinterpret_cast<float*>(reinterpret_cast<char*>(token) + 8) > 0.0f) {
                token = Stream::readToken();
                uVar2 = *reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(token) + 8);
            }
            reinterpret_cast<uint32_t*>(this)[0x88/4] = uVar2;
            break;
        }
        case 28: { // Int at +0x8c, similar to case 27
            token = Stream::readToken();
            uVar2 = 0;
            if (*reinterpret_cast<float*>(reinterpret_cast<char*>(token) + 8) > 0.0f) {
                token = Stream::readToken();
                uVar2 = *reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(token) + 8);
            }
            reinterpret_cast<uint32_t*>(this)[0x8c/4] = uVar2;
            break;
        }
        default:
            break;
        }
    }
}