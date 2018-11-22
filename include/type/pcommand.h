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

#ifndef E65_TYPE_PCOMMAND_H_
#define E65_TYPE_PCOMMAND_H_

#include <map>

namespace e65 {

	namespace type {

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

		#define E65_PCOMMAND_MAX e65::type::E65_PCOMMAND_WAI

		static const std::string E65_PCOMMAND_STR[] = {
			"adc",
			"and",
			"asl",
			"bbr0", "bbr1", "bbr2", "bbr3", "bbr4", "bbr5", "bbr6", "bbr7",
			"bbs0", "bbs1", "bbs2", "bbs3", "bbs4", "bbs5", "bbs6", "bbs7",
			"bcc", "bcs", "beq",
			"bit",
			"bmi", "bne", "bpl", "bra",
			"brk",
			"bvc", "bvs",
			"clc", "cld", "cli", "clv",
			"cmp", "cpx", "cpy",
			"dec", "dex", "dey",
			"eor",
			"inc", "inx", "iny",
			"jmp", "jsr",
			"lda", "ldx", "ldy",
			"lsr",
			"nop",
			"ora",
			"pha", "php", "phx", "phy",
			"pla", "plp", "plx", "ply",
			"rmb0", "rmb1", "rmb2", "rmb3", "rmb4", "rmb5", "rmb6", "rmb7",
			"rol", "ror",
			"rti", "rts",
			"sbc",
			"sec", "sed", "sei",
			"smb0", "smb1", "smb2", "smb3", "smb4", "smb5", "smb6", "smb7",
			"sta",
			"stp",
			"stx", "sty", "stz",
			"tax","tay","trb","tsb","tsx","txa","txs","tya",
			"wai",
			};

		#define E65_PCOMMAND_STRING(_TYPE_) \
			(((_TYPE_) > E65_PCOMMAND_MAX) ? E65_STRING_UNKNOWN : \
				E65_STRING_CHECK(e65::type::E65_PCOMMAND_STR[_TYPE_]))

		enum {
			E65_PCOMMAND_MODE_ABSOLUTE = 0,
			E65_PCOMMAND_MODE_ABSOLUTE_INDEX_INDIRECT,
			E65_PCOMMAND_MODE_ABSOLUTE_INDEX_X,
			E65_PCOMMAND_MODE_ABSOLUTE_INDEX_Y,
			E65_PCOMMAND_MODE_ABSOLUTE_INDIRECT,
			E65_PCOMMAND_MODE_ACCUMULATOR,
			E65_PCOMMAND_MODE_IMMEDIATE,
			E65_PCOMMAND_MODE_IMPLIED,
			E65_PCOMMAND_MODE_RELATIVE,
			E65_PCOMMAND_MODE_ZEROPAGE,
			E65_PCOMMAND_MODE_ZEROPAGE_INDEX_INDIRECT,
			E65_PCOMMAND_MODE_ZEROPAGE_INDEX_X,
			E65_PCOMMAND_MODE_ZEROPAGE_INDEX_Y,
			E65_PCOMMAND_MODE_ZEROPAGE_INDIRECT,
			E65_PCOMMAND_MODE_ZEROPAGE_INDIRECT_INDEX,
		};

		#define E65_PCOMMAND_MODE_MAX e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDIRECT_INDEX

		static const std::string E65_PCOMMAND_MODE_STR[] = {
			"abs", "[abs, x]", "abs, x", "abs, y", "[abs]",
			"acc",
			"imm",
			"imp",
			"rel",
			"zp", "[zp, x]", "zp, x", "zp, y", "[zp]", "[zp], y",
			};

		#define E65_PCOMMAND_MODE_STRING(_TYPE_) \
			(((_TYPE_) > E65_PCOMMAND_MODE_MAX) ? E65_STRING_UNKNOWN : \
				E65_STRING_CHECK(e65::type::E65_PCOMMAND_MODE_STR[_TYPE_]))

