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

#ifndef BLUEZ5DEVICE_H
#define BLUEZ5DEVICE_H

#include <string>
#include <bluetooth-sil-api.h>

extern "C" {
#include "freedesktop-interface.h"
#include "bluez-interface.h"
}

class Bluez5Adapter;

class Bluez5Device
{
public:
	Bluez5Device(Bluez5Adapter *adapter, const std::string &objectPath);
	~Bluez5Device();

	void pair(BluetoothResultCallback callback);
	void unpair(BluetoothResultCallback callback);
	void cancelPairing(BluetoothResultCallback callback);

	void connect(const std::string& uuid, BluetoothResultCallback callback);
	void disconnect(const std::string &uuid, BluetoothResultCallback callback);
	void connect(BluetoothResultCallback callback);
	void disconnect(BluetoothResultCallback callback);
	void connectGatt(BluetoothResultCallback callback);

	std::string getObjectPath() const;

	std::string getName() const;
	std::string getAddress() const;
	uint32_t getClassOfDevice() const;
	BluetoothDeviceType getType() const;
	std::vector<std::string> getUuids() const;
	bool getConnected() const;
	Bluez5Adapter* getAdapter() const;

	BluetoothPropertiesList buildPropertiesList() const;

	static void handlePropertiesChanged(BluezDevice1 *, gchar *interface,  GVariant *changedProperties,
									GVariant *invalidatedProperties, gpointer userData);

	void setPaired (bool paired) { mPaired = paired; }
	bool setDevicePropertySync(const BluetoothProperty& property);
	void setDevicePropertyAsync(const BluetoothProperty& property, BluetoothResultCallback callback);

private:
	bool parsePropertyFromVariant(const std::string &key, GVariant *valueVar);
	GVariant* devPropertyValueToVariant(const BluetoothProperty& property);
	std::string devPropertyTypeToString(BluetoothProperty::Type type);

private:
	Bluez5Adapter *mAdapter;
	std::string mName;
	std::string mAlias;
	std::string mAddress;
	std::string mObjectPath;
	uint32_t mClassOfDevice;
	BluetoothDeviceType mType;
	std::vector<std::string> mUuids;
	std::vector <std::uint8_t> mManufacturerData;
	bool mPaired;
	BluezDevice1 *mDeviceProxy;
	FreeDesktopDBusProperties *mPropertiesProxy;
	bool mConnected;
	bool mTrusted;
	bool mBlocked;
	int mTxPower;
	int mRSSI;
};

#endif // BLUEZ5DEVICE_H
