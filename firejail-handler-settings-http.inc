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
# follow XDG specifications and fallback to hardcoded drop dir location
# https://github.com/glitsj16/firejail-handler-http/issues/3
if [ "$(which xdg-user-dir)" ]; then
    _drop_dir="$(xdg-user-dir DOWNLOAD)"
else
    _xdg_config_home="$(env | grep -c "XDG_CONFIG_HOME")"
    if [ "$_xdg_config_home" = 1 ]; then
	if [ -s "${XDG_CONFIG_HOME}/user-dirs.dirs" ]; then
	    _drop_dir="$(grep "^XDG_DOWNLOAD_DIR=" "${XDG_CONFIG_HOME}/user-dirs.dirs" | awk '{split($0,a,"="); print a[2]}' | sed 's/"//g')"
	fi
    elif [ -s "${HOME}/.config/user-dirs.dirs" ]; then
	_drop_dir="$(grep "^XDG_DOWNLOAD_DIR=" "${HOME}/.config/user-dirs.dirs" | awk '{split($0,a,"="); print a[2]}' | sed 's/"//g')"
    else
	_drop_dir="${HOME}/Downloads"
    fi
fi
_drop_dir="${_drop_dir}/.firejail-dropzone"
_drop_file="${_drop_dir}/firejail.drop"

## xdg-open wrapper path
#+ IMPORTANT: this needs to point to a location preceding /usr/bin in your PATH
_xdg_open_wrapper_bin="/usr/local/bin/xdg-open"
