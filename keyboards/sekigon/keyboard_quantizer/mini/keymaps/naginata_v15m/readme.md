# Keyboard Quantizer Mini

## 不具合
* keymap.h がない  
→ 製作
```
typedef enum {
    KEY_OS_OVERRIDE_DISABLE, /* Disable key override for JP/US OS */
    US_KEY_JP_OS_OVERRIDE_DISABLE, /* Enable US keyboard on JP OS */
    JP_KEY_US_OS_OVERRIDE_DISABLE, /* Enable JP keyboard on US OS */
} key_os_override_t;

typedef union {
  uint32_t raw;
  struct {
    uint8_t key_os_override;
  };
} user_config_t;
```
* EEPROMに書き込もうとすると暴走する  
書き込んだ後にキー入力を受け付けなくなるだけなので、その都度パソコンから外すなどしながら一通り設定する。  
その後、EEPROMに書き込むことがあるキーコードを消せばよい
* Windowsでのユニコード入力は `#define TAP_CODE_DELAY 10` になっているので遅い  
なお、この設定を 0 にすることはできないらしい
* `OS_DETECTION_ENABLE = yes` は効かないらしい
* 「Q+W」で横書きに、「Q+A」で縦書きになる  
EEPROMには書き込まないので電源を切るまで有効。  
OLEDは通常、薙刀式オフまで変化しない
