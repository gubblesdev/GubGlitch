#define PLUG_MFR "Gubbles"
#define PLUG_NAME "Gub Glitch"

#define PLUG_CLASS_NAME GubGlitch

#define BUNDLE_MFR "Gubbles"
#define BUNDLE_NAME "Gub Glitch"

#define PLUG_ENTRY GubGlitch_Entry
#define PLUG_FACTORY GubGlitch_Factory
#define PLUG_VIEW_ENTRY GubGlitch_ViewEntry

#define PLUG_ENTRY_STR "GubGlitch_Entry"
#define PLUG_VIEW_ENTRY_STR "GubGlitch_ViewEntry"

#define VIEW_CLASS GubGlitch_View
#define VIEW_CLASS_STR "GubGlitch_View"

// Format        0xMAJR.MN.BG - in HEX! so version 10.1.5 would be 0x000A0105
#define PLUG_VER 0x00000001
#define VST3_VER_STR "0.0.1"

#define PLUG_COPYRIGHT  "Copyright 2018 Gubbles"

// http://service.steinberg.de/databases/plugin.nsf/plugIn?openForm
// 4 chars, single quotes. At least one capital letter
#define PLUG_UNIQUE_ID 'GbGt'
// make sure this is not the same as BUNDLE_MFR
#define PLUG_MFR_ID 'Gubb'

// ProTools stuff

#if (defined(AAX_API) || defined(RTAS_API)) && !defined(_PIDS_)
  #define _PIDS_
  const int PLUG_TYPE_IDS[2] = {'EFN1', 'EFN2'};
  const int PLUG_TYPE_IDS_AS[2] = {'EFA1', 'EFA2'}; // AudioSuite
#endif

#define PLUG_MFR_PT "Gubbles\nGubbles\nAcme"
#define PLUG_NAME_PT "GubGlitch\nIPEF"
#define PLUG_TYPE_PT "Effect"
#define PLUG_DOES_AUDIOSUITE 1

/* PLUG_TYPE_PT can be "None", "EQ", "Dynamics", "PitchShift", "Reverb", "Delay", "Modulation", 
"Harmonic" "NoiseReduction" "Dither" "SoundField" "Effect" 
instrument determined by PLUG _IS _INST
*/

#define PLUG_CHANNEL_IO "1-1 2-2"

#define PLUG_LATENCY 0
#define PLUG_IS_INST 0

// if this is 0 RTAS can't get tempo info
#define PLUG_DOES_MIDI 1

#define PLUG_DOES_STATE_CHUNKS 0

// Unique IDs for each image resource.
#define BACKGROUND_ID 101
#define KNOB_ID 102

#define CPAD_2_ID 103
#define CPAD_4_ID 104
#define CPAD_8_ID 105
#define CPAD_16_ID 106
#define CPAD_32_ID 107
#define CPAD_64_ID 108
#define CPAD_3_ID 109
#define CPAD_6_ID 110
#define CPAD_12_ID 111
#define CPAD_24_ID 112
#define CPAD_48_ID 113
#define CPAD_HOLD_ID 114

#define SPAD_2_ID 115
#define SPAD_4_ID 116
#define SPAD_8_ID 117
#define SPAD_16_ID 118
#define SPAD_32_ID 119
#define SPAD_64_ID 120
#define SPAD_3_ID 121
#define SPAD_6_ID 122
#define SPAD_12_ID 123
#define SPAD_24_ID 124
#define SPAD_48_ID 125
#define SPAD_KEY_ID 126

// Image resource locations for this plug.
#define BACKGROUND_FN "resources/img/background.png"
#define KNOB_FN "resources/img/knob_small.png"

#define CPAD_2_FN "resources/img/cpad_2.png"
#define CPAD_4_FN "resources/img/cpad_4.png"
#define CPAD_8_FN "resources/img/cpad_8.png"
#define CPAD_16_FN "resources/img/cpad_16.png"
#define CPAD_32_FN "resources/img/cpad_32.png"
#define CPAD_64_FN "resources/img/cpad_64.png"
#define CPAD_3_FN "resources/img/cpad_3.png"
#define CPAD_6_FN "resources/img/cpad_6.png"
#define CPAD_12_FN "resources/img/cpad_12.png"
#define CPAD_24_FN "resources/img/cpad_24.png"
#define CPAD_48_FN "resources/img/cpad_48.png"
#define CPAD_HOLD_FN "resources/img/cpad_hold.png"

#define SPAD_2_FN "resources/img/spad_2.png"
#define SPAD_4_FN "resources/img/spad_4.png"
#define SPAD_8_FN "resources/img/spad_8.png"
#define SPAD_16_FN "resources/img/spad_16.png"
#define SPAD_32_FN "resources/img/spad_32.png"
#define SPAD_64_FN "resources/img/spad_64.png"
#define SPAD_3_FN "resources/img/spad_3.png"
#define SPAD_6_FN "resources/img/spad_6.png"
#define SPAD_12_FN "resources/img/spad_12.png"
#define SPAD_24_FN "resources/img/spad_24.png"
#define SPAD_48_FN "resources/img/spad_48.png"
#define SPAD_KEY_FN "resources/img/spad_key.png"

// GUI default dimensions
#define GUI_WIDTH 807
#define GUI_HEIGHT 497

// on MSVC, you must define SA_API in the resource editor preprocessor macros as well as the c++ ones
#if defined(SA_API)
#include "app_wrapper/app_resource.h"
#endif

// vst3 stuff
#define MFR_URL "www.gubblesdev.com"
#define MFR_EMAIL "gubblesdev@gmail.com"
#define EFFECT_TYPE_VST3 "Fx|Instrument"

/* "Fx|Analyzer"", "Fx|Delay", "Fx|Distortion", "Fx|Dynamics", "Fx|EQ", "Fx|Filter",
"Fx", "Fx|Instrument", "Fx|InstrumentExternal", "Fx|Spatial", "Fx|Generator",
"Fx|Mastering", "Fx|Modulation", "Fx|PitchShift", "Fx|Restoration", "Fx|Reverb",
"Fx|Surround", "Fx|Tools", "Instrument", "Instrument|Drum", "Instrument|Sampler",
"Instrument|Synth", "Instrument|Synth|Sampler", "Instrument|External", "Spatial",
"Spatial|Fx", "OnlyRT", "OnlyOfflineProcess", "Mono", "Stereo",
"Surround"
*/
