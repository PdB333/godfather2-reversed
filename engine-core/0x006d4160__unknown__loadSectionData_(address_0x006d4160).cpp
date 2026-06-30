// FUNC_NAME: unknown::loadSectionData (address 0x006d4160)
// This function reads a hierarchical data section from a stream, likely for animation/skeleton transforms.
// It first reads an initial block (possibly a header or bone count), then iterates reading typed elements.
// The readings store floats (possibly scaled) and 4-float blocks (quaternions/matrices) into the object fields.

struct __declspec(align(4)) unknown {
    // Fields identified from offsets (partial):
    float field_0x60; // +0x60
    float field_0x64; // +0x64
    float field_0x68; // +0x68
    float field_0x6c; // +0x6c (often set to _DAT_00d5780c)
    float field_0x80; // +0x80
    float field_0x84; // +0x84
    float field_0x88; // +0x88
    float field_0x8c; // +0x8c
    float field_0x90; // +0x90
    int   field_0xa0; // +0xa0
    float field_0xa4; // +0xa4
    float field_0xa8; // +0xa8
    float field_0xac; // +0xac
    int   field_0xb0; // +0xb0
    float field_0xb4[4]; // +0xb4
    float field_0xc4[4]; // +0xc4
    // ... many more 4-float blocks up to +0x1e4...
    // Offsets: 0x1e4, 0x1f4, 0x204, 0x214, ~0x224 etc. (approx 22 quads)
    float field_0x1e4[4]; // +0x1e4
    float field_0x1f4[4]; // +0x1f4
    float field_0x204[4]; // +0x204
    float field_0x214[4]; // +0x214
    // ... (others)
};

// Constants
extern const float DAT_00e445c8; // scale factor, e.g., inches to meters
extern const int _DAT_00d5780c;  // some zero constant (likely 0)

// Forward declarations of helper functions (EA EARS engine style):
void __cdecl streamInit(void* stream);                           // 0x004738b0
void __cdecl streamPushSection(void* stream, uint32_t hash);    // 0x0043aff0
void __cdecl streamSetMode(int mode);                           // 0x0043af00
bool __cdecl streamSectionBegin(void);                          // 0x0043b120 - returns true when finished
int  __cdecl streamReadToken(void* buffer);                     // 0x0043b210 - reads token into buffer, returns pointer?
void __cdecl streamProcessToken(void* buffer);                  // 0x0043ac60
void __cdecl streamExtractTransform(void* in, float* out1, float* out2, float* out3); // 0x0056c180
int  __cdecl streamGetDataType(void);                           // 0x0043ab70 - returns 0..0x1c
int* __cdecl streamReadVector4(void);                           // 0x0043abc0 - returns pointer to 4 floats
void __cdecl streamAdvance(void);                               // 0x0043b1a0

