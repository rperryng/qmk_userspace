build:
  #!/usr/bin/env bash
  set -eo pipefail

  # qmk compile -kb ergodox_ez/glow
  qmk compile -kb dasbob

  if just is_wsl; then
    echo "copying files to host Windows machine"

    # rm -f /mnt/d/qmk/moonlander_rperryng.bin
    # cp zsa_moonlander_rperryng.bin /mnt/d/qmk/rperryng.bin

    # rm -f /mnt/d/qmk/ez_glow.hex
    # cp ergodox_ez_glow_rperryng.hex /mnt/d/qmk/ez_glow_rperryng.hex

    TIMESTAMP=$(date -u +"%Y-%m-%dT%H-%M-%SZ")
    cp dasbob_rperryng.uf2 /mnt/d/qmk/dasbob_rperryng_${TIMESTAMP}.uf2
  fi

is_wsl:
  #!/usr/bin/env bash
  if [[ -f '/proc/version' ]]; then
    grep -qi microsoft '/proc/version' && exit 0
  fi

  exit 1
