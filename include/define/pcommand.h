/**
 * E65
 * Copyright (C) 2018 David Jolly
 *
 * E65 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * E65 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef E65_DEFINE_PCOMMAND_H_
#define E65_DEFINE_PCOMMAND_H_

namespace e65 {

	enum {
		E65_PCOMMAND_ADC = 0,
		E65_PCOMMAND_AND,
		E65_PCOMMAND_ASL,
		E65_PCOMMAND_BBR0,
		E65_PCOMMAND_BBR1,
		E65_PCOMMAND_BBR2,
		E65_PCOMMAND_BBR3,
		E65_PCOMMAND_BBR4,
		E65_PCOMMAND_BBR5,
		E65_PCOMMAND_BBR6,
		E65_PCOMMAND_BBR7,
		E65_PCOMMAND_BBS0,
		E65_PCOMMAND_BBS1,
		E65_PCOMMAND_BBS2,
		E65_PCOMMAND_BBS3,
		E65_PCOMMAND_BBS4,
		E65_PCOMMAND_BBS5,
		E65_PCOMMAND_BBS6,
		E65_PCOMMAND_BBS7,
		E65_PCOMMAND_BCC,
		E65_PCOMMAND_BCS,
		E65_PCOMMAND_BEQ,
		E65_PCOMMAND_BIT,
		E65_PCOMMAND_BMI,
		E65_PCOMMAND_BNE,
		E65_PCOMMAND_BPL,
		E65_PCOMMAND_BRA,
		E65_PCOMMAND_BRK,
		E65_PCOMMAND_BVC,
		E65_PCOMMAND_BVS,
		E65_PCOMMAND_CLC,
		E65_PCOMMAND_CLD,
		E65_PCOMMAND_CLI,
		E65_PCOMMAND_CLV,
		E65_PCOMMAND_CMD,
		E65_PCOMMAND_CMP,
		E65_PCOMMAND_CPX,
		E65_PCOMMAND_CPY,
		E65_PCOMMAND_DEC,
		E65_PCOMMAND_DEX,
		E65_PCOMMAND_DEY,
		E65_PCOMMAND_EOR,
		E65_PCOMMAND_INC,
		E65_PCOMMAND_INX,
		E65_PCOMMAND_INY,
		E65_PCOMMAND_JMP,
		E65_PCOMMAND_JSR,
		E65_PCOMMAND_LDA,
		E65_PCOMMAND_LDX,
		E65_PCOMMAND_LDY,
		E65_PCOMMAND_LSR,
		E65_PCOMMAND_NOP,
		E65_PCOMMAND_ORA,
		E65_PCOMMAND_PHA,
		E65_PCOMMAND_PHP,
		E65_PCOMMAND_PHX,
		E65_PCOMMAND_PHY,
		E65_PCOMMAND_PLA,
		E65_PCOMMAND_PLP,
		E65_PCOMMAND_PLX,
		E65_PCOMMAND_PLY,
		E65_PCOMMAND_RMB0,
		E65_PCOMMAND_RMB1,
		E65_PCOMMAND_RMB2,
		E65_PCOMMAND_RMB3,
		E65_PCOMMAND_RMB4,
		E65_PCOMMAND_RMB5,
		E65_PCOMMAND_RMB6,
		E65_PCOMMAND_RMB7,
		E65_PCOMMAND_ROL,
		E65_PCOMMAND_ROR,
		E65_PCOMMAND_RTI,
		E65_PCOMMAND_RTS,
		E65_PCOMMAND_SBC,
		E65_PCOMMAND_SEC,
		E65_PCOMMAND_SED,
		E65_PCOMMAND_SEI,
		E65_PCOMMAND_SMB0,
		E65_PCOMMAND_SMB1,
		E65_PCOMMAND_SMB2,
		E65_PCOMMAND_SMB3,
		E65_PCOMMAND_SMB4,
		E65_PCOMMAND_SMB5,
		E65_PCOMMAND_SMB6,
		E65_PCOMMAND_SMB7,
		E65_PCOMMAND_STA,
		E65_PCOMMAND_STP,
		E65_PCOMMAND_STX,
		E65_PCOMMAND_STY,
		E65_PCOMMAND_STZ,
		E65_PCOMMAND_TAX,
		E65_PCOMMAND_TAY,
		E65_PCOMMAND_TRB,
		E65_PCOMMAND_TSB,
		E65_PCOMMAND_TSX,
		E65_PCOMMAND_TXA,
		E65_PCOMMAND_TXS,
		E65_PCOMMAND_TYA,
		E65_PCOMMAND_WAI,
	};

	#define E65_PCOMMAND_MAX e65::E65_PCOMMAND_WAI

	static const std::string E65_PCOMMAND_STR[] = {
		"adc", "and", "asl", "bbr0", "bbr1", "bbr2", "bbr3", "bbr4", "bbr5", "bbr6", "bbr7",
		"bbs0", "bbs1", "bbs2", "bbs3", "bbs4", "bbs5", "bbs6", "bbs7", "bcc", "bcs", "beq",
		"bit", "bmi", "bne", "bpl", "bra", "brk", "bvc", "bvs", "clc", "cld", "cli", "clv",
		"cmd", "cmp", "cpx", "cpy", "dec", "dex", "dey", "eor", "inc", "inx", "iny", "jmp", "jsr",
		"lda", "ldx", "ldy", "lsr", "nop", "ora", "pha", "php", "phx", "phy", "pla", "plp", "plx", "ply",
		"rmb0", "rmb1", "rmb2", "rmb3", "rmb4", "rmb5", "rmb6", "rmb7", "rol", "ror", "rti", "rts",
		"sbc", "sec", "sed", "sei", "smb0", "smb1", "smb2", "smb3", "smb4", "smb5", "smb6", "smb7",
		"sta", "stp", "stx", "sty", "stz", "tax", "tay", "trb", "tsb", "tsx", "txa", "txs", "tya", "wai",
		};

	#define E65_PCOMMAND_STRING(_TYPE_) \
		(((_TYPE_) > E65_PCOMMAND_MAX) ? E65_STRING_UNKNOWN : \
			E65_STRING_CHECK(e65::E65_PCOMMAND_STR[_TYPE_]))
}

#endif // E65_DEFINE_PCOMMAND_H_
