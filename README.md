# Audio Filters

An experimental audio-processing project written in C. The repository currently provides the beginnings of a small digital signal processing toolkit: a direct Discrete Fourier Transform (DFT), complex-number helpers, and data structures for parsing WAV files.

> [!IMPORTANT]
> This project is in an early stage of development. The DFT utilities are implemented, but WAV parsing is unfinished and the command-line entry point does not process audio yet.

## Current Features

- Forward DFT for integer-valued signals
- Complex magnitude and phase calculations
- Helpers for printing time-domain samples, complex frequency bins, and magnitude/phase values
- Initial WAV format and data chunk structures
- A minimal C entry point for future examples and command-line processing

## Project Structure

```text
audio-filters/
├── main.c   # Placeholder command-line entry point
├── dft.h    # DFT, complex-number, and output helpers
└── wave.h   # WAV chunk structures and work-in-progress parser
```

## Requirements

- A C compiler such as GCC or Clang
- The standard C math library

## Getting Started

Clone the repository:

```bash
git clone https://github.com/lakshyarajrtm/audio-filters.git
cd audio-filters
```

Build the current program:

```bash
cc -std=gnu11 -Wall -Wextra main.c -o audio-filters -lm
```

Run it:

```bash
./audio-filters
```

The current `main` function exits immediately, so this command does not produce output yet.

## Using the DFT Utilities

Include `dft.h`, pass an integer signal to `dft`, and release the returned frequency-domain array when finished:

```c
#include <stdio.h>
#include <stdlib.h>

#include "dft.h"

int main(void) {
    int signal[] = {1, 0, -1, 0};
    int sample_count = (int)(sizeof(signal) / sizeof(signal[0]));

    Complex *spectrum = dft(signal, sample_count);
    if (spectrum == NULL) {
        fprintf(stderr, "Could not allocate the DFT output.\n");
        return 1;
    }

    print_dft_mag_phase(spectrum, sample_count);
    free(spectrum);
    return 0;
}
```

Compile a source file using the header with:

```bash
cc -std=gnu11 -Wall -Wextra example.c -o example -lm
```

### DFT API

| Function | Description |
| --- | --- |
| `dft(int *signal, int N)` | Computes an unnormalized, forward DFT and returns `N` complex frequency bins allocated on the heap. |
| `magnitude(Complex num)` | Returns the magnitude of a complex value. |
| `phase(Complex num)` | Returns the phase angle in radians. |
| `print_signal(int *signal, int N)` | Prints one time-domain sample per line. |
| `print_dft_coord(Complex *signal, int N)` | Prints frequency bins in rectangular form. |
| `print_dft_mag_phase(Complex *signal, int N)` | Prints the magnitude and phase of each bin. |

The direct DFT implementation takes `O(N²)` time. It is useful for learning and small inputs, but an FFT will be more practical for large audio buffers.

## WAV Support

`wave.h` defines `HeadChunk` and `DataChunk`, which model fields needed for WAV format and data chunks. The `readWaveHead` function is not complete and must not be called yet.

Planned parsing work includes:

- Validating the RIFF and WAVE identifiers
- Locating `fmt ` and `data` chunks safely
- Reading little-endian fields without alignment assumptions
- Supporting extra or unknown WAV chunks
- Validating buffer bounds and malformed input
- Returning parsed sample data and useful errors

## Current Limitations

- `main.c` is only a placeholder.
- WAV parsing is incomplete.
- No audio filters are implemented yet.
- DFT input is limited to integer samples.
- The transform is not normalized and has no inverse DFT counterpart.
- Functions are defined directly in headers, which can cause duplicate-symbol errors when included by multiple translation units.
- There are no automated tests, example audio files, or benchmarks.

## Roadmap

- [ ] Complete and test WAV parsing
- [ ] Add a working command-line example
- [ ] Separate public headers from C implementation files
- [ ] Add inverse DFT and normalization options
- [ ] Implement common filters such as low-pass, high-pass, band-pass, and notch filters
- [ ] Support floating-point audio samples
- [ ] Add unit tests and sample fixtures
- [ ] Add FFT-based processing for larger inputs

## Contributing

Contributions are welcome. Because the codebase is still taking shape, please open an issue before making a large change so the implementation and public API can be discussed first.

When contributing, keep changes focused, compile with warnings enabled, and include tests for new signal-processing or WAV-parsing behavior.

## License

This repository does not currently include a license. Until one is added, the source remains under the copyright holder's default rights.
