#include "undertale_fight_simulator.h"

void play_music(enum Song song) {
    // Make sure that the sound engine on the ARM7 is initialized
    soundEnable();

    if (song == 0)
    {
        soundPlaySample(toriel_bin, // Pointer to sample
                        SoundFormat_16Bit,           // Format: Signed 16 bits
                        toriel_bin_size,         // Size in bytes of the sample
                        11025, // Frequency in Hz
                        127,   // Volume: Max
                        64,    // Panning: Center
                        true,  // Enable looping
                        0);    // Loop start point (not used here)
    }
    else
    {
        soundPlaySample(toriel_bin, // Pointer to sample
                        SoundFormat_16Bit,           // Format: Signed 16 bits
                        toriel_bin_size,         // Size in bytes of the sample
                        11025, // Frequency in Hz
                        127,   // Volume: Max
                        64,    // Panning: Center
                        true,  // Enable looping
                        0);    // Loop start point (not used here)
    }
}