# dlms_parser

`dlms_parser` is a lightweight C++20 library for parsing DLMS/COSEM push telegrams from electricity meters. It handles transport decoding (`RAW`, `HDLC`, `M-Bus`), optional AES-128-GCM decryption, APDU unwrapping, and AXDR pattern matching to extract meter values in a form that is easy to consume from embedded code.

It is designed for embedded and integration-heavy environments such as ESPHome, but it also builds and tests on desktop platforms.

## Features

- Parses DLMS/COSEM push telegrams from complete frames
- Supports `RAW`, `HDLC`, and `MBUS` input formats
- Handles optional AES-128-GCM encrypted APDUs
- Extracts values through a simple callback-based API
- Includes built-in AXDR descriptor patterns for common meter layouts
- Allows custom patterns for vendor-specific structures
- Provides optional raw captures for advanced integrations

## Quick Start

```cpp
#include "dlms_parser/dlms_parser.h"

dlms_parser::DlmsParser parser;
parser.set_frame_format(dlms_parser::FrameFormat::RAW);
parser.load_default_patterns();

auto on_value = [](const char* obis, float num, const char* str, bool is_numeric) {
    if (is_numeric) {
        printf("%s = %.3f\n", obis, num);
    } else {
        printf("%s = \"%s\"\n", obis, str);
    }
};

size_t count = parser.parse(frame_bytes, frame_len, on_value);
printf("%zu objects found\n", count);
```

If your meter uses transport framing or encryption, set those options before calling `parse()`:

```cpp
parser.set_frame_format(dlms_parser::FrameFormat::HDLC);
parser.set_decryption_key(key);
```

## Supported Inputs

- `RAW`: buffer already starts with a supported APDU tag or raw AXDR container
- `HDLC`: framed DLMS telegrams, including segmented frames
- `MBUS`: wired M-Bus wrapped DLMS telegrams
- Encrypted APDUs: `General-GLO-Ciphering` and `General-DED-Ciphering`

## Typical Usage Flow

1. Create `dlms_parser::DlmsParser`
2. Select the frame format
3. Set the decryption key if the meter is encrypted
4. Load built-in patterns and optionally register custom ones
5. Pass one complete frame to `parse()`
6. Consume extracted values in the callback

## Documentation

- [HOWTO.md](HOWTO.md): practical guide, examples, troubleshooting
- [REFERENCE.md](REFERENCE.md): public API, pattern DSL, protocol/reference notes

## Build And Test

The repository includes CMake build files, PlatformIO metadata, and integration tests based on real meter dumps.

Typical local workflow:

```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build
```

## License

Apache-2.0. See [LICENSE](LICENSE).
