#
# Shared settings for Firejail HTTP(S) URL handler scripts
#

# shellcheck disable=SC2034

### vars

#######################################
## IMPORTANT: use full paths in the variables below
#######################################

# web browser executable path
_browser_bin="/usr/bin/firefox"

# debug mode (enabled = 1; disabled = 0)
_debug=0

## dropzone location where the URL data will be saved temporarily
#+ IMPORTANT: this needs to be read/write accessible in the sandbox
#+ ~/Downloads can be assumed to be a supported location
_drop_dir="${HOME}/Downloads/.firejail-dropzone"
_drop_file="${_drop_dir}/firejail.drop"

## xdg-open wrapper path
#+ IMPORTANT: this needs to point to a location preceding /usr/bin in your PATH
_xdg_open_wrapper_bin="/usr/local/bin/xdg-open"
