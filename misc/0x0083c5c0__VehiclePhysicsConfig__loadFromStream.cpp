// FUNC_NAME: VehiclePhysicsConfig::loadFromStream
// Address: 0x0083c5c0
// This function reads vehicle physics parameters from a binary stream in the EARS engine format.
// It handles a tokenized input (likely from a serialized configuration file or network packet)
// and performs post-load validation/clamping on speed and acceleration values.

#include <cstring>

// Forward declarations of helper functions (engine/library calls)
void startReadStream(void* stream);
void setStreamVersion(void* stream, uint version);
char isStreamEnd();
void advanceStream();
int readNextNode();
int getTokenType();
char* readString();
void advanceStreamToken(); // post-switch advancement
int hashString(const char* str); // e.g., FUN_0043c1c0
void initSubObject(void* subObj); // FUN_0043ad10
void strcpy(void* dst, const char* src); // FUN_004089b0
void notifySomething(int id, void* obj); // FUN_008f6f50
void memcpy(void* dst, const void* src, int size); // FUN_00408900

extern float someGlobal1;        // _DAT_00d577a0
extern float someGlobal2;        // DAT_00d5779c
extern void* g_someDataPtr;      // DAT_012069f4

class VehiclePhysicsConfig {
public:
    // Fields (offsets from this)
    uint m_idHash;                // +0xd4
    float m_maxSpeed;             // +0x58
    float m_acceleration;         // +0x5c
    float m_anotherSpeed;         // +0x60
    float m_minSpeed;             // +0x64
    float m_turnRateSquared;      // +0x68
    int m_soundEventHash;         // +0xf4
    float m_speedC;               // +0x6c
    float m_dualValue;            // +0x70
    float m_dualValueCopy;        // +0xa0
    float m_float9;               // +0x74
    int m_intA;                   // +0x78
    int m_intB;                   // +0x7c
    float m_floatC;               // +0x80
    float m_floatD;               // +0x88
    uint m_flags;                 // +0xa8
    uint m_flags2;                // +0xac
    // sub-object at +0xb0
    struct SubObj* m_subObj;      // +0xb0 (actually inline, but pointer-sized)
    // string buffers
    char m_string1[32];           // +0xdc (size guessed)
    char m_string2[32];           // +0xe4
    char m_string3[32];           // +0xec
    // large data block
    char m_dataBlock[0x8000];     // +0x3c

    void loadFromStream(void* stream);
};

void __thiscall VehiclePhysicsConfig::loadFromStream(void* thisPtr, void* stream)
{
    VehiclePhysicsConfig* self = (VehiclePhysicsConfig*)thisPtr;

    startReadStream(stream);
    setStreamVersion(stream, 0xb7d515f0);

    // Main parsing loop – read token-by-token until stream ends
    while (!isStreamEnd())
    {
        advanceStream();
        int tokenType = getTokenType();

        switch (tokenType)
        {
            case 0:  // ID hash
            {
                int node = readNextNode();
                self->m_idHash = *(uint*)(node + 8);
                break;
            }
            case 1:  // max speed
            {
                int node = readNextNode();
                self->m_maxSpeed = *(float*)(node + 8);
                break;
            }
            case 2:  // acceleration
            {
                int node = readNextNode();
                self->m_acceleration = *(float*)(node + 8);
                break;
            }
            case 3:  // another speed (e.g., cruising or limit)
            {
                int node = readNextNode();
                self->m_anotherSpeed = *(float*)(node + 8);
                break;
            }
            case 4:  // min speed
            {
                int node = readNextNode();
                self->m_minSpeed = *(float*)(node + 8);
                break;
            }
            case 5:  // turn rate squared
            {
                int node = readNextNode();
                float val = *(float*)(node + 8);
                self->m_turnRateSquared = val * val;
                break;
            }
            case 6:  // sound event name (hash)
            {
                readNextNode(); // skip token node
                char* str = readString();
                if (strlen(str) == 0)
                    self->m_soundEventHash = -1;
                else
                    self->m_soundEventHash = hashString(str);
                break;
            }
            case 7:  // speed clamp value
            {
                int node = readNextNode();
                self->m_speedC = *(float*)(node + 8);
                break;
            }
            case 8:  // dual-purpose float
            {
                int node = readNextNode();
                float val = *(float*)(node + 8);
                self->m_dualValue = val;
                self->m_dualValueCopy = val;
                break;
            }
            case 9:  // generic float 9
            {
                int node = readNextNode();
                self->m_float9 = *(float*)(node + 8);
                break;
            }
            case 10: // int A (e.g., max gear or limit)
            {
                int node = readNextNode();
                self->m_intA = *(int*)(node + 8);
                break;
            }
            case 11: // int B (e.g., current gear or state)
            {
                int node = readNextNode();
                self->m_intB = *(int*)(node + 8);
                break;
            }
            case 12: // float C
            {
                int node = readNextNode();
                self->m_floatC = *(float*)(node + 8);
                break;
            }
            case 13: // float D
            {
                int node = readNextNode();
                self->m_floatD = *(float*)(node + 8);
                break;
            }
            case 14: // flag bits
            {
                int node = readNextNode();
                self->m_flags |= *(uint*)(node + 8);
                break;
            }
            case 15: // sub-object
            {
                // read sub-object into inline storage at +0xb0
                readNextNode((void*)((uintptr_t)self + 0xb0));
                initSubObject((void*)((uintptr_t)self + 0xb0));
                break;
            }
            case 16: // first string (e.g., audio file path)
            {
                readNextNode();
                char* str = readString();
                strcpy(self->m_string1, str);
                break;
            }
            case 17: // second string
            {
                readNextNode();
                char* str = readString();
                strcpy(self->m_string2, str);
                break;
            }
            case 18: // third string
            {
                readNextNode();
                char* str = readString();
                strcpy(self->m_string3, str);
                break;
            }
        }
        advanceStreamToken();
        if (isStreamEnd()) break;
    }

    // --- Post-process: clamp and adjust values ---
    float curSpeed = self->m_anotherSpeed;    // +0x60
    float maxSpeed = self->m_maxSpeed;        // +0x58
    float temp = maxSpeed;

    // Clamp: ensure m_anotherSpeed is between maxSpeed and minSpeed
    if (maxSpeed < curSpeed)
    {
        temp = self->m_minSpeed;              // +0x64
        if (curSpeed < self->m_minSpeed)
            temp = curSpeed;
    }
    curSpeed = self->m_acceleration;          // +0x5c
    self->m_anotherSpeed = temp;

    // Adjust acceleration if below threshold
    if (curSpeed <= someGlobal1)
    {
        curSpeed = self->m_minSpeed;
        if ((self->m_flags >> 5) & 1)
            curSpeed = temp;
        curSpeed += someGlobal2;
    }

    // Set speedC if current speed exceeds it
    if (self->m_speedC <= curSpeed && curSpeed != self->m_speedC)
        self->m_speedC = curSpeed;

    // Ensure minSpeed is not less than maxSpeed (apply increment)
    if (self->m_minSpeed <= maxSpeed)
        self->m_minSpeed = maxSpeed + someGlobal2;

    // Enforce intA >= intB (intA is upper limit)
    if (self->m_intB < self->m_intA)
        self->m_intA = self->m_intB;

    // Notify if not already flagged
    if (!(self->m_flags2 & 0x4))
        notifySomething(0x13, thisPtr);

    // Copy external data block (e.g., sound bank) into internal buffer
    if (g_someDataPtr)
        memcpy(self->m_dataBlock, g_someDataPtr, 0x8000);

    self->m_flags2 |= 4;
}