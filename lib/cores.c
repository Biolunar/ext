/*
 * Copyright 2017 Mahdi Khanalizadeh
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "ext/cores.h"

#ifdef _WIN32

#include <limits.h>

#include <Windows.h>

unsigned int ext_num_cores(void)
{
	SYSTEM_INFO info;
	GetNativeSystemInfo(&info);
	if (info.dwNumberOfProcessors > UINT_MAX)
		return UINT_MAX;
	else
		return info.dwNumberOfProcessors;
}

#else // _WIN32

#include <stdio.h>

unsigned int ext_num_cores(void)
{
	FILE* const file = fopen(u8"/proc/cpuinfo", "r");
	if (!file)
		return 0;

	unsigned int ret = 0;
	char buffer[1024] = {0};
	while (fgets(buffer, sizeof buffer, file))
	{
		if (buffer[0] == '\n')
			++ret;
	}
	if (!feof(file))
		ret = 0; // return 0 even if we read something useful before failing

	fclose(file);
	return ret;
}

#endif // _WIN32
