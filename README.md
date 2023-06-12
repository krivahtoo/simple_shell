# Simple Shell
This is a simple implementation of the UNIX shell (`/bin/sh`).
This is implemented as part of the ALX SE Low-level programming & Algorithm group project.

# Build

```shell
$ make
# or
$ gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

## Run

#### Interactive
```shell
$ ./hsh
```

#### Non-interactive
```shell
$ echo "ls" | ./hsh
```

# Features/TODO
- [x] Handle the `PATH`
- [x] Implement the `exit` built-in, that exits the shell
	* [x] Usage: `exit status`, where status is an integer used to exit the shell
- [x] Implement the `env` built-in, that prints the current environment
- [x] Implement the `setenv` and `unsetenv` builtin commands
- [x] Implement the builtin command `cd`
- [ ] Handle the commands separator `;`
- [ ] Handle the `&&` and `||` shell logical operators
- [x] Implement the `alias` builtin command
- [x] Handle variables replacement
	* [x] Handle the `$?` variable
	* [x] Handle the `$$` variable
- [x] Handle comments (`#`)
- [x] Handle file as input, i.e. `./hsh file`

# Contributors
<a href="https://github.com/krivahtoo/simple_shell/graphs/contributors">
  <img src="https://contrib.rocks/image?repo=krivahtoo/simple_shell" />
</a>

Made with [contrib.rocks](https://contrib.rocks).

- [**Noah Cheptoo**](https://github.com/krivahtoo)
- [**Chiemeka Onyeabo**](https://github.com/Dibuji)
