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

		#define E65_PCOMMAND_MAX e65::type::E65_PCOMMAND_WAI

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

		#define E65_PCOMMAND_MODE_MAX E65_PCOMMAND_MODE_ZEROPAGE_INDIRECT_INDEX

		static const std::string E65_PCOMMAND_MODE_STR[] = {
			"abs", "[abs, x]", "abs, x", "abs, y", "[abs]", "acc", "imm", "imp", "rel", "zp", "[zp, x]",
			"zp, x", "zp, y", "[zp]", "[zp], y",
			};

		#define E65_PCOMMAND_MODE_STRING(_TYPE_) \
			(((_TYPE_) > E65_PCOMMAND_MODE_MAX) ? A65_STRING_UNKNOWN : \
				A65_STRING_CHECK(E65_PCOMMAND_MODE_STR[_TYPE_]))

		static const std::map<uint8_t, std::pair<int, int>> E65_PCOMMAND_ID_MAP = {
			std::make_pair(0x00, std::make_pair(e65::type::E65_PCOMMAND_BRK, e65::type::E65_PCOMMAND_MODE_IMPLIED)),
			std::make_pair(0xea, std::make_pair(e65::type::E65_PCOMMAND_NOP, e65::type::E65_PCOMMAND_MODE_IMPLIED)),
			std::make_pair(0xdb, std::make_pair(e65::type::E65_PCOMMAND_STP, e65::type::E65_PCOMMAND_MODE_IMPLIED)),
			std::make_pair(0x9a, std::make_pair(e65::type::E65_PCOMMAND_WAI, e65::type::E65_PCOMMAND_MODE_IMPLIED)),

			// TODO
			};

		#define E65_PCOMMAND_VALID(_TYPE_) \
			(e65::type::E65_PCOMMAND_ID_MAP.find(_TYPE_) != e65::type::E65_PCOMMAND_ID_MAP.end())

		#define E65_PCOMMAND_ID(_TYPE_) \
			e65::type::E65_PCOMMAND_ID_MAP.find(_TYPE_)->second.first

		#define E65_PCOMMAND_MODE(_TYPE_) \
			e65::type::E65_PCOMMAND_MODE_MAP.find(_TYPE_)->second.second

		static const std::map<int, std::pair<uint8_t, uint8_t>> E65_PCOMMAND_CYCLE_MAP = {
			std::make_pair(e65::type::E65_PCOMMAND_BRK, std::make_pair(7, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_NOP, std::make_pair(2, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_STP, std::make_pair(3, 0)),
			std::make_pair(e65::type::E65_PCOMMAND_WAI, std::make_pair(2, 0)),

			// TODO
			};

		#define E65_PCOMMAND_CYCLE_NOT_TAKEN(_TYPE_) \
			e65::type::E65_PCOMMAND_CYCLE_MAP.find(_TYPE_)->second.second

		#define E65_PCOMMAND_CYCLE_TAKEN(_TYPE_) \
			e65::type::E65_PCOMMAND_CYCLE_MAP.find(_TYPE_)->second.first

		enum {
			E65_PCOMMAND_LENGTH_NONE = 1,
			E65_PCOMMAND_LENGTH_BYTE,
			E65_PCOMMAND_LENGTH_WORD,
		};

		static const std::map<int, uint8_t> E65_PCOMMAND_LENGTH_MAP = {
			std::make_pair(e65::type::E65_PCOMMAND_BRK, E65_PCOMMAND_LENGTH_NONE),
			std::make_pair(e65::type::E65_PCOMMAND_NOP, E65_PCOMMAND_LENGTH_NONE),
			std::make_pair(e65::type::E65_PCOMMAND_STP, E65_PCOMMAND_LENGTH_NONE),
			std::make_pair(e65::type::E65_PCOMMAND_WAI, E65_PCOMMAND_LENGTH_NONE),

			// TODO
			};

		#define E65_PCOMMAND_LENGTH(_TYPE_) \
			e65::type::E65_PCOMMAND_LENGTH_MAP.find(_TYPE_)->second
	}
}

#endif // E65_TYPE_PCOMMAND_H_
