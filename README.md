# Bad Apple HTML (AudioNoise Guitar)

A standalone WebAudio phaser demo that plays Bad Apple!! guitar scores extracted from MIDI. This directory contains only the new code prepared for a separate public release.

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

## Data

- `bad_apple_guitar_scores.json` is generated from `alstroemeria_records_bad_apple.mid` using a MIDI parser.
- Each channel contains monophonic scores (highest/lowest) plus chord metadata.

## Credits & Respect

- Audio effect core inspired by **Linus Torvalds' AudioNoise** (GPL-2.0).
- **Bad Apple!!** original composition by **ZUN** (Touhou Project).
- **Bad Apple!! MV** by **Alstroemeria Records**.
- **MIDI arrangement** by **Ronald Macdonald** (YouTube).
- **MIDI file source URL**: https://github.com/CalvinLoke/bad-apple (contains `alstroemeria_records_bad_apple.mid`).

## License

GPL-2.0. See `LICENSE` (English) and the unofficial Japanese summary in `LICENSE.ja.md`.
