
blink.elf:     file format elf32-littlearm

Sections:
Idx Name          Size      VMA       LMA       File off  Algn
  0 .text         0000031c  00000000  00000000  00010000  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
  1 .init         00000004  0000031c  0000031c  0001031c  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
  2 .fini         00000004  00000320  00000320  00010320  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
  3 .bss          00000104  20000000  20000000  00020000  2**2
                  ALLOC
  4 .ARM.attributes 0000002a  00000000  00000000  00010324  2**0
                  CONTENTS, READONLY
  5 .comment      0000007e  00000000  00000000  0001034e  2**0
                  CONTENTS, READONLY

Disassembly of section .text:

00000000 <g_pfnVectors>:
   0:	00 01 00 20 c1 02 00 00 b5 02 00 00 b9 02 00 00     ... ............
  10:	bd 02 00 00 bd 02 00 00 bd 02 00 00 00 00 00 00     ................
	...
  2c:	bd 02 00 00 bd 02 00 00 00 00 00 00 bd 02 00 00     ................
  3c:	bd 02 00 00 bd 02 00 00 bd 02 00 00 bd 02 00 00     ................
  4c:	bd 02 00 00 bd 02 00 00 bd 02 00 00 bd 02 00 00     ................
  5c:	bd 02 00 00 bd 02 00 00 bd 02 00 00 bd 02 00 00     ................
  6c:	bd 02 00 00 bd 02 00 00 bd 02 00 00 bd 02 00 00     ................
  7c:	bd 02 00 00 bd 02 00 00 bd 02 00 00 bd 02 00 00     ................
  8c:	bd 02 00 00 bd 02 00 00 bd 02 00 00 bd 02 00 00     ................
  9c:	bd 02 00 00 bd 02 00 00 bd 02 00 00 bd 02 00 00     ................
  ac:	bd 02 00 00 bd 02 00 00 bd 02 00 00 bd 02 00 00     ................
  bc:	bd 02 00 00 bd 02 00 00 bd 02 00 00 bd 02 00 00     ................
  cc:	bd 02 00 00 bd 02 00 00 bd 02 00 00 bd 02 00 00     ................
  dc:	bd 02 00 00 bd 02 00 00 bd 02 00 00 00 00 00 00     ................
  ec:	bd 02 00 00 bd 02 00 00 bd 02 00 00 bd 02 00 00     ................
  fc:	bd 02 00 00 bd 02 00 00 bd 02 00 00 bd 02 00 00     ................
 10c:	bd 02 00 00 00 00 00 00 00 00 00 00 bd 02 00 00     ................
 11c:	bd 02 00 00 bd 02 00 00 bd 02 00 00 bd 02 00 00     ................
 12c:	bd 02 00 00 bd 02 00 00 bd 02 00 00 bd 02 00 00     ................
 13c:	bd 02 00 00 00 00 00 00 00 00 00 00 00 00 00 00     ................
 14c:	00 00 00 00 bd 02 00 00 bd 02 00 00 bd 02 00 00     ................
 15c:	bd 02 00 00 00 00 00 00 00 00 00 00 00 00 00 00     ................
	...
 1b0:	bd 02 00 00 bd 02 00 00 bd 02 00 00 bd 02 00 00     ................
 1c0:	bd 02 00 00 bd 02 00 00 bd 02 00 00 bd 02 00 00     ................
 1d0:	bd 02 00 00 bd 02 00 00 bd 02 00 00 bd 02 00 00     ................
 1e0:	bd 02 00 00 bd 02 00 00 bd 02 00 00 00 00 00 00     ................
 1f0:	00 00 00 00 bd 02 00 00 bd 02 00 00 bd 02 00 00     ................
 200:	bd 02 00 00 bd 02 00 00 00 00 00 00 00 00 00 00     ................
 210:	bd 02 00 00 bd 02 00 00 bd 02 00 00 bd 02 00 00     ................
 220:	bd 02 00 00 bd 02 00 00 bd 02 00 00 bd 02 00 00     ................
 230:	bd 02 00 00 bd 02 00 00 bd 02 00 00 bd 02 00 00     ................
 240:	bd 02 00 00 bd 02 00 00 bd 02 00 00 bd 02 00 00     ................
 250:	bd 02 00 00 bd 02 00 00 bd 02 00 00 bd 02 00 00     ................
 260:	bd 02 00 00 bd 02 00 00 bd 02 00 00                 ............

