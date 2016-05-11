/*
 * EEPROM_Mapping.h
 *
 *  Created on: 09-May-2016
 *      Author: MSamal
 *
 *  LICENSE:-
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef INC_EEPROM_MAPPING_H_
#define INC_EEPROM_MAPPING_H_

#include "porting.h"

/*! \var EE_PAGES
    \brief A Macro for EEPROM Page count
*/
#define EE_PAGES				(64)

/*! \var EE_PAGESIZE
    \brief A Macro for EEPROM Page size
*/
#define EE_PAGESIZE				(32)

#define __SIMULATE_EE_MEMORY_AS_ARRAY



EE_ReturnCode_t EE_ReadWrite(UINT16_t Address, UINT8_t * pWriteBuffer,
		size_t Size, EE_Opcode_t operation);
#endif /* INC_EEPROM_MAPPING_H_ */
