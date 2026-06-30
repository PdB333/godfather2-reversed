// FUNC_NAME: JobQueue::setCurrentJob
void __fastcall JobQueue::setCurrentJob(int this, Job* newJob)
{
    // Increment reference count of new job
    if (newJob != nullptr) {
        newJob->refCount++;
    }

    // Get current job from this->currentJob (+0x44)
    Job* oldJob = *(Job**)(this + 0x44);

    if (oldJob != nullptr) {
        // Decrement reference count of old job
        oldJob->refCount--;

        // If old job is not flagged as persistent and reference count reaches zero,
        // remove it from the global job list
        if (oldJob->flags == 0 && oldJob->refCount == 0) {
            Job* prev = oldJob->prev;   // +0
            Job* next = oldJob->next;   // +4

            // Standard doubly-linked list unlink
            if (prev != nullptr) {
                prev->next = next;
            }
            if (next != nullptr) {
                next->prev = prev;
            }

            // Update global list head/tail (DAT_0120555c)
            // Global structure: +0 = head, +4 = tail, +8 = sentinel.prev, +0xC = sentinel.next
            int* globalList = (int*)0x0120555c;
            globalList[2] = globalList[1]; // sentinel.prev = tail
            globalList[1] = (int)prev;     // tail = prev

            if (prev == nullptr) {
                // List is now empty, update sentinel to point to itself
                globalList[2] = globalList[3];
            }
        }
    }

    // Set the new current job
    *(Job**)(this + 0x44) = newJob;
}