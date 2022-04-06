


# bootsect.s————引导扇区启动程序  

该部分汇编代码编译链接产生的执行程序，可放入磁盘第一个扇区用来引导计算机启动。  

* as86汇编语言  
* 感叹号！和分号; 后的部分为注释  
* 汇编指示符以字符‘.’开始   如 .global  不会在编译时产生代码  
* .global汇编指示符(汇编伪指令)  后面定义的是全局标号  如后面 begtext:
* entry关键字，通常在链接多个目标文件成一个可执行文件时，应该在其中一个汇编程序中用该关键字指定一个入口标号


* CS；代码段寄存器  
* DS；数据段寄存器  
* SS; 堆栈段寄存器  
* ES: 附加段寄存器

mov传送指令的一些用法  
```as86
!jmp  直接寄存器寻址。 跳转到bx值指定的地址处，相当于把bx的值拷贝到IP中  
mov bx, ax
jmp bx  

!间接寄存器寻址        
mov [bx], ax !将ax寄存器的值赋值给bx值指定的内存处
jmp [bx]  !bx值指定的内存位置处的内容作为IP的值

!把立即数xxx放入ax中  
mov ax, #1234  ! 将立即数1234传送到ax
mov ax, #msg1  ! 把一个标号msg1的地址值放到ax   

!绝对寻址  把内存地址xxxx处的内容放入ax
mov ax, 1234  ! 将内存地址1234处的内容放入ax
mov ax, msg1  ! 将内存地址msg1处的内容放入ax
mov ax, [msg1] ! []表示取里面内存地址的内容，与上面一条含义一样？

!索引寻址
mov ax, msg1[bx] ! msg1是个地址，msg1[bx]是该地址偏移bx的地址，即将msg1[bx]这个内存地址的内容放入ax
mov ax, msg1[bx*4+si] !将msg1[bx*4+si]地址处内容放入ax  
```







