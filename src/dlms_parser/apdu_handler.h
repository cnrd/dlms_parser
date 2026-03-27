#pragma once

#include "gcm_decryptor.h"
#include "types.h"
#include <cstdint>
#include <functional>

namespace dlms_parser {

// Callback fired by ApduHandler with raw AXDR payload bytes (after header stripping / decryption).
using AxdrPayloadCallback = std::function<void(const uint8_t* axdr, size_t len)>;

// Scans a buffer byte-by-byte for the first recognized DLMS APDU tag.
// Unknown leading bytes are skipped. Recognized tags:
//   0xE0  General-Block-Transfer   : reassembles numbered blocks, then recurses
//   0x0F  DATA-NOTIFICATION        : strips Long-Invoke-ID and optional datetime header
//   0xDB  General-Glo-Ciphering    : decrypts with GcmDecryptor, then recurses
//   0xDF  General-Ded-Ciphering    : decrypts with GcmDecryptor, then recurses
//   0x01 / 0x02  raw ARRAY/STRUCT  : no APDU wrapper (e.g. HDLC/Aidon)
class ApduHandler {
 public:
  void set_decryptor(GcmDecryptor* d) { decryptor_ = d; }

  // Fires cb exactly once on success with the raw AXDR payload span.
  bool parse(const uint8_t* buf, size_t len, AxdrPayloadCallback cb) const;

 private:
  bool parse_data_notification_(const uint8_t* buf, size_t len, AxdrPayloadCallback cb) const;
  bool parse_ciphered_apdu_(const uint8_t* buf, size_t len, uint8_t tag, AxdrPayloadCallback cb) const;
  bool parse_general_block_transfer_(const uint8_t* buf, size_t len, AxdrPayloadCallback cb) const;

  GcmDecryptor* decryptor_{nullptr};
};

}  // namespace dlms_parser
