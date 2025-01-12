#include "MT32Params.h"

namespace MT32Param
{
	void TimbreCommon::clear()
	{
		for (int i=0;i<11;++i)
		{
			patchName[i]=0;
		}
		partial12=STRUCT_TYPE1;
		partial34=STRUCT_TYPE1;
		for (int i=0;i<4;++i)
		{
			partialMute[i]=false;
		}
		noSustain=false;
	}

	void TimbreCommon::readData(const char* from)
	{
		// timbre name(10 byte)
		for (int i=0;i<10;++i)
		{
			patchName[i]=*(from++);
		}
		patchName[10]=0x00; // Guard
		from++;
		partial12=static_cast<PartialStruct>(*(from++));
		partial34=static_cast<PartialStruct>(*(from++));
		char muteflag=*(from++);
		for (int i=0;i<4;++i)
		{
			partialMute[i]=((muteflag&(1>>(i)))!=0) ? true : false;
		}
		noSustain=(*(from)!=0) ? true:false;
	}

	void PartialParam::clear()
	{
		pitchCoarse=48;
		pitchFine=50;
	}

	void PartialParam::readData(const char* from)
	{
		pitchCoarse=*(from++);
		pitchFine=*(from++);

		// and more
		// keyfollow
		// bender sw
		// wg waveform/pcm bnank
		// wg pcm wave #
		// wg pulse width
		// pw velo sens
		// pitch env depth
		// pitch env velo sens
		// pitch env time keyfollow
		// pitch env time 1
		// pitch env time 2
		// pitch env time 3
		// pitch env time 4
		// pitch env level 0(0-100 -50-50)
		// pitch env level 1
		// pitch env level 2
		// pitch env level sustain
		// pitch end level

		// pitch lfo rate
		// pitch lfo depth
		// pitch lfo mod sens

		// tvf cutoff
		// tvf reso
		// tvf keyfollow(0-14 -1,-1/2,-1/4,0,1/8,1/4,3/8,1/2,5/8,3/4,7/8,1,5/4,3/2,2)
		// tvf bias point/dir 0-127 
		// tvf bias level
		// tvf env depth
		// tvf env velo sens
		// tvf env depth keyf
		// tvf env time keyf
		// tvf env time 1
		// tvf env time 2
		// tvf env time 3
		// tvf env time 4
		// tvf env time 5
		// tvf env level 1
		// tvf env level 2
		// tvf env level 3
		// tvf env sustain level
		// tva level
		// tva velo sens
		// tva bias point 1
		// tva bias level 1
		// tva bias point 2
		// tva bias level 2
		// tva env time keyf 
		// tva env time velo follow
		// tva env time 1
		// tva env time 2
		// tva env time 3
		// tva env time 4
		// tva env time 5
		// tva env level 1
		// tva env level 2
		// tva env level 3
		// tva env sustain level
	}

	TimbreMemory::TimbreMemory()
	{
		commonParam.clear();
		for (int i=0;i<4;++i)
		{
			partial[i].clear();
		}
	}

	void TimbreMemory::readData(const char* from)
	{
		commonParam.readData(from);
		from+=0x0e;
		for (int i=0;i<4;++i)
		{
			partial[i].readData(from);
			from+=0x3a;
		}
	}

	PatchMemory::PatchMemory()
	{
		timbregroup=GROUP_A;
		timbrenumber=0;
		keyShift=24;
		fineTune=50;
		benderRange=12;

		assignMode=POLY_1;

		enableReverb=true;
	}

	void PatchMemory::readData(const char* from)
	{
		timbregroup=static_cast<TimbreGroup>(*(from++));
		timbrenumber=*(from++);
		keyShift=*(from++);
		fineTune=*(from++);
		benderRange=*(from++);
		assignMode=static_cast<AssignMode>(*(from));
	}
}