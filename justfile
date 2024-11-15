build:
  #!/usr/bin/env bash
  set -eo pipefail

  qmk compile

  if [[ is_wsl ]]; then
    echo "copying files to host Windows machine"
    rm /mnt/d/qmk/rperryng.bin
    cp zsa_moonlander_rperryng.bin /mnt/d/qmk/rperryng.bin
  fi
