#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <alloc_table.h>
#include <list.h>

enum MemoryType
{
    FreeMemory = 1,  // 可用内存 EfiConventionalMemory EfiBootServices(Code/Data) EfiLoader(Code/Data) EfiReservedMemoryType
    ReservedMemory,  // 保留(不可用) EfiRuntimeServices(Code/Data) EfiMemoryMappedIO EfiMemoryMappedIOPortSpace EfiPalCode
    ACPIMemory,      // ACPI可回收内存 EfiACPIReclaimMemory
    ACPIMemoryNVS,   // ACPI NVS内存  EfiACPIMemoryNVS
    UnuseableMemory, // 不可用的内存 EfiUnusableMemory 
    MaxMemoryType,   // (EfiMaxMemoryType)
};

struct MEMDESC
{
    struct ALLOCATE_TABLE FreeMemDescTable;
};


struct MemoryBlock
{
    struct ListNode Free;
};

struct MemoryDesc
{
    UINTN BlockSize;
    UINTN Blocks;
    struct List FreeBlockList;
};

struct Zone
{
    struct MemoryDesc* Desc;
    UINTN Cnt;
    BOOL Large;
};

#define MaxAllocateSize 524288
#define NumberOfMemoryBlocks 13
extern struct MemoryDesc KernelMemoryBlock[NumberOfMemoryBlocks]; // 128,256,512,1024,2048,4096,8192,16384,32768,65536,131072 ,262144,524288

PUBLIC void init_memory();
/**
 * @brief 分配指定页数
 * @param NumberOfPages 要分配的内存页数
 * @return 分配的内存页起始地址
*/
PUBLIC void* AllocPage(int NumberOfPages);

/**
 * @brief 释放指定页数
 * @param Addr 释放内存页的起始地址(对齐到2MB边界)
 * @param NumberOfPages 要释放的内存页数
 * @return 分配的内存页起始地址
*/
PUBLIC void FreePage(void* Addr,int NumberOfPages);

PUBLIC void* kmalloc(UINTN Size);
PUBLIC void kfree(void* Addr);

#endif