```as86
!
! SYS_SIZE is the number of clicks (16 bytes) to be loaded.
! 0x3000 is 0x30000 bytes = 196kB, more than enough for current
! versions of linux
!
SYSSIZE = 0x3000
!
!	bootsect.s		(C) 1991 Linus Torvalds
!
! bootsect.s is loaded at 0x7c00 by the bios-startup routines, and moves
! iself out of the way to address 0x90000, and jumps there.
!
! It then loads 'setup' directly after itself (0x90200), and the system
! at 0x10000, using BIOS interrupts. 
!
! NOTE! currently system is at most 8*65536 bytes long. This should be no
! problem, even in the future. I want to keep it simple. This 512 kB
! kernel size should be enough, especially as this doesn't contain the
! buffer cache as in minix
!
! The loader has been made as simple as possible, and continuos
! read errors will result in a unbreakable loop. Reboot by hand. It
! loads pretty fast by getting whole sectors at a time whenever possible.

.globl begtext, begdata, begbss, endtext, enddata, endbss    !.global汇编指示符(汇编伪指令)  后面定义的是全局标号  如后面begtext:
.text      !伪操作符  用于标识正文段的开始位置，并切换到text段
begtext:   !定义了上面的全局标号  begtext
.data      !伪操作符  用于标识数据段的开始位置，并把当前段切换到text段
begdata:   !在数据段定义标号begdata
.bss       !伪操作符  用于标识未初始化段的开始位置，并把当前段切换到bss段
begbss:    !在bss段定义标号begbss
.text	   !上面的代码用于在每一个段定义一个标号，这里再切换正文段开始编写后面的代码  

!注意：这里三个段都定义在了同一重叠地址范围中,因此实际上不分段  

SETUPLEN = 4				! nr of setup-sectors
BOOTSEG  = 0x07c0			! original address of boot-sector  赋值语句，定义标识符BOOTSEG的值(符号常量  可用10，8，16进制表示)  这是BIOS加载bootsect代码的原始段地址
INITSEG  = 0x9000			! we move boot here - out of the way
SETUPSEG = 0x9020			! setup starts here
SYSSEG   = 0x1000			! system loaded at 0x10000 (65536).
ENDSEG   = SYSSEG + SYSSIZE		! where to stop loading

! ROOT_DEV:	0x000 - same type of floppy as boot.
!		0x301 - first partition on first drive etc
ROOT_DEV = 0x306

entry _start        !告知链接程序，程序从_start标号开始  
_start:
	mov	ax,#BOOTSEG  !0x07c0给ax
	mov	ds,ax        !0x07c0给数据段寄存器  因为ds是地址段寄存器，段寄存器不能直接将值传动给自己，必须借助其他寄存器  
	mov	ax,#INITSEG  !setup起始地址
	mov	es,ax        
	mov	cx,#256
	sub	si,si
	sub	di,di
	rep
	movw
	jmpi	go,INITSEG   ! jmpi 长跳转
go:	mov	ax,cs
	mov	ds,ax
	mov	es,ax
! put stack at 0x9ff00.
	mov	ss,ax
	mov	sp,#0xFF00		! arbitrary value >>512

! load the setup-sectors directly after the bootblock.
! Note that 'es' is already set up.

load_setup:
	mov	dx,#0x0000		! drive 0, head 0
	mov	cx,#0x0002		! sector 2, track 0
	mov	bx,#0x0200		! address = 512, in INITSEG
	mov	ax,#0x0200+SETUPLEN	! service 2, nr of sectors
	int	0x13			! read it
	jnc	ok_load_setup		! ok - continue
	mov	dx,#0x0000
	mov	ax,#0x0000		! reset the diskette
	int	0x13
	j	load_setup

ok_load_setup:

! Get disk drive parameters, specifically nr of sectors/track

	mov	dl,#0x00
	mov	ax,#0x0800		! AH=8 is get drive parameters
	int	0x13
	mov	ch,#0x00
	seg cs
	mov	sectors,cx
	mov	ax,#INITSEG
	mov	es,ax

! Print some inane message

	mov	ah,#0x03		! read cursor pos
	xor	bh,bh
	int	0x10
	
	mov	cx,#24
	mov	bx,#0x0007		! page 0, attribute 7 (normal)
	mov	bp,#msg1
	mov	ax,#0x1301		! write string, move cursor
	int	0x10

! ok, we've written the message, now
! we want to load the system (at 0x10000)

	mov	ax,#SYSSEG
	mov	es,ax		! segment of 0x010000
	call	read_it
	call	kill_motor

! After that we check which root-device to use. If the device is
! defined (!= 0), nothing is done and the given device is used.
! Otherwise, either /dev/PS0 (2,28) or /dev/at0 (2,8), depending
! on the number of sectors that the BIOS reports currently.

	seg cs
	mov	ax,root_dev
	cmp	ax,#0
	jne	root_defined
	seg cs
	mov	bx,sectors
	mov	ax,#0x0208		! /dev/ps0 - 1.2Mb
	cmp	bx,#15
	je	root_defined
	mov	ax,#0x021c		! /dev/PS0 - 1.44Mb
	cmp	bx,#18
	je	root_defined
undef_root:
	jmp undef_root
root_defined:
	seg cs
	mov	root_dev,ax

! after that (everyting loaded), we jump to
! the setup-routine loaded directly after
! the bootblock:

	jmpi	0,SETUPSEG

! This routine loads the system at address 0x10000, making sure
! no 64kB boundaries are crossed. We try to load it as fast as
! possible, loading whole tracks whenever we can.
!
! in:	es - starting address segment (normally 0x1000)
!
sread:	.word 1+SETUPLEN	! sectors read of current track
head:	.word 0			! current head
track:	.word 0			! current track

read_it:
	mov ax,es
	test ax,#0x0fff
die:	jne die			! es must be at 64kB boundary
	xor bx,bx		! bx is starting address within segment
rp_read:
	mov ax,es
	cmp ax,#ENDSEG		! have we loaded all yet?
	jb ok1_read
	ret
ok1_read:
	seg cs
	mov ax,sectors
	sub ax,sread
	mov cx,ax
	shl cx,#9
	add cx,bx
	jnc ok2_read
	je ok2_read
	xor ax,ax
	sub ax,bx
	shr ax,#9
ok2_read:
	call read_track
	mov cx,ax
	add ax,sread
	seg cs
	cmp ax,sectors
	jne ok3_read
	mov ax,#1
	sub ax,head
	jne ok4_read
	inc track
ok4_read:
	mov head,ax
	xor ax,ax
ok3_read:
	mov sread,ax
	shl cx,#9
	add bx,cx
	jnc rp_read
	mov ax,es
	add ax,#0x1000
	mov es,ax
	xor bx,bx
	jmp rp_read

read_track:
	push ax
	push bx
	push cx
	push dx
	mov dx,track
	mov cx,sread
	inc cx
	mov ch,dl
	mov dx,head
	mov dh,dl
	mov dl,#0
	and dx,#0x0100
	mov ah,#2
	int 0x13
	jc bad_rt
	pop dx
	pop cx
	pop bx
	pop ax
	ret
bad_rt:	mov ax,#0
	mov dx,#0
	int 0x13
	pop dx
	pop cx
	pop bx
	pop ax
	jmp read_track

!/*
! * This procedure turns off the floppy drive motor, so
! * that we enter the kernel in a known state, and
! * don't have to worry about it later.
! */
kill_motor:
	push dx
	mov dx,#0x3f2
	mov al,#0
	outb
	pop dx
	ret

sectors:
	.word 0

msg1:
	.byte 13,10
	.ascii "Loading system ..."
	.byte 13,10,13,10

.org 508
root_dev:
	.word ROOT_DEV
boot_flag:
	.word 0xAA55

.text
endtext:
.data
enddata:
.bss
endbss:
```




