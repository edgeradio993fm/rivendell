### Rivendell Radio Automation for Raspberry Pi Hardware

Welcome to the github for the Rivendell on Raspberry Pi project. This release has no affiliation with the official Rivendell software. We aim to provide a stable release for those who wish to use the software on Raspberry Pi hardware. We will be merging as much of the official code as possible. This repository's changes will be based on running the system reliably on the Raspberry Pi hardware and the official Raspbian distribution. The packages and images are provided as is and come with no guarenteed or warranty.

Please see the [releases](https://github.com/edgeradio993fm/rivendell/releases) page for the latest images and update packages.

#### If you would like to get updates via the APT package manager

Run this command to download and install the repo GPG Key.
```bash
wget -qO - https://7edg.org/repo/rivendellpi.key | sudo apt-key add -
```
Edit your /etc/apt/sources.list file and add this line at the bottom.
```bash
deb https://7edg.org/repo buster main
```

***

### This is the README for the Rivendell package.

This software comes with ABSOLUTELY NO WARRANTY. See the file COPYING for
details.

Welcome to this release of the Rivendell Project. Rivendell aims
to be a robust, functionally complete digital audio system for use in 
professional radio broadcast environments.

See the file INSTALL for installation instructions. If you are upgrading from
a 1.x or 2.x version of Rivendell, also see the file 'UPGRADING'
for important notes and pointers.


OVERVIEW
Rivendell contains a full set of functionality needed to operate a radio
automation system, consisting of the following components:

RDAdmin
A comprehensive application for the administration and configuration
of Rivendell.

RDLibrary
The production audio interface.

RDCatch
The automatic recorder and task scheduler interface.

RDLogin
A small utility for logging users into and out of the system.

RDLogEdit
A air log creation, editing and voicetracker tool.

RDLogManager
A utility for the automatic generation of logs, based on templates.
It also supports importation of schedule information from a wide
variety of third-party traffic and music scheduling systems.

RDAirPlay
The on-air playout application.

RDPanel
A 'fullscreen' SoundPanel cartwall application.

RDCartSlots
An application that emulates a multi-slot cart decks.

RDCastManager
A utility for posting and managing podcast episodes.

RDGpiMon
A utility for monitoring GPI line status.

RDAlsaConfig
A utility for configuring ALSA audio adapters.

RDDbConfig
A utility for creating, backing up and restoring the Rivendell
database.

RDImport
A command-line utility for batch importing audio along with
accompanying metadata. Do:

	man 1 rdimport

for usage help.

RMLSend
A GUI and command-line utility for sending Rivendell Macro Language
(RML) commands.

RDSoftKeys
A lightweight button panel utility for sending RML commands.
