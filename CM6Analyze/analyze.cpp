#include "analyze.h"
#include <assert.h>
#include <stdio.h>

namespace
{
	const char* MT32PresetA[64]=
	{
		"A.Piano1",
		"A.Piano2",
		"A.Piano3",
		"E.Piano1",
		"E.Piano2",
		"E.Piano3",
		"E.Piano4",
		"Honkytonk",
		
		"E.Org1",
		"E.Org2",
		"E.Org3",
		"E.Org4",
		"PipeOrg1",
		"PipeOrg2",
		"PipeOrg3",
		"Accordion",

		"Harpsi.1",
		"Harpsi.2",
		"Harpsi.3",
		"Clavi1",
		"Clavi2",
		"Clavi3",
		"Celesta1",
		"Celesta2",

		"SynBrass1",
		"SynBrass2",
		"SynBrass3",
		"SynBrass4",
		"SynBass1",
		"SynBass2",
		"SynBass3",
		"SynBass4",

		"Fantasy",
		"HarmoPan",
		"Chorale",
		"Glasses",
		"Soundtrack",
		"Atmosphere",
		"Warm Bell",
		"Funny Vox",
		
		"Echo Bell",
		"Ice Rain",
		"Oboe2001",
		"EchoPan",
		"DoctorSolo",
		"Schooldaze",
		"Bellsinger",
		"SquareWave",

		"Str Sect1",
		"Str Sect2",
		"Str Sect3",
		"Pizzicato",
		"Violin1",
		"Violin2",
		"Cello1",
		"Cello2",

		"Contrabass",
		"Harp1",
		"Harp2",
		"Guitar1",
		"Guitar2",
		"E.Guitar1",
		"E.Guitar2",
		"Sitar"
	};

	const char* MT32PresetB[64]=
	{
		"A.Bass1",
		"A.Bass2",
		"E.Bass1",
		"E.Bass2",
		"SlapBass1",
		"SlapBass2",
		"Fretless1",
		"Fretless2",

		"Flute1",
		"Flute2",
		"Piccolo1",
		"Piccolo2",
		"Recorder",
		"PanPipes",
		"Sax1",
		"Sax2",

		"Sax3",
		"Sax4",
		"Clarinet1",
		"Clarinet2",
		"Oboe",
		"Engl Horn",
		"Bassoon",
		"Harmonica",
		
		"Trumpet 1",
		"Trumpet 2",
		"Trombone1",
		"Trombone2",
		"Fr Horn1",
		"Fr Horn2",
		"Tuba",
		"Brs Sect1",
		
		"Brs Sect2",
		"Vibe 1",
		"Vibe 2",
		"Syn Mallet",
		"Windbell",
		"Glock",
		"Tube Bell",
		"Xylophone",

		"Marimba",
		"Koto",
		"Sho",
		"Shakuhachi",
		"Whistle1",
		"Whistle2",
		"Bottleblow",
		"BreathPipe",

		"Timpani",
		"Melodic Tom",
		"Deep Snare",
		"Elec Perc1",
		"Elec Perc2",
		"Taiko",
		"Taiko Rim",
		"Cymbal",

		"Castanets",
		"Triangle",
		"Orche Hit",
		"Telephone",
		"Bird Tweet",
		"One Note Jam",
		"Water Bells",
		"Jungle Tune"
	};

	const int CM6FileSize=22601;

	const int CM6LASystemAreaStart=0x0080;
	const int CM6UserTimberStart=0x0e34;
	const int CM6UserTimberSize=0x100;
	const int CM6RhythmSetTemp1Start=0x130;
	const int CM6RhyhmSetTemp2Start=0x230; // CM64 Only Data
	const int CM6LAPatchTempAreaStart=0x00a0;
	const int CM6TimberTempArea1Start=0x0284;
	const int CM6TimberTempArea2Start=0x037a;
	const int CM6TimberTempArea2Size=0x0f6;
	const int CM6LAPatchMemoryStart=0x0a34; //a34/ab4/b34/bb4/c34/cb4/d43/db4 each 16 memory(8 bytes*16)
	const int CM6PCMPatchTempStart=0x4e34;
	const int CM6PCMPatchMemoryStart=0x4eb2; // 0x98 byte each 16 memory(19 bytes*16)
	const int CM6PCMSysAreaStart=0x5832;

};

CM6Analyze::CM6Analyze()
{
	_readBuf=NULL;
	_isAnalyzed=false;
}

CM6Analyze::~CM6Analyze()
{
	delete[] _readBuf;
	_readBuf=NULL;
}

std::string CM6Analyze::getPCMPatchName(int patchNo)
{
	if (patchNo < 128)
	{
		return _PCMPatch[patchNo].getToneName();
	}
	else
	{
		assert(0);
		return "Unknown Param.(bug?)";
	}
}

std::string CM6Analyze::getLAPatchName(int patchNo)
{
	if (patchNo<128)
	{
		int timbreNo=_LAPatch[patchNo].timbrenumber;
		switch (_LAPatch[patchNo].timbregroup)
		{
		case MT32Param::PatchMemory::GROUP_A:
			return MT32PresetA[timbreNo];
			break;
		case MT32Param::PatchMemory::GROUP_B:
			return MT32PresetB[timbreNo];
			break;
		case MT32Param::PatchMemory::GROUP_USER:
			return _userTimber[timbreNo].commonParam.patchName;
			break;
		case MT32Param::PatchMemory::GROUP_RHYTHM:
			return "RHYTHM Note";
			break;
		default:
			assert(0);
			return "Unknown Param.(bug?)";
			break;
		}
	}
	else
	{
		assert(0);
		return "Unknown Param.(bug?)";
	}
}

bool CM6Analyze::readFile(std::string fileName)
{
	if (!checkAndReadFile(fileName))
	{
		return false;
	}
	for (int i=0;i<64;++i)
	{
		_userTimber[i].readData(&(_readBuf[CM6UserTimberStart+i*CM6UserTimberSize]));
	}
	for (int i=0;i<128;++i)
	{
		_LAPatch[i].readData(&(_readBuf[CM6LAPatchMemoryStart+i*8]));
	}
	for (int i = 0; i < 128; ++i)
	{
		_PCMPatch[i].readData(&(_readBuf[CM6PCMPatchMemoryStart + i * 0x13]));
	}
	_isAnalyzed=true;

	return true;
}

bool CM6Analyze::checkAndReadFile(std::string fileName)
{
	FILE* f;
	errno_t err=fopen_s(&f,fileName.c_str(),"rb");
	if (err!=0)
	{
		printf_s("fopen error.\n");
		return false; // Ž¸”s
	}

	// check filesize
	fseek(f,0,SEEK_END);
	if (ftell(f)!=22601)
	{
		printf_s("file size mismatch.\n");
		return false;
	}
	fseek(f,0,SEEK_SET);
	delete[] _readBuf;
	_readBuf=new char[CM6FileSize];

	fread_s(_readBuf,CM6FileSize,1,CM6FileSize,f);

	fclose(f);

	return true; // ¬Œ÷
}

