// FUNC_NAME: ActionController::update
#include <cstdint>

// Global variables (to be defined elsewhere)
extern float g_fActionThreshold;      // 0x00e44598
extern float g_fSomeGlobalValue;      // 0x00e2eff4
extern int32_t g_mutex;               // 0x00e2e4c8 (mutex location)

// External functions (to be defined elsewhere)
void lockMutex(int32_t* mutex);      // FUN_00ab4db0
void unlockMutex();                  // FUN_00ab4e70
bool checkCondition();               // FUN_00458a80
void audioStart();                   // FUN_00c9eac0
void audioSetParam(int32_t arg1, int32_t arg2); // FUN_00c9cd40
int32_t audioGetValue();             // FUN_00c9eb20
void audioStop();                    // FUN_00c9eae0
void advance(int32_t arg1, float dt); // FUN_004584f0

class ActionController {
public:
    int32_t m_actionState;          // +0x170: 1=playing, 2=stopped, 3=?
    int32_t m_subState;             // +0x16c: 0=idle, 1=ready, 2=active
    int32_t m_flag1;                // +0x164: reset flag
    int32_t m_audioValue;           // +0x168: value from audio system
    int32_t m_someFlag;             // +0x13c: some reset flag
    int32_t* m_ptr1;                // +0x138: pointer to external buffer
    float   m_someGlobal;           // +0x158: assigned from global
    int32_t m_flag2;                // +0x14c: another reset flag
    int32_t* m_ptr2;                // +0x148: pointer to external buffer
    bool    m_active;               // +0xe0: active flag (0/1)

    // Constructor/destructor assumed
};

void ActionController::update(float dt) {
    lockMutex(&g_mutex);

    if (dt < g_fActionThreshold) {
        // State transition
        if (m_actionState == 1 || m_actionState == 3) {
            m_actionState = 2;
        }

        if (m_subState == 1) {
            bool condition = checkCondition();
            if (!condition) {
                // Reset all states
                m_flag1 = 0;
                m_audioValue = 0;
                m_someFlag = 0;
                if (m_ptr1 != nullptr) {
                    *m_ptr1 = 0;
                }
                m_subState = 0;
            } else {
                // Prepare audio system
                audioStart();
                audioSetParam(1, 0);
                m_audioValue = audioGetValue();
                audioStop();
                m_subState = 2;
            }
            m_someGlobal = g_fSomeGlobalValue;
        }

        // Reset pointers and flag
        m_flag2 = 0;
        if (m_ptr2 != nullptr) {
            *m_ptr2 = 0;
        }
        m_active = false;

        unlockMutex();
        return;
    }

    // dt >= threshold case
    if (m_subState != 0) {
        advance(0, dt);
        m_active = true;
    }

    unlockMutex();
}