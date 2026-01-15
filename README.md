# Bad Apple HTML (AudioNoise Guitar)

**[Live Demo](https://akihiko.shirai.as/bad-apple-html/)** | **[日本語版](README.ja.md)** | **[Blog Post (EN)](2026-01-16-wasm-en.md)** | **[ブログ記事 (JA)](2026-01-16-wasm.md)**

All 7 of Linus Torvalds' [AudioNoise](https://github.com/torvalds/AudioNoise) guitar effects running in the browser via WebAssembly, playing Bad Apple!! from MIDI scores.

[![Bad Apple HTML Demo](https://img.youtube.com/vi/YOUR_VIDEO_ID/0.jpg)](https://www.youtube.com/watch?v=YOUR_VIDEO_ID)

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
- **PLAY**: play selected channels.
- **MUTE**: toggle master output.
- **Channel Matrix**: toggle any MIDI channel on/off and choose a note strategy (highest/lowest).
- **Knobs**: LFO speed, feedback, center frequency, resonance (Q).

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

- Audio effect core inspired by **Linus Torvalds' AudioNoise** (GPL-2.0).
- **Bad Apple!!** original composition by **ZUN** (Touhou Project).
- **Bad Apple!! MV** by **Alstroemeria Records**.
- **MIDI arrangement** by **Ronald Macdonald** (YouTube).
- **MIDI file source URL**: https://github.com/CalvinLoke/bad-apple (contains `alstroemeria_records_bad_apple.mid`).

## License

GPL-2.0. See `LICENSE` (English) and the unofficial Japanese summary in `LICENSE.ja.md`.
