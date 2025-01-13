#ifdef USE_AMIITOOL
#include "jswrap_ntag215.h"
#include "jsinteractive.h"
#include "nfc3d/amiibo.h"

/*JSON{
  "type" : "class",
  "class" : "amiitool",
  "ifdef" : "USE_AMIITOOL"
}
Amiitool.
*/

/*JSON{
  "type" : "staticmethod",
  "class" : "amiitool",
  "name" : "unpack",
  "generate" : "jswrap_amiitool_unpack",
  "ifdef" : "USE_AMIITOOL",
  "params" : [
    ["key","JsVar","A UInt8Array containing the contents of key_retail.bin."],
    ["data","JsVar","A UInt8Array containing the encrypted tag data."]
  ],
  "return" : ["bool", "If the hmac hash matched."]
}*/
bool jswrap_amiitool_unpack(JsVar *key, JsVar *data){
  if (!jsvIsArrayBuffer(key)) {
    jsExceptionHere(JSET_ERROR, "Key is not an array buffer.");
    return;
  }

  if (!jsvIsArrayBuffer(data)) {
    jsExceptionHere(JSET_ERROR, "Data is not an array buffer.");
    return;
  }

  size_t keyLength=0;
  char *keyPointer = jsvGetDataPointer(key, &keyLength);

  if (keyPointer == 0) {
    jsExceptionHere(JSET_ERROR, "Failed to get flat string from key array.");
    return;
  }

  size_t dataLength=0;
  char *dataPointer = jsvGetDataPointer(data, &dataLength);

  if (dataPointer == 0) {
    jsExceptionHere(JSET_ERROR, "Failed to get flat string from data array.");
    return;
  }

  if (dataLength < NFC3D_AMIIBO_SIZE) {
    jsExceptionHere(JSET_ERROR, "Data is not at least 520 bytes");
  }

  char newData[NFC3D_AMIIBO_SIZE];

  bool unpack_ret = nfc3d_amiibo_unpack(keyPointer, dataPointer, &newData[0]);

  memcpy(dataPointer, &newData[0], NFC3D_AMIIBO_SIZE);

  return unpack_ret == true;
}

/*JSON{
  "type" : "staticmethod",
  "class" : "amiitool",
  "name" : "pack",
  "generate" : "jswrap_amiitool_pack",
  "ifdef" : "USE_AMIITOOL",
  "params" : [
    ["key","JsVar","A UInt8Array containing the contents of key_retail.bin."],
    ["data","JsVar","A UInt8Array containing the decrypted tag data."]
  ]
}*/
void jswrap_amiitool_pack(JsVar *key, JsVar *data){
  if (!jsvIsArrayBuffer(key)) {
    jsExceptionHere(JSET_ERROR, "Key is not an array buffer.");
    return;
  }

  if (!jsvIsArrayBuffer(data)) {
    jsExceptionHere(JSET_ERROR, "Data is not an array buffer.");
    return;
  }

  size_t keyLength=0;
  char *keyPointer = jsvGetDataPointer(key, &keyLength);

  if (keyPointer == 0) {
    jsExceptionHere(JSET_ERROR, "Failed to get flat string from key array.");
    return;
  }

  size_t dataLength=0;
  char *dataPointer = jsvGetDataPointer(data, &dataLength);

  if (dataPointer == 0) {
    jsExceptionHere(JSET_ERROR, "Failed to get flat string from data array.");
    return;
  }

  if (dataLength < NFC3D_AMIIBO_SIZE) {
    jsExceptionHere(JSET_ERROR, "Data is not at least 520 bytes");
  }

  char newData[NFC3D_AMIIBO_SIZE];

  nfc3d_amiibo_pack(keyPointer, dataPointer, &newData[0]);

  memcpy(dataPointer, &newData[0], NFC3D_AMIIBO_SIZE);
}

/*JSON{
  "type" : "staticmethod",
  "class" : "amiitool",
  "name" : "internalToTag",
  "generate" : "jswrap_amiitool_internal_to_tag",
  "ifdef" : "USE_AMIITOOL",
  "params" : [
    ["data","JsVar","A UInt8Array containing the data."]
  ]
}*/
void jswrap_amiitool_internal_to_tag(JsVar *data){
  if (!jsvIsArrayBuffer(data)) {
    jsExceptionHere(JSET_ERROR, "Data is not an array buffer.");
    return;
  }

  size_t dataLength=0;
  char *dataPointer = jsvGetDataPointer(data, &dataLength);

  if (dataPointer == 0) {
    jsExceptionHere(JSET_ERROR, "Failed to get flat string from data array.");
    return;
  }

  if (dataLength < NFC3D_AMIIBO_SIZE) {
    jsExceptionHere(JSET_ERROR, "Data is not at least 520 bytes");
  }

  char newData[NFC3D_AMIIBO_SIZE];

  nfc3d_amiibo_internal_to_tag(dataPointer, &newData[0]);

  memcpy(dataPointer, &newData[0], NFC3D_AMIIBO_SIZE);
}

/*JSON{
  "type" : "staticmethod",
  "class" : "amiitool",
  "name" : "tagToInternal",
  "generate" : "jswrap_amiitool_tag_to_internal",
  "ifdef" : "USE_AMIITOOL",
  "params" : [
    ["data","JsVar","A UInt8Array containing the data."]
  ]
}*/
void jswrap_amiitool_tag_to_internal(JsVar *data){
  if (!jsvIsArrayBuffer(data)) {
    jsExceptionHere(JSET_ERROR, "Data is not an array buffer.");
    return;
  }

  size_t dataLength=0;
  char *dataPointer = jsvGetDataPointer(data, &dataLength);

  if (dataPointer == 0) {
    jsExceptionHere(JSET_ERROR, "Failed to get flat string from data array.");
    return;
  }

  if (dataLength < NFC3D_AMIIBO_SIZE) {
    jsExceptionHere(JSET_ERROR, "Data is not at least 520 bytes");
  }

  char newData[NFC3D_AMIIBO_SIZE];

  nfc3d_amiibo_tag_to_internal(dataPointer, &newData[0]);

  memcpy(dataPointer, &newData[0], NFC3D_AMIIBO_SIZE);
}
#endif

//bool nfc3d_amiibo_unpack(const nfc3d_amiibo_keys * amiiboKeys, const uint8_t * tag, uint8_t * plain);
//void nfc3d_amiibo_pack(const nfc3d_amiibo_keys * amiiboKeys, const uint8_t * plain, uint8_t * tag);
