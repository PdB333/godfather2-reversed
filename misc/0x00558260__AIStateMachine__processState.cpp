// FUNC_NAME: AIStateMachine::processState
// Address: 0x00558260
// Role: Evaluates state type, delegates to specialized handler if type is 2, 3, or 4.
// Uses a vtable-based query function at (this->m_pController + 0x2c) to retrieve default query parameters.

class AIStateMachine {
public:
    // m_pController at +0x54, points to an object with a virtual table.
    // The vtable entry at offset 0x2c is likely a "getDefaultQuery" or "getQueryForType".
    // param_2: Usually an enable/active flag (non-zero means active).
    // param_3: Output pointer for type; if NULL, uses local default (type=1, param=8).
    // Returns 0 if param_2 is 0 or type is not 2,3,4;
    // otherwise delegates to FUN_00558130 and returns its result.
    int __thiscall processState(int param_2, int *param_3) {
        if (param_2 != 0) {
            int localQuery[2] = {1, 8}; // local_10: default query {type, value}
            if (param_3 == nullptr) {
                // Call virtual function on m_pController to fill query
                (*(code **)(*(int *)(this + 0x54) + 0x2c))(localQuery);
                param_3 = localQuery;
            }
            int type = *param_3;
            if (type == 2 || type == 3 || type == 4) {
                return FUN_00558130(this, param_2, param_3);
            }
        }
        return 0;
    }
};