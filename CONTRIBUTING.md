# Contributing to W26 ESC

## Setup

### Prerequisites
- Git (install and configure with GitHub account)

#### Firmware Subteam
- VS Code
- MSYS2 (to build)
- LATER, but not yet: STM32CubeIDE (latest)

#### Electrical Subteam
- KiCad 9 (latest)

### Clone the Repo
```bash
git clone https://github.com/Electrium-Mobility/esc-w26.git
cd esc-w26
```

## Git Workflow
1. Before starting development, create a branch for your task:
    ```bash
    git checkout -b <subteam>-<task>
2. Develop!
3. Stage your changes before committing:
    ```bash
    git add .
4. Make regular commits with clear messages to document changes (e.g. CAN hardware):
    ```bash
    git commit -m "Defined MCU pins to CAN transceiver module"
5. Push your local changes to the remote branch:
    ```bash
    git push origin <subteam>-<task>
6. Open a pull request (PR) on GitHub and wait for it to be reviewed and merged!

## Building

### Setup
1. Open the MSYS2 UCRT64 shell
2. Install the toolchain and cmake packages:
    ```bash
    pacman -Syu
    pacman -S mingw-w64-ucrt-x86_64-toolchain mingw-w64-ucrt-x86_64-cmake

### Build
1. Configure (while in the MSYS2 UCRT64 shell)
    ```bash
    cmake -S . -B build
2. Build
    ```bash
    cmake --build build
