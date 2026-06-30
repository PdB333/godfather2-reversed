// FUNC_NAME: PlayerSM::canProceedWithAction

extern int* FUN_00637f90(); // getGlobalStatePointer
extern int FUN_00636800();  // isSystemReady
extern void FUN_00633ac0(void* obj, int* stateData); // applyTransition

class PlayerSM {
public:
    int m_stateType;   // +0x00 (5 or 7 for specific states)
    int* m_stateInfo;  // +0x08 pointer to array of transition data

    int __thiscall canProceedWithAction(int* actionState) {
        // Check if current state (5 or 7) allows transitions and global pointer is valid
        if ((m_stateType == 5 || m_stateType == 7) &&
            (int* globalPtr = FUN_00637f90(); *globalPtr != 0)) {

            // If the desired action state is also 5 or 7, refresh global pointer
            if (*actionState == 5 || *actionState == 7) {
                FUN_00637f90();
            }

            if (FUN_00636800() != 0) {
                FUN_00633ac0(this, globalPtr);

                // Evaluate transition data: first element must be non-zero,
                // and if it equals 1, the second element must also be non-zero
                int firstVal = *m_stateInfo;   // m_stateInfo[0]
                int secondVal = m_stateInfo[1]; // m_stateInfo[1]

                if (firstVal != 0 && (firstVal != 1 || secondVal != 0)) {
                    return 1; // success
                }
                return 0; // failure
            }
        }
        return -1; // invalid state or not ready
    }
};