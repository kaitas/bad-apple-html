# Bad Apple HTML (AudioNoise Guitar)

Bad Apple!! のMIDIから抽出したギタースコアを、AudioNoise風のフェイザーで再生するデモです。公開用に新規コードのみをまとめています。

## 使い方

1) ローカルサーバを起動

```bash
python3 -m http.server 8000
```

2) ブラウザで開く

```text
http://localhost:8000/bad-apple-html/
```

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
