// FUNC_NAME: JobManager::clearJobs
// Function address: 0x005f8c90
// This function releases all jobs in the job manager, decrementing reference counts,
// removing nodes from linked lists, and freeing memory. Likely called from destructor or reset.

struct JobNode {
    void* m_head;       // +0x00: pointer to list head object
    JobNode* m_next;    // +0x04: next node in singly linked list
    class DynamicJob* m_job; // +0x08: pointer to job data
};

struct DynamicJob {
    uint16_t m_flags;   // +0x18: flags (bit 15 = active/pending)
    uint8_t m_refCount; // +0x1d: reference count (byte)
};

class JobManager {
public:
    void clearJobs(); // __thiscall

private:
    JobNode** m_jobNodes; // +0x2c: array of pointers to job nodes
    uint32_t m_jobCount;  // +0x30: number of job nodes
    int32_t m_something;  // +0x34: unknown (reset to zero)
};

// External helper functions (likely operator delete and array delete)
void FUN_009c8eb0(void* ptr);
void FUN_009c8f10(void* ptr);

void __thiscall JobManager::clearJobs()
{
    if (m_jobCount != 0) {
        for (uint32_t i = 0; i < m_jobCount; i++) {
            JobNode* node = m_jobNodes[i];
            if (node != nullptr) {
                // Decrement reference count and clear pending flag if needed
                if (node->m_head != nullptr) {
                    DynamicJob* job = node->m_job;
                    job->m_refCount--;
                    if (job->m_refCount == 0) {
                        job->m_flags &= ~0x8000; // clear bit 15 (active flag)
                    }
                }

                // Remove node from its linked list (singly linked, head stored in node->m_head)
                void* listHead = node->m_head;
                if (listHead != nullptr) {
                    // The list head object has a pointer to the first node at offset +4
                    JobNode* firstNode = *(JobNode**)((char*)listHead + 4);
                    if (firstNode == node) {
                        // Node was the first in list; update head's next pointer
                        *(JobNode**)((char*)listHead + 4) = node->m_next;
                    } else {
                        // Traverse list to find and unlink the node
                        JobNode* prev = firstNode;
                        JobNode* curr = prev->m_next;
                        while (curr != node) {
                            prev = curr;
                            curr = curr->m_next;
                        }
                        prev->m_next = node->m_next;
                    }
                }

                // Free the node itself
                FUN_009c8eb0(node);
            }
        }
        m_jobCount = 0;
    }

    // Free the array of node pointers and reset members
    FUN_009c8f10(m_jobNodes);
    m_jobNodes = nullptr;
    m_something = 0;
}