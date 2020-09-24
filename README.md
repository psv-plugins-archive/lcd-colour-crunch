# LCD Colour Crunch

Change the LCD colour space with one click and force colour space settings in PSPEmu applications. This program is only for PlayStation Vita 2000 models with LCD screens to toggle OLED emulation mode. Vita 1000 models already have OLED screens and do not have OLED emulation mode.

## Installation

Install `lcd-colour-crunch.vpk` with VitaShell. To force colour space settings in PSPEmu applications, write the module file path in the `*KERNEL` section of your taiHEN config.

```
*KERNEL
ur0:/tai/pspemu-colour-crunch.skprx
```

## Usage

Open LCD Colour Crunch to toggle between original mode and OLED emulation mode. You can do so even when a game is open.

## Building

Dependencies:

- [DolceSDK](https://forum.devchroma.nl/index.php/topic,129.0.html)
- [fnblit and bit2sfn](https://git.shotatoshounenwachigau.moe/vita/fnblit)
- [taiHEN](https://git.shotatoshounenwachigau.moe/vita/taihen)
- [Terminus font](http://terminus-font.sourceforge.net)

To build dependencies, application, and module:

```sh
cmake .
make dep-all
make
```

## Contributing

Use [git-format-patch](https://www.git-scm.com/docs/git-format-patch) or [git-request-pull](https://www.git-scm.com/docs/git-request-pull) and email me at <asakurareiko@protonmail.ch>.

## See also

- [Discussion](https://forum.devchroma.nl/index.php/topic,201.0.html)
- [Source repository](https://git.shotatoshounenwachigau.moe/vita/lcd-colour-crunch)
