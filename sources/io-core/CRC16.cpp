/* SECU-3  - An open source, free engine control unit
   Copyright (C) 2007 Alexey A. Shabelnikov. Ukraine, Gorlovka

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.

   contacts:
              http://secu-3.org
              email: shabelnikov@secu-3.org
*/

#include "stdafx.h"
#include "CRC16.h"

#define      P_16        0xA001

unsigned short CRC_API crc16(const unsigned char *buf, unsigned long num)
{
 unsigned int i;
 unsigned short crc = 0xffff;

 while ( num-- )
 {
  crc ^= *buf++;
  i = 8;
  do
  {
   if ( crc & 1 )
    crc = ( crc >> 1 ) ^ P_16;
   else
    crc >>= 1;
  } while ( --i );
 }
 return( crc );
}
