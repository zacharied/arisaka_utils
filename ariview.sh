#!/usr/bin/env bash

[[ -z "$ARILOG_FILE" ]] && ARILOG_FILE="$HOME/.arilog"

parse_logline() {
    while read -r line; do
        level="$(sed 's/^\[.*\]\[\(INFO \|DEBUG\|WARN \|ERROR\)\].*$/\1/' <<< "$line")"
        case "$level" in
            'ERROR')
                printf '\033[0;31m'
                ;;
        esac
        printf '%s\n' "$line"
    done
}

tail -f "$ARILOG_FILE" | parse_logline
