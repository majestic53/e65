; Subroutine test

	.def fill_addr 0xfe
	.def index_addr 0x0000
	.def video_low 0x02
	.def video_high 0x06

	.org 0x0200

	.res 0x0400

	.org 0x0600

reset:
	jsr fill
	stp

fill:
	pha
	phx
	phy
	ldx #0
	ldy #video_low
	stx index_addr
	sty index_addr + 1
fill_loop:
	ldx index_addr
	ldy index_addr + 1
	lda fill_addr
	sta [index_addr]
	inx
	bne fill_loop_done
	iny
	cpy #video_high
	beq fill_done
fill_loop_done:
	stx index_addr
	sty index_addr + 1
	jmp fill_loop
fill_done:
	ply
	plx
	pla
	rts

	.org 0xfffa

	.dw 0x0000
	.dw reset
	.dw 0x0000
