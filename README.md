# HTTP(S) URL handler for Firejail

[Firejail](https://github.com/netblue30/firejail) is a SUID sandbox program that reduces the risk of security breaches by restricting the running environment of untrusted applications using Linux namespaces, seccomp-bpf
and Linux capabilities. It allows a process and all its descendants to have their own private view of the globally shared kernel resources, such as the network stack, process table, mount table. Firejail can work in a SELinux or AppArmor environment, and it is integrated with Linux Control Groups.

When using Firejail's desktop integration features, all supported applications will run fully sandboxed. Opening hyperlinks with a firejailed web browser from within another sandboxed application can become tedious. Until this functionality is natively supported, it is recommended to copy-paste hyperlinks from sandbox to sandbox (see e.g.  [#2228](https://github.com/netblue30/firejail/issues/2228) and [#2047](https://github.com/netblue30/firejail/issues/2047)). Work is underway to implement this via the newly introduced [D-Bus filtering](https://github.com/netblue30/firejail/issues/3471#issuecomment-646582480), but that's not in any firejail release yet.

The scripts in this repository implement a more user-friendly - still fully secure - way to relay HTTP(S) traffic between firejailed applications. There is no D-Bus functionality involved, so the current profiles should work. The basic idea is to pass hyperlink data between sandboxes indirectly. Relying on a simple `xdg-open` wrapper script, a URL is temporarily stored in the filesystem in a pre-determined location (which needs read-write access in the originating profile). A companion shell script uses `inotifywait` to pick up the URL from outside the sandbox and relays it to a fully firejailed web browser of choice (defaulting to firefox).

## Installing

Arch Linux users can install from the AUR: [firejail-handler-http](https://aur.archlinux.org/packages/firejail-handler-http/).

On other distributions you'll need the following dependencies:

	* firejail
	* inotify-tools
	* a web browser with a working firejail profile
	* xdg-utils

Clone the source code from the Git repository and install manually:

`````
$ git clone https://github.com/glitsj16/firejail-handler-http.git
$ cd firejail-handler-http
$ sudo install -Dm755 ./firejail-handler-http /usr/bin/firejail-handler-http
$ sudo install -Dm755 ./firejail-handler-http-ctl /usr/bin/firejail-handler-http-ctl
$ sudo install -Dm644 ./firejail-handler-settings-http.inc /etc/firejail/firejail-handler-settings-http.inc
$ sudo install -Dm755 ./firejail-xdg-open /usr/local/bin/xdg-open
$ sudo install -Dm644 ./firejail-handler-http-ctl.desktop /etc/xdg/autostart/firejail-handler-http-ctl.desktop
`````


## Settings

The scripts will look for user-provided settings in `~/.config/firejail/firejail-handler-settings-http.inc` first. If that file does not exist it will try `/etc/firejail/firejail-handler-settings-http.inc`. Finally, if none of these locations exist, hard-coded defaults will be used.

## Usage

- (1) Configure your firejailed application(s) to use `firejail-handler-http` as web browser.
- (2) If the relevant firejail profile has the private-bin option, you will have to make sure
to add everything that's needed for the handler script to work inside the sandbox.
The easiest way to achieve this is by creating a ~/.config/firejail/foo.local override
and take care of the additional private-bin commands there.
- Re-login to autostart `firejail-handler-http-ctl` via the XDG desktop file or start it
manually by other means.
