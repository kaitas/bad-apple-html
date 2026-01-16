# Bad Apple HTML (AudioNoise Guitar)

**[Live Demo](https://akihiko.shirai.as/bad-apple-html/)** | **[日本語版](README.ja.md)** | **[Blog Post (EN)](2026-01-16-wasm-en.md)** | **[ブログ記事 (JA)](2026-01-16-wasm.md)**

All 7 of Linus Torvalds' [AudioNoise](https://github.com/torvalds/AudioNoise) guitar effects running in the browser via WebAssembly, playing Bad Apple!! from MIDI scores.

### Wasm Version (Full Effects)
[![Bad Apple Wasm Demo](https://img.youtube.com/vi/_5ruHnVR9sI/0.jpg)](https://www.youtube.com/watch?v=_5ruHnVR9sI)

### HTML Version (Simple JS Phaser)
[![Bad Apple HTML Demo](https://img.youtube.com/vi/1kPKrw_lNNM/0.jpg)](https://www.youtube.com/watch?v=1kPKrw_lNNM)

## Features

- **Full Wasm Build**: All effects (phaser, echo, flanger, distortion, fm, am, discont) compiled from original C code
- **Real-time Effect Switching**: Change effects while playing
- **Multi-Channel Playback**: Select MIDI channels to play
- **Oscilloscope Visualization**: See the waveform in real-time
- **Works Offline**: Single-file version with embedded Wasm (base64)

## Quick Start

1) Start a local server

```bash
python3 -m http.server 8000
```

2) Open the app

```text
http://localhost:8000/bad-apple-html/
```

## Controls

- **STOMP**: start/suspend the audio engine.
- **PLAY**: play selected channels (enables all channels).
- **MUTE**: toggle master output.
- **Channel Matrix**: toggle any MIDI channel on/off.
- **BPM Slider**: adjust playback speed (50-200 BPM).
- **Knobs (Pot1-4)**: effect parameters (see table below).

## Pot Mapping per Effect

Each effect uses 4 potentiometers differently, just like Linus designed for a physical guitar pedal:

### Guitar Effects (process input signal)

| Effect | Pot1 | Pot2 | Pot3 | Pot4 |
|--------|------|------|------|------|
| **Phaser** | LFO Period [25-2000ms] | Feedback [0-75%] | Center Freq [50-880Hz] | Q [0.25-2.0] |
| **Echo** | Delay Time [0-1000ms] | (unused) | LFO Depth [0-4ms] | Feedback [0-100%] |
| **Flanger** | LFO Speed [0-10Hz²] | Delay [0-4ms] | Depth [0-100%] | Feedback [0-100%] |
| **Distortion** | Drive [1-50x] | Tone [1-10kHz] | Level [0-100%] | Mode [soft/hard/asym] |
| **Discont** | Pitch Ratio [0.5-2.0x] | (unused) | (unused) | (unused) |

### Synth Effects (ignore input, generate test tones)

| Effect | Pot1 | Pot2 | Pot3 | Pot4 |
|--------|------|------|------|------|
| **FM** | Volume [0-100%] | Carrier [100-8100Hz] | Mod Depth [±1 oct] | Mod Freq [1-11Hz] |
| **AM** | Volume [0-100%] | Carrier [100-8100Hz] | Mod Depth [0-100%] | Mod Freq [1-11Hz] |

> **Note**: FM/AM are test tone generators from Linus's `convert.c`. They completely ignore the input signal and generate their own sound.

## Data: JSON Score Format

`bad_apple_guitar_scores.json` - Parsed MIDI data for programmatic playback:

```json
{
  "channels": {
    "2": {
      "duration": 180.9,
      "monophonic": {
        "highest": [
          {"f": 440.0, "d": 0.25},  // frequency (Hz), duration (sec)
          {"f": 493.88, "d": 0.125},
          ...
        ]
      }
    }
  }
}
```

This format is useful for:
- Web Audio synthesis demos
- Music visualization projects
- MIDI-to-JSON conversion reference

## Credits & Respect

### Audio Effects
- **[Linus Torvalds' AudioNoise](https://github.com/torvalds/AudioNoise)** (GPL-2.0) - Original C implementation of guitar effects
- Found a bug in phaser.h! → [Issue #59](https://github.com/torvalds/AudioNoise/issues/59)

### Bad Apple!!
- **Original composition**: ZUN (Touhou Project)
- **Bad Apple!! feat. nomico**: Alstroemeria Records
- **MIDI arrangement**: Ronald Macdonald ([YouTube](https://www.youtube.com/watch?v=FtutLA63Cp8))
- **MIDI file source**: https://github.com/CalvinLoke/bad-apple

### Project
- **Author**: [Akihiko SHIRAI](https://github.com/kaitas) / [@o_ob](https://x.com/o_ob)
- **Blog post**: [VibeCoding #14](https://note.com/o_ob/n/nf596c20a7bc5)
- **AICU (AI Creators Union)**: [YouTube](https://www.youtube.com/@aaborning) | [Tech Blog](https://note.com/aicu/m/m2a2f46d9b1c7)

## License

GPL-2.0. See `LICENSE` (English) and the unofficial Japanese summary in `LICENSE.ja.md`.
