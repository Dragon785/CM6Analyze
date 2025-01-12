#pragma once

#include <string>
#include <vector>
#include "MT32Params.h"
#include "CM32PParams.h"

class CM6Analyze
{
public:
	CM6Analyze();
	virtual ~CM6Analyze();
	bool readFile(std::string fileName);
	bool isAnalyzed() const { return _isAnalyzed; };
	std::string getLAPatchName(int patchNo);
	std::string getPCMPatchName(int patchNo);

private:
	bool _isAnalyzed;
	MT32Param::PatchMemory _LAPatch[128];
	MT32Param::TimbreMemory _userTimber[64];
	CM32PParam::PatchMemory _PCMPatch[128];

private:
	char* _readBuf;
	bool checkAndReadFile(std::string fileName);
};