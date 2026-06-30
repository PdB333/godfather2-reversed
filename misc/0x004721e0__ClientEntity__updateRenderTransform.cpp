// FUNC_NAME: ClientEntity::updateRenderTransform
// Address: 0x004721e0
// Reconstructed from Ghidra decompilation for The Godfather 2 (EARS engine)
// This function updates the render transform (interpolation between simulation states) 
// and submits it to the renderer. It also sends a network update for ghost objects.

// Assumed class layout (partial):
// class ClientEntity {
//     // +0x00 vtable
//     // ...
//     // +0x168: m_pSimObject (pointer to SimObject, contains two 48-byte transforms at +0x00 and +0x30)
//     // +0x130: m_pNetworkObject (pointer for sending network events)
//     // Virtual methods at vtable offsets:
//     //   +0x28: submitRenderTransform (or sendNetworkUpdate)
//     //   +0x34: interpolateTransform (blend two transforms)
//     //   +0x40: sendMessage (on m_pNetworkObject)
// };

// SimObject layout (per inference):
// struct SimObject {
//     // +0x00: transform0 (48 bytes - 3x4 affine matrix)
//     // +0x30: transform1 (48 bytes)
//     // +0x60: byte flags (active, etc.)
//     // +0x61: byte index (selects which transform to use, bit 0)
//     // +0x62: byte flag (something about interpolation allowed)
//     // +0x63: unused?
//     // +0x64: int (timestamp of last update?)
//     // +0x70: ??? (not used here)
//     // +0x64 (0x64) is 100 decimal: byte alive flag
// };

// Stack fixed-size matrices (4x4 = 16 floats = 64 bytes)
typedef float Matrix44[16];  // row-major; translation at [12], [13], [14]

// External functions (to be linked)
void ReadTransform(void* src, Matrix44* dst);       // 0x0056cef0
void UpdateTimestamp(int time);                     // 0x0046da60 (maybe)
void StoreInterpolatedTransform(Matrix44* src, void* dst); // 0x0044b4e0 (unknown)
void InterpolateTransform(Matrix44* result);        // 0x0046dbd0
void QueueNetworkUpdate(void* buffer, Matrix44* transform); // 0x00449da0

// External globals
extern int g_SimTime;               // DAT_01205224
extern float g_IdentityW;          // DAT_00e2b1a4 (likely 1.0f)
extern float g_MaxInterpolateDistSq; // DAT_01128680

void __fastcall ClientEntity::updateRenderTransform(int* thisPtr) {
    int* simObj = (int*)thisPtr[0x5a];           // +0x168
    unsigned char flags = *(unsigned char*)(simObj + 0x60);
    unsigned char isAlive = *(char*)(simObj + 100); // +0x64

    if (isAlive && flags != 0) {
        // Select which transform slot to use (0 or 1)
        int slot = (*(unsigned char*)(simObj + 0x61) & 1);
        // Read the 3x4 affine transform into a full 4x4 matrix
        Matrix44 currentTransform;
        ReadTransform((char*)simObj + slot * 48, &currentTransform);

        // Extract position from the matrix (row-major: translation at indices 12,13,14)
        float posX = currentTransform[12];
        float posY = currentTransform[13];
        float posZ = currentTransform[14];
        float w = g_IdentityW;            // last element of 4th row

        // Check if interpolation should be applied
        if (flags > 1) {
            // Check interpolation conditions
            char* extraPtr = (char*)(simObj); // likely something else, but use simObj for offsets
            if (*(char*)(extraPtr + 0x62) != 0) {
                int timeSinceUpdate = g_SimTime - *(int*)((char*)simObj + 0x24); // +0x24? Actually from extraout_ECX, not reliable
                // Original: uint(DAT_01205224 - *(int*)(extraout_ECX+0x24)) < 2000
                // Assuming extraout_ECX points to some structure, we approximate:
                int delta = g_SimTime - *(int*)(simObj + 0x24); // maybe offset 0x24?
                if ((unsigned int)delta < 2000) {
                    UpdateTimestamp(g_SimTime);
                    // Call virtual method at +0x34: blend transforms
                    // This call takes (output, input1, input2) and produces interpolated result
                    // We assume it modifies the local transform (currentTransform) and writes to local_d0
                    Matrix44 interpolatedTransform;
                    (**(void (__thiscall**)(Matrix44*, Matrix44*, Matrix44*))(thisPtr[0] + 0x34))(
                        &currentTransform, &currentTransform, &interpolatedTransform);
                    // Store the interpolated transform somewhere (param_1 + 0x34)
                    StoreInterpolatedTransform(&interpolatedTransform, (char*)thisPtr + 0xD0);
                }
            }
        }

        // Decide final render transform
        Matrix44 renderTransform;
        bool useInterpolation = true;
        // Condition: if simObj+99 (alive again?) is zero OR distance from previous to current is too large
        if (*(char*)(simObj + 99) == 0 || 
            ( (renderTransform[8] - posX)*(renderTransform[8] - posX) + // fStack_a0 - local_e0
              (renderTransform[9] - posY)*(renderTransform[9] - posY) + // fStack_9c - fStack_dc
              (renderTransform[10] - posZ)*(renderTransform[10] - posZ) ) > g_MaxInterpolateDistSq )
        {
            // Use the raw currentTransform (copy its contents)
            renderTransform[0] = currentTransform[0];
            renderTransform[1] = currentTransform[1];
            renderTransform[2] = currentTransform[2];
            renderTransform[3] = currentTransform[3];
            renderTransform[4] = currentTransform[4];
            renderTransform[5] = currentTransform[5];
            renderTransform[6] = currentTransform[6];
            renderTransform[7] = currentTransform[7];
            renderTransform[8] = currentTransform[8];
            renderTransform[9] = currentTransform[9];
            renderTransform[10] = currentTransform[10];
            renderTransform[11] = currentTransform[11];
            renderTransform[12] = posX;
            renderTransform[13] = posY;
            renderTransform[14] = posZ;
            renderTransform[15] = w;
        } else {
            // Perform interpolation from previous to current (using separate function)
            InterpolateTransform(&renderTransform);
        }

        // Prepare a packet buffer (stack temporary)
        Matrix44 netTransform;
        netTransform[0] = 0.0f; netTransform[1] = 0.0f; netTransform[2] = 0.0f; netTransform[3] = 0.0f; // clear
        netTransform[4] = 0.0f; netTransform[5] = 0.0f; netTransform[6] = 0.0f; netTransform[7] = 0.0f;
        netTransform[8] = 0.0f; netTransform[9] = 0.0f; netTransform[10] = 0.0f; netTransform[11] = 0.0f;
        netTransform[12] = 0.0f; netTransform[13] = 0.0f; netTransform[14] = 0.0f; netTransform[15] = g_IdentityW;
        
        // Queue network update (m_networkObject? virtual call at +0x28)
        // This call uses a temporary buffer (auStack_50) and the renderTransform
        char packetBuffer[48]; // size unknown, likely smaller
        QueueNetworkUpdate(packetBuffer, &renderTransform);
        (**(void (__thiscall**)(char*))(thisPtr[0] + 0x28))(packetBuffer);
    }

    // Send message to network object if present
    int netObj = thisPtr[0x4c];   // +0x130
    if (netObj != 0) {
        (**(void (__thiscall**)(int, int))(*(int*)netObj + 0x40))(0xd444da9d, 0);
    }
}