		static const std::map<uint8_t, std::pair<int, int>> E65_PCOMMAND_ID_MAP = {
			std::make_pair(0x6d, std::make_pair(e65::type::E65_PCOMMAND_ADC, e65::type::E65_PCOMMAND_MODE_ABSOLUTE)),
			std::make_pair(0x7d, std::make_pair(e65::type::E65_PCOMMAND_ADC, e65::type::E65_PCOMMAND_MODE_ABSOLUTE_INDEX_X)),
			std::make_pair(0x79, std::make_pair(e65::type::E65_PCOMMAND_ADC, e65::type::E65_PCOMMAND_MODE_ABSOLUTE_INDEX_Y)),
			std::make_pair(0x69, std::make_pair(e65::type::E65_PCOMMAND_ADC, e65::type::E65_PCOMMAND_MODE_IMMEDIATE)),
			std::make_pair(0x65, std::make_pair(e65::type::E65_PCOMMAND_ADC, e65::type::E65_PCOMMAND_MODE_ZEROPAGE)),
			std::make_pair(0x61, std::make_pair(e65::type::E65_PCOMMAND_ADC, e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDEX_INDIRECT)),
			std::make_pair(0x75, std::make_pair(e65::type::E65_PCOMMAND_ADC, e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDEX_X)),
			std::make_pair(0x72, std::make_pair(e65::type::E65_PCOMMAND_ADC, e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDIRECT)),
			std::make_pair(0x71, std::make_pair(e65::type::E65_PCOMMAND_ADC, e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDIRECT_INDEX)),
			std::make_pair(0x2d, std::make_pair(e65::type::E65_PCOMMAND_AND, e65::type::E65_PCOMMAND_MODE_ABSOLUTE)),
			std::make_pair(0x3d, std::make_pair(e65::type::E65_PCOMMAND_AND, e65::type::E65_PCOMMAND_MODE_ABSOLUTE_INDEX_X)),
			std::make_pair(0x39, std::make_pair(e65::type::E65_PCOMMAND_AND, e65::type::E65_PCOMMAND_MODE_ABSOLUTE_INDEX_Y)),
			std::make_pair(0x29, std::make_pair(e65::type::E65_PCOMMAND_AND, e65::type::E65_PCOMMAND_MODE_IMMEDIATE)),
			std::make_pair(0x25, std::make_pair(e65::type::E65_PCOMMAND_AND, e65::type::E65_PCOMMAND_MODE_ZEROPAGE)),
			std::make_pair(0x21, std::make_pair(e65::type::E65_PCOMMAND_AND, e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDEX_INDIRECT)),
			std::make_pair(0x35, std::make_pair(e65::type::E65_PCOMMAND_AND, e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDEX_X)),
			std::make_pair(0x32, std::make_pair(e65::type::E65_PCOMMAND_AND, e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDIRECT)),
			std::make_pair(0x31, std::make_pair(e65::type::E65_PCOMMAND_AND, e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDIRECT_INDEX)),
			std::make_pair(0x00, std::make_pair(e65::type::E65_PCOMMAND_BRK, e65::type::E65_PCOMMAND_MODE_IMPLIED)),
			std::make_pair(0x18, std::make_pair(e65::type::E65_PCOMMAND_CLC, e65::type::E65_PCOMMAND_MODE_IMPLIED)),
			std::make_pair(0xd8, std::make_pair(e65::type::E65_PCOMMAND_CLD, e65::type::E65_PCOMMAND_MODE_IMPLIED)),
			std::make_pair(0x58, std::make_pair(e65::type::E65_PCOMMAND_CLI, e65::type::E65_PCOMMAND_MODE_IMPLIED)),
			std::make_pair(0xb8, std::make_pair(e65::type::E65_PCOMMAND_CLV, e65::type::E65_PCOMMAND_MODE_IMPLIED)),
			std::make_pair(0xcd, std::make_pair(e65::type::E65_PCOMMAND_CMP, e65::type::E65_PCOMMAND_MODE_ABSOLUTE)),
			std::make_pair(0xdd, std::make_pair(e65::type::E65_PCOMMAND_CMP, e65::type::E65_PCOMMAND_MODE_ABSOLUTE_INDEX_X)),
			std::make_pair(0xd9, std::make_pair(e65::type::E65_PCOMMAND_CMP, e65::type::E65_PCOMMAND_MODE_ABSOLUTE_INDEX_Y)),
			std::make_pair(0xc9, std::make_pair(e65::type::E65_PCOMMAND_CMP, e65::type::E65_PCOMMAND_MODE_IMMEDIATE)),
			std::make_pair(0xc5, std::make_pair(e65::type::E65_PCOMMAND_CMP, e65::type::E65_PCOMMAND_MODE_ZEROPAGE)),
			std::make_pair(0xc1, std::make_pair(e65::type::E65_PCOMMAND_CMP, e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDEX_INDIRECT)),
			std::make_pair(0xd5, std::make_pair(e65::type::E65_PCOMMAND_CMP, e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDEX_X)),
			std::make_pair(0xd2, std::make_pair(e65::type::E65_PCOMMAND_CMP, e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDIRECT)),
			std::make_pair(0xd1, std::make_pair(e65::type::E65_PCOMMAND_CMP, e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDIRECT_INDEX)),
			std::make_pair(0xca, std::make_pair(e65::type::E65_PCOMMAND_DEX, e65::type::E65_PCOMMAND_MODE_IMPLIED)),
			std::make_pair(0x88, std::make_pair(e65::type::E65_PCOMMAND_DEY, e65::type::E65_PCOMMAND_MODE_IMPLIED)),
			std::make_pair(0x4d, std::make_pair(e65::type::E65_PCOMMAND_EOR, e65::type::E65_PCOMMAND_MODE_ABSOLUTE)),
			std::make_pair(0x5d, std::make_pair(e65::type::E65_PCOMMAND_EOR, e65::type::E65_PCOMMAND_MODE_ABSOLUTE_INDEX_X)),
			std::make_pair(0x59, std::make_pair(e65::type::E65_PCOMMAND_EOR, e65::type::E65_PCOMMAND_MODE_ABSOLUTE_INDEX_Y)),
			std::make_pair(0x49, std::make_pair(e65::type::E65_PCOMMAND_EOR, e65::type::E65_PCOMMAND_MODE_IMMEDIATE)),
			std::make_pair(0x45, std::make_pair(e65::type::E65_PCOMMAND_EOR, e65::type::E65_PCOMMAND_MODE_ZEROPAGE)),
			std::make_pair(0x41, std::make_pair(e65::type::E65_PCOMMAND_EOR, e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDEX_INDIRECT)),
			std::make_pair(0x55, std::make_pair(e65::type::E65_PCOMMAND_EOR, e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDEX_X)),
			std::make_pair(0x52, std::make_pair(e65::type::E65_PCOMMAND_EOR, e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDIRECT)),
			std::make_pair(0x51, std::make_pair(e65::type::E65_PCOMMAND_EOR, e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDIRECT_INDEX)),
			std::make_pair(0xe8, std::make_pair(e65::type::E65_PCOMMAND_INX, e65::type::E65_PCOMMAND_MODE_IMPLIED)),
			std::make_pair(0xc8, std::make_pair(e65::type::E65_PCOMMAND_INY, e65::type::E65_PCOMMAND_MODE_IMPLIED)),
			std::make_pair(0xad, std::make_pair(e65::type::E65_PCOMMAND_LDA, e65::type::E65_PCOMMAND_MODE_ABSOLUTE)),
			std::make_pair(0xbd, std::make_pair(e65::type::E65_PCOMMAND_LDA, e65::type::E65_PCOMMAND_MODE_ABSOLUTE_INDEX_X)),
			std::make_pair(0xb9, std::make_pair(e65::type::E65_PCOMMAND_LDA, e65::type::E65_PCOMMAND_MODE_ABSOLUTE_INDEX_Y)),
			std::make_pair(0xa9, std::make_pair(e65::type::E65_PCOMMAND_LDA, e65::type::E65_PCOMMAND_MODE_IMMEDIATE)),
			std::make_pair(0xa5, std::make_pair(e65::type::E65_PCOMMAND_LDA, e65::type::E65_PCOMMAND_MODE_ZEROPAGE)),
			std::make_pair(0xa1, std::make_pair(e65::type::E65_PCOMMAND_LDA, e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDEX_INDIRECT)),
			std::make_pair(0xb5, std::make_pair(e65::type::E65_PCOMMAND_LDA, e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDEX_X)),
			std::make_pair(0xb2, std::make_pair(e65::type::E65_PCOMMAND_LDA, e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDIRECT)),
			std::make_pair(0xb1, std::make_pair(e65::type::E65_PCOMMAND_LDA, e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDIRECT_INDEX)),
			std::make_pair(0xea, std::make_pair(e65::type::E65_PCOMMAND_NOP, e65::type::E65_PCOMMAND_MODE_IMPLIED)),
			std::make_pair(0x0d, std::make_pair(e65::type::E65_PCOMMAND_ORA, e65::type::E65_PCOMMAND_MODE_ABSOLUTE)),
			std::make_pair(0x1d, std::make_pair(e65::type::E65_PCOMMAND_ORA, e65::type::E65_PCOMMAND_MODE_ABSOLUTE_INDEX_X)),
			std::make_pair(0x19, std::make_pair(e65::type::E65_PCOMMAND_ORA, e65::type::E65_PCOMMAND_MODE_ABSOLUTE_INDEX_Y)),
			std::make_pair(0x09, std::make_pair(e65::type::E65_PCOMMAND_ORA, e65::type::E65_PCOMMAND_MODE_IMMEDIATE)),
			std::make_pair(0x05, std::make_pair(e65::type::E65_PCOMMAND_ORA, e65::type::E65_PCOMMAND_MODE_ZEROPAGE)),
			std::make_pair(0x01, std::make_pair(e65::type::E65_PCOMMAND_ORA, e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDEX_INDIRECT)),
			std::make_pair(0x15, std::make_pair(e65::type::E65_PCOMMAND_ORA, e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDEX_X)),
			std::make_pair(0x12, std::make_pair(e65::type::E65_PCOMMAND_ORA, e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDIRECT)),
			std::make_pair(0x11, std::make_pair(e65::type::E65_PCOMMAND_ORA, e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDIRECT_INDEX)),
			std::make_pair(0x48, std::make_pair(e65::type::E65_PCOMMAND_PHA, e65::type::E65_PCOMMAND_MODE_IMPLIED)),
			std::make_pair(0x08, std::make_pair(e65::type::E65_PCOMMAND_PHP, e65::type::E65_PCOMMAND_MODE_IMPLIED)),
			std::make_pair(0xda, std::make_pair(e65::type::E65_PCOMMAND_PHX, e65::type::E65_PCOMMAND_MODE_IMPLIED)),
			std::make_pair(0x5a, std::make_pair(e65::type::E65_PCOMMAND_PHY, e65::type::E65_PCOMMAND_MODE_IMPLIED)),
			std::make_pair(0x68, std::make_pair(e65::type::E65_PCOMMAND_PLA, e65::type::E65_PCOMMAND_MODE_IMPLIED)),
			std::make_pair(0x28, std::make_pair(e65::type::E65_PCOMMAND_PLP, e65::type::E65_PCOMMAND_MODE_IMPLIED)),
			std::make_pair(0xfa, std::make_pair(e65::type::E65_PCOMMAND_PLX, e65::type::E65_PCOMMAND_MODE_IMPLIED)),
			std::make_pair(0x7a, std::make_pair(e65::type::E65_PCOMMAND_PLY, e65::type::E65_PCOMMAND_MODE_IMPLIED)),
			std::make_pair(0x40, std::make_pair(e65::type::E65_PCOMMAND_RTI, e65::type::E65_PCOMMAND_MODE_IMPLIED)),
			std::make_pair(0x60, std::make_pair(e65::type::E65_PCOMMAND_RTS, e65::type::E65_PCOMMAND_MODE_IMPLIED)),
			std::make_pair(0xed, std::make_pair(e65::type::E65_PCOMMAND_SBC, e65::type::E65_PCOMMAND_MODE_ABSOLUTE)),
			std::make_pair(0xfd, std::make_pair(e65::type::E65_PCOMMAND_SBC, e65::type::E65_PCOMMAND_MODE_ABSOLUTE_INDEX_X)),
			std::make_pair(0xf9, std::make_pair(e65::type::E65_PCOMMAND_SBC, e65::type::E65_PCOMMAND_MODE_ABSOLUTE_INDEX_Y)),
			std::make_pair(0xe9, std::make_pair(e65::type::E65_PCOMMAND_SBC, e65::type::E65_PCOMMAND_MODE_IMMEDIATE)),
			std::make_pair(0xe5, std::make_pair(e65::type::E65_PCOMMAND_SBC, e65::type::E65_PCOMMAND_MODE_ZEROPAGE)),
			std::make_pair(0xe1, std::make_pair(e65::type::E65_PCOMMAND_SBC, e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDEX_INDIRECT)),
			std::make_pair(0xf5, std::make_pair(e65::type::E65_PCOMMAND_SBC, e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDEX_X)),
			std::make_pair(0xf2, std::make_pair(e65::type::E65_PCOMMAND_SBC, e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDIRECT)),
			std::make_pair(0xf1, std::make_pair(e65::type::E65_PCOMMAND_SBC, e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDIRECT_INDEX)),
			std::make_pair(0x38, std::make_pair(e65::type::E65_PCOMMAND_SEC, e65::type::E65_PCOMMAND_MODE_IMPLIED)),
			std::make_pair(0xf8, std::make_pair(e65::type::E65_PCOMMAND_SED, e65::type::E65_PCOMMAND_MODE_IMPLIED)),
			std::make_pair(0x78, std::make_pair(e65::type::E65_PCOMMAND_SEI, e65::type::E65_PCOMMAND_MODE_IMPLIED)),
			std::make_pair(0x8d, std::make_pair(e65::type::E65_PCOMMAND_STA, e65::type::E65_PCOMMAND_MODE_ABSOLUTE)),
			std::make_pair(0x9d, std::make_pair(e65::type::E65_PCOMMAND_STA, e65::type::E65_PCOMMAND_MODE_ABSOLUTE_INDEX_X)),
			std::make_pair(0x99, std::make_pair(e65::type::E65_PCOMMAND_STA, e65::type::E65_PCOMMAND_MODE_ABSOLUTE_INDEX_Y)),
			std::make_pair(0x85, std::make_pair(e65::type::E65_PCOMMAND_STA, e65::type::E65_PCOMMAND_MODE_ZEROPAGE)),
			std::make_pair(0x81, std::make_pair(e65::type::E65_PCOMMAND_STA, e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDEX_INDIRECT)),
			std::make_pair(0x95, std::make_pair(e65::type::E65_PCOMMAND_STA, e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDEX_X)),
			std::make_pair(0x92, std::make_pair(e65::type::E65_PCOMMAND_STA, e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDIRECT)),
			std::make_pair(0x91, std::make_pair(e65::type::E65_PCOMMAND_STA, e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDIRECT_INDEX)),
			std::make_pair(0xdb, std::make_pair(e65::type::E65_PCOMMAND_STP, e65::type::E65_PCOMMAND_MODE_IMPLIED)),
			std::make_pair(0xaa, std::make_pair(e65::type::E65_PCOMMAND_TAX, e65::type::E65_PCOMMAND_MODE_IMPLIED)),
			std::make_pair(0xa8, std::make_pair(e65::type::E65_PCOMMAND_TAY, e65::type::E65_PCOMMAND_MODE_IMPLIED)),
			std::make_pair(0xba, std::make_pair(e65::type::E65_PCOMMAND_TSX, e65::type::E65_PCOMMAND_MODE_IMPLIED)),
			std::make_pair(0x8a, std::make_pair(e65::type::E65_PCOMMAND_TXA, e65::type::E65_PCOMMAND_MODE_IMPLIED)),
			std::make_pair(0x9a, std::make_pair(e65::type::E65_PCOMMAND_TXS, e65::type::E65_PCOMMAND_MODE_IMPLIED)),
			std::make_pair(0x98, std::make_pair(e65::type::E65_PCOMMAND_TYA, e65::type::E65_PCOMMAND_MODE_IMPLIED)),
			std::make_pair(0x9a, std::make_pair(e65::type::E65_PCOMMAND_WAI, e65::type::E65_PCOMMAND_MODE_IMPLIED)),
			};

