#include "SpectralBlur.h"
#include <iostream>
#include <typeinfo>
//#include "OnePole.h"

using namespace plogue::biduleSDK;
using namespace acme;

SpectralBlur::SpectralBlur(BiduleHost* host):BidulePlugin(host) {
	//fill in plugin capabilities as a mask
//  _caps = CAP_SYNCMASTER | CAP_SYNCSLAVE
    _caps = 0; 
	_numAudioIns=0;
	_numAudioOuts=0;
	_numMIDIIns=0;
	_numMIDIOuts=0;
	_numFreqIns=1;
	_numFreqOuts=1;
	_numMagIns=1;
	_numMagOuts=1;
	_numParams=2;

    
    
}

SpectralBlur::~SpectralBlur(){
    cout << "destroying" << endl;
}

bool
SpectralBlur::init() {
//    _filter.setFc(1.0);
//    _filter.sayHello();
//    cout << "SpectralBlur Addr: " << &_filter << endl;
//    cout << "SpectralBlur Size: " << sizeof(_filter) << endl;
//    cout << "fftOverlapPerBuffer: " << (size_t)_dspInfo.fftOverlapPerBuffer << endl;
    
    return true;
}

void 
SpectralBlur::getAudioInNames(std::vector<std::string>& vec){
	vec.push_back("Passthrough audio in");
}

void 
SpectralBlur::getAudioOutNames(std::vector<std::string>& vec){
	vec.push_back("Passthrough audio out");
}

void 
SpectralBlur::getMIDIInNames(std::vector<std::string>& vec){
	vec.push_back("Passthrough MIDI in");
}

void 
SpectralBlur::getMIDIOutNames(std::vector<std::string>& vec){
	vec.push_back("Passthrough MIDI out");
}

void 
SpectralBlur::getFreqInNames(std::vector<std::string>& vec){
	vec.push_back("frequency in");
}

void 
SpectralBlur::getFreqOutNames(std::vector<std::string>& vec){
	vec.push_back("frequency out");
}

void 
SpectralBlur::getMagInNames(std::vector<std::string>& vec){
	vec.push_back("magnitude in");
}

void 
SpectralBlur::getMagOutNames(std::vector<std::string>& vec){
	vec.push_back("magnitude out");
}

void
SpectralBlur::getParametersInfos(ParameterInfo* pinfos) {
	pinfos[0].id = 0;
	strcpy(pinfos[0].name, "blur mags...");
	pinfos[0].type = DOUBLEPARAM;
	pinfos[0].ctrlType = GUICTRL_SLIDER;
	pinfos[0].linkable = 1;
	pinfos[0].saveable = 1;
	pinfos[0].paramInfo.pd.defaultValue = 0.0;
	strcpy(pinfos[0].paramInfo.pd.units, "dollars");
	pinfos[0].paramInfo.pd.precision = 1;
	pinfos[0].paramInfo.pd.minValue = 0.f;
	pinfos[0].paramInfo.pd.maxValue = 5.f;
	pinfos[0].paramInfo.pd.scaling = SCALING_LINEAR;
    
    pinfos[1].id = 1;
    strcpy(pinfos[1].name, "blur freqs...");
    pinfos[1].type = DOUBLEPARAM;
    pinfos[1].ctrlType = GUICTRL_SLIDER;
    pinfos[1].linkable = 1;
    pinfos[1].saveable = 1;
    pinfos[1].paramInfo.pd.defaultValue = 0.0;
    strcpy(pinfos[1].paramInfo.pd.units, "dollars");
    pinfos[1].paramInfo.pd.precision = 1;
    pinfos[1].paramInfo.pd.minValue = 0.f;
    pinfos[1].paramInfo.pd.maxValue = 5.f;
    pinfos[1].paramInfo.pd.scaling = SCALING_LINEAR;
}

void 
SpectralBlur::getParameterChoices(long id, std::vector<std::string>& vec) {
}

void 
SpectralBlur::parameterUpdate(long id){
    if(id == 0) {
		getParameterValue(0, _blurAmtMag);
        _filterMag.setFc(_blurAmtMag);
    }
    if(id == 1) {
        getParameterValue(1, _blurAmtFreq);
        _filterFreq.setFc(_blurAmtFreq);
    }
 
}

void 
SpectralBlur::process(Sample** sampleIn, Sample** sampleOut, MIDIEvents* midiIn, MIDIEvents* midiOut, Frequency*** freqIn, Frequency*** freqOut, Magnitude*** magIn, Magnitude*** magOut, SyncInfo* syncIn, SyncInfo* syncOut){
	
	//VC6 has scope problems with for loop indices
    //	unsigned int i = 0;
    //	unsigned int j = 0;

    
    
// The formula for calculating the cutoff frequency of the filter: frame rate / hopsize = new frame starts per second (in Hz), then the percentage of half the framerate. For example, looking at the first note in the example, the frame rate is 44100 / 256 = 172,265625 Hz (= 172 new frame starts per second). half of the frame rate is about 86 Hz, and one percent of this is 0.86 Hz.
    
//    for(unsigned int i = 0; i < _numFreqIns; ++i) {
//        for(unsigned int j = 0; j < (size_t)_dspInfo.fftOverlapPerBuffer; ++j) {
//            if (j == 0) {
//                cout << "Freq: " << *freqIn[i][j] << endl;
//                cout << typeid(freqIn[i][j]).name() << endl;
//            }

//            freqOut[i][uint32_tj] = *freqIn[i][j] * 0.0;
//            memcpy(freqOut[i][j], freqIn[i][j], _dspInfo.fftWindowSizeHalf * sizeof(Frequency));
//        }
//    }

    for(uint32_t i = 0; i < _numFreqIns; ++i) {
        for(uint32_t j = 0; j < static_cast<uint32_t>(_dspInfo.fftOverlapPerBuffer); ++j) {
            for(uint32_t k = 0; k < static_cast<uint32_t>(_dspInfo.fftWindowSizeHalf); ++k) {
//                cout << typeid(freqIn[i][j][k]).name() << endl;
                freqOut[i][j][k] = _filterFreq.process(freqIn[i][j][k]);
            }
        }
    }
    
    for(uint32_t i = 0; i < _numMagIns; ++i) {
        for(uint32_t j = 0; j < static_cast<uint32_t>(_dspInfo.fftOverlapPerBuffer); ++j) {
            for(uint32_t k = 0; k < static_cast<uint32_t>(_dspInfo.fftWindowSizeHalf); ++k) {
                magOut[i][j][k] =  _filterMag.process(magIn[i][j][k]);
            }
        }
    }

}