void __thiscall unknown::loadSectionData(void* stream)
{
    char buffer[12]; // for reading a token (e.g., a hash or name)
    float initialTransform1[4]; // +0x80
    float initialTransform2[4]; // +0x60
    float tmpQuat[27]; // large temporary (only first element used)

    streamInit(stream);
    streamPushSection(stream, 0xb390b11a; // hash for "boneData" or similar
    streamSetMode(1); // binary mode?

    // Check if section exists; if so, read initial data
    if (!streamSectionBegin()) {
        // Read a token (maybe a name) that determines how to extract initial transforms
        streamReadToken(buffer);
        streamProcessToken(buffer);
        streamExtractTransform(buffer, &initialTransform1[0], &initialTransform2[0], tmpQuat);

        // Store the two extracted transforms (possibly a position and orientation)
        field_0x80 = initialTransform1[0];
        field_0x84 = initialTransform1[1];
        field_0x88 = initialTransform1[2];
        field_0x8c = initialTransform1[3];

        field_0x60 = initialTransform2[0];
        field_0x64 = initialTransform2[1];
        field_0x68 = initialTransform2[2];
        field_0x6c = initialTransform2[3]; // often zero from _DAT_00d5780c
    }

    // Now read a second section (or continue the same?)
    streamPushSection(stream, 0xa9b45f9c; // hash for "boneTransforms" or similar
    while (!streamSectionBegin()) {
        int dataType = streamGetDataType();
        int* dataPtr;
        streamReadToken(); // read and discard some token

        switch (dataType) {
        case 0: // Scale factor for field_0x90
            dataPtr = streamReadToken(); // actually returns pointer to token data
            field_0x90 = *(float*)(dataPtr + 8) * DAT_00e445c8;
            break;
        case 1: // Integer for field_0xa0 (e.g., bone index)
            dataPtr = streamReadToken();
            field_0xa0 = *(int*)(dataPtr + 8);
            break;
        case 2: // Scale for field_0xa4
            dataPtr = streamReadToken();
            field_0xa4 = *(float*)(dataPtr + 8) * DAT_00e445c8;
            break;
        case 3: // Scale for field_0xa8
            dataPtr = streamReadToken();
            field_0xa8 = *(float*)(dataPtr + 8) * DAT_00e445c8;
            break;
        case 4: // Scale for field_0xac
            dataPtr = streamReadToken();
            field_0xac = *(float*)(dataPtr + 8) * DAT_00e445c8;
            break;
        case 5: // Integer for field_0xb0 (e.g., another index)
            dataPtr = streamReadToken();
            field_0xb0 = *(int*)(dataPtr + 8);
            break;
        case 6: // Quaternion bone 1
            streamReadToken();
            dataPtr = streamReadVector4();
            field_0x1e4[0] = dataPtr[0];
            field_0x1e4[1] = dataPtr[1];
            field_0x1e4[2] = dataPtr[2];
            field_0x1e4[3] = dataPtr[3];
            break;
        case 7: // Quaternion bone 2
            streamReadToken();
            dataPtr = streamReadVector4();
            field_0x1f4[0] = dataPtr[0];
            field_0x1f4[1] = dataPtr[1];
            field_0x1f4[2] = dataPtr[2];
            field_0x1f4[3] = dataPtr[3];
            break;
        case 8: // Quaternion bone 3
            streamReadToken();
            dataPtr = streamReadVector4();
            field_0x204[0] = dataPtr[0];
            field_0x204[1] = dataPtr[1];
            field_0x204[2] = dataPtr[2];
            field_0x204[3] = dataPtr[3];
            break;
        case 9: // Quaternion bone 4
            streamReadToken();
            dataPtr = streamReadVector4();
            field_0x214[0] = dataPtr[0];
            field_0x214[1] = dataPtr[1];
            field_0x214[2] = dataPtr[2];
            field_0x214[3] = dataPtr[3];
            break;
        case 10: // Quaternion bone 5
            streamReadToken();
            dataPtr = streamReadVector4();
            field_0xb4[0] = dataPtr[0];
            field_0xb4[1] = dataPtr[1];
            field_0xb4[2] = dataPtr[2];
            field_0xb4[3] = dataPtr[3];
            break;
        case 11: // Quaternion bone 6
            streamReadToken();
            dataPtr = streamReadVector4();
            field_0xc4[0] = dataPtr[0];
            field_0xc4[1] = dataPtr[1];
            field_0xc4[2] = dataPtr[2];
            field_0xc4[3] = dataPtr[3];
            break;
        case 12: // Quaternion bone 7
            streamReadToken();
            dataPtr = streamReadVector4();
            field_0xd4[0] = dataPtr[0];
            field_0xd4[1] = dataPtr[1];
            field_0xd4[2] = dataPtr[2];
            field_0xd4[3] = dataPtr[3];
            break;
        case 13: // Quaternion bone 8
            streamReadToken();
            dataPtr = streamReadVector4();
            field_0xe4[0] = dataPtr[0];
            field_0xe4[1] = dataPtr[1];
            field_0xe4[2] = dataPtr[2];
            field_0xe4[3] = dataPtr[3];
            break;
        case 14: // Quaternion bone 9
            streamReadToken();
            dataPtr = streamReadVector4();
            field_0xf4[0] = dataPtr[0];
            field_0xf4[1] = dataPtr[1];
            field_0xf4[2] = dataPtr[2];
            field_0xf4[3] = dataPtr[3];
            break;
        case 15: // Quaternion bone 10
            streamReadToken();
            dataPtr = streamReadVector4();
            field_0x104[0] = dataPtr[0];
            field_0x104[1] = dataPtr[1];
            field_0x104[2] = dataPtr[2];
            field_0x104[3] = dataPtr[3];
            break;
        case 16: // Quaternion bone 11
            streamReadToken();
            dataPtr = streamReadVector4();
            field_0x114[0] = dataPtr[0];
            field_0x114[1] = dataPtr[1];
            field_0x114[2] = dataPtr[2];
            field_0x114[3] = dataPtr[3];
            break;
        case 17: // Quaternion bone 12
            streamReadToken();
            dataPtr = streamReadVector4();
            field_0x124[0] = dataPtr[0];
            field_0x124[1] = dataPtr[1];
            field_0x124[2] = dataPtr[2];
            field_0x124[3] = dataPtr[3];
            break;
        case 18: // Quaternion bone 13
            streamReadToken();
            dataPtr = streamReadVector4();
            field_0x134[0] = dataPtr[0];
            field_0x134[1] = dataPtr[1];
            field_0x134[2] = dataPtr[2];
            field_0x134[3] = dataPtr[3];
            break;
        case 19: // Quaternion bone 14
            streamReadToken();
            dataPtr = streamReadVector4();
            field_0x144[0] = dataPtr[0];
            field_0x144[1] = dataPtr[1];
            field_0x144[2] = dataPtr[2];
            field_0x144[3] = dataPtr[3];
            break;
        case 20: // Quaternion bone 15
            streamReadToken();
            dataPtr = streamReadVector4();
            field_0x154[0] = dataPtr[0];
            field_0x154[1] = dataPtr[1];
            field_0x154[2] = dataPtr[2];
            field_0x154[3] = dataPtr[3];
            break;
        case 21: // Quaternion bone 16
            streamReadToken();
            dataPtr = streamReadVector4();
            field_0x164[0] = dataPtr[0];
            field_0x164[1] = dataPtr[1];
            field_0x164[2] = dataPtr[2];
            field_0x164[3] = dataPtr[3];
            break;
        case 22: // Quaternion bone 17
            streamReadToken();
            dataPtr = streamReadVector4();
            field_0x174[0] = dataPtr[0];
            field_0x174[1] = dataPtr[1];
            field_0x174[2] = dataPtr[2];
            field_0x174[3] = dataPtr[3];
            break;
        case 23: // Quaternion bone 18
            streamReadToken();
            dataPtr = streamReadVector4();
            field_0x184[0] = dataPtr[0];
            field_0x184[1] = dataPtr[1];
            field_0x184[2] = dataPtr[2];
            field_0x184[3] = dataPtr[3];
            break;
        case 24: // Quaternion bone 19
            streamReadToken();
            dataPtr = streamReadVector4();
            field_0x194[0] = dataPtr[0];
            field_0x194[1] = dataPtr[1];
            field_0x194[2] = dataPtr[2];
            field_0x194[3] = dataPtr[3];
            break;
        case 25: // Quaternion bone 20
            streamReadToken();
            dataPtr = streamReadVector4();
            field_0x1a4[0] = dataPtr[0];
            field_0x1a4[1] = dataPtr[1];
            field_0x1a4[2] = dataPtr[2];
            field_0x1a4[3] = dataPtr[3];
            break;
        case 26: // Quaternion bone 21
            streamReadToken();
            dataPtr = streamReadVector4();
            field_0x1b4[0] = dataPtr[0];
            field_0x1b4[1] = dataPtr[1];
            field_0x1b4[2] = dataPtr[2];
            field_0x1b4[3] = dataPtr[3];
            break;
        case 27: // Quaternion bone 22
            streamReadToken();
            dataPtr = streamReadVector4();
            field_0x1c4[0] = dataPtr[0];
            field_0x1c4[1] = dataPtr[1];
            field_0x1c4[2] = dataPtr[2];
            field_0x1c4[3] = dataPtr[3];
            break;
        case 28: // Quaternion bone 23 (extra? but offset only up to 0x1e0? Actually last case is 0x1c = 28)
            // The original code has case 0x1c (28) writing to +0x1d4, so we need that too.
            streamReadToken();
            dataPtr = streamReadVector4();
            field_0x1d4[0] = dataPtr[0];
            field_0x1d4[1] = dataPtr[1];
            field_0x1d4[2] = dataPtr[2];
            field_0x1d4[3] = dataPtr[3];
            break;
        }

        streamAdvance(); // move to next token
    }
}