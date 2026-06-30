// FUNC_NAME: ContextManager::pushAndProcessContext
// Address: 0x00619a50
// This function stores context parameters into global state, checks if the context manager's vtable is valid,
// releases any previously allocated context objects, then triggers processing of the new context.

#include <cstdint>

// Forward declarations for helper functions (these would be defined elsewhere)
void releaseObject(void* ptr);
void processContext(int32_t arg1, int32_t arg2, float* param);

// Global state for context manager (offsets relative to 0x01127760 assumed)
extern int32_t* PTR_PTR_01127760; // vtable pointer for context manager
extern int32_t DAT_012058e8;      // current vtable to compare
extern int32_t DAT_01127774;      // some context ID or pointer
extern int32_t DAT_01127884;      // another context value

// These are the storage slots for context parameters (offsets around 0xA8-0xD4)
extern int32_t _DAT_01127808;   // param_2 stored here
extern int32_t _DAT_0112781c;   // param_1 stored here
extern float   _DAT_01127830;   // from XMM0 (float)
extern int32_t _DAT_01127834;   // param_3 stored here
extern int32_t _DAT_01127838;   // param_4 stored here
extern int32_t _DAT_0112783c;   // param_5 stored here
extern int32_t _DAT_01127814;   // from EAX
extern int32_t _DAT_01127818;   // from ESI

// Context object slots that may need to be freed (offsets within the context area)
extern void* _DAT_01127858;     // context object 1
extern void* _DAT_0112785c;     // context object 2
extern void* _DAT_01127860;     // context object 3
extern void* _DAT_01127870;     // context object 4

// Additional context data used by processContext
extern int32_t DAT_01127864;    // some parameter for processContext

class ContextManager
{
public:
    // push parameters to global context and process if manager is ready
    static void pushAndProcessContext(
        int32_t param1,      // arg1
        int32_t param2,      // arg2
        int32_t param3,      // arg3
        int32_t param4,      // arg4
        int32_t param5,      // arg5
        int32_t eaxParam,    // from EAX register
        int32_t esiParam,    // from ESI register
        float   xmm0Param    // from XMM0 register
    )
    {
        // Store parameters into global context slots
        _DAT_01127834 = param3;
        _DAT_01127838 = param4;
        _DAT_0112781c = param1;
        _DAT_01127808 = param2;
        _DAT_0112783c = param5;
        _DAT_01127814 = eaxParam;
        _DAT_01127818 = esiParam;
        _DAT_01127830 = xmm0Param;

        // Check if the context manager's vtable is still valid
        // and the context state matches (likely verifying object type)
        if (DAT_012058e8 == (int32_t)&PTR_PTR_01127760 && DAT_01127774 == DAT_01127884)
        {
            // Free any existing objects in the context slots
            if (_DAT_01127858 != 0)
            {
                releaseObject(_DAT_01127858);
            }
            if (_DAT_0112785c != 0)
            {
                releaseObject(_DAT_0112785c);
            }
            if (_DAT_01127860 != 0)
            {
                releaseObject(_DAT_01127860);
            }
            if (_DAT_01127870 != 0)
            {
                releaseObject(_DAT_01127870);
            }

            // Trigger processing of the new context
            processContext(DAT_01127774, DAT_01127864, &_DAT_01127830);
        }
    }
};