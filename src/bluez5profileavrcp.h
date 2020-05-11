// Copyright (c) 2018-2020 LG Electronics, Inc.
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

#ifndef BLUEZ5PROFILEAVRCP_H
#define BLUEZ5PROFILEAVRCP_H

#include <bluetooth-sil-api.h>
#include <bluez5profilebase.h>
#include <string>

extern "C" {
#include "freedesktop-interface.h"
#include "bluez-interface.h"
}

/* AVRCP features */
#define REMOTE_DEVICE_AVRCP_FEATURE_NONE			0x00
#define REMOTE_DEVICE_AVRCP_FEATURE_METADATA		0x01
#define REMOTE_DEVICE_AVRCP_FEATURE_ABSOLUTE_VOLUME	0x02
#define REMOTE_DEVICE_AVRCP_FEATURE_BROWSE		0x04

class Bluez5Adapter;

typedef gboolean (* bluezSendPassThroughCommand)(
		BluezMediaPlayer1 *proxy,
		GCancellable *cancellable,
		GError **error);

class Bluez5ProfileAvcrp : public Bluez5ProfileBase,
                      public BluetoothAvrcpProfile
{
public:
	static const std::map <std::string, BluetoothAvrcpPassThroughKeyCode> mKeyMap;
	static const std::map<BluetoothAvrcpPassThroughKeyCode, bluezSendPassThroughCommand> mPassThroughCmd;
	static const std::map<std::string, BluetoothMediaPlayStatus::MediaPlayStatus> mPlayStatus;
	Bluez5ProfileAvcrp(Bluez5Adapter* adapter);
	~Bluez5ProfileAvcrp();
	void connect(const std::string& address, BluetoothResultCallback callback) override;
	static void handleBluezServiceStarted(GDBusConnection* conn, const gchar* name, const gchar* nameOwner, gpointer user_data);
	static void handleBluezServiceStopped(GDBusConnection* conn, const gchar* name, gpointer user_data);
	static void handleObjectAdded(GDBusObjectManager* objectManager, GDBusObject* object, void* userData);
	static void handleObjectRemoved(GDBusObjectManager* objectManager, GDBusObject* object, void* userData);
	static void handlePropertiesChanged(BluezMediaPlayer1* transportInterface, gchar*,
		GVariant* changedProperties, GVariant* invalidatedProperties, gpointer userData);
	BluetoothPlayerApplicationSettingsRepeat repeatStringToEnum(std::string repeatVal);
	BluetoothPlayerApplicationSettingsShuffle shuffleStringToEnum(std::string shuffleVal);
	BluetoothPlayerApplicationSettingsScan scanStringToEnum(std::string scanVal);
	BluetoothPlayerApplicationSettingsEqualizer equalizerStringToEnum(std::string equalizerVal);
	std::string equalizerEnumToString(BluetoothPlayerApplicationSettingsEqualizer equalizer);
	std::string repeatEnumToString(BluetoothPlayerApplicationSettingsRepeat repeat);
	std::string shuffleEnumToString(BluetoothPlayerApplicationSettingsShuffle shuffle);
	std::string scanEnumToString(BluetoothPlayerApplicationSettingsScan scan);
	void parsePropertyFromVariant(const std::string& key, GVariant* valueVar);
	void disconnect(const std::string& address, BluetoothResultCallback callback) override;
	void enable(const std::string &uuid, BluetoothResultCallback callback) override;
	void disable(const std::string &uuid, BluetoothResultCallback callback) override;
	void getProperties(const std::string &address, BluetoothPropertiesResultCallback  callback) override;
	void getProperty(const std::string &address, BluetoothProperty::Type type, BluetoothPropertyResultCallback callback) override;
	void supplyMediaMetaData(BluetoothAvrcpRequestId requestId, const BluetoothMediaMetaData &metaData, BluetoothResultCallback callback) override;
	void supplyMediaPlayStatus(BluetoothAvrcpRequestId requestId, const BluetoothMediaPlayStatus &playStatus, BluetoothResultCallback callback) override;
	void mediaMetaDataRequested(const std::string &address);
	void mediaPlayStatusRequested(const std::string &address);
	void updateConnectionStatus(const std::string &address, bool status, const std::string &uuid);
	void updateVolume(const std::string &address, int volume);
	void recievePassThroughCommand(std::string address, std::string key, std::string state);
	BluetoothError setAbsoluteVolume(const std::string &address, int volume);
	BluetoothError sendPassThroughCommand(const std::string& address, BluetoothAvrcpPassThroughKeyCode keyCode,
		BluetoothAvrcpPassThroughKeyStatus keyStatus) override;
	void setPlayerApplicationSettingsProperties(const BluetoothPlayerApplicationSettingsPropertiesList &properties,
                BluetoothResultCallback callback) override;
	void updateRemoteFeatures(uint8_t features, const std::string &role, const std::string &address);
	void updateSupportedNotificationEvents(uint16_t notificationEvents, const std::string& address);

private:
	BluetoothAvrcpRequestId generateMetaDataRequestId() { return ++mMetaDataRequestId; }
	BluetoothAvrcpRequestId generateMediaPlayStatusRequestId() { return ++mMediaPlayStatusRequestId; }

private:
	BluetoothAvrcpRequestId mMetaDataRequestId;
	BluetoothAvrcpRequestId mMediaPlayStatusRequestId;
	/* TRUE if connected as controller */
	bool mConnectedController;
	/* TRUE if connected as target */
	bool mConnectedTarget;
	/* TRUE if either of the roles is connected. FALSE if both the roles are disconnected*/
	bool mConnected;
	std::string mConnectedDeviceAddress;
	GDBusObjectManager *mObjectManager;
	BluezMediaPlayer1 *mPlayerInterface;
	FreeDesktopDBusProperties* mPropertiesProxy;
	BluetoothMediaPlayStatus mMediaPlayStatus;
};

#endif
