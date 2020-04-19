import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Controls.impl 2.12
import QtQuick.Window 2.13
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import Theme 1.0

Drawer {
    id: settings_dialog
    objectName: "settingsDialog"
    modal: true
    focus: true
    width: overlay.width * 0.85
    height: overlay.height
    padding: 30

    background: Rectangle {
        color: palette.toolTipBase
    }

    ColumnLayout {
        width: parent.width
        height: parent.height
        spacing: 16

        Label {
            id: settings_title
            text: qsTr("SEGS Client Settings")
            Layout.fillWidth: true
            padding: 15
            verticalAlignment: Text.AlignBottom
            font.family: Theme.header_font.name
            font.pointSize: Theme.headerTextSize

            layer.enabled: true
            layer.effect: DropShadow {
                source: settings_title
                color: Theme.headerDropShadow
                radius: 0
                transparentBorder: true
                horizontalOffset: 2
                verticalOffset: 2
            }
        }

        TabBar {
            id: settings_tab_bar
            Layout.fillWidth: true

            TabButton {
                text: qsTr("General")
                font.family: Theme.header_font.name
                font.pointSize: Theme.settingsTabTextSize

                background: Rectangle {
                    implicitHeight: 35
                    color: Color.blend(parent.checked ? parent.palette.button : parent.palette.mid,
                                                         parent.palette.highlight, parent.down ? 0.5 : 0.0)
                }
            }
            TabButton {
                text: qsTr("Controls")
                font.family: Theme.header_font.name
                font.pointSize: Theme.settingsTabTextSize

                background: Rectangle {
                    implicitHeight: 35
                    color: Color.blend(parent.checked ? parent.palette.button : parent.palette.mid,
                                                         parent.palette.highlight, parent.down ? 0.5 : 0.0)
                }
            }
            TabButton {
                text: qsTr("Keymapping")
                font.family: Theme.header_font.name
                font.pointSize: Theme.settingsTabTextSize

                background: Rectangle {
                    implicitHeight: 35
                    color: Color.blend(parent.checked ? parent.palette.button : parent.palette.mid,
                                                         parent.palette.highlight, parent.down ? 0.5 : 0.0)
                }
            }
            TabButton {
                text: qsTr("Graphics/Audio")
                font.family: Theme.header_font.name
                font.pointSize: Theme.settingsTabTextSize

                background: Rectangle {
                    implicitHeight: 35
                    color: Color.blend(parent.checked ? parent.palette.button : parent.palette.mid,
                                                         parent.palette.highlight, parent.down ? 0.5 : 0.0)
                }
            }
            TabButton {
                text: qsTr("Windows")
                font.family: Theme.header_font.name
                font.pointSize: Theme.settingsTabTextSize

                background: Rectangle {
                    implicitHeight: 35
                    color: Color.blend(parent.checked ? parent.palette.button : parent.palette.mid,
                                                         parent.palette.highlight, parent.down ? 0.5 : 0.0)
                }
            }
        }

        StackLayout {
            Layout.fillWidth: true
            currentIndex: settings_tab_bar.currentIndex

            // each tab has it's own qml file
            SettingsDialog_General {
                id: settings_general
            }

            SettingsDialog_Controls {
                id: settings_controls
            }

            SettingsDialog_Keymapping {
                id: settings_keymapping
            }

            SettingsDialog_GraphicsAudio {
                id: settings_graphicsaudio
            }

            SettingsDialog_Windows {
                id: settings_windows
            }
        }

        RowLayout {
            id: button_group
            Layout.alignment: Qt.AlignRight | Qt.AlignBottom
            spacing: 15
            Layout.fillWidth: true
            Layout.minimumHeight: 30
            Layout.maximumHeight: 60
            Layout.preferredHeight: 40
            Layout.margins: 15

            Button {
                id: reset_button
                text: qsTr("Reset to Defaults")
                font.family: Theme.header_font.name
                font.pointSize: Theme.settingsButtonTextSize
                Layout.alignment: Qt.AlignLeft
                Layout.minimumWidth: 120
                padding: 8

                // override base style
                background: Rectangle {
                    implicitWidth: 120
                    implicitHeight: 35
                    visible: !parent.flat || parent.down || parent.checked || parent.highlighted
                    color: Color.blend(parent.checked || parent.highlighted ? Qt.tint(Theme.button, "#22FFFFFF") : Theme.button,
                                                                                        Qt.tint(Theme.button, "#66000000"), parent.down ? 0.5 : 0.0)
                    border.color: parent.palette.highlight
                    border.width: parent.visualFocus ? 2 : 0
                    radius: 4
                }

                onClicked: {
                    Theme.info_button_sfx.play() // this probably doesn't even fire
                }
            }

            // silly hack to get buttons to separate without anchor warnings
            // this is because QML tosses out warnings for Row and RowLayouts
            // that use Layouts and anchors with their parents/children
            Item {
                Layout.fillWidth: true
                height: reset_button.implicitHeight
            }

            Button {
                id: cancel_button
                text: qsTr("Cancel")
                font.family: Theme.header_font.name
                font.pointSize: Theme.settingsButtonTextSize
                Layout.alignment: Qt.AlignRight
                Layout.minimumWidth: 100
                padding: 8

                // override base style
                background: Rectangle {
                    implicitWidth: 100
                    implicitHeight: 35
                    visible: !parent.flat || parent.down || parent.checked || parent.highlighted
                    color: Color.blend(parent.checked || parent.highlighted ? Qt.tint(Theme.accentRed, "#22FFFFFF") : Theme.accentRed,
                                                                                        Qt.tint(Theme.accentRed, "#66000000"), parent.down ? 0.5 : 0.0)
                    border.color: parent.palette.highlight
                    border.width: parent.visualFocus ? 2 : 0
                    radius: 4
                }

                onClicked: {
                    Theme.bad_button_sfx.play()
                    settings_dialog.close()
                }
            }

            Button {
                id: save_button
                text: qsTr("Save")
                highlighted: true
                font.family: Theme.header_font.name
                font.pointSize: Theme.settingsButtonTextSize
                Layout.alignment: Qt.AlignRight
                Layout.minimumWidth: 100
                padding: 8

                // override base style
                background: Rectangle {
                    implicitWidth: 100
                    implicitHeight: 35
                    visible: !parent.flat || parent.down || parent.checked || parent.highlighted
                    color: Color.blend(parent.checked || parent.highlighted ? Qt.tint(Theme.accentGreen, "#22FFFFFF") : Theme.accentGreen,
                                                                                        Qt.tint(Theme.accentGreen, "#66000000"), parent.down ? 0.5 : 0.0)
                    border.color: parent.palette.highlight
                    border.width: parent.visualFocus ? 2 : 0
                    radius: 4
                }

                onClicked: {
                    Theme.good_button_sfx.play()
                    settings_dialog.close()
                }
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;height:600;width:600}
}
##^##*/
