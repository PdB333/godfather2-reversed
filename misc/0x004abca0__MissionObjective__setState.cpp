// FUNC_NAME: MissionObjective::setState
// Function address: 0x004abca0
// Role: Sets a state field and triggers an update if a related object is present and not active.
// This appears to be a method of a mission objective or task object in the EA EARS engine.

class MissionObjective {
public:
    // Sets the objective state to the given value.
    // If there is a related object (mRelatedObject) and its active flag is zero, calls update().
    void setState(int state) {
        // +0x3c: mState - the state/value field
        mState = state;

        // +0x1c: mRelatedObject - pointer to another object (e.g., a controller or behavior)
        // +0x44 in that object: mIsActive - a byte flag indicating if the object is active
        if (mRelatedObject != nullptr && mRelatedObject->mIsActive == 0) {
            update(); // FUN_004abd20: likely triggers a re-evaluation or state change
        }
    }

private:
    // Hidden struct definitions for offsets
    struct RelatedObject {
        char _pad0x00[0x44]; // padding to reach +0x44
        char mIsActive;       // +0x44: flag byte, 0 = inactive, non-zero = active
    };

    RelatedObject* mRelatedObject; // +0x1c: pointer to related object
    int mState;                     // +0x3c: state value

    void update(); // +0x004abd20: internal update method
};