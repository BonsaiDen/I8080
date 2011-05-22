# One more 8080 emulator

Wrote this thing over the weekend, yes I'm reaaaaaaaaaaaly bored.

Anyways, its working for the most part. I/O isn't implement and MEMORY 
is still one static array, but the actually instructions are working 
and speed control is there too. 

It's running at an awesome 2.00 Mhz!

Lots of stuff to do before this boots CM/S, but hey the the boring part 
of implementing all the OP codes is already done.

## Speed

Uses 2% of my 1.8ghz Dual Core here. Sure you could make it faster by 
using a less "object oriented approch" and doing tricky stuffs.

But come on!

## Portability

Works with GCC:

    $ gcc -o main cpu/8080.c mmu.c main.c -O3 -fomit-frame-pointer

As for other OS / Compilers, no idea!

# TODO

- Implement I/O, Interrupts and a good MMU
- Make sure that there are no bugs.A

