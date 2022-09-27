#include <pgmspace.h>
 
#define SECRET
#define THINGNAME "P10_Display"                         //change this
 
const char WIFI_SSID[] = "Embedded";               //change this
const char WIFI_PASSWORD[] = "1234567890@";           //change this
const char AWS_IOT_ENDPOINT[] = "a3sepl9yw0mx23-ats.iot.us-east-2.amazonaws.com";       //change this
 
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
 
// Device Certificate                                               //change this
static const char AWS_CERT_CRT[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
MIIDWjCCAkKgAwIBAgIVAJ+J0IgYEEdG2nk+Np7kydp23tWNMA0GCSqGSIb3DQEB
CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t
IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0yMjA2MzAwNjU2
MjVaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh
dGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQCv93Llpx+5RRhYaZZk
NnO84s++MPyE6Zizhjq3NA2a/YUmzRv7pMk0YwyQcQCkQ7dGsYJDJIKNdN5nEIgB
7tF/hfQEXf6QFQhkkkYjDtF5QA+qfFF87nhXEUkSxdcjmlSzJ4XD+sRZG12JOiVN
tO4MeX2JbE9LppIUvqsKy4EkDluEEIyKaOwrQpScGniAdHg/z2NL3unuuAzJnRZ+
WFcYkmcLhxudg62io87YAqOviD7zE15YqjlixXygWiR17RnQRPFO3bqxsRH9z9dH
2IxK2gtPeebf8GQIeLDqhHvvS9nNfPUv3kjOOVk9BNv2WIEQz8BSVBrPIw3vdoZz
OWsDAgMBAAGjYDBeMB8GA1UdIwQYMBaAFKid8hZpOQoFuvvIdhc6+1fTqLL1MB0G
A1UdDgQWBBRVkues8f5PddHJydprcLaM3iNCkTAMBgNVHRMBAf8EAjAAMA4GA1Ud
DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEAZ9jXEeQ+U+8ZUYyrtztzZ8KR
16NqGZZAbvGWml/g9Cml1XLAMQ+iVXEhD7VGdROYfDcl21caOds8KXk0vpPsLm52
PAHUEwPF5VwWfq/u8FDunbaJVRTw4GfDkhx+ibq9tJGQoEBsburpgsVTWudb0SCe
FdI3MR8ayDqhIQvHbhZmx9x1ug2Fziou5QIyW1Oi2mvlK9qvK2t/7fXRbCtN1ffC
GcnNEb05Vo/nXftrcA5CWPrrrwiFViA78OWiBlm9bIriYVOMk0bggiSBLLUx01XV
0Eui7SOYK30M8wZhaAGB+gwhuT1t7Py/RDjWMiGS2Q8M8Blt1qtUYG6bUll2BA==
-----END CERTIFICATE-----
 
 
)KEY";
 
// Device Private Key                                               //change this
static const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
MIIEpAIBAAKCAQEAr/dy5acfuUUYWGmWZDZzvOLPvjD8hOmYs4Y6tzQNmv2FJs0b
+6TJNGMMkHEApEO3RrGCQySCjXTeZxCIAe7Rf4X0BF3+kBUIZJJGIw7ReUAPqnxR
fO54VxFJEsXXI5pUsyeFw/rEWRtdiTolTbTuDHl9iWxPS6aSFL6rCsuBJA5bhBCM
imjsK0KUnBp4gHR4P89jS97p7rgMyZ0WflhXGJJnC4cbnYOtoqPO2AKjr4g+8xNe
WKo5YsV8oFokde0Z0ETxTt26sbER/c/XR9iMStoLT3nm3/BkCHiw6oR770vZzXz1
L95IzjlZPQTb9liBEM/AUlQazyMN73aGczlrAwIDAQABAoIBAA/YywIfkN3QeSbN
K3wO41FpY6gPJU6a8uOH/RWunGMO3cTmx9RbvLr5CJKheptQddrp9X8ydIdktPq3
JGh4J2nCmH0kMd6r5juYaLSTiw3OVRrXY0dK+o9swRXttzg/l80ijAtgM/qKWlwX
XnCnEKES99k+Zc28TH+NxD2Ooiyq8BmHRQL9OWc48nJpWZNHqtzZMk0cE87LQLDp
zvZp6JuNsPQtLl/vB27qV5WsV/I6uA17ae4HetW40T6zGKdg3xv8vhlfLyjmj0h/
FeIboNdUOiopMUTEBY6rop58/ZfAUBetLhQ9tp9rOS7hU4fVc+x1cia7/W2cRT/y
U33vSQECgYEA2YpDAQVGk0hhxlSRgGNDlhpFtBCwxu90s2QmBXk9QtHL2a6SRHqU
eNSyRx1n26Ma2iDpvRY5u552lQfp61KJZ/HIjUGfxE/MiF8sHd//6XF80hmB+oL7
9Ni96weJeeY4ArQx8wDVCbxl1dd0HaTU+kvz+t10loXh4FsdbufA48ECgYEAzxOY
V/qrp+V3KIcLh2XrpobeefQHUc3xZH5BBsYWWbMzUKTHnp0ayEhFZWAKW9ibywEH
6NpHKSIZr1DEko6iIkKaJHV1znk9n0LttKtb71I/Z0IkMM+VKyTrux/PMhAbvcSo
A/GgPbgiFTgsRNFXS1lQxVyp5eXD35TjDJpbr8MCgYBz+l6WoLVruF9IWbXo+QMD
d6ZJxcw5g1h4e6A5stWSVj+UIpogoCmf8eXKPEcutdqPCJUVFlBZUrZt5fY0W6Ce
Ji2CAcan5tNosTTYCKBrWPHvIWJGqKajdxppv27v6mlaJ6+pmnv54NN6Go/xbfuO
JghBaufJiD9QWcNraWtRAQKBgQC1CM2EBPszEnJFNSMIITuOX5R6i7QmeWRTVell
kaISk48GLrjx2ymB9WTuBrOnrkwtgt42XTYfKNfJpFPmSNpIF3AI9cOjWe1cobeM
3s7GAGK71GAtaB1iFaoc8udCPkDye83jfMd5jdQGNxDErTui/ReXI7bI7UF74v9I
kl4b3wKBgQC2Q6DscUvN9ZcEScJiHb2L3JWOVjGZmNBRvDoYvgXt3J+wFTjF0poO
kbUMSC5nAByRxw8g169lg7Dmlq5bNDphd+/VvXf6v901ARA2ot+N1xEGmv/thJB6
VTRCuX0YoJY+gCyMfR+0tzcv8adt3dqFJA1RwpfqZIXBNv/Rsoe3hg==
-----END RSA PRIVATE KEY-----
 
 
)KEY";