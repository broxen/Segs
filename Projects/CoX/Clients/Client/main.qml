import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Controls.impl 2.12
import QtQuick.Window 2.13
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import QtMultimedia 5.13
import Theme 1.0
import SettingsDialog 1.0

ApplicationWindow {
    id: segs_client
    visible: true
    width: 1024
    height: 768
    minimumWidth: 800
    minimumHeight: 600
    title: qsTr("SEGS Client")

    background: Image {
        source: "./Resources/images/login-bg.png"
    }

    // TODO: create custom Theme
    font.family: Theme.core_font.name
    font.pointSize: Theme.textSize
    palette {
        alternateBase:      Theme.alternateBase
        base:               Theme.base
        brightText:         Theme.brightText
        button:             Theme.button
        buttonText:         Theme.buttonText
        dark:               Theme.dark
        highlight:          Theme.highlight
        highlightedText:    Theme.highlightedText
        light:              Theme.light
        link:               Theme.link
        linkVisited:        Theme.linkVisited
        mid:                Theme.mid
        midlight:           Theme.midlight
        shadow:             Theme.shadow
        text:               Theme.text
        toolTipBase:        Theme.toolTipBase
        toolTipText:        Theme.toolTipText
        window:             Theme.window
        windowText:         Theme.windowText
    }

    ColumnLayout {
        id: login_form_controls
        Layout.minimumWidth: 400
        Layout.minimumHeight: 400
        Layout.preferredWidth: parent.width * 0.25
        Layout.preferredHeight: parent.height * 0.5
        width: parent.width * 0.25
        height: parent.height * 0.5
        anchors.right: parent.right
        anchors.rightMargin: parent.width * 0.07
        anchors.verticalCenter: parent.verticalCenter
        spacing: 6

        Label {
            id: login_username_label
            text: qsTr("Account Name:")
            verticalAlignment: Text.AlignBottom
            font.family: Theme.header_font.name
            font.pointSize: Theme.headerTextSize
            Layout.fillWidth: true
            Layout.topMargin: 8

            layer.enabled: true
            layer.effect: DropShadow {
                source: login_username_label
                color: Theme.headerDropShadow
                radius: 0
                transparentBorder: true
                horizontalOffset: 2
                verticalOffset: 2
            }
        }

        TextField {
            id: login_username
            text: qsTr(LoginSystem.username)
            placeholderText: "Username"
            selectByMouse: true
            font.pointSize: Theme.loginControlTextSize
            implicitWidth: parent.width
            implicitHeight: 45
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.fillWidth: true
            Layout.preferredHeight: 45
            Layout.minimumHeight: 40
            padding: 10
            leftPadding: 12
            clip: true

            // override base style
            background: Rectangle {
                Layout.fillHeight: true
                Layout.fillWidth: true
                color: parent.activeFocus ? "#F1F1F1" : "#E1E1E1"
                border.width: parent.activeFocus ? 2 : 1
                border.color: parent.activeFocus ? parent.palette.highlight : parent.palette.mid
                opacity: 0.5
                radius: 4
            }
        }

        Switch {
            id: login_remember_name
            text: qsTr("Remember Account Name")
            leftPadding: 12
            indicator.scale: parent.scale * 0.65
            Layout.minimumHeight: 10
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.fillWidth: true
            Layout.maximumHeight: 40
            Layout.preferredHeight: parent.height * 0.1
            checked: LoginSystem.remember_username
        }

        Label {
            id: login_password_label
            text: qsTr("Account Password:")
            verticalAlignment: Text.AlignBottom
            font.family: Theme.header_font.name
            font.pointSize: Theme.headerTextSize
            Layout.fillWidth: true
            Layout.topMargin: 8

            layer.enabled: true
            layer.effect: DropShadow {
                source: login_password_label
                color: Theme.headerDropShadow
                radius: 0
                transparentBorder: true
                horizontalOffset: 2
                verticalOffset: 2
            }
        }

        TextField {
            id: login_password
            text: qsTr("")
            placeholderText: "Password"
            font.pointSize: Theme.loginControlTextSize
            echoMode: TextInput.Password
            implicitWidth: parent.width
            implicitHeight: 45
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.fillWidth: true
            Layout.preferredHeight: 45
            Layout.minimumHeight: 40
            padding: 10
            leftPadding: 12
            clip: true

            // override base style
            background: Rectangle {
                Layout.fillHeight: true
                Layout.fillWidth: true
                color: parent.activeFocus ? "#F1F1F1" : "#E1E1E1"
                border.width: parent.activeFocus ? 2 : 1
                border.color: parent.activeFocus ? parent.palette.highlight : parent.palette.mid
                opacity: 0.5
                radius: 4
            }
        }

        RowLayout {
            spacing: parent.width * 0.2
            Layout.minimumHeight: 30
            Layout.maximumHeight: 60
            Layout.preferredHeight: parent.height * 0.15
            Layout.topMargin: 15

            Button {
                id: exit_button
                text: qsTr("Exit")
                font.family: Theme.header_font.name
                font.pointSize: Theme.loginButtonTextSize
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                Layout.preferredWidth: parent.width * 0.4
                Layout.minimumWidth: 50
                padding: 10

                // override base style
                background: Rectangle {
                    implicitWidth: 100
                    implicitHeight: 40
                    visible: !parent.flat || parent.down || parent.checked || parent.highlighted
                    color: Color.blend(parent.checked || parent.highlighted ? Qt.tint(Theme.accentRed, "#22FFFFFF") : Theme.accentRed,
                                                                                        Qt.tint(Theme.accentRed, "#66000000"), parent.down ? 0.5 : 0.0)
                    border.color: parent.palette.highlight
                    border.width: parent.visualFocus ? 2 : 0
                    radius: 4
                }

                onClicked: {
                    Qt.quit()
                }
            }

            Button {
                id: login_button
                text: qsTr("Login")
                highlighted: true
                font.family: Theme.header_font.name
                font.pointSize: Theme.loginButtonTextSize
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                Layout.preferredWidth: parent.width * 0.4
                Layout.minimumWidth: 50
                padding: 10

                enabled: login_username.text && login_password.text ? true : false

                // override base style
                background: Rectangle {
                    implicitWidth: 100
                    implicitHeight: 40
                    visible: !parent.flat || parent.down || parent.checked || parent.highlighted
                    color: enabled ? Color.blend(parent.checked || parent.highlighted ? Qt.tint(Theme.accentGreen, "#22FFFFFF") : Theme.accentGreen,
                                                                                        Qt.tint(Theme.accentGreen, "#66000000"), parent.down ? 0.5 : 0.0) : Theme.disabledGreen
                    border.color: parent.palette.highlight
                    border.width: parent.visualFocus ? 2 : 0
                    radius: 4
                }

                onClicked: {
                    Theme.good_button_sfx.play()
                    LoginSystem.submitLoginInfo(login_username.text.toString(), login_password.text.toString())
                }
            }
        }

        Button {
            id: settings_button
            text: qsTr("Settings")
            font.family: Theme.header_font.name
            font.pointSize: Theme.loginButtonTextSize
            Layout.alignment: Qt.AlignCenter | Qt.AlignVCenter
            Layout.preferredWidth: parent.width * 0.75
            Layout.minimumWidth: 50
            Layout.topMargin: 15
            padding: 10

            // override base style
            background: Rectangle {
                implicitWidth: 100
                implicitHeight: 40
                visible: !parent.flat || parent.down || parent.checked || parent.highlighted
                color: Color.blend(parent.checked || parent.highlighted ? Qt.tint(Theme.button, "#22FFFFFF") : Theme.button,
                                                                                    Qt.tint(Theme.button, "#66000000"), parent.down ? 0.5 : 0.0)
                border.color: parent.palette.highlight
                border.width: parent.visualFocus ? 2 : 0
                radius: 4
            }

            onClicked: {
                Theme.info_button_sfx.play()
                settings_dialog.open()
            }
        }
    }

    Text {
        id: client_version_string
        color: palette.windowText
        text: qsTr(LoginSystem.version_string)
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignRight
        anchors.right: parent.right
        anchors.rightMargin: parent.width * 0.07
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        font.italic: true
    }

    // load our Settings Dialog Drawer for use later
    SettingsDialog {
        id: settings_dialog
    }

    Component.onCompleted: {
        console.log("Window Loaded Successfully!")
    }
}
