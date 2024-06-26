#include <pgmspace.h>

#define SECRET
#define THINGNAME "prototype_iot"

const char WIFI_SSID[] = "ochomovil";
const char WIFI_PASSWORD[] = "ochoiphone";
const char AWS_IOT_ENDPOINT[] = "a2vduqt2lbdw5l-ats.iot.us-east-1.amazonaws.com";

// Amazon Root CA 1
static const char AWS_CERT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";

// Device Certificate
static const char AWS_CERT_CRT[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
MIIDWjCCAkKgAwIBAgIVAOA4jcFut6/O1BEab8Op20pThg3NMA0GCSqGSIb3DQEB
CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t
IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0yNDA0MjAyMzI2
NDRaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh
dGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDh7p1vziVREDVn8JPm
t1Y66hrF7/s86DjL5TjHtDGT2oTqK2TxYibVH5s0s50vUZlSOzEWQ+Li3I/d7Kc0
i+Ov/W8zZgnUSxcpH2fLtd+ktMVi3RrlqdnUZs8GOt3L0o/tzp1suMKa0yaabPEb
EANry9a+NzfxikXLkxoOBGhvaJwMvQhty0nDWmsMOf/f2uxx+PXnlbwdjm5KraLO
OXN6G/9U5QzENlMItr78w7nVokQIGcdNsSd7ZeYEdHad274M2TIQZjJ0K/BOxDrn
oZLN9AyWJP7ish9ey8yV+Uw6ARZfvlsTLIJ+uXPrOeqmPrgCMin2TIQ3mDAdQ2wF
GYP/AgMBAAGjYDBeMB8GA1UdIwQYMBaAFGMDrwt+DU/Mrla2MLcfOld5zcqIMB0G
A1UdDgQWBBQarzT3da9OKqwHindeI8bVLaIIQTAMBgNVHRMBAf8EAjAAMA4GA1Ud
DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEATxLfpnlvhq9iEUAbLKmUmdzr
beiEV10jUg80FYVXOzqQTdhb3SMY6cs2McH65Vy1TRr/4fD+zpR22i8+X5LWxJvF
rL3UmNytCT+bDAq5i+Dy2S4Q4MUJDnqLbDvj+kvytxjt0u66Ls0CkBvB8mgLAOjv
ao6EVZ+NhbytVxgoVLMARO40yVUGFMPPvKEKOydirXtgpXoeOjYxOaGcGqw1P1sP
yYU9p+jTaHeNfP4TO02Qcuauvw56whxZMTUdjWtZK8mgt/Amf0DVIvIufqq7uclm
76sjrUAtUM5D1x+H9zb4207PCHJ2WIOtoUkTfyiU5ndC8IX061j7/HSjHpN4xw==
-----END CERTIFICATE-----
)KEY";

// Device Private Key
static const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
MIIEpgIBAAKCAQEA4e6db84lURA1Z/CT5rdWOuoaxe/7POg4y+U4x7Qxk9qE6itk
8WIm1R+bNLOdL1GZUjsxFkPi4tyP3eynNIvjr/1vM2YJ1EsXKR9ny7XfpLTFYt0a
5anZ1GbPBjrdy9KP7c6dbLjCmtMmmmzxGxADa8vWvjc38YpFy5MaDgRob2icDL0I
bctJw1prDDn/39rscfj155W8HY5uSq2izjlzehv/VOUMxDZTCLa+/MO51aJECBnH
TbEne2XmBHR2ndu+DNkyEGYydCvwTsQ656GSzfQMliT+4rIfXsvMlflMOgEWX75b
EyyCfrlz6znqpj64AjIp9kyEN5gwHUNsBRmD/wIDAQABAoIBAQC5Z4xRFPVwmYGK
I1XsDmW4AScpae9doyAAysGWuJu6vqc2V5gFsks1uDMww3jpPOg6IBL/N4R4MRHq
x2rLZ0TYxnw7zK+iRGDkQT53YHAABMy6fcG12HXGpPudHC+pNMkiGNz9PH2OelqC
fYY6dCCqlGNMQ5ooIBV4ouXNvPZK/R2RuFp5+AKzX18N2Txeu6lRFxZekS0sYRou
iJLN0X8969joip8LkdiVt/C7NWNd3c2BBzVKUTfM6k956ly4/qAD/PF7B8q99r3c
edYCHe8E4P2CLuyJZfRj3tREJOf1ACyEULLU0B2qUsO6H7ok1azsi8lXUo0/TYoT
sR+yWKIJAoGBAPpIYVuznPalO2sGUBELiarrHAdwrskaIKGgOOremTQjQrolmvBL
qgP8psza8U8sueTwKOkNj6+G38WV6IEeVb/nndnt5eAFqflXCclNxGxLrqP7C23s
m04eQzU5JqyLvLZIdw2kcWTYmLmgI89vxgGojlVJGQrzKQArQcydv4M1AoGBAOcX
1dwApD8x7puBEa7awLn55uC4Fp9TC0rcc6yoWjUz//+w44PhyJ9hNR1o5MONbCHs
SHrkPsLmxYnECuuuZNgAEgF838phl2P4wM49wxQ590tfo9x2re5I0KN+/ooZYIOn
2X8+daU7YvQ4BSxtXEgdsEYpCL6smqsiW6DmoPzjAoGBAJk5WrFDYuL1AU1iTf5B
bATBbyV27OqdHkEU0AOqR2zN8Xn4r8RQ7kMGmC9uErGAFkZ8aO9UqBSzo6dZQUBb
C/AyokbbCBKAJTFLAejFvWz3YHFvre2cHvBSQp8A4BZebifCcXBerjUpDUcHLSU/
rp8xTAIWgEhd2UoLMXtNUAPJAoGBAN61OtYODDwW6+QTTC5eBTR14QoafzrGdnCL
6jKwAFebqJALMggsNQNcVCrmpujKxzYeF2/PvahpbGArfXbKl8cOskuaw7WvvY2L
8owQO4unnWqXXjyeZ1rn86JNRhNjB3956ILXd9toUyIXRu0c671YV0QWUaYog9p/
fxyehvGPAoGBALWcXWLsrBLQBvhjtDJ6h3td0Q5+4r3QDa0TPmoBq2Syy1+kCTyc
bYpB/FHxoz2DAqbFcmlW3dYagLaKEZqmQBSDUTxfrLsq+Ukj3BDDVxAIZHUCEDYD
p2drZbSvv9Gi6Rltwlk/5phP/OVfjKDiJXXkpZO7q9Q/sWQpzulO0Jyl
-----END RSA PRIVATE KEY-----
)KEY";