0000026c <main>:
 26c:	4a0b      	ldr	r2, [pc, #44]	; (29c <main+0x30>)
 26e:	490c      	ldr	r1, [pc, #48]	; (2a0 <main+0x34>)
 270:	4d0c      	ldr	r5, [pc, #48]	; (2a4 <main+0x38>)
 272:	4c0d      	ldr	r4, [pc, #52]	; (2a8 <main+0x3c>)
 274:	4b0d      	ldr	r3, [pc, #52]	; (2ac <main+0x40>)
 276:	2020      	movs	r0, #32
 278:	6010      	str	r0, [r2, #0]
 27a:	6812      	ldr	r2, [r2, #0]
 27c:	600a      	str	r2, [r1, #0]
 27e:	480c      	ldr	r0, [pc, #48]	; (2b0 <main+0x44>)
 280:	2208      	movs	r2, #8
 282:	602a      	str	r2, [r5, #0]
 284:	6022      	str	r2, [r4, #0]
 286:	681a      	ldr	r2, [r3, #0]
 288:	f042 0208 	orr.w	r2, r2, #8
 28c:	601a      	str	r2, [r3, #0]
 28e:	6008      	str	r0, [r1, #0]
 290:	681a      	ldr	r2, [r3, #0]
 292:	f022 0208 	bic.w	r2, r2, #8
 296:	601a      	str	r2, [r3, #0]
 298:	6008      	str	r0, [r1, #0]
 29a:	e7f4      	b.n	286 <main+0x1a>
 29c:	400fe108 	.word	0x400fe108
 2a0:	20000100 	.word	0x20000100
 2a4:	40025400 	.word	0x40025400
 2a8:	4002551c 	.word	0x4002551c
 2ac:	400253fc 	.word	0x400253fc
 2b0:	00030d40 	.word	0x00030d40

000002b4 <NmiSR>:
 2b4:	e7fe      	b.n	2b4 <NmiSR>
 2b6:	bf00      	nop

000002b8 <FaultISR>:
 2b8:	e7fe      	b.n	2b8 <FaultISR>
 2ba:	bf00      	nop

000002bc <IntDefaultHandler>:
 2bc:	e7fe      	b.n	2bc <IntDefaultHandler>
 2be:	bf00      	nop

000002c0 <ResetISR>:
 2c0:	4b10      	ldr	r3, [pc, #64]	; (304 <zero_loop+0x1a>)
 2c2:	4a11      	ldr	r2, [pc, #68]	; (308 <zero_loop+0x1e>)
 2c4:	4293      	cmp	r3, r2
 2c6:	d20c      	bcs.n	2e2 <ResetISR+0x22>
 2c8:	1d18      	adds	r0, r3, #4
 2ca:	3203      	adds	r2, #3
 2cc:	1a12      	subs	r2, r2, r0
 2ce:	f022 0203 	bic.w	r2, r2, #3
 2d2:	490e      	ldr	r1, [pc, #56]	; (30c <zero_loop+0x22>)
 2d4:	4402      	add	r2, r0
 2d6:	f851 0b04 	ldr.w	r0, [r1], #4
 2da:	f843 0b04 	str.w	r0, [r3], #4
 2de:	4293      	cmp	r3, r2
 2e0:	d1f9      	bne.n	2d6 <ResetISR+0x16>
 2e2:	480c      	ldr	r0, [pc, #48]	; (314 <zero_loop+0x2a>)
 2e4:	490c      	ldr	r1, [pc, #48]	; (318 <zero_loop+0x2e>)
 2e6:	f04f 0200 	mov.w	r2, #0

000002ea <zero_loop>:
 2ea:	4288      	cmp	r0, r1
 2ec:	bfb8      	it	lt
 2ee:	f840 2b04 	strlt.w	r2, [r0], #4
 2f2:	dbfa      	blt.n	2ea <zero_loop>
 2f4:	4a06      	ldr	r2, [pc, #24]	; (310 <zero_loop+0x26>)
 2f6:	6813      	ldr	r3, [r2, #0]
 2f8:	f443 0370 	orr.w	r3, r3, #15728640	; 0xf00000
 2fc:	6013      	str	r3, [r2, #0]
 2fe:	f7ff bfb5 	b.w	26c <main>
 302:	bf00      	nop
 304:	20000000 	.word	0x20000000
 308:	20000000 	.word	0x20000000
 30c:	0000031c 	.word	0x0000031c
 310:	e000ed88 	.word	0xe000ed88
 314:	20000000 	.word	0x20000000
 318:	20000104 	.word	0x20000104

Disassembly of section .init:

0000031c <_init>:
 31c:	b5f8      	push	{r3, r4, r5, r6, r7, lr}
 31e:	bf00      	nop

Disassembly of section .fini:

00000320 <_fini>:
 320:	b5f8      	push	{r3, r4, r5, r6, r7, lr}
 322:	bf00      	nop
