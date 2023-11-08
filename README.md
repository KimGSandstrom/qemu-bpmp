
# Short intstructions:


1. git clone https://gitlab.com/qemu-project/qemu.git
2  cd qemu
3  git checkout v8.1.2
4 ./configure --target-list=aarm64-softmmu
5  make -j12



Device memory map:

0x090c0000 +  /* Base address, size 0x01000 */

     0x0000 \ Tx buffer
     0x01FF /
     0x0200 \ Rx buffer
     0x03FF /
     0x0400  -- Tx size
     0x0408  -- Rx size
     0x0410  -- Ret
     0x0500  -- mrq



 Data should be aligned to 64bit paragraph.

 Protocol is:
 1. Write data buffers to 0x0000-0x01FF and 0x0200-0x03FF
 2. Write buffer sizes to 0x0400 (Tx) and 0x0408 (Rx)
 2. Start operation by writing mrq opcode to address 0x0500
 3. Read ret code from 0x0410 and response data from the buffers


For reading and writing busybox may be used as:

      busybox devmem 0x090c0000

and so on

For instance, to reset the UARTA (with ID 0x64) you can sed the next
command:

      busybox devmem 0x090c0000 64 0x0000006400000001
      busybox devmem 0x090c0400 8 0x08
      busybox devmem 0x090c0500 8 0x14

```
