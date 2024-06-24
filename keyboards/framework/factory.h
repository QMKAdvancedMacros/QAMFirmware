// Copyright 2023 Framework Computer
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

void enable_factory_mode(bool enable);

#ifndef VIA_ENABLE
extern void handle_macro_hid(uint8_t *data, uint8_t length);
#endif
