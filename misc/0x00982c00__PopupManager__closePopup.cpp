// FUNC_NAME: PopupManager::closePopup
// Address: 0x00982c00
// Role: Handles closing the current popup on the stack, invoking its close callback,
//       and transitioning the state machine to 'popupClosed' or 'allPopupsClosed' states.

#include <cstdint>

// Forward declarations (assumed types, adjust based on actual game headers)
struct Popup; // +0x14: void (*m_closeCallback)(void*, Popup*, void*);

// Structure for the state machine (simplified)
struct PopupStateMachine {
    // ... internal state
};

// External functions (assumed from EA EARS engine)
extern void gLogger_Log(const char* message, int arg1, const char* data, int arg3);
extern void Fsm_PushState(PopupStateMachine* fsm, void* stateFunc, bool flag);

// Structure for the popup manager (offsets documented)
struct PopupManager {
    void** vtable;                        // +0x00
    // ... unknown fields up to +0x4C
    Popup* m_popupStack[16];              // +0x4C (approximate, size unknown)
    int32_t m_popupStackCount;            // +0x6C
    int32_t m_modalPopupCount;            // +0x68
    int32_t m_blockingPopupCount;         // +0x7C
    // ... other members
};

// Labels for state functions (actual addresses in the binary)
extern void state_PopupClosed(void);
extern void state_AllPopupsClosed(void);

void __thiscall PopupManager::closePopup(void* param2, void* param3)
{
    gLogger_Log("ClosePopup", 0, &DAT_00d90628, 0);

    // Get the current popup stack count and the top popup
    int stackCount = this->m_popupStackCount;
    Popup* topPopup = this->m_popupStack[stackCount];

    // Decrement the stack count
    this->m_popupStackCount = stackCount - 1;

    // Call the popup's close callback if it exists
    if (topPopup->m_closeCallback != nullptr) {
        topPopup->m_closeCallback(param2, topPopup, param3);
    }

    // If the stack is now empty, transition to 'popupClosed' state
    bool isStackEmpty = (this->m_popupStackCount == 0);
    if (isStackEmpty) {
        // State machine is embedded at offset +4
        Fsm_PushState(reinterpret_cast<PopupStateMachine*>(this + 4), &state_PopupClosed, 1);
        // Re-evaluate stack emptiness (the state push might have changed it)
        isStackEmpty = (this->m_popupStackCount == 0);
    }

    // If the stack is empty and no blocking or modal popups remain, we are fully closed
    if (isStackEmpty && (this->m_blockingPopupCount == 0) && (this->m_modalPopupCount == 0)) {
        Fsm_PushState(reinterpret_cast<PopupStateMachine*>(this + 4), &state_AllPopupsClosed, 1);
        // Call virtual function at vtable offset 0x2C (onAllPopupsClosed)
        (*(void(**)(void))(*this->vtable + 0x2C))();
    }
}