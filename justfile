build:
  #!/usr/bin/env bash
  set -eo pipefail

  qmk compile

  if just is_wsl; then
    echo "copying files to host Windows machine"
    TIMESTAMP=$(date -u +"%Y-%m-%dT%H-%M-%SZ")
    cp dasbob_rperryng.uf2 /mnt/d/qmk/dasbob_rperryng_${TIMESTAMP}.uf2
  fi

[no-exit-message]
is_wsl:
  #!/usr/bin/env bash
  if [[ -f '/proc/version' ]]; then
    grep -qi microsoft '/proc/version' && exit 0
  fi

  exit 1
