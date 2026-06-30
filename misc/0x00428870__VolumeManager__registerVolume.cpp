// FUNC_NAME: VolumeManager::registerVolume

struct SoundVolume {
    float minBounds[4];  // 0x00
    float maxBounds[4];  // 0x10
    float volume;        // 0x20
    uint8_t unkFlag;     // 0x24
    float unkNan;        // 0x28
    // padding? maybe more fields
    float id;            // 0x40
    float refCount;      // 0x44 (actually used as int)
    float* linkedList;   // 0x48 (pointer to list)
    float listSize;      // 0x4C (count of items)
};

SoundVolume g_soundVolumePool[128]; // DAT_012053cc

// Globals (constants)
float g_smoothingFactor;    // DAT_00e2cd54
float g_minExtent;         // DAT_00e2b1a4
float g_minVolume;         // DAT_00e2e644

// Fastcall: first argument in EAX (float id), param_1 = minBounds, param_2 = maxBounds
void __fastcall VolumeManager::registerVolume(float id, float* minBounds, float* maxBounds)
{
    // First pass: find existing entry with matching ID
    for (int i = 0; i < 128; i++) {
        SoundVolume* volume = &g_soundVolumePool[i];
        if (volume->id == id) {
            volume->refCount = (float)((int)volume->refCount + 1);
            return;
        }
    }

    // Second pass: find empty slot (id == 0.0)
    for (int i = 0; i < 128; i++) {
        SoundVolume* volume = &g_soundVolumePool[i];
        if (volume->id == 0.0f) {
            volume->id = id;
            volume->unkFlag = 0;        // set byte at offset +0x24
            volume->unkNan = -std::numeric_limits<float>::quiet_NaN(); // -NAN
            // Clear linked list entries
            if (volume->listSize != 0.0f) {
                int* list = (int*)(int)volume->linkedList; // cast pointer to int*
                int count = (int)volume->listSize;
                for (int j = 0; j < count; j++) {
                    list[10 + j * 20] = 0xFFFFFFFF; // clear 0x28 + j*0x50 bytes? Actually offset 0x28 + j*0x50
                }
            }
            // Initialize min/max bounds
            volume->minBounds[0] = minBounds[0];
            volume->minBounds[1] = minBounds[1];
            volume->minBounds[2] = minBounds[2];
            volume->minBounds[3] = minBounds[3];
            volume->maxBounds[0] = maxBounds[0];
            volume->maxBounds[1] = maxBounds[1];
            volume->maxBounds[2] = maxBounds[2];
            volume->maxBounds[3] = maxBounds[3];
            // Set other fields
            volume->unkNan = 0.0f; // reset after?
            volume->refCount = 1.4013e-45f; // smallest positive float
            // Compute and clamp extents
            float dx = volume->maxBounds[0] - volume->minBounds[0];
            if (dx < g_minExtent) {
                float adjust = (g_minExtent - dx) * g_smoothingFactor;
                volume->minBounds[0] -= adjust;
                volume->maxBounds[0] += adjust;
            }
            float dy = volume->maxBounds[1] - volume->minBounds[1];
            if (dy < g_minExtent) {
                float adjust = (g_minExtent - dy) * g_smoothingFactor;
                volume->minBounds[1] -= adjust;
                volume->maxBounds[1] += adjust;
            }
            float dz = volume->maxBounds[2] - volume->minBounds[2];
            if (dz < g_minExtent) {
                float adjust = (g_minExtent - dz) * g_smoothingFactor;
                volume->minBounds[2] -= adjust;
                volume->maxBounds[2] += adjust;
            }
            // Compute volume (product of dimensions)
            float vol = (volume->maxBounds[2] - volume->minBounds[2]) * 
                        (volume->maxBounds[1] - volume->minBounds[1]) * 
                        (volume->maxBounds[0] - volume->minBounds[0]);
            volume->volume = vol;
            if (vol < g_minVolume) {
                volume->id = 0.0f; // discard too small volume
            }
            return;
        }
    }
}