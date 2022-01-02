# zombie

These C programs test the portability of three methods to handle
zombie processes, such as those are created by `fork(3)` when a child
process ends.

According to _The Linux Programming Interface_ (section 26.3.3):

> The only completely portable way of preventing the creation of
> zombies is to call `wait()` or `waitpid()`, possibly from within a
> handler established for `SIGCHLD`.

However, there are two other ways to handle zombies: ignoring
`SIGCHLD` and the `SIG_NOCLDWAIT` flag.

Results of which modern (POSIX.1-2008 supporting) platforms support
these different methods is tracked below. If you have results for your
own system, please share them.

# Usage

    $ meson build
    $ cd build
    $ ninja test
    [2/3] Running all tests.
    1/3 test_zombie1        OK              1.01s
    2/3 test_zombie2        OK              1.01s
    3/3 test_zombie3        OK              1.01s

    OK:                 3
    Expected Fail:      0
    Fail:               0
    Unexpected Pass:    0
    Skipped:            0
    Timeout:            0

    Full log written to /home/kris/c/zombie/build/meson-logs/testlog.txt

# Method 1: Ignore `SIGCHLD`

```c
struct sigaction action = { .sa_handler = SIG_IGN };
sigemptyset(&action.sa_mask);
sigaction(SIGCHLD, &action, NULL);
```

This is equivalent to the venerable

```c
signal(SIGCHLD, SIG_IGN);
```

# Method 2: `SIG_NOCLDWAIT` flag

```c
struct sigaction action = { .sa_flags = SA_NOCLDWAIT };
sigemptyset(&action.sa_mask);
sigaction(SIGCHLD, &action, NULL);
```

# Method 3: Calling `waitpid()`

```c
struct sigaction action = { .sa_handler = handler };
sigemptyset(&action.sa_mask);
sigaction(SIGCHLD, &action, NULL);
```

with the signal handler

```c
static void handler(int signum)
{
    pid_t pid;

    while ((pid = waitpid(-1, NULL, WNOHANG)) > 0)
        ;
}
```

This is the most portable way to clean up zombie processes.

# Results

| Platform   | libc          |`SIG_IGN` | `SIG_NOCLDWAIT` | `waitpid()` |
|------------|---------------|----------|-----------------|-------------|
| Linux 5.15 | GNU libc 2.34 | ✅ | ✅ | ✅ |

## Contributing

[Pull requests][pulls] and [issue/bug reports][issues] are very much encouraged.

## License

[MIT](LICENSE)


[issues]: https://github.com/bitmandu/zombie/issues
[pulls]: https://github.com/bitmandu/zombie/pulls
