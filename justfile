

build:
  #!/usr/bin/env bash
  set -eo pipefail

  # qmk compile -kb ergodox_ez/glow
  qmk compile -kb dasbob

  if is_wsl; then
    echo "copying files to host Windows machine"

    # rm -f /mnt/d/qmk/moonlander_rperryng.bin
    # cp zsa_moonlander_rperryng.bin /mnt/d/qmk/rperryng.bin

    # rm -f /mnt/d/qmk/ez_glow.hex
    # cp ergodox_ez_glow_rperryng.hex /mnt/d/qmk/ez_glow_rperryng.hex

    rm -f /mnt/d/qmk/dasbob_rperryng.uf2
    cp dasbob_rperryng.uf2 /mnt/d/qmk/dasbob_rperryng.uf2
  fi
