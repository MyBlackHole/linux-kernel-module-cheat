#ifndef COMMON_ARCH_H
#define COMMON_ARCH_H

#define ASSERT_EQ(reg, const) \
    push %rax; \
    push %rbx; \
    mov reg, %rax; \
    mov const, %rbx; \
    cmp %rax, %rbx; \
    ASSERT(je); \
    pop %rbx; \
    pop %rax; \
;

# TODO
##define ASSERT_MEMCMP(s1, s2, n) \
#    MEMCMP(s1, s2, n); \
#    ASSERT_EQ(x0, 0); \
#;

/* Program entry point.
 *
 * Return with EXIT.
 *
 * Basically implements an x86_64 prologue:
 *
 * - save callee saved registers
 *   x86_64 explained at: https://stackoverflow.com/questions/18024672/what-registers-are-preserved-through-a-linux-x86-64-function-call/55207335#55207335
 * - save register arguments for later usage
 */
#define ENTRY \
.text; \
.global asm_main; \
asm_main: \
    push %rbp; \
    mov %rsp, %rbp; \
    push %r15; \
    push %r14; \
    push %r13; \
    push %r12; \
    push %rbx; \
    push %rdi; \
    sub $8, %rsp; \
asm_main_after_prologue: \
;

/* Meant to be called at the end of ENTRY.*
 *
 * Branching to "fail" makes tests fail with exit status 1.
 *
 * If EXIT is reached, the program ends successfully.
 */
#define EXIT \
    mov $0, %rax; \
    jmp pass; \
fail: \
    mov -0x8(%rbp), %rbx; \
    movl %eax, (%rbx); \
    mov $1, %rax; \
pass: \
    pop %rbx; \
    pop %r12; \
    pop %r13; \
    pop %r14; \
    pop %r15; \
    add $16, %rsp; \
    pop %rbp; \
    ret; \
;

#define FAIL \
    mov $__LINE__, %eax; \
    jmp fail; \
;

# TODO
##define MEMCMP(s1, s2, n) \
#    adr x0, s1; \
#    adr x1, s2; \
#    ldr x2, =n; \
#    bl memcmp; \
#;

#endif
