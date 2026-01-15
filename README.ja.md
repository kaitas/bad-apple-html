# Bad Apple HTML (AudioNoise Guitar)

Bad Apple!! のMIDIから抽出したギタースコアを、AudioNoise風のフェイザーで再生するデモです。公開用に新規コードのみをまとめています。

## デモ

**GitHub Pages**: https://akihiko.shirai.as/bad-apple-html/

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
- **PLAY**: 選択したチャンネルを再生。
- **MUTE**: マスター出力のミュート切替。
- **Channel Matrix**: 任意のMIDIチャンネルをON/OFF、ノート戦略（最高音/最低音）を選択。
- **Knobs**: LFO速度、フィードバック、中心周波数、レゾナンス(Q)。

## データ

- `bad_apple_guitar_scores.json` は `alstroemeria_records_bad_apple.mid` から生成した中間データです。
- 各チャンネルに単音スコア（最高音/最低音）とコード情報を保持しています。

## クレジット / リスペクト

- オーディオエフェクトの核は **Linus Torvalds の AudioNoise** (GPL-2.0) に強くインスパイアされています。
- **Bad Apple!!** 原曲: **ZUN**（東方Project）。
- **Bad Apple!! MV**: **Alstroemeria Records**。
- **MIDIアレンジ**: **Ronald Macdonald**（YouTube）。
- **MIDI配布元URL**: https://github.com/CalvinLoke/bad-apple （`alstroemeria_records_bad_apple.mid` を含むリポジトリ）。

## ライセンス

GPL-2.0。英語の `LICENSE` が正文です。参考訳は `LICENSE.ja.md` を参照してください。
