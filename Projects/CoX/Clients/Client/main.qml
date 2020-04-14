import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Window 2.13
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import QtMultimedia 5.13

ApplicationWindow {
    id: segs_client
    visible: true
    width: 1024
    height: 768
    minimumWidth: 800
    minimumHeight: 600
    title: qsTr("SEGS Client")

    FontLoader {
        id: core_font
        source: "resources/fonts/cantarell-bold.otf"
        onStatusChanged: if (core_font.status == FontLoader.Ready) console.log('Loaded Core Font')
    }

    FontLoader {
        id: header_font
        source: "resources/fonts/cuppajoe-regular.otf"
        onStatusChanged: if (header_font.status == FontLoader.Ready) console.log('Loaded Header Font')
    }

    Audio {
        id: login_music
        source: "resources/music/menu_loop.ogg"
        audioRole: GameRole
        autoLoad: true
        autoPlay: true
        loops: Infinite
        volume: 0.65
    }

    Audio {
        id: good_button_sfx
        source: "resources/sfx/run.ogg"
        audioRole: SonificationRole
    }

    Audio {
        id: bad_button_sfx
        source: "resources/sfx/zone_border.ogg"
        audioRole: SonificationRole
    }

    Audio {
        id: info_button_sfx
        source: "resources/sfx/computer.ogg"
        audioRole: SonificationRole
    }

    background: Image {
        source: "resources/images/login-bg.png"
    }

    palette {
        windowText: "#F1F1F1" // since we're on a colored background
        highlight: "SteelBlue"
        dark: "SteelBlue" // reverse because we're on a dark bg
        base: "#333333"
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
            color: "#F1F1F1"
            text: qsTr("Account Name:")
            verticalAlignment: Text.AlignBottom
            font.family: header_font.name
            font.pointSize: 18
            Layout.fillWidth: true
            Layout.topMargin: 8

            layer.enabled: true
            layer.effect: DropShadow {
                anchors.fill: login_username_label
                source: login_username_label
                color: "#AA4682B4"
                radius: 0
                transparentBorder: true
                horizontalOffset: 2
                verticalOffset: 2
            }
        }

        TextField {
            id: login_username
            text: qsTr("")
            placeholderText: "Username"
            font.family: core_font.name
            font.pointSize: 12
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
                color: login_username.activeFocus ? "#F1F1F1" : "#E1E1E1"
                border.width: login_username.activeFocus ? 2 : 1
                border.color: login_username.activeFocus ? login_username.palette.highlight : login_username.palette.mid
                opacity: 0.5
                radius: 4
            }
        }

        Switch {
            id: login_remember_name
            text: qsTr("Remember Account Name")
            leftPadding: 12
            indicator.scale: parent.scale * 0.75
            Layout.minimumHeight: 10
            font.family: core_font.name
            font.pointSize: 12
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.fillWidth: true
            Layout.maximumHeight: 40
            Layout.preferredHeight: parent.height * 0.1
        }

        Label {
            id: login_password_label
            color: "#F1F1F1"
            text: qsTr("Account Password:")
            verticalAlignment: Text.AlignBottom
            font.family: header_font.name
            font.pointSize: 18
            Layout.fillWidth: true
            Layout.topMargin: 8

            layer.enabled: true
            layer.effect: DropShadow {
                anchors.fill: login_password_label
                source: login_password_label
                color: "#AA4682B4"
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
            font.family: core_font.name
            font.pointSize: 12
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
                color: login_password.activeFocus ? "#F1F1F1" : "#E1E1E1"
                border.width: login_password.activeFocus ? 2 : 1
                border.color: login_password.activeFocus ? login_password.palette.highlight : login_password.palette.mid
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
                font.family: header_font.name
                font.pointSize: 12
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                Layout.preferredWidth: parent.width * 0.4
                Layout.minimumWidth: 50
                padding: 14

                palette {
                    button: "#F24444"
                    buttonText: "#F1F1F1"
                }

                // override base style
                background: Rectangle {
                    implicitWidth: 100
                    implicitHeight: 40
                    color: exit_button.down ? "#F78C8C" : "#F24444"
                    border.color: exit_button.palette.highlight
                    border.width: exit_button.visualFocus ? 2 : 0
                    radius: 6
                }

                onClicked: {
                    bad_button_sfx.play() // this probably doesn't even fire
                    Qt.quit()
                }
            }

            Button {
                id: login_button
                text: qsTr("Login")
                highlighted: true
                font.family: header_font.name
                font.pointSize: 12
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                Layout.preferredWidth: parent.width * 0.4
                Layout.minimumWidth: 50
                padding: 14

                palette {
                    button: "#6BA358"
                    dark: "#6BA358"
                    buttonText: "#F1F1F1"
                }

                // override base style
                background: Rectangle {
                    implicitWidth: 100
                    implicitHeight: 40
                    color: login_button.down ? "#92BF88" : "#6BA358"
                    border.color: login_button.palette.highlight
                    border.width: login_button.visualFocus ? 2 : 0
                    radius: 6
                }

                onClicked: { good_button_sfx.play() }
            }
        }

        Button {
            id: settings_button
            text: qsTr("Settings")
            font.family: header_font.name
            font.pointSize: 12
            Layout.alignment: Qt.AlignCenter | Qt.AlignVCenter
            Layout.preferredWidth: parent.width * 0.75
            Layout.minimumWidth: 50
            Layout.topMargin: 15
            padding: 14

            palette {
                buttonText: "#F1F1F1"
                button: "SteelBlue"
            }

            // override base style
            background: Rectangle {
                implicitWidth: 100
                implicitHeight: 40
                color: settings_button.down ? "LightSteelBlue" : "SteelBlue"
                border.color: settings_button.palette.highlight
                border.width: settings_button.visualFocus ? 2 : 0
                radius: 6
            }

            onClicked: {
                info_button_sfx.play()
                var settings_dialog = Qt.createComponent("SettingsDialog.qml").createObject(segs_client.contentItem, {});
                settings_dialog.show();
            }
        }
    }

    Text {
        id: client_version_string
        text: qsTr("Version String Will Go Here")
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignRight
        anchors.right: parent.right
        anchors.rightMargin: parent.width * 0.07
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        font.family: core_font.name
        font.italic: true
        font.pointSize: 10
        color: "#F1F1F1"
    }

    Component.onCompleted: {
        console.log("Window Loaded Successfully!")
    }
}
