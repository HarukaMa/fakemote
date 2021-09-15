/*
	Custom IOS Library

	Copyright (C) 2008 neimod.
	Copyright (C) 2009 WiiGator.
	Copyright (C) 2009 Waninkoko.
	Copyright (C) 2010 Hermes.
	Copyright (C) 2011 davebaol.

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "stealth.h"
#include "swi_mload.h"
#include "syscalls.h"
#include "types.h"


s32 Stealth_CheckRunningTitle(const char* command)
{
	s32 ret;

	/* Get stealth mode */
	ret = Swi_GetRunningTitle();

	 /* Trace blocked request */
	if (ret)
		Stealth_Log(STEALTH_RUNNING_TITLE, command);

	return ret;
}

s32 Stealth_CheckEsRequest(const char* command)
{
	s32 ret;

	/* Get ES status */
	ret = Swi_GetEsRequest();

	/* Trace blocked request */
	if (!ret)
		Stealth_Log(STEALTH_ES_REQUEST, command);

	return ret;
}

void Stealth_Log(u32 type, const char* command)
{
	svc_write(moduleName);
	svc_write(": ");
	if (type & STEALTH_RUNNING_TITLE) {
		svc_write("Title identified");
		if (type & STEALTH_ES_REQUEST)
			svc_write(" or ");
	}
	if (type & STEALTH_ES_REQUEST)
		svc_write("Request not coming from ES");
	svc_write(". Blocking ");
	if (command) {
		svc_write("custom command ");
		svc_write(command);
	}
	else
		svc_write("opening request");
	svc_write(".\n");
}


