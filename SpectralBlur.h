#ifndef SpectralBlur_H
#define SpectralBlur_H

#include <string>
#include "../common/BiduleSDK.h"
#include "OnePole.h"

namespace acme {
    using namespace plogue::biduleSDK;
    class SpectralBlur: public BidulePlugin {

	    public:
		    SpectralBlur(BiduleHost* host);
			virtual ~SpectralBlur();
            virtual bool init();
			virtual void getAudioInNames(std::vector<std::string>& vec);
			virtual void getAudioOutNames(std::vector<std::string>& vec);
			virtual void getMIDIInNames(std::vector<std::string>& vec);
			virtual void getMIDIOutNames(std::vector<std::string>& vec);
			virtual void getFreqInNames(std::vector<std::string>& vec);
			virtual void getFreqOutNames(std::vector<std::string>& vec);
			virtual void getMagInNames(std::vector<std::string>& vec);
			virtual void getMagOutNames(std::vector<std::string>& vec);

            virtual void parameterUpdate(long id);
			virtual void getParametersInfos(ParameterInfo* pinfos);
			virtual void getParameterChoices(long id, std::vector<std::string>& vec);

			virtual void process(Sample** sampleIn, Sample** sampleOut, MIDIEvents* midiIn, MIDIEvents* midiOut, Frequency*** freqIn, Frequency*** freqOut, Magnitude*** magIn, Magnitude*** magOut, SyncInfo* syncIn, SyncInfo* syncOut);
		protected:
            OnePole _filterFreq;
            OnePole _filterMag;
			double _blurAmtFreq;
            double _blurAmtMag;

    };
};

#endif
