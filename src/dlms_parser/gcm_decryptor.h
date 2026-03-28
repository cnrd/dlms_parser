#pragma once

#include <array>
#include <cstdint>
#include <vector>

namespace dlms_parser {

// AES-128-GCM decryptor. Platform-abstracted:
//   ESP8266            : BearSSL
//   ESP32 IDF >= 6.0   : PSA Crypto
//   all others         : mbedTLS
class GcmDecryptor {
 public:
  void set_key(const std::array<uint8_t, 16>& key);
  void set_key(const std::vector<uint8_t>& key);

  bool has_key() const { return has_key_; }

  // In-place decrypt: reads ciphertext from buf[cipher_offset..], writes plaintext to buf[0..].
  // Returns plaintext length, or 0 on failure. iv must be exactly 12 bytes.
  size_t decrypt_in_place(const uint8_t* iv, uint8_t* buf, size_t cipher_offset, size_t cipher_len) const;

 private:
  bool has_key_{false};
  std::array<uint8_t, 16> key_{};
};

}  // namespace dlms_parser
