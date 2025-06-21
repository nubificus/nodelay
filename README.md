# nodelay.so – Disable Nagle's Algorithm via `LD_PRELOAD`

This project provides a minimal `LD_PRELOAD`-based shared object (`nodelay.so`)
that forces TCP sockets to disable Nagle’s algorithm (`TCP_NODELAY`), even if
the application doesn’t set it explicitly.

## Build

Make sure you have `gcc` installed, then run:

```sh
make
```

This will produce `nodelay.so`.

## Usage

Preload the shared object when running a TCP-based program:

```sh
LD_PRELOAD=./nodelay.so ./my_tcp_benchmark
```

This forces all `socket()` and `setsockopt()` calls to set `TCP_NODELAY` on `SOCK_STREAM` sockets.

## Example

```sh
LD_PRELOAD=./nodelay.so curl http://localhost:8080
```

## Clean up

```sh
make clean
```

## Notes

- Works only for TCP sockets (`SOCK_STREAM`)
- Has no effect on Unix domain sockets or UDP
- Designed for Linux

## Files

- `nodelay.c`: Source code for the preload library
- `Makefile`: Build script

## License

Apache-2.0
