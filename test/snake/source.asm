; Snake Example
; Code adapted from the Easy 6502 tutorial page by Nick Morgan (https://skilldrick.github.io/easy6502/)

	.def applel 0x00
	.def appleh 0x01
	.def snakeheadl 0x10
	.def snakeheadh 0x11
	.def snakebodystart 0x12
	.def snakedirection 0x02
	.def snakelength 0x03

	.def movingup 1
	.def movingright 2
	.def movingdown 4
	.def movingleft 8

	.def ascii_w 0x77
	.def ascii_a 0x61
	.def ascii_s 0x73
	.def ascii_d 0x64

	.def sysrandom 0xfe
	.def syslastkey 0xff

	.org 0x0600

	jsr init
	jsr loop


init:
	jsr initsnake
	jsr generateappleposition
	rts


initsnake:
	lda #movingright
	sta snakedirection

	lda #4
	sta snakelength

	lda #0x11
	sta snakeheadl

	lda #0x10
	sta snakebodystart

	lda #0x0f
	sta 0x14

	lda #0x04
	sta snakeheadh
	sta 0x13
	sta 0x15
	rts


generateappleposition:
	lda sysrandom
	sta applel
	lda sysrandom
	and #0x03
	clc
	adc #2
	sta appleh

	rts

loop:
	jsr readkeys
	jsr checkcollision
	jsr updatesnake
	jsr drawapple
	jsr drawsnake
	jsr spinwheels
	jmp loop


readkeys:
	lda syslastkey
	cmp #ascii_w
	beq upkey
	cmp #ascii_d
	beq rightkey
	cmp #ascii_s
	beq downkey
	cmp #ascii_a
	beq leftkey
	rts

upkey:
	lda #movingdown
	bit snakedirection
	bne illegalmove

	lda #movingup
	sta snakedirection
	rts

rightkey:
	lda #movingleft
	bit snakedirection
	bne illegalmove

	lda #movingright
	sta snakedirection
	rts

downkey:
	lda #movingup
	bit snakedirection
	bne illegalmove

	lda #movingdown
	sta snakedirection
	rts

leftkey:
	lda #movingright
	bit snakedirection
	bne illegalmove

	lda #movingleft
	sta snakedirection
	rts

illegalmove:
	rts


checkcollision:
	jsr checkapplecollision
	jsr checksnakecollision
	rts


checkapplecollision:
	lda applel
	cmp snakeheadl
	bne donecheckingapplecollision
	lda appleh
	cmp snakeheadh
	bne donecheckingapplecollision

	inc snakelength
	inc snakelength
	jsr generateappleposition

donecheckingapplecollision:
	rts


checksnakecollision:
	ldx #2
	snakecollisionloop:
	lda snakeheadl, x
	cmp snakeheadl
	bne continuecollisionloop

maybecollided:
	lda snakeheadh, x
	cmp snakeheadh
	beq didcollide

continuecollisionloop:
	inx
	inx
	cpx snakelength
	beq didntcollide
	jmp snakecollisionloop

didcollide:
	jmp gameover

didntcollide:
	rts


updatesnake:
	ldx snakelength
	dex
	txa

updateloop:
	lda snakeheadl, x
	sta snakebodystart, x
	dex
	bpl updateloop

	lda snakedirection
	lsr a
	bcs up
	lsr a
	bcs right
	lsr a
	bcs down
	lsr a
	bcs left

up:
	lda snakeheadl
	sec
	sbc #0x20
	sta snakeheadl
	bcc upup
	rts

upup:
	dec snakeheadh
	lda #0x1
	cmp snakeheadh
	beq collision
	rts

right:
	inc snakeheadl
	lda #0x1f
	bit snakeheadl
	beq collision
	rts

down:
	lda snakeheadl
	clc
	adc #0x20
	sta snakeheadl
	bcs downdown
	rts

downdown:
	inc snakeheadh
	lda #0x6
	cmp snakeheadh
	beq collision
	rts

left:
	dec snakeheadl
	lda snakeheadl
	and #0x1f
	cmp #0x1f
	beq collision
	rts

collision:
	jmp gameover


drawapple:
	ldy #0
	lda sysrandom
	sta [applel], y
	rts


drawsnake:
	ldx snakelength
	lda #0
	sta [snakeheadl, x]

	ldx #0
	lda #1
	sta [snakeheadl, x]
	rts


spinwheels:
	ldx #0

spinloop:
	nop
	nop
	dex
	bne spinloop
	rts


gameover:
	stp


	.org 0xfffa

	.dw 0x0000
	.dw 0x0600
	.dw 0x0000
