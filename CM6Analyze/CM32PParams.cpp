#include "CM32PParams.h"

#include <sstream>
#include <iostream>

#include "U110_07_ToneName.h"

namespace CM32PParam
{
	static const int INTERNAL_PCM_COUNT = 84;
	static const std::string INTERNAL_PCM_NAME[INTERNAL_PCM_COUNT] =
	{
		"A.Piano 1", "A.Piano 2", "A.Piano 3", "A.Piano 4", "A.Piano 5",
		"A.Piano 6", "A.Piano 7", "A.Piano 8", "A.Piano 9", "A.Piano 10",

		"E.Piano 1", "E.Piano 2", "E.Piano 3", "E.Piano 4", "E.Piano 5",

		"A.Guitar 1", "A.Guitar 2", "A.Guitar 3", "A.Guitar 4", "A.Guitar 5",
		"E.Guitar 1", "E.Guitar 2", "E.Guitar 3", "E.Guitar 4",

		"Slap 1", "Slap 2", "Slap 3", "Slap 4", "Slap 5", "Slap 6", "Slap 7",
		"Slap 8", "Slap 9", "Slap 10", "Slap 11", "Slap 12",
		"FingerBass 1", "FingerBass 2",
		"PickedBass 1", "PickedBass 2",
		"Fretless 1", "Fretless 2",
		"AC.Bass",
		"Choir 1", "Choir 2", "Choir 3", "Choir 4",
		"Strings 1", "Strings 2", "Strings 3", "Strings 4",
		"E.Organ 1", "E.Organ 2", "E.Organ 3", "E.Organ 4",
		"E.Organ 5", "E.Organ 6", "E.Organ 7", "E.Organ 8",
		"E.Organ 9", "E.Organ 10", "E.Organ 11", "E.Organ 12", "E.Organ 13",
		"Soft Tp 1", "Soft Tp 2", "Soft Tp 3",
		"Tp/Trb 1", "Tp/Trb 2", "Tp/Trb 3", "Tp/Trb 4",
		"Tp/Trb 5", "Tp/Trb 6",
		"Sax 1", "Sax 2", "Sax 3", "Sax 4", "Sax 5",
		"Brass 1", "Brass 2", "Brass 3", "Brass 4", "Brass 5",
		"Orche Hit",
	};
	void PatchMemory::clear()
	{
		media = MEDIA::INTERNAL;
		toneNumber = 0;
		keyShift = 0;
		fineTune = 0;
		benderRange = 0;
		toneName = "";
	}

	void PatchMemory::readData(const char* from)
	{
		switch (*from)
		{
		case 0:
			media = MEDIA::INTERNAL;
			break;
		case 1:
			media = MEDIA::CARD;
			break;
		default:
			media = MEDIA::INTERNAL;
			std::cerr << "Unknown Media Type" << std::endl;
			// error
			break;
		}
		from++;
		toneNumber = *from++;
		keyShift = (*from++) - 12;
		fineTune = (*from++) - 50;
		benderRange = (*from++);

		// check ToneName
		switch (media)
		{
		case MEDIA::INTERNAL:
		{
								if (toneNumber < INTERNAL_PCM_COUNT)
								{
									toneName = INTERNAL_PCM_NAME[toneNumber];
								}
								else
								{
									std::cerr << "Unknown Internal Tone Number" << std::endl;
								}
		}
			break;
		case MEDIA::CARD:
		{
			std::ostringstream os;

			os << "CARD #" << toneNumber + 1 << " (07:" << CARD07NAME[toneNumber] << ")";
			toneName = os.str();

		}
			break;
		default:
			std::cerr << "Unknown Media Type" << std::endl;
			break;
		}
	}

}