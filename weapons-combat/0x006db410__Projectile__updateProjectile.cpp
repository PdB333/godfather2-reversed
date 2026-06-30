// FUNC_NAME: Projectile::updateProjectile

// Function address: 0x006db410
// Role: Updates projectile state, handles launch and transition from state 2 to 3 (e.g., travel to return/expire).
// Uses global time delta (_DAT_00d5780c) and a per‑weapon data table (_DAT_012233a0).

class Projectile
{
public:
    // state machine: 1 = initial, 2 = traveling, 3 = returning/expiring?
    enum State { STATE_INITIAL = 1, STATE_TRAVELING = 2, STATE_RETURNING = 3 };

    // Called each frame with target position and weapon index
    void updateProjectile(float* targetPos, int weaponIndex);

private:
    // Offsets (relative to this)
    // +0x08 : unknown byte (cleared on launch)
    // +0x110-0x11c : position (float[4]) – current world position
    // +0x170-0x17c : target/destination position (float[4]) – for path following
    // +0x1a0 : byte flag (set to 1 on launch)
    // +0x1a4 : state (int)
    // +0x1a8 : int (cleared on launch)
    // +0x1ac : float – duration (seconds) for state 2→3 transition
    // +0x1b0 : float – elapsed timer for state 2

    void startProjectile(int index);   // calls FUN_006d68e0
    void activateProjectile();          // calls FUN_006db310
};

// Global time delta (e.g., from frame update)
extern float g_deltaTime; // _DAT_00d5780c

// Array of weapon data pointers (at +0x04 in the table)
extern int* g_weaponDataTable; // _DAT_012233a0, offset 4 used to index

void Projectile::updateProjectile(float* targetPos, int weaponIndex)
{
    float fVar1, fVar2, fVar3, fVar5;
    int iVar4;

    // State 2: traveling – check if time is up, transition to state 3
    if (m_state == STATE_TRAVELING)
    {
        // Original: fVar5 = g_deltaTime - (m_timer / m_duration)
        // Then: m_timer = fVar5 * m_duration
        // Equivalent to: m_timer = g_deltaTime * m_duration - m_timer
        // But careful: the subtraction is (g_deltaTime - timer/duration) * duration = g_deltaTime*duration - timer
        // Actually it's just setting timer to remaining time scaled? Simplifies to:
        // timer = g_deltaTime * m_duration - m_timer
        // But the original does: fVar5 = g_deltaTime - (timer / duration); then timer = fVar5 * duration.
        // So new timer = g_deltaTime*duration - timer. That's odd; maybe it's a countdown.
        m_timer = (g_deltaTime - (m_timer / m_duration)) * m_duration;
        m_state = STATE_RETURNING;
        return;
    }

    // If not state 3, perform initial launch (state 1 or other)
    if (m_state != STATE_RETURNING)
    {
        // Retrieve weapon-specific data pointer (offset 0x1f30 subtracted? This looks like a base address adjustment)
        iVar4 = g_weaponDataTable[weaponIndex];
        if (iVar4 != 0)
            iVar4 -= 0x1f30;    // adjust to actual projectile data structure

        // Start the projectile (e.g., initialize physics, load effects)
        startProjectile(iVar4);

        // Store current position from targetPos (first 4 floats)
        m_position[0] = targetPos[0];
        m_position[1] = targetPos[1];
        m_position[2] = targetPos[2];
        m_position[3] = targetPos[3];  // w component (unused or alignment)

        // Set target destination – same X/Z, but Y offset by gravity (g_deltaTime used as gravity magnitude here)
        m_target[0] = targetPos[0] + 0.0f;
        m_target[1] = targetPos[1] + g_deltaTime;
        m_target[2] = targetPos[2] + 0.0f;
        m_target[3] = 0.0f;

        // Activate projectile (e.g., set motion, attach to scene)
        activateProjectile();

        // Mark as active; clear unknown state byte
        m_activeFlag = 1;
        m_unknownByte8 = 0;

        // Reset timer and state to initial (state 1)
        m_timerReset = 0;
        m_state = STATE_INITIAL;
    }
    // If state == 3, do nothing (return)
}