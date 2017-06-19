# vscode-cpp-remote-debug
Project for testing remote debugging of C++ code with gdb and gdbserver in VS Code

> **~~Problem~~**
>
> ~~When remotely debugging C++ source code residing in a complex folder hierarchy VS Code lacks proper graphical debugging integration in the GUI.~~
>
> After fixing the `.vscode/launch.json` by adding
> ```json
> // ...
> "sourceFileMap": {
>   "/": "/run/user/1000/gvfs/sftp:host=nafhh-atlas06.desy.de/"
> },
> // ...
> ```
> as suggested in [this GitHub issue](https://github.com/Microsoft/vscode-cpptools/issues/834#issuecomment-309519732) the graphical remote debugging works perfectly fine!


In order to demonstrate this, this repo intentionally contains the full folder structure for out-of-source builds as well as a minimum failing folder setup consisting of two source code folders.


## Setup

- local machine is Linux notebook (Linux Mint 18 Cinnamon Edition), denoted by `local $`

  the file system of the remote machine is mounted on the local machine either using `File -> Connect to Server` (type: `ssh`) from the Nemo file browser or using `sshfs`
  
- remote machine is Linux server, denoted by `remote $`, on which `gdbserver` is available


## Step-by-Step Instructions to Reproduce

- SSH to remote machine and use port forwarding
  ```sh
  local $ ssh -L9091:localhost:9091 user@some.server.org
  ```
- Clone repo with
  ```sh
  remote $ git clone https://github.com/dmrauch/vscode-cpp-remote-debug.git
  ```
- Out-of-source build with debug symbols
  ```sh
  remote $ cd vscode-cpp-remote-debug/build/debug
  remote $ cmake -DCMAKE_BUILD_TYPE=Debug ../../source
  remote $ make
  ```
- Start `gdbserver`
  ```sh
  remote $ cd ../.. # going back into vscode-cpp-remote-debug/
  remote $ gdbserver :9091 build/debug/file1
  ```
- Set breakpoints somewhere in both source code files `folder1/file1.cxx` and `folder2/file2.cxx`

- Open the debug view, select the `Remote Debug` configuration and launch the debugger configuration `(gdb) Launch Remote Debugging of file1`

Happy debugging!

![screenshot-graphical-remote-debugging](screenshot-graphical-remote-debugging.png)


## Credits

- The `launch.json` is based on the following, very helpful article: [Debugging C/C++ Programs Remotely Using Visual Studio Code and gdbserver](https://medium.com/@spe_/debugging-c-c-programs-remotely-using-visual-studio-code-and-gdbserver-559d3434fb78).
- Big thanks go to [@pieandcakes](https://github.com/pieandcakes) for pointing out the `sourceFileMap` property in `.vscode/launch.json`.