		static const std::map<int, std::pair<uint8_t, uint8_t>> E65_PCOMMAND_ABSOLUTE_CYCLE_MAP = {
			std::make_pair(e65::type::E65_PCOMMAND_ADC, std::make_pair(4, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_AND, std::make_pair(4, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_CMP, std::make_pair(4, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_EOR, std::make_pair(4, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_LDA, std::make_pair(4, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_ORA, std::make_pair(4, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_SBC, std::make_pair(4, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_STA, std::make_pair(4, 0)),
			};

		static const std::map<int, std::pair<uint8_t, uint8_t>> E65_PCOMMAND_ABSOLUTE_INDEX_X_CYCLE_MAP = {
			std::make_pair(e65::type::E65_PCOMMAND_ADC, std::make_pair(4, 1)),
			std::make_pair(e65::type::E65_PCOMMAND_AND, std::make_pair(4, 1)),
			std::make_pair(e65::type::E65_PCOMMAND_CMP, std::make_pair(4, 1)),
			std::make_pair(e65::type::E65_PCOMMAND_EOR, std::make_pair(4, 1)),
			std::make_pair(e65::type::E65_PCOMMAND_LDA, std::make_pair(4, 1)),
			std::make_pair(e65::type::E65_PCOMMAND_ORA, std::make_pair(4, 1)),
			std::make_pair(e65::type::E65_PCOMMAND_SBC, std::make_pair(4, 1)),
			std::make_pair(e65::type::E65_PCOMMAND_STA, std::make_pair(5, 0)),
			};

		static const std::map<int, std::pair<uint8_t, uint8_t>> E65_PCOMMAND_ABSOLUTE_INDEX_Y_CYCLE_MAP = {
			std::make_pair(e65::type::E65_PCOMMAND_ADC, std::make_pair(4, 1)),
			std::make_pair(e65::type::E65_PCOMMAND_AND, std::make_pair(4, 1)),
			std::make_pair(e65::type::E65_PCOMMAND_CMP, std::make_pair(4, 1)),
			std::make_pair(e65::type::E65_PCOMMAND_EOR, std::make_pair(4, 1)),
			std::make_pair(e65::type::E65_PCOMMAND_LDA, std::make_pair(4, 1)),
			std::make_pair(e65::type::E65_PCOMMAND_ORA, std::make_pair(4, 1)),
			std::make_pair(e65::type::E65_PCOMMAND_SBC, std::make_pair(4, 1)),
			std::make_pair(e65::type::E65_PCOMMAND_STA, std::make_pair(5, 0)),
			};

		static const std::map<int, std::pair<uint8_t, uint8_t>> E65_PCOMMAND_IMMEDIATE_CYCLE_MAP = {
			std::make_pair(e65::type::E65_PCOMMAND_ADC, std::make_pair(2, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_AND, std::make_pair(2, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_CMP, std::make_pair(2, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_EOR, std::make_pair(2, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_LDA, std::make_pair(2, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_ORA, std::make_pair(2, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_SBC, std::make_pair(2, 0)),
			};

		static const std::map<int, std::pair<uint8_t, uint8_t>> E65_PCOMMAND_IMPLIED_CYCLE_MAP = {
			std::make_pair(e65::type::E65_PCOMMAND_BRK, std::make_pair(7, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_CLC, std::make_pair(2, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_CLD, std::make_pair(2, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_CLI, std::make_pair(2, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_CLV, std::make_pair(2, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_DEX, std::make_pair(2, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_DEY, std::make_pair(2, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_INX, std::make_pair(2, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_INY, std::make_pair(2, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_NOP, std::make_pair(2, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_PHA, std::make_pair(3, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_PHP, std::make_pair(3, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_PHX, std::make_pair(3, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_PHY, std::make_pair(3, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_PLA, std::make_pair(4, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_PLP, std::make_pair(4, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_PLX, std::make_pair(4, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_PLY, std::make_pair(4, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_RTI, std::make_pair(6, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_RTS, std::make_pair(6, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_SEC, std::make_pair(2, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_SED, std::make_pair(2, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_SEI, std::make_pair(2, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_STP, std::make_pair(3, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_TAX, std::make_pair(2, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_TAY, std::make_pair(2, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_TSX, std::make_pair(2, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_TXA, std::make_pair(2, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_TXS, std::make_pair(2, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_TYA, std::make_pair(2, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_WAI, std::make_pair(2, 0)),
			};

		static const std::map<int, std::pair<uint8_t, uint8_t>> E65_PCOMMAND_ZEROPAGE_CYCLE_MAP = {
			std::make_pair(e65::type::E65_PCOMMAND_ADC, std::make_pair(3, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_AND, std::make_pair(3, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_CMP, std::make_pair(3, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_EOR, std::make_pair(3, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_LDA, std::make_pair(3, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_ORA, std::make_pair(3, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_SBC, std::make_pair(3, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_STA, std::make_pair(3, 0)),
			};

		static const std::map<int, std::pair<uint8_t, uint8_t>> E65_PCOMMAND_ZEROPAGE_INDEX_INDIRECT_CYCLE_MAP = {
			std::make_pair(e65::type::E65_PCOMMAND_ADC, std::make_pair(6, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_AND, std::make_pair(6, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_CMP, std::make_pair(6, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_EOR, std::make_pair(6, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_LDA, std::make_pair(6, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_ORA, std::make_pair(6, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_SBC, std::make_pair(6, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_STA, std::make_pair(6, 0)),
			};

		static const std::map<int, std::pair<uint8_t, uint8_t>> E65_PCOMMAND_ZEROPAGE_INDEX_X_CYCLE_MAP = {
			std::make_pair(e65::type::E65_PCOMMAND_ADC, std::make_pair(4, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_AND, std::make_pair(4, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_CMP, std::make_pair(4, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_EOR, std::make_pair(4, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_LDA, std::make_pair(4, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_ORA, std::make_pair(4, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_SBC, std::make_pair(4, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_STA, std::make_pair(4, 0)),
			};

		static const std::map<int, std::pair<uint8_t, uint8_t>> E65_PCOMMAND_ZEROPAGE_INDIRECT_CYCLE_MAP = {
			std::make_pair(e65::type::E65_PCOMMAND_ADC, std::make_pair(5, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_AND, std::make_pair(5, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_CMP, std::make_pair(5, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_EOR, std::make_pair(5, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_LDA, std::make_pair(5, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_ORA, std::make_pair(5, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_SBC, std::make_pair(5, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_STA, std::make_pair(5, 0)),
			};

		static const std::map<int, std::pair<uint8_t, uint8_t>> E65_PCOMMAND_ZEROPAGE_INDIRECT_INDEX_CYCLE_MAP = {
			std::make_pair(e65::type::E65_PCOMMAND_ADC, std::make_pair(5, 1)),
			std::make_pair(e65::type::E65_PCOMMAND_AND, std::make_pair(5, 1)),
			std::make_pair(e65::type::E65_PCOMMAND_CMP, std::make_pair(5, 1)),
			std::make_pair(e65::type::E65_PCOMMAND_EOR, std::make_pair(5, 1)),
			std::make_pair(e65::type::E65_PCOMMAND_LDA, std::make_pair(5, 1)),
			std::make_pair(e65::type::E65_PCOMMAND_ORA, std::make_pair(5, 1)),
			std::make_pair(e65::type::E65_PCOMMAND_SBC, std::make_pair(5, 1)),
			std::make_pair(e65::type::E65_PCOMMAND_STA, std::make_pair(6, 0)),
			};

		static const std::map<int, std::map<int, std::pair<uint8_t, uint8_t>>> E65_PCOMMAND_CYCLE_MAP = {
			std::make_pair(e65::type::E65_PCOMMAND_MODE_ABSOLUTE, E65_PCOMMAND_ABSOLUTE_CYCLE_MAP),
			std::make_pair(e65::type::E65_PCOMMAND_MODE_ABSOLUTE_INDEX_X, E65_PCOMMAND_ABSOLUTE_INDEX_X_CYCLE_MAP),
			std::make_pair(e65::type::E65_PCOMMAND_MODE_ABSOLUTE_INDEX_Y, E65_PCOMMAND_ABSOLUTE_INDEX_Y_CYCLE_MAP),
			std::make_pair(e65::type::E65_PCOMMAND_MODE_IMMEDIATE, E65_PCOMMAND_IMMEDIATE_CYCLE_MAP),
			std::make_pair(e65::type::E65_PCOMMAND_MODE_IMPLIED, E65_PCOMMAND_IMPLIED_CYCLE_MAP),
			std::make_pair(e65::type::E65_PCOMMAND_MODE_ZEROPAGE, E65_PCOMMAND_ZEROPAGE_CYCLE_MAP),
			std::make_pair(e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDEX_INDIRECT, E65_PCOMMAND_ZEROPAGE_INDEX_INDIRECT_CYCLE_MAP),
			std::make_pair(e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDEX_X, E65_PCOMMAND_ZEROPAGE_INDEX_X_CYCLE_MAP),
			std::make_pair(e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDIRECT, E65_PCOMMAND_ZEROPAGE_INDIRECT_CYCLE_MAP),
			std::make_pair(e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDIRECT_INDEX, E65_PCOMMAND_ZEROPAGE_INDIRECT_INDEX_CYCLE_MAP),
			};

		enum {
			E65_PCOMMAND_LENGTH_NONE = 1,
			E65_PCOMMAND_LENGTH_BYTE,
			E65_PCOMMAND_LENGTH_WORD,
		};

		static const std::map<int, int> E65_PCOMMAND_LENGTH_MAP = {
			std::make_pair(e65::type::E65_PCOMMAND_MODE_ABSOLUTE, e65::type::E65_PCOMMAND_LENGTH_WORD),
			std::make_pair(e65::type::E65_PCOMMAND_MODE_ABSOLUTE_INDEX_X, e65::type::E65_PCOMMAND_LENGTH_WORD),
			std::make_pair(e65::type::E65_PCOMMAND_MODE_ABSOLUTE_INDEX_Y, e65::type::E65_PCOMMAND_LENGTH_WORD),
			std::make_pair(e65::type::E65_PCOMMAND_MODE_IMMEDIATE, e65::type::E65_PCOMMAND_LENGTH_BYTE),
			std::make_pair(e65::type::E65_PCOMMAND_MODE_IMPLIED, e65::type::E65_PCOMMAND_LENGTH_NONE),
			std::make_pair(e65::type::E65_PCOMMAND_MODE_ZEROPAGE, e65::type::E65_PCOMMAND_LENGTH_BYTE),
			std::make_pair(e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDEX_INDIRECT, e65::type::E65_PCOMMAND_LENGTH_BYTE),
			std::make_pair(e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDEX_X, e65::type::E65_PCOMMAND_LENGTH_BYTE),
			std::make_pair(e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDIRECT, e65::type::E65_PCOMMAND_LENGTH_BYTE),
			std::make_pair(e65::type::E65_PCOMMAND_MODE_ZEROPAGE_INDIRECT_INDEX, e65::type::E65_PCOMMAND_LENGTH_BYTE),
			};
	}
}

#endif // E65_TYPE_PCOMMAND_H_
