
#pragma once

#include <stddef.h>
#include "esp_err.h"

esp_err_t LogHistory_init(void);
void LogHistory_disable(void);
void LogHistory_dump(void);
