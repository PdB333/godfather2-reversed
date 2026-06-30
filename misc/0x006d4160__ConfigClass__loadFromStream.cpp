// FUNC_NAME: ConfigClass::loadFromStream
// Address: 0x006d4160
// Role: Deserialize property block from a binary stream into member variables.
// This function reads a series of named properties (identified by hash) and stores them
// at specific offsets in the object. It handles both scalar and 4-component vector properties.

extern void beginReadStream(void* dataSource);
extern void readSectionHash(void* dataSource, unsigned int hash);
extern void setSectionVersion(int version);
extern bool isNextElement(); // Returns false when more data available
extern char* readPropertyName(); // Returns a pointer to the property name string
extern int readPropertyType(); // Returns type identifier (0..0x1c)
extern uint32* readPropertyValueArray(); // Returns pointer to 4 uint32 values
extern void processPropertyValue(char* name); // Called after reading property name?
extern void advanceToNextProperty(); // Advance to next property

extern void readTransformData(char* buffer, float* out1, float* out2, float* out3, float* out4, float* out5, float* out6);
// Simplified, actual call is different.

extern float gScaleFactor; // DAT_00e445c8
extern uint32 gDefaultValue; // _DAT_00d5780c (maybe 0 or 1.0f)

void __thiscall ConfigClass::loadFromStream(void* dataSource)
{
    char nameBuffer[12]; // local_c0
    float transformOut1, transformOut2; // local_134, local_130, but also local_12c[0] etc.
    uint32 extra[27]; // local_12c

    beginReadStream(dataSource);
    readSectionHash(dataSource, 0xb390b11a);
    setSectionVersion(1);

    if (!isNextElement()) {
        // Read initial transform/header data
        readPropertyName(nameBuffer);
        processPropertyValue(nameBuffer);
        readTransformData(nameBuffer, &transformOut1, &transformOut2, &extra[0], &extra[1], &extra[2], &extra[3]);
        // Store values at specific offsets (likely position/rotation/scale)
        *(float*)(this + 0x80) = transformOut1; // offset 0x80
        *(float*)(this + 0x84) = transformOut2; // offset 0x84
        *(float*)(this + 0x88) = *(float*)&extra[0]; // offset 0x88
        *(float*)(this + 0x8c) = *(float*)&gDefaultValue; // offset 0x8c
        *(float*)(this + 0x60) = *(float*)&extra[1]; // offset 0x60 (uninitialized from previous)
        *(float*)(this + 0x64) = *(float*)&extra[2]; // offset 0x64
        *(float*)(this + 0x68) = *(float*)&extra[3]; // offset 0x68
        *(float*)(this + 0x6c) = *(float*)&gDefaultValue; // offset 0x6c
    }

    // Read main property section
    readSectionHash(dataSource, 0xa9b45f9c);
    while (!isNextElement()) {
        readPropertyName(); // property name read but not used
        int type = readPropertyType();
        switch (type) {
        case 0: {
            // Float property scaled
            float* ptr = (float*)(this + 0x90);
            *ptr = *(float*)(readPropertyName() + 8) * gScaleFactor;
            break;
        }
        case 1: {
            // Integer property
            *(int*)(this + 0xa0) = *(int*)(readPropertyName() + 8);
            break;
        }
        case 2: {
            // Float property scaled
            *(float*)(this + 0xa4) = *(float*)(readPropertyName() + 8) * gScaleFactor;
            break;
        }
        case 3: {
            *(float*)(this + 0xa8) = *(float*)(readPropertyName() + 8) * gScaleFactor;
            break;
        }
        case 4: {
            *(float*)(this + 0xac) = *(float*)(readPropertyName() + 8) * gScaleFactor;
            break;
        }
        case 5: {
            // Integer property
            *(int*)(this + 0xb0) = *(int*)(readPropertyName() + 8);
            break;
        }
        case 6: {
            // 4-component vector
            readPropertyName();
            uint32* vec = readPropertyValueArray();
            memcpy((void*)(this + 0x1e4), vec, 16); // offset 0x1e4..0x1f0
            break;
        }
        case 7: {
            readPropertyName();
            uint32* vec = readPropertyValueArray();
            memcpy((void*)(this + 0x1f4), vec, 16); // offset 0x1f4..0x200 (1f4,1f8,1fc,200)
            break;
        }
        case 8: {
            readPropertyName();
            uint32* vec = readPropertyValueArray();
            memcpy((void*)(this + 0x204), vec, 16);
            break;
        }
        case 9: {
            readPropertyName();
            uint32* vec = readPropertyValueArray();
            memcpy((void*)(this + 0x214), vec, 16);
            break;
        }
        case 10: {
            readPropertyName();
            uint32* vec = readPropertyValueArray();
            memcpy((void*)(this + 0xb4), vec, 16); // offset 0xb4..0xc0
            break;
        }
        case 11: {
            readPropertyName();
            uint32* vec = readPropertyValueArray();
            memcpy((void*)(this + 0xc4), vec, 16); // offset 0xc4..0xd0
            break;
        }
        case 12: {
            readPropertyName();
            uint32* vec = readPropertyValueArray();
            memcpy((void*)(this + 0xd4), vec, 16); // offset 0xd4..0xe0
            break;
        }
        case 13: {
            readPropertyName();
            uint32* vec = readPropertyValueArray();
            memcpy((void*)(this + 0xe4), vec, 16); // offset 0xe4..0xf0
            break;
        }
        case 14: {
            readPropertyName();
            uint32* vec = readPropertyValueArray();
            memcpy((void*)(this + 0xf4), vec, 16); // offset 0xf4..0x100
            break;
        }
        case 15: {
            readPropertyName();
            uint32* vec = readPropertyValueArray();
            memcpy((void*)(this + 0x104), vec, 16); // offset 0x104..0x110
            break;
        }
        case 16: {
            readPropertyName();
            uint32* vec = readPropertyValueArray();
            memcpy((void*)(this + 0x114), vec, 16); // offset 0x114..0x120
            break;
        }
        case 17: {
            readPropertyName();
            uint32* vec = readPropertyValueArray();
            memcpy((void*)(this + 0x124), vec, 16); // offset 0x124..0x130
            break;
        }
        case 18: {
            readPropertyName();
            uint32* vec = readPropertyValueArray();
            memcpy((void*)(this + 0x134), vec, 16); // offset 0x134..0x140
            break;
        }
        case 19: {
            readPropertyName();
            uint32* vec = readPropertyValueArray();
            memcpy((void*)(this + 0x144), vec, 16); // offset 0x144..0x150
            break;
        }
        case 20: {
            readPropertyName();
            uint32* vec = readPropertyValueArray();
            memcpy((void*)(this + 0x154), vec, 16); // offset 0x154..0x160
            break;
        }
        case 21: {
            readPropertyName();
            uint32* vec = readPropertyValueArray();
            memcpy((void*)(this + 0x164), vec, 16); // offset 0x164..0x170
            break;
        }
        case 22: {
            readPropertyName();
            uint32* vec = readPropertyValueArray();
            memcpy((void*)(this + 0x174), vec, 16); // offset 0x174..0x180
            break;
        }
        case 23: {
            readPropertyName();
            uint32* vec = readPropertyValueArray();
            memcpy((void*)(this + 0x184), vec, 16); // offset 0x184..0x190
            break;
        }
        case 24: {
            readPropertyName();
            uint32* vec = readPropertyValueArray();
            memcpy((void*)(this + 0x194), vec, 16); // offset 0x194..0x1a0
            break;
        }
        case 25: {
            readPropertyName();
            uint32* vec = readPropertyValueArray();
            memcpy((void*)(this + 0x1a4), vec, 16); // offset 0x1a4..0x1b0
            break;
        }
        case 26: {
            readPropertyName();
            uint32* vec = readPropertyValueArray();
            memcpy((void*)(this + 0x1b4), vec, 16); // offset 0x1b4..0x1c0
            break;
        }
        case 27: {
            readPropertyName();
            uint32* vec = readPropertyValueArray();
            memcpy((void*)(this + 0x1c4), vec, 16); // offset 0x1c4..0x1d0
            break;
        }
        case 28: {
            readPropertyName();
            uint32* vec = readPropertyValueArray();
            memcpy((void*)(this + 0x1d4), vec, 16); // offset 0x1d4..0x1e0
            break;
        }
        // NOTE: Many case numbers (0x1d, 0x1e, 0x1f) are missing; possible they don't exist.
        }
        advanceToNextProperty();
    }
}