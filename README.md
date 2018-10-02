# Merge log

Scroll down for the original README.md!

Base revision: a0c222c00645bff70b2347ddef66767bfc303535

|PR Number|Commit|Title|Author|Merge Success|
|----|----|----|----|----|
|[21](undefined)|1d7548856280c62bc40764e940015a5c15d1c952|Canary Base|j-selby|true|
|[4282](undefined)|cb775eb1ba90048367510a0b8767cb56aaf577be|core, citra_qt: add frame advancing to framelimiter|zhaowenlan1779|false|
|[4279](undefined)|deaed383572cc3f6dadf2988183a58c2e1a68410|applets: stub mii selector to always return a standard mii|FearlessTobi|true|
|[4272](undefined)|6b31a81f7668eea23b2c3ed82cc85a72f9676611|Core: pass down Core::System reference to all services|wwylele|false|
|[4270](undefined)|3970d86f35a20c5b87dbdd279d8c3461b2228dd0|Threaded CPU vertex shader processing|jroweboy|true|
|[4267](undefined)|9d142f981dd4810085355b0659173d2cb0a12e7f|movie: Add clock init time to CTM header|zhaowenlan1779|true|
|[4244](undefined)|41d53cee1f291a989315462815ba00dd522dcf2e|common/swap: add swap template for enum|wwylele|true|
|[4229](undefined)|8cf1132b2e1f4a09176801cc2d97b646b3d2bf88|citra_qt, core: game list "Open XXX Location" improvements|zhaowenlan1779|false|
|[4089](undefined)|80bdc4ac2d49af26e9649a6febf9efe970f9d448|[NOT FOR MERGE YET] Ignore format reinterpretation hack|jroweboy|true|


End of merge log. You can find the original README.md below the break.

------

**BEFORE FILING AN ISSUE, READ THE RELEVANT SECTION IN THE [CONTRIBUTING](https://github.com/citra-emu/citra/blob/master/CONTRIBUTING.md#reporting-issues) FILE!!!**

Citra
==============
[![Travis CI Build Status](https://travis-ci.org/citra-emu/citra.svg?branch=master)](https://travis-ci.org/citra-emu/citra)
[![AppVeyor CI Build Status](https://ci.appveyor.com/api/projects/status/sdf1o4kh3g1e68m9?svg=true)](https://ci.appveyor.com/project/bunnei/citra)

Citra is an experimental open-source Nintendo 3DS emulator/debugger written in C++. It is written with portability in mind, with builds actively maintained for Windows, Linux and macOS.

Citra emulates a subset of 3DS hardware and therefore is useful for running/debugging homebrew applications, and it is also able to run many commercial games! Some of these do not run at a playable state, but we are working every day to advance the project forward. (Playable here means compatibility of at least "Okay" on our [game compatibility list](https://citra-emu.org/game).)

Citra is licensed under the GPLv2 (or any later version). Refer to the license.txt file included. Please read the [FAQ](https://citra-emu.org/wiki/faq/) before getting started with the project.

Check out our [website](https://citra-emu.org/)!

For development discussion, please join us at #citra-dev on freenode.

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
