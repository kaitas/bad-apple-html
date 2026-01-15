# AudioNoise Wasm Build
#
# Prerequisites:
#   brew install emscripten
#   or
#   git clone https://github.com/emscripten-core/emsdk.git
#   cd emsdk && ./emsdk install latest && ./emsdk activate latest
#   source emsdk_env.sh

EMCC = emcc
AUDIONOISE_DIR = /Users/aki/git.local/AudioNoise

# Exported functions for JavaScript
EXPORTED_FUNCS = '["_effect_init", "_effect_step", "_set_effect", "_get_effects_list", "_malloc", "_free"]'
EXPORTED_RUNTIME = '["ccall", "cwrap", "getValue", "setValue"]'

EMCC_FLAGS = -O2 \
    -s WASM=1 \
    -s EXPORTED_FUNCTIONS=$(EXPORTED_FUNCS) \
    -s EXPORTED_RUNTIME_METHODS=$(EXPORTED_RUNTIME) \
    -s MODULARIZE=1 \
    -s EXPORT_NAME="AudioNoiseModule" \
    -s ALLOW_MEMORY_GROWTH=1 \
    -s SINGLE_FILE=0

.PHONY: all clean check-emcc

all: check-emcc audionoise.js

check-emcc:
	@which emcc > /dev/null || (echo "Error: emscripten not found. Install with 'brew install emscripten'" && exit 1)

# Copy headers from AudioNoise (if not already present)
headers:
	@echo "Linking AudioNoise headers..."
	@for h in util.h lfo.h biquad.h effect.h process.h \
	          phaser.h echo.h flanger.h distortion.h \
	          fm.h am.h discont.h gensin.h; do \
	    [ -f $$h ] || ln -sf $(AUDIONOISE_DIR)/$$h .; \
	done

# Generate gensin.h if needed
gensin.h:
	@if [ ! -f gensin.h ]; then \
	    echo "Generating gensin.h..."; \
	    cd $(AUDIONOISE_DIR) && make gensin.h; \
	    ln -sf $(AUDIONOISE_DIR)/gensin.h .; \
	fi

# Main Wasm build
audionoise.js: audionoise_wasm.c headers gensin.h
	$(EMCC) audionoise_wasm.c -o audionoise.js $(EMCC_FLAGS) \
	    -I. -I$(AUDIONOISE_DIR)

clean:
	rm -f audionoise.js audionoise.wasm
	rm -f util.h lfo.h biquad.h effect.h process.h
	rm -f phaser.h echo.h flanger.h distortion.h
	rm -f fm.h am.h discont.h gensin.h

# Development: watch and rebuild
watch:
	@echo "Watching for changes..."
	@while true; do \
	    make all 2>&1; \
	    sleep 2; \
	done
