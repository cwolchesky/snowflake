/*
* snowflake - An IoT controller for an AC using an Arduino-based device
* Copyright (C) 2017 Chris Wolchesky
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <IRLibSendBase.h>
#include <IRLib_HashRaw.h>

#define RAW_DATA_LEN 68

class Remote {
private:
  IRsendRaw IRSender;
public:
  void powerButton(void);
  void coolMode(void);
  void energySaverMode(void);
  void fanOnlyMode(void);
  void autoFanMode(void);
  void sleepButton(void);
  void timerButton(void);
  void fanDown(void);
  void fanUp(void);
  void tempDown(void);
  void tempUp(void);
}
