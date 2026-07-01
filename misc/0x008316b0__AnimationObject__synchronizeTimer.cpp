// FUNC_NAME: AnimationObject::synchronizeTimer

void __thiscall AnimationObject::synchronizeTimer(AnimationObject* this, TimerSyncEntry* entry)
{
    AnimationManager* manager = (AnimationManager*)gAnimationManager; // global pointer at 0x0112dba8
    beginTimerSync();           // FUN_008334a0 - initialize sync
    prepareTimerSync();         // FUN_00825120 - prepare sync state

    float totalTime = gBaseTimerValue; // global base time at 0x00d5780c

    if (entry != nullptr)
    {
        // Check if entry's node ID matches this object's ID
        if (entry->node->id == this->id) // +0x0c offset
        {
            totalTime -= entry->time; // subtract entry time
            setTimer(entry->node + 0x30, entry->time); // apply time to entry's node
        }
    }

    setTimer(this + 0x30, totalTime); // set this object's timer to adjusted total time

    manager->syncComplete = false; // clear sync flag at manager+0x1c
}