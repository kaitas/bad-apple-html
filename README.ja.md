# Bad Apple HTML (AudioNoise Guitar)

Bad Apple!! のMIDIから抽出したギタースコアを、Linus Torvaldsの[AudioNoise](https://github.com/torvalds/AudioNoise)エフェクトで再生するデモです。WebAssemblyで全7エフェクトを実装。

## デモ

**GitHub Pages**: https://akihiko.shirai.as/bad-apple-html/

### Wasm版（全エフェクト対応）
[![Bad Apple Wasm Demo](https://img.youtube.com/vi/_5ruHnVR9sI/0.jpg)](https://www.youtube.com/watch?v=_5ruHnVR9sI)

### HTML版（JSフェイザーのみ）
[![Bad Apple HTML Demo](https://img.youtube.com/vi/1kPKrw_lNNM/0.jpg)](https://www.youtube.com/watch?v=1kPKrw_lNNM)

## 使い方

### オンライン版（推奨）

上記URLにアクセスするだけで動作します。

### ローカル実行

```bash
# サーバを起動
python3 -m http.server 8000

# ブラウザで開く
open http://localhost:8000/
```

### なぜHTTPサーバが必要？

`file://` プロトコルでは以下の制限があり動作しません：

| 機能 | 制限理由 |
|------|----------|
| `fetch()` | CORS (Same-Origin Policy) |
| WebAssembly | `instantiateStreaming()` はHTTP必須 |
| AudioWorklet | セキュリティ制限 |
| ES Modules | `type="module"` が file:// で制限 |

**回避策**: `wasm_base64.html` は Wasm を base64 埋め込みしているため、file:// でも動作します（ただしファイルサイズが大きくなります）。

## 操作

- **STOMP**: オーディオエンジンの起動/停止。
- **PLAY**: 全チャンネルをONにして再生。
- **MUTE**: マスター出力のミュート切替。
- **Channel Matrix**: 任意のMIDIチャンネルをON/OFF。
- **BPM Slider**: 再生速度を調整（50-200 BPM）。
- **Knobs (Pot1-4)**: エフェクトパラメータ（下表参照）。

## エフェクト別Potマッピング

Linusの設計では、4つのポットが各エフェクトで異なる役割を持ちます（物理的なギターペダルを想定）:

### ギターエフェクト（入力信号を加工）

| Effect | Pot1 | Pot2 | Pot3 | Pot4 |
|--------|------|------|------|------|
| **Phaser** | LFO周期 [25-2000ms] | フィードバック [0-75%] | 中心周波数 [50-880Hz] | Q値 [0.25-2.0] |
| **Echo** | 遅延時間 [0-1000ms] | (未使用) | LFO深さ [0-4ms] | フィードバック [0-100%] |
| **Flanger** | LFO速度 [0-10Hz²] | 遅延 [0-4ms] | 深さ [0-100%] | フィードバック [0-100%] |
| **Distortion** | ドライブ [1-50x] | トーン [1-10kHz] | 出力 [0-100%] | モード [soft/hard/asym] |
| **Discont** | ピッチ比 [0.5-2.0x] | (未使用) | (未使用) | (未使用) |

### シンセエフェクト（入力を無視してテストトーン生成）

| Effect | Pot1 | Pot2 | Pot3 | Pot4 |
|--------|------|------|------|------|
| **FM** | 音量 [0-100%] | キャリア [100-8100Hz] | 変調深さ [±1 oct] | 変調周波数 [1-11Hz] |
| **AM** | 音量 [0-100%] | キャリア [100-8100Hz] | 変調深さ [0-100%] | 変調周波数 [1-11Hz] |

> **注意**: FM/AMはLinusの`convert.c`に含まれるテストトーン生成器です。入力信号を完全に無視し、独自の音を生成します。

## データ

- `bad_apple_guitar_scores.json` は `alstroemeria_records_bad_apple.mid` から生成した中間データです。
- 各チャンネルに単音スコア（最高音/最低音）とコード情報を保持しています。

## クレジット / リスペクト

### オーディオエフェクト
- **[Linus Torvalds の AudioNoise](https://github.com/torvalds/AudioNoise)** (GPL-2.0) - ギターエフェクトのC実装
- Phaserにバグを発見！ → [Issue #59](https://github.com/torvalds/AudioNoise/issues/59)

### Bad Apple!!
- **原曲**: ZUN（東方Project）
- **Bad Apple!! feat. nomico**: Alstroemeria Records
- **MIDIアレンジ**: Ronald Macdonald ([YouTube](https://www.youtube.com/watch?v=FtutLA63Cp8))
- **MIDI配布元**: https://github.com/CalvinLoke/bad-apple

### プロジェクト
- **作者**: [白井暁彦](https://github.com/kaitas) / [@o_ob](https://x.com/o_ob)
- **ブログ記事**: [VibeCoding #14](https://note.com/o_ob/n/nf596c20a7bc5)
- **AICU (AI Creators Union)**: [YouTube](https://www.youtube.com/@aaborning) | [Tech Blog](https://note.com/aicu/m/m2a2f46d9b1c7)

## ライセンス

GPL-2.0。英語の `LICENSE` が正文です。参考訳は `LICENSE.ja.md` を参照してください。
