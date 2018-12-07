// Copyright (c) 2014-2018 LG Electronics, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0

#ifndef BLUEZ5BUSCONFIG_H_
#define BLUEZ5BUSCONFIG_H_

#ifdef USE_SYSTEM_BUS_FOR_OBEX
	#define BLUEZ5_OBEX_DBUS_BUS_TYPE G_BUS_TYPE_SYSTEM
#else
	#define BLUEZ5_OBEX_DBUS_BUS_TYPE G_BUS_TYPE_SESSION
#endif

#endif
