// FUNC_NAME: ParticleManager::updateParticles

#pragma pack(push, 1)
struct ParticleEntry {
    // +0x00: XYZ components (maybe position or velocity)
    int x;          // +0x00
    int y;          // +0x04
    int z;          // +0x08
    int w;          // +0x0C
    int timer;      // +0x10 (frames remaining?)
    int minRand;    // +0x14 (minimum random value)
    int maxRand;    // +0x18 (maximum random value)
    // padding?
    char field_1C[0x10]; // +0x1C to +0x2B
    char flagActive;     // +0x2C (0 = inactive, 1 = active)
    char flagVisible;    // +0x2D (0 = not visible, 1 = visible)
    // total 0x30
};
#pragma pack(pop)

class ParticleManager {
public:
    // +0x50: global active flag
    char m_bGlobalActive;
    // +0x51: (probably padding)
    char m_bSpawnFlag;    // +0x52 (set to zero when global becomes active)
    // +0x54: count of particles
    int m_nParticleCount;
    // +0x58: pointer to array of ParticleEntry (size m_nParticleCount)
    ParticleEntry* m_pParticles;

    // param_3 likely a pointer to some game context (e.g., FrameTimeData)
    // param_4 unused
    // param_5 base position (array of 3 floats)
    // param_6 time scale (delta time)
    void __thiscall updateParticles(int* pCounter, int* pContext, int unused, float* pBasePos, float timeScale);
};

void __thiscall ParticleManager::updateParticles(int* pCounter, int* pContext, int unused, float* pBasePos, float timeScale) {
    int i;
    int index = 0;
    ParticleEntry* pEntry;

    if (m_bGlobalActive != 0) {
        // Global active flag is set, skip spawning but still process timer reset?
        if (m_bSpawnFlag != 0) {
            m_bSpawnFlag = 0;
        }
        i = 0;
        if (m_nParticleCount > 0) {
            int offset = 0;
            do {
                pEntry = (ParticleEntry*)((int)m_pParticles + offset);
                // If particle has any non-zero position/velocity component and not already visible
                if ((pEntry->x != 0 || pEntry->y != 0 || pEntry->z != 0 || pEntry->w != 0) &&
                    pEntry->flagVisible == 0) {
                    // Some callback per particle (maybe spawn effect)
                    FUN_006a4310(i, pContext, unused);
                }
                i++;
                offset += 0x30;
            } while (i < m_nParticleCount);
        }
        m_bGlobalActive = 0;
        return;
    }

    // Normal update path
    i = 0;
    index = 0;
    if (m_nParticleCount > 0) {
        do {
            pEntry = &m_pParticles[i];
            // Check if particle has any non-zero position component and is visible and timer == 0
            if ((pEntry->x != 0 || pEntry->y != 0 || pEntry->z != 0 || pEntry->w != 0) &&
                pEntry->flagVisible != 0 && pEntry->timer == 0) {
                int contextVal = *(int*)(pContext + 8); // probably a distance or time threshold
                int minVal = pEntry->minRand;

                // Check if particle's minRand is less than contextVal, and maxRand condition
                if (pEntry->maxRand < minVal) {
                    if (contextVal < minVal) goto checkBounds;
                } else if (minVal <= contextVal) {
checkBounds:
                    if (contextVal <= pEntry->maxRand) {
                        // Reset flags
                        pEntry->flagVisible = 0;
                        pEntry->flagActive = 0;
                        // Allocate spawn data (returns handle)
                        int spawnData = FUN_006a42c0((int)&m_pParticles[i] + 0x30*i? Actually passes pointer to entry?
                        // Wait, the code does FUN_006a42c0(*(int*)(param_1 + 0x58) + iVar5)
                        // So it passes the address of the particle entry? No, it passes the base pointer plus offset.
                        // Let's assume it returns a handle to a new effect object.
                        int handle = FUN_006a42c0((int)pEntry);
                        pEntry->timer = handle; // store handle as timer? That seems odd.
                        if (handle != 0) {
                            (*pCounter)++;
                            // Random number generation for position variation
                            float randFloat1 = *(float*)(DAT_010c2680 + (DAT_010c2678 & DAT_012054b4) * 4) * DAT_00d5d70c;
                            DAT_012054b4++;
                            double dblRand1 = (double)randFloat1;
                            FUN_00b99fcb(); // maybe seeding? Not clear.
                            float local4 = (float)dblRand1;
                            double dblRand2 = (double)randFloat1;
                            FUN_00b99e20();
                            float offsetX = (float)dblRand2 * timeScale + pBasePos[0];
                            float offsetY = pBasePos[1];
                            float offsetZ = local4 * timeScale + pBasePos[2];
                            // Set position of the effect object
                            FUN_005e6580(pEntry->timer, &offsetX); // likely setPosition
                            // Activate the effect (e.g., set visible)
                            FUN_005e67c0(pEntry->timer, 0x80); // maybe setFlag(0x80)
                        }
                        // Callback for particle
                        FUN_006a4310(index, pContext, unused);
                    }
                }
            }
            index++;
            i++;
        } while (index < m_nParticleCount);
    }
    return;
}