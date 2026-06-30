// FUNC_NAME: JobManager::setCurrentJob
// Function address: 0x0056f740
// Replaces the current head of the job list with a new node, managing reference counts and list cleanup.
// The class has a member at +0x40 pointing to the current head node.
// Node structure: +0x00 prev, +0x04 next, +0x08 activeFlag, +0x09 refCount
// Global list descriptor at DAT_0120558c: +0x00 head, +0x04 tail, +0x08 ? , +0x0c ?

void __fastcall JobManager::setCurrentJob(JobNode* newNode)
{
    JobNode* oldHead;
    JobNode* prev;
    JobNode* next;
    int* listDesc;

    // Increment reference count on the new node
    if (newNode != 0) {
        newNode->refCount++;
    }

    oldHead = this->currentHead; // +0x40
    if (oldHead != 0) {
        oldHead->refCount--;

        // If the old head is not active and has no remaining references, remove it from the global list
        if (oldHead->activeFlag == 0 && oldHead->refCount == 0) {
            prev = oldHead->prev;
            next = oldHead->next;

            // Unlink from the doubly linked list
            if (prev != 0) {
                prev->next = next;
            }
            listDesc = DAT_0120558c;
            if (next != 0) {
                next->prev = prev;
                this->currentHead = newNode;
                return;
            }
            // If next is null, update tail pointer
            *(int*)(listDesc + 8) = *(int*)(listDesc + 4); // tail? -> something
            *(int*)(listDesc + 4) = prev; // new tail
            if (prev == 0) {
                *(int*)(listDesc + 8) = *(int*)(listDesc + 0xc); // reset tail? 
            }
        }
    }

    this->currentHead = newNode;
}