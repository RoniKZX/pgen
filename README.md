# PGEN: A Command Line Password Generator!

A password generator written in C++.

## Requirements to compile

Linux >= 5.4
[libsodium](https://doc.libsodium.org/) >= 1.0.19
[CLI11](https://github.com/CLIUtils/CLI11/) >= 2.3.2
g++ >= 13.2.1

## Instructions to compile

1. Clone this repository:
`git clone --depth 1 https://github.com/RoniKZX/pgen`

2. Compile the code:
`g++ src/pgen.cpp -lsodium -o build/pgen`

You should be ready to go!

Just execute: `./build/pgen -h` to see the help

### Disclaimer
Even if I know a thing or two, I'm not a security professional whatsoever.
I just did this to practice while trying to make it "as secure as ***I*** can."
You know... Just something not to get rusty.
