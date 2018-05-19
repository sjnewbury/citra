# Merge log

Scroll down for the original README.md!

Base revision: 85e47f1ea7013eb9a0f27ec4b946d71e04f970c1

|PR Number|Commit|Title|Author|Merge Success|
|----|----|----|----|----|
|[21](undefined)|f941e1f36559dff65bd8527aeb2ce0da270d94da|Canary Base|j-selby|true|
|[3746](undefined)|e289c87e421378a63e360259fe93a1158f7b229a|Service/NDM: convert to ServiceFramework|wwylele|true|
|[3729](undefined)|5f3b6401b558d3f645610f22d05453a969be3647|gl_rasterizer: implement shadow map 2D|wwylele|true|
|[3724](undefined)|8e1e52cad917a80d121d7ad6aa4236d5bcc0a56e|gl_rasterizer: Remove redundant scissor state change.|degasus|true|
|[3714](undefined)|08a38370b0ece0302f33ab778d4764e962953dd8|video_core/command_processor: correctly handles 0xFFFF index as a normal index|wwylele|true|
|[3706](undefined)|3f0e017e1b5e2107cb1e502235065bd448f5c178|Use Travis CI to build MinGW packages|liushuyu|true|
|[3617](undefined)|cc138ab550a59afd5239756a599eade6c788b9c5|QT: Add support for multiple game directories|BreadFish64|true|


End of merge log. You can find the original README.md below the break.

------

**BEFORE FILING AN ISSUE, READ THE RELEVANT SECTION IN THE [CONTRIBUTING](https://github.com/citra-emu/citra/blob/master/CONTRIBUTING.md#reporting-issues) FILE!!!**

Citra Emulator
==============
[![Travis CI Build Status](https://travis-ci.org/citra-emu/citra.svg?branch=master)](https://travis-ci.org/citra-emu/citra)
[![AppVeyor CI Build Status](https://ci.appveyor.com/api/projects/status/sdf1o4kh3g1e68m9?svg=true)](https://ci.appveyor.com/project/bunnei/citra)

Citra is an experimental open-source Nintendo 3DS emulator/debugger written in C++. It is written with portability in mind, with builds actively maintained for Windows, Linux and macOS. Citra only emulates a subset of 3DS hardware and therefore is generally only useful for running/debugging homebrew applications.

Citra is even able to boot several commercial games! Some of these do not run at a playable state, but we are working every day to advance the project forward. (Playable here means the same as "OK" on our [game compatibility list](https://citra-emu.org/game).)

Citra is licensed under the GPLv2 (or any later version). Refer to the license.txt file included. Please read the [FAQ](https://citra-emu.org/wiki/faq/) before getting started with the project.

Check out our [website](https://citra-emu.org/)!

For development discussion, please join us at #citra on freenode.

### Development

Most of the development happens on GitHub. It's also where [our central repository](https://github.com/citra-emu/citra) is hosted.

If you want to contribute please take a look at the [Contributor's Guide](CONTRIBUTING.md) and [Developer Information](https://github.com/citra-emu/citra/wiki/Developer-Information). You should as well contact any of the developers in the forum in order to know about the current state of the emulator because the [TODO list](https://docs.google.com/document/d/1SWIop0uBI9IW8VGg97TAtoT_CHNoP42FzYmvG1F4QDA) isn't maintained anymore.

If you want to contribute to the user interface translation, please checkout [citra project on transifex](https://www.transifex.com/citra/citra). We centralize the translation work there, and periodically upstream translation.

### Building

* __Windows__: [Windows Build](https://github.com/citra-emu/citra/wiki/Building-For-Windows)
* __Linux__: [Linux Build](https://github.com/citra-emu/citra/wiki/Building-For-Linux)
* __macOS__: [macOS Build](https://github.com/citra-emu/citra/wiki/Building-for-macOS)


### Support
We happily accept monetary donations or donated games and hardware. Please see our [donations page](https://citra-emu.org/donate/) for more information on how you can contribute to Citra. Any donations received will go towards things like:
* 3DS consoles for developers to explore the hardware
* 3DS games for testing
* Any equipment required for homebrew
* Infrastructure setup
* Eventually 3D displays to get proper 3D output working

We also more than gladly accept used 3DS consoles, preferably ones with firmware 4.5 or lower! If you would like to give yours away, don't hesitate to join our IRC channel #citra on [Freenode](http://webchat.freenode.net/?channels=citra) and talk to neobrain or bunnei. Mind you, IRC is slow-paced, so it might be a while until people reply. If you're in a hurry you can just leave contact details in the channel or via private message and we'll get back to you.
