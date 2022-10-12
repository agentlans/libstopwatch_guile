# libstopwatch
Easy simple stopwatch for Guile Scheme

## Install

Required:
- [GNU Guile](https://www.gnu.org/software/guile/)
- C++11 compiler
- `make` toolchain
- Unix environment

1. Clone repository
2. Run `make install`
3. Run `make uninstall` to remove this Guile extension

## Use

```scheme
(use-modules (extra stopwatch))

;; Create a stopwatch and start it
(define sw (make-stopwatch))
(start-stopwatch! sw)
;; Do computations here
(stop-stopwatch! sw)

;; How much time passed in seconds?
(stopwatch-time sw)

;; Sets time to 0.
(reset-stopwatch! sw)

;; Run a thunk and time how long
(time-thunk (lambda () (display "Hello world")))
```

## Author, License

Copyright :copyright: 2022 Alan Tseng

MIT License
