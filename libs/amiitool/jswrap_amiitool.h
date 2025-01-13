#ifdef USE_AMIITOOL
#include <stdint.h>
#include <stdbool.h>
#include "jsinteractive.h"

bool jswrap_amiitool_unpack(JsVar *, JsVar *);
void jswrap_amiitool_pack(JsVar *, JsVar *);
void jswrap_amiitool_internal_to_tag(JsVar *);
void jswrap_amiitool_tag_to_internal(JsVar *);
#endif
