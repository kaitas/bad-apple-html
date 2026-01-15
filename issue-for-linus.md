# GitHub Issue Draft for torvalds/AudioNoise

**Repository**: https://github.com/torvalds/AudioNoise

---

## Title

`[Showcase] AudioNoise effects running in browser via WebAssembly`

---

## Body

Hi Linus,

I really enjoyed reading through the AudioNoise codebase. The single-header design, the `fastpow()` bit manipulation trick, and the LFO implementation using a 32-bit phase accumulator are all elegant solutions.

I compiled all 7 effects (phaser, echo, flanger, distortion, fm, am, discont) to WebAssembly using Emscripten and created a browser-based demo playing "Bad Apple!!" through your effects.

**Live Demo**: https://akihiko.shirai.as/bad-apple-html/

Features:
- All effects selectable in real-time
- 4 pot controls (just like the hardware)
- Multi-channel MIDI playback
- Oscilloscope visualization

**Source**: https://github.com/kaitas/bad-apple-html

One small note: I had to add `sync_effect_delay()` to immediately set `effect_delay = target_effect_delay` after flanger/echo init, since the Wasm context doesn't have the continuous `UPDATE()` loop that convert.c uses.

Thanks for sharing this code! The DSP techniques are educational and the audio quality is great.

---

**Note to self**:

Before posting, consider:
1. Making sure the demo works well on various browsers
2. Maybe adding a screenshot/video to the issue
3. This is a "showcase" not a bug report or PR - be respectful of Linus's time
