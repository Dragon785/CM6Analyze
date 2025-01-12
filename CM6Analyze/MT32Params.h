#pragma once
namespace MT32Param
{
	// MT-32ç\ë¢ëÃ
	struct TimbreCommon
	{
		char patchName[11]; // 10+NULL
		enum PartialStruct
		{
			STRUCT_TYPE1=0,
			STRUCT_TYPE2,
			STRUCT_TYPE3,
			STRUCT_TYPE4,
			STRUCT_TYPE5,
			STRUCT_TYPE6,
			STRUCT_TYPE7,
			STRUCT_TYPE8,
			STRUCT_TYPE9,
			STRUCT_TYPE10,
			STRUCT_TYPE11,
			STRUCT_TYPE12,
			STRUCT_TYPE13,
		} partial12,partial34;
		bool partialMute[4]; // bit 0000 to 1111
		bool noSustain;
		TimbreCommon() { clear(); };
		void clear();

		void readData(const char* from);
	};

	struct PartialParam
	{
		int pitchCoarse; // 0 to 96, C1-C9
		int pitchFine; // 0 to 100 -50 to 50
		// and more...
		PartialParam() { clear(); };

		void clear();
		void readData(const char* from);
	};

	struct TimbreMemory
	{
		TimbreCommon commonParam;
		PartialParam partial[4];
		TimbreMemory();

		void readData(const char* from);
	};

	struct PatchMemory
	{
		enum TimbreGroup
		{
			GROUP_A,
			GROUP_B,
			GROUP_USER,
			GROUP_RHYTHM
		} timbregroup;

		int timbrenumber; // 0 to 63
		int keyShift; // 0 to 48 (-24 to +24)
		int fineTune; // 0 to 100 (-50 to +50)
		int benderRange; // 0 to 24
		enum AssignMode
		{
			POLY_1,
			POLY_2,
			POLY_3,
			POLY_4
		} assignMode;

		bool enableReverb;

		void readData(const char* from);

		PatchMemory();
	};
};