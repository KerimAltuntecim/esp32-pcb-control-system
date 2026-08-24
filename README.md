# ESP32 PCB Control System

ESP32-C3 tabanlı, Nextion HMI ekran üzerinden kontrol edilen çok işlevli bir PCB prototipi. Kart; sensör okuma, motor sürme, röle/triyak/MOSFET çıkışları ve kullanıcı arayüzü haberleşmesini tek bir donanım üzerinde birleştirir.

## Öne çıkan özellikler

- ESP32-C3-WROOM-02 mikrodenetleyici
- Nextion ekran ile UART haberleşmesi
- STEP/DIR sinyalleriyle A4988 step motor sürücüsü
- PC817 optokuplörlü sensör ve MOSFET kontrol girişleri
- MOC3022M + BTA136-500 triyak sürücü katı
- Röle ile harici yük açma/kapama
- IR2101 + IRF540N MOSFET güç sürücü katı
- TCRT5000 dijital sensör girişi
- LM35 analog sıcaklık girişi
- RGB LED PWM kontrolü ve buzzer uyarısı
- 15 V'tan 5 V üreten L7805 besleme katı

## Nextion arayüzü

Nextion ekran üzerinden aşağıdaki menüler tasarlanmıştır:

- Step motor: yön ve adım miktarı
- Triyak: kontrol/ateşleme seviyesi
- RGB LED: kırmızı, yeşil ve mavi parlaklık seviyeleri
- Sensör: algılama görseli ve 0/1 durumu
- MOSFET: PWM kontrol seviyesi
- Röle: açma/kapama

ESP32 firmware’i Nextion’dan gelen `role`, `tri`, `fet`, `rgbr`, `rgbg`, `rgbb`, `sens` ve `step` komutlarını işler. `kerim.HMI`, arayüzün düzenlenebilir Nextion Editor kaynak dosyasıdır.

## Klasörler

- `firmware/`: ESP32 Arduino firmware’i
- `hardware/kicad/`: KiCad şematik ve PCB tasarımı
- `nextion/`: Nextion HMI kaynak dosyası
- `docs/images/`: PCB, şematik ve arayüz görselleri

## Prototip durumu ve sınırlamalar

Bu çalışma ilk el montajı yapılmış bir prototiptir; seri üretime hazır ürün olarak değerlendirilmemelidir. Firmware’in bazı bölümleri donanım üzerinde yeniden doğrulanmalıdır. Triyak ve MOSFET kontrol seviyelerinin gerçek yükteki etkisi, bağlı yük tipine ve güç katı ayarlarına bağlıdır. Batarya ADC ölçümü bu firmware sürümünde aktif bir özellik olarak kullanılmamaktadır.

Triyak/röle tarafında şebeke gerilimi bulunabileceğinden test ve kullanım sırasında uygun elektriksel izolasyon ve güvenlik prosedürleri uygulanmalıdır.

## Lisans

MIT License ile yayımlanmıştır.
