/**
 * 正確なWeb Audioスケジューリングの例
 *
 * ポイント:
 * 1. audioCtx.currentTime は μs 精度のハードウェアクロック
 * 2. setValueAtTime() で「未来の時刻」にイベントを予約
 * 3. ルックアヘッド (先読み) で余裕を持ってスケジュール
 */

class PreciseScheduler {
    constructor(audioCtx) {
        this.audioCtx = audioCtx;
        this.oscillator = null;
        this.gainNode = null;

        // スケジューリングパラメータ
        this.lookahead = 0.1;      // 100ms先までスケジュール
        this.scheduleInterval = 25; // 25msごとにチェック

        this.notes = [];
        this.noteIndex = 0;
        this.startTime = 0;
        this.scheduledUntil = 0;
        this.intervalId = null;
    }

    init() {
        // オシレーターは周波数を「予約」できる
        this.oscillator = this.audioCtx.createOscillator();
        this.oscillator.type = 'sawtooth';

        this.gainNode = this.audioCtx.createGain();
        this.gainNode.gain.value = 0.3;

        this.oscillator.connect(this.gainNode);
        this.gainNode.connect(this.audioCtx.destination);
        this.oscillator.start();
    }

    play(notes, bpmMultiplier = 1.0) {
        this.notes = notes;
        this.noteIndex = 0;
        this.startTime = this.audioCtx.currentTime;
        this.scheduledUntil = this.startTime;

        // 最初のスケジュール
        this.scheduleNotes(bpmMultiplier);

        // 定期的に先読みスケジュール
        this.intervalId = setInterval(() => {
            this.scheduleNotes(bpmMultiplier);
        }, this.scheduleInterval);
    }

    scheduleNotes(bpmMultiplier) {
        const now = this.audioCtx.currentTime;
        const scheduleEnd = now + this.lookahead;

        // scheduledUntil から scheduleEnd までのノートを予約
        while (this.scheduledUntil < scheduleEnd && this.noteIndex < this.notes.length) {
            const note = this.notes[this.noteIndex];
            const noteStart = this.scheduledUntil;
            const noteDuration = note.d * bpmMultiplier;

            // 🎯 ここがポイント: 正確な時刻に周波数変更を予約
            this.oscillator.frequency.setValueAtTime(note.f, noteStart);

            // 次のノート時刻を計算
            this.scheduledUntil = noteStart + noteDuration;
            this.noteIndex++;
        }
    }

    stop() {
        if (this.intervalId) {
            clearInterval(this.intervalId);
            this.intervalId = null;
        }
        this.oscillator.frequency.setValueAtTime(0, this.audioCtx.currentTime);
    }
}

// 使用例
/*
const scheduler = new PreciseScheduler(audioCtx);
scheduler.init();
scheduler.play(scoreNotes, bpmMultiplier);
*/
