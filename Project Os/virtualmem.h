#include <queue>
#include <iostream>

// Memory config
#define PAGE_SIZE 4096
#define VIRTUAL_MEM_SIZE 65536
#define PHYSICAL_MEM_SIZE 32768

//calculate num of pages and frames
const int NUM_PAGES = VIRTUAL_MEM_SIZE / PAGE_SIZE;
const int NUM_FRAMES = PHYSICAL_MEM_SIZE / PAGE_SIZE;

//page table entry
struct PageEntry {
    bool val = false;
    int framNum = -1;
    bool dir = false;
};

//Virtual memory  vlass for process page table
class VirtMemory {
    public:
        PageEntry pagetable [NUM_PAGES];

};

//virtual memory structure
struct Frame {
    int pagNum = -1;
    bool taken = false;
};

//replacement policy
std::queue<int> fifo;

//function for fault page handler
void handleFaultPage(int pageNum, Frame tableFram[NUM_FRAMES], VirtMemory& vm){
    int frameUse = -1;

    for(int i = 0; i < NUM_FRAMES; i++){
        if(!tableFram[i].taken) {
            frameUse = i;
            break;
        }
    }

    if(frameUse == -1){
        if(fifo.empty()){
            std::cerr << "ERROR: No frame for eviction and FIFO is empty\n";
            return;
        }

        frameUse = fifo.front();
        fifo.pop();

        int old = tableFram[frameUse].pagNum;
        vm.pagetable[old].val = false;
        std::cout << "Evict Page " << old << " from frame " << frameUse << "\n";
    }

    tableFram[frameUse] = {pageNum, true};
    vm.pagetable[pageNum].val = true;
    vm.pagetable[pageNum].framNum = frameUse;

    fifo.push(frameUse);
    std::cout << "Loaded page " << pageNum << " into frame " << frameUse << "\n";


}

//translate virtual address to physical address
int translation(int virtAdd, Frame tableFram[NUM_FRAMES], VirtMemory& vm) {
    int pageNum = virtAdd / PAGE_SIZE;
    int offset = virtAdd % PAGE_SIZE;

    if(!vm.pagetable[pageNum].val){
        std::cout << "PAGEFAULT: PAGE " << pageNum << " NOT IN MEMORY!\n";
        handleFaultPage(pageNum, tableFram, vm);
    }

    int fram = vm.pagetable[pageNum].framNum;
    return fram * PAGE_SIZE + offset;
}