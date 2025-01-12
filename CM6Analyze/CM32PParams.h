#pragma once
#include <string>

namespace CM32PParam
{
	struct PatchMemory
	{
		enum MEDIA
		{
			INTERNAL=0,
			CARD=1,
		} media;
		int toneNumber;
		int keyShift;
		int fineTune;
		int benderRange;
		std::string toneName;

		void clear();
		void readData(const char* from);
		const std::string& getToneName() const {
			return toneName;
		};

		PatchMemory() {
			clear();
		};
	};

}