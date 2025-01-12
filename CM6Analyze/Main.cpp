#include <stdio.h>
#include <string>
#include <vector>

#include "analyze.h"

int main(int argc,char* argv[])
{
	if (argc!=2)
	{
		printf_s("Usage: CM6Analyze filename[.cm6]\n");
		return -1;
	}

	int retval=0;

	CM6Analyze* pAnalyzer=new CM6Analyze;
	if (pAnalyzer->readFile(argv[1]))
	{
		if (pAnalyzer->isAnalyzed())
		{
			printf_s("LA Part\n");
			for (int i=0;i<128;++i)
			{
				printf_s("Program No.\t(for RCM #%03d) #%03d\tPatchName\t%s\n",i,i+1,pAnalyzer->getLAPatchName(i).c_str());
			}
			printf_s("PCM Part \n");
			for (int i = 0; i < 128; ++i)
			{
				printf_s("Program No.\t(for RCM #%03d) #%03d\tPatchName\t%s\n", i, i + 1, pAnalyzer->getPCMPatchName(i).c_str());
			}
		}
		else
		{
			printf_s("Error occur on analyze.\n");
			retval=-1;
		}
	}
	else
	{
		printf_s("Can't open file\n");
		retval=-1;
	}

	delete pAnalyzer;pAnalyzer=NULL;

	return retval;
}
