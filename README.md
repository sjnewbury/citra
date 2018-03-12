# Merge log

Scroll down for the original README.md!

Base revision: 959261b37a1eda8b38d1250f9dc435f99af5380a

|PR Number|Commit|Title|Author|Merge Success|
|----|----|----|----|----|
|[22](undefined)|d4982025bf39d37b90ad8139e08dfdaaca9b6b20|Glvtx configuration options for LibRetro|j-selby|true|
|[21](undefined)|66facd4d7a68b62431dd4b0a000b5523c729f127|Canary Base|j-selby|true|
|[3501](undefined)|e5c1a8218b1dd75fa0c8981896ef6b39394dfb73|Move WebServices to use LibreSSL + cpp-httplib|j-selby|false|
|[3499](undefined)|9de84c966b00439d625a9841220eeebc97bd4556|Convert PICA Shaders to GLSL|jroweboy|true|
|[3498](undefined)|ea82203780d8f0666d48cc07a3700fb121f6e30c| Service/CFG: convert to ServiceFramework |wwylele|true|
|[3489](undefined)|29d6e050445df9d5c78faaf02e0ea5024a8097b8|NWM_ UDS:Let connected clients handle the eapol packet|B3n30|true|
|[3484](undefined)|92c7bb9d20c0d33cf579f36093c90d49af7394ca|pica/lighting: compute highlight clamp after one-/two-sided diffuse pass|wwylele|true|
|[3481](undefined)|ac836b7b0eafda82f838ec25a2500bed839166a3|NWM_UDS:: Check flags in SendTo|B3n30|true|
|[3073](undefined)|4f658dd8accf3557f784e33bbcc1e6d08f086bc1|Citra-qt: Add multiplayer ui|jroweboy|true|


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
