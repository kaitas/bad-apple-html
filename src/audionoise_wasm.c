/**
 * AudioNoise Wasm Wrapper
 *
 * Exposes AudioNoise effects to WebAssembly/JavaScript.
 * Based on torvalds/AudioNoise (GPL-2.0)
 */

#include <stdint.h>
#include <string.h>
#include <math.h>
#include <stdio.h>

// Wasm環境では stderr 出力を無効化
#ifdef __EMSCRIPTEN__
#define fprintf(...)
#endif

// Emscripten export macro
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#define EXPORT EMSCRIPTEN_KEEPALIVE
#else
#define EXPORT
#endif

// Type definitions (from convert.c)
typedef int32_t s32;
typedef uint32_t u32;
typedef unsigned int uint;

#define SAMPLES_PER_SEC (48000.0f)

// Include AudioNoise core
#include "util.h"
#include "lfo.h"
#include "effect.h"
#include "biquad.h"
#include "process.h"

// Include all effects
#include "phaser.h"
#include "echo.h"
#include "flanger.h"
#include "distortion.h"
#include "fm.h"
#include "am.h"
#include "discont.h"

// Effect enumeration
typedef enum {
    EFFECT_PHASER = 0,
    EFFECT_ECHO,
    EFFECT_FLANGER,
    EFFECT_DISTORTION,
    EFFECT_FM,
    EFFECT_AM,
    EFFECT_DISCONT,
    EFFECT_COUNT
} EffectType;

// Current effect state
static EffectType current_effect = EFFECT_PHASER;
static float current_pots[4] = {0.3f, 0.3f, 0.5f, 0.5f};

// Forward declaration
EXPORT void effect_init(float pot1, float pot2, float pot3, float pot4);

// Force effect_delay to match target (skip smooth transition)
static void sync_effect_delay(void) {
    extern float effect_delay, target_effect_delay;
    effect_delay = target_effect_delay;
}

// Effect names for JavaScript
static const char* effect_names[] = {
    "phaser",
    "echo",
    "flanger",
    "distortion",
    "fm",
    "am",
    "discont"
};

/**
 * Get list of available effects (returns count)
 */
EXPORT int get_effects_list(void) {
    return EFFECT_COUNT;
}

/**
 * Set current effect by index
 */
EXPORT void set_effect(int effect_idx) {
    if (effect_idx >= 0 && effect_idx < EFFECT_COUNT) {
        current_effect = (EffectType)effect_idx;
        // Re-initialize with current pots
        effect_init(current_pots[0], current_pots[1], current_pots[2], current_pots[3]);
    }
}

/**
 * Initialize effect with pot values (0.0 - 1.0)
 */
EXPORT void effect_init(float pot1, float pot2, float pot3, float pot4) {
    current_pots[0] = pot1;
    current_pots[1] = pot2;
    current_pots[2] = pot3;
    current_pots[3] = pot4;

    switch (current_effect) {
        case EFFECT_PHASER:
            phaser_init(pot1, pot2, pot3, pot4);
            break;
        case EFFECT_ECHO:
            echo_init(pot1, pot2, pot3, pot4);
            sync_effect_delay();  // Echo uses delay line
            break;
        case EFFECT_FLANGER:
            flanger_init(pot1, pot2, pot3, pot4);
            sync_effect_delay();  // Flanger uses delay line
            break;
        case EFFECT_DISTORTION:
            distortion_init(pot1, pot2, pot3, pot4);
            break;
        case EFFECT_FM:
            fm_init(pot1, pot2, pot3, pot4);
            break;
        case EFFECT_AM:
            am_init(pot1, pot2, pot3, pot4);
            break;
        case EFFECT_DISCONT:
            discont_init(pot1, pot2, pot3, pot4);
            break;
        default:
            break;
    }
}

/**
 * Process single sample through current effect
 * Input/output range: -1.0 to 1.0
 */
EXPORT float effect_step(float input) {
    float output;

    switch (current_effect) {
        case EFFECT_PHASER:
            output = phaser_step(input);
            break;
        case EFFECT_ECHO:
            output = echo_step(input);
            break;
        case EFFECT_FLANGER:
            output = flanger_step(input);
            break;
        case EFFECT_DISTORTION:
            output = distortion_step(input);
            break;
        case EFFECT_FM:
            output = fm_step(input);
            break;
        case EFFECT_AM:
            output = am_step(input);
            break;
        case EFFECT_DISCONT:
            output = discont_step(input);
            break;
        default:
            output = input;
            break;
    }

    // Clamp output to valid range
    if (output > 1.0f) output = 1.0f;
    if (output < -1.0f) output = -1.0f;

    return output;
}

/**
 * Process buffer of samples (more efficient than per-sample calls)
 * buffer_ptr: pointer to Float32Array in Wasm memory
 * length: number of samples
 */
EXPORT void effect_process_buffer(float* buffer, int length) {
    for (int i = 0; i < length; i++) {
        buffer[i] = effect_step(buffer[i]);
    }
}

/**
 * Get current effect index
 */
EXPORT int get_current_effect(void) {
    return (int)current_effect;
}

/**
 * Update single pot value (0-3) without full re-init
 * Useful for real-time knob changes
 */
EXPORT void set_pot(int pot_idx, float value) {
    if (pot_idx >= 0 && pot_idx < 4) {
        current_pots[pot_idx] = value;
        // Some effects need re-init, others can update live
        // For simplicity, always re-init
        effect_init(current_pots[0], current_pots[1], current_pots[2], current_pots[3]);
    }
}
