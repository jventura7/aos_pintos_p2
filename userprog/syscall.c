#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "devices/block.h"
#include "threads/interrupt.h"
#include "threads/thread.h"
#include "threads/vaddr.h"

static void syscall_handler (struct intr_frame *);

void syscall_init (void)
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

static void syscall_handler (struct intr_frame *f UNUSED)
{
  printf ("system call!\n");
  int syscall_number;
  syscall_number = *((int *)(f->esp));
  validate_addr((const void*)f->esp);

  switch (syscall_number) {
    case SYS_WRITE:
      printf("write");
      break;
  }
  thread_exit ();
}

void validate_addr(const void *addr) {
  if (!is_user_vaddr(addr) || addr == NULL) {
    thread_exit();
  }
}