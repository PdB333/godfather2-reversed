// FUNC_NAME: AnimPlayer::processMessage
// Function at 0x00768d70: Handles animation messages (play, set speed, and manages animation queue)

int __thiscall AnimPlayer::processMessage(AnimPlayer *this, int msgData, float timeScale, int someFlag, unsigned int msgId, int userData)
{
    int *pOwner; // ptr to owner object at this+0x5C
    int *pNextPtr; // linked list next pointer
    int result;
    int currentAnim;
    int newAnim;
    int temp;

    // Handle specific message IDs
    if (msgId != 0x23) {
        if (msgId == 0x24) {
            // Set animation speed
            pOwner = (int *)this->owner; // this+0x5C
            if (*(int *)(pOwner[0x24cc/4] + 0x24cc) != 0) { // offset 0x24cc from owner
                currentAnim = *(int *)(pOwner[0x24cc/4] + 0x24cc) - 0x48; // assume 0x48 is size of anim node
                if (currentAnim != 0) {
                    // Call to set animation speed (global timeScale factor)
                    FUN_00470230(currentAnim, timeScale * DAT_00d636b8, 0);
                }
            }
            return 1;
        }
        // Default: delegate to base class handler
        return FUN_0073e610(msgData, timeScale, someFlag, msgId, userData);
    }

    // msgId == 0x23: Start/play animation
    pOwner = (int *)this->owner; // this+0x5C
    result = 0;
    if ((this->currentAnim != 0) && (this->currentAnim != 0x48)) {
        // Get a scene node or object and attach something
        result = FUN_00701050(); // Get some root/controller
        result = FUN_00715ee0(result); // Add child or create component
    }
    // Call vtable function at offset 0x2c on result
    (*(code **)(*result + 0x2c))(result, 1, 1, 0, pOwner[0x76f/4], 0x3f800000); // play with speed 1.0

    // Manage linked list of animation states (queue of current animation)
    currentAnim = pOwner[0x1d3/4]; // offset 0x1d3 from owner
    pNextPtr = pOwner + 0x1d3/4; // pointer to next field
    if ((currentAnim != 0) && (currentAnim != 0x48)) {
        if (this->currentAnim == 0) {
            temp = 0;
        } else {
            temp = this->currentAnim - 0x48;
        }
        if (currentAnim - 0x48 != temp) {
            // Call some cleanup function on current animation
            (*(code **)(*currentAnim + 0x260))(); // likely anim stop or unlink
        }
    }

    // Update linked list: remove old, insert new
    if (this->currentAnim == 0) {
        newAnim = 0;
    } else {
        newAnim = this->currentAnim - 0x48;
    }
    if (newAnim == 0) {
        newAnim = 0;
    } else {
        newAnim = newAnim + 0x48;
    }
    if (*pNextPtr != newAnim) {
        if (*pNextPtr != 0) {
            FUN_004daf90(pNextPtr); // remove from list
        }
        *pNextPtr = newAnim;
        if (newAnim != 0) {
            pOwner[0x1d4/4] = *(int *)(newAnim + 4); // set prev pointer
            *(int **)(newAnim + 4) = pNextPtr; // link back
            return 1;
        }
    }
    return 1;
}