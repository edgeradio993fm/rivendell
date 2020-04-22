### Rivendell Radio Automation for Raspberry Pi Hardware

Welcome to the github for the Rivendell on Raspberry Pi project. This release has no affiliation with the official Rivendell software. We aim to provide a stable release for those who wish to use the software on Raspberry Pi hardware. We will be merging as much of the official code as possible. This repository's changes will be based on running the system reliably on the Raspberry Pi hardware and the official Raspbian distribution. The packages and images are provided as is and come with no guarenteed or warranty.

Please see the [releases](https://github.com/edgeradio993fm/rivendell/releases) page for the latest images and update packages.

#### If you would like to get updates via the APT package manager

Run this command to download and install the repo GPG Key.
```bash
wget -qO - https://7edg.org/repo/rivendellpi.key | sudo apt-key add -
```
Run this command to add our repository to your /ect/apt/sources.list file.
```bash
sudo echo "deb https://7edg.org/repo buster main" | sudo tee -a /etc/apt/sources.list
```
We do not recommend installing Rivendell directly from our repository as you will have to manually set a number of configuration options such as the mysql database and audio storage. Use the below automated install to do the initial setup and then update your Rivendell install using **sudo apt update -y && sudo apt upgrade rivendell -y** when required.
***

### Installing Rivendell From Scratch

Installing a fresh copy of Rivendell on a Raspbian and Debian based system it isn't too hard. We have made an automated install script that will install Rivendell on a Rasbian Raspberry Pi (armhf) and Debian (amd64) based systems for the current sudo user, configure audio storage and set up a blank database. This will also install the required dependancies to build Rivendell from source should the need occour. This process will also install our repository for future updates and the [Debian Multimeida Packages]( https://deb-multimedia.org) repository, as some required audio codecs are no longer included in Debian Buster by default.

Make sure you have **wget** and **curl** installed before running the install process.

Run this command in a terminal to start the automated install process.
```bash
curl -L https://7edg.org/rdinstall/install.sh | sudo bash
```
Post install you should run **rdadmin** to generate/configure your host settings.
***

### A Quick Note For Those Running Debian and Ubuntu Based Distributions

**Debian**  
This forked repo will compile and run fine on other Debian based systems. We've have added an amd64 package to our repository for Debian Buster. You can install it using the above method. While it has been sucsessfully tested on our end, there may still be a few bugs. 

**Ubuntu**  
There is no support for Ubuntu based systems and the install process will fail. You can get things to work by adding the Debian Repositories to your Ubuntu system. However, this is very much not recommended.

If you have any feedback or encounter bugs, please let us know via [tech@edgeradio.org.au](mailto:tech@edgeradio.org.au).
***

### Let Us Know If You Use Rivendell On Your Raspberry Pi
If you find using Rivendell on your Raspberry Pi is working for you, please let us know via email. We're keen to complile a list of stations that run Pi based Rivendell systems. Doesn't matter if you only use them as workstations or full on setups. Drop us a line and share your experence.

[tech@edgeradio.org.au](mailto:tech@edgeradio.org.au)
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
