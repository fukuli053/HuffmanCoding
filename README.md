## Grup elemanları
 Furkan ERGÜN - b181210091
 Ahmet Selim ÖZTÜRK - g181210082
 Berkay ÖZDAĞ - b191210051


## Proje Hakkında Açıklama
 Projemize ilk olarak libfdr kütüphanesini ekleyerek başladık. Daha sonra .kilit adlı json dosyasını okuyup belirli bir formata göre tırnak işaretlerini kaldırdık. Değerleri {key,value}  ya göre JRB ağacına ekleme yaptık. Kelimelerin Huffman algoritmasındaki karşılığını encripted dosyasına yazdırdık. Şifrelenmiş dosyayı da .kilit dosyasına göre çözerek decripted dosyasına çözümlenmiş halini yazdırdık.

## Projemizin çalıştırılması

Gerçekleştirdiğimiz projede:
 - Projeyi derlemek ve kripto isimli çalıştırılabilir dosyayı oluşturmak için:

    `make`
    
 - Derleme esnasında oluşan tüm dosyaları silmek için (*.o, kripto, vb) :
  `make clean`
  
 - Derleme sırasında oluşan dosyaların yanı sıra (.kilit, encripted, decripted, ornek_metin, *txt isimli dosyalar)  var ise hepsini silmek için :
  `make cleanall`
  
 - clean ile temizlemek make ile derlemek ve iki komutuda (-e,- d) sırasıyla çalıştırarak (ornek_metin ) encripted ve decripted dosyaları üretmek için : 
  `make run`
