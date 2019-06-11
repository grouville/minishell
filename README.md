# minishell
<b>Shell development 1.0 : first encounter</b>

The second project of the system branch.

The aim ? To reproduce as quickly as possible, and without any prior in-depth reflection, a basic shell capable of executing commands.

As the project progressed, I learned the shell execution part through the execve function, the chaotic errors of lexing and parsing through an strsplit, an initiation to signal management and the implementation of env, echo, exit, setenv and unsetenv built-ins.

This implementation supports a basic quote management and a very basic escape management.
