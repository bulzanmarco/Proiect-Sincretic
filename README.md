**1. Se va realiza un sistem de conducere pe bază de microcontroller și tehnologii Cloud (Azure for Students) care va efectua următoarele funcții:**

- Citirea temperaturii sistemului de la distanță.

- Controlul luminilor LED de la distanță.

- Transmiterea mesajelor prin internet către sistem.

- Detecția și alertarea inundațiilor.

**2. Interfața web**

- Sistemul va dispune de o interfață web ce va afișa temperatura curentă (citită de la un senzor LM35).

- Va oferi posibilitatea de transmitere a unui mesaj către sistem (Cloud -> micro-controller).

- Interfața va dispune de un buton de tip ON/OFF pentru controlul unui LED conecta la micro-controller.

- Evenimentele de tip inundație vor fi transmise prin e-mail la o adresa prestabilită

**3. Dezvoltarea Software**

- Se vor stoca în memoria nevolatilă ultimele 10 mesaje primite din Cloud.

- Se vor stoca în memoria nevolatilă datele ultimelor 10 evenimente de tip inundație.

- Pentru conectarea la internet a sistemului se poate folosi o comunicație serială cu un PC sau o conexiune Wi-Fi/Ethernet/3G.

- Se pot folosi orice librării open-source.

- Proiectul va avea un repository GitHub 

**4.Teme opționale**

- Reglarea temperaturii de la distanță. Regulator format din senzorul de temperatură și sursă de căldură controlată prin PWM.

- Stabilirea unui orar zilnic de funcționare din interfața web pentru luminile LED.
