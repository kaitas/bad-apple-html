# 作業ログ / Release Note (Bad Apple HTML)

## 概要
Bad Apple!! のMIDIから抽出したギターパートを、WebAudioのフェイザーで再生するデモを制作。AudioNoiseの設計思想に敬意を払いつつ、ブラウザで再生できる形に落とし込んだ。

## 進捗
- MIDIを解析し、**全チャンネル**のスコアをJSON中間形式に整理。
- UIでチャンネルを**チェックボックスON/OFF**して試聴できるように拡張。
- 再生状態が分かるよう**ステータス表示と進行バー**を追加。
- WebAudioは**DSP(Worklet)とUIを分離**し、後から拡張できる構造にした。

## こだわり
- クリックノイズを避けるため、**ゲインと周波数は`setTargetAtTime`で平滑化**。
- チャンネル数に応じて**自動で音量を正規化**し、歪みを抑制。
- 旧来の`file://`アクセスでも動作するよう、**JSONの埋め込みフォールバック**を用意。

## データ/クレジット
- MIDI入手元: https://github.com/CalvinLoke/bad-apple （`alstroemeria_records_bad_apple.mid`）
- **Bad Apple!!** 原曲: ZUN（東方Project）
- **Bad Apple!! MV**: Alstroemeria Records
- **MIDIアレンジ**: Ronald Macdonald
- **AudioNoise**: Linus Torvalds（GPL-2.0）

## まだやりたいこと
- チャンネルの**Solo/Group再生**。
- コード再生（複数オシレータ）への拡張。
- エフェクト構成の最適化（Dry/Wet、Limiterの導入など）。
