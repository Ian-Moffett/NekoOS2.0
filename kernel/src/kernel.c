#include <stdint.h>
#include <stddef.h>
#include "../stivale2.h"

// Kernel stack, this will be allocated in BSS.
static uint8_t kernel_stack[8000];


void* get_tag(struct stivale2_struct* stivale2_struct, uint64_t id) {
    struct stivale2_tag* curTag = (void*)stivale2_struct->tags;

    while (1) {
        if (!(curTag)) {
            // End.
            return NULL;
        }

        if (curTag->identifier == id) {
            return curTag;
        }

        curTag = (void*)curTag->next;
    }
}


// Terminal tag.
static struct stivale2_header_tag_terminal terminal_tag = {
    .tag = {
        .identifier = STIVALE2_HEADER_TAG_TERMINAL_ID,
        .next = 0
    },

    .flags = 0
};


// Framebuffer tag.
static struct stivale2_header_tag_framebuffer lfb_tag = {
    .tag = {
        .identifier = STIVALE2_HEADER_TAG_FRAMEBUFFER_ID,
        .next = (uint64_t)&terminal_tag
    },

    .framebuffer_width = 0,
    .framebuffer_height = 0,
    .framebuffer_bpp = 0
};


// This will be a header inside the ELF.
__attribute__((section(".stivale2hdr"), used)) static struct stivale2_header stivale_hdr = {
    .entry_point = 0,
    .stack = (uintptr_t)(kernel_stack + sizeof(kernel_stack)),
    .flags = (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4),
    .tags = (uintptr_t)&lfb_tag
};


// Kernels entry point.
void _start(struct stivale2_struct* ss) {
    while (1) {
        __asm__ __volatile__("hlt");
    }
}
