#include "ext/cores.h"

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
