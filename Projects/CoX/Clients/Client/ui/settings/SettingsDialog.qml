import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Controls.impl 2.12
import QtQuick.Window 2.13
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0

Drawer {
    id: settings_dialog
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
            font.family: header_font.name
            font.pointSize: 18

            layer.enabled: true
            layer.effect: DropShadow {
                anchors.fill: settings_title
                source: settings_title
                color: "#AA4682B4" // semitransparent steelblue
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
                font.family: header_font.name
                font.pointSize: 11

                background: Rectangle {
                    implicitHeight: 35
                    color: Color.blend(parent.checked ? parent.palette.button : parent.palette.mid,
                                                         parent.palette.highlight, parent.down ? 0.5 : 0.0)
                }
            }
            TabButton {
                text: qsTr("Controls")
                font.family: header_font.name
                font.pointSize: 11

                background: Rectangle {
                    implicitHeight: 35
                    color: Color.blend(parent.checked ? parent.palette.button : parent.palette.mid,
                                                         parent.palette.highlight, parent.down ? 0.5 : 0.0)
                }
            }
            TabButton {
                text: qsTr("Keymapping")
                font.family: header_font.name
                font.pointSize: 11

                background: Rectangle {
                    implicitHeight: 35
                    color: Color.blend(parent.checked ? parent.palette.button : parent.palette.mid,
                                                         parent.palette.highlight, parent.down ? 0.5 : 0.0)
                }
            }
            TabButton {
                text: qsTr("Graphics/Audio")
                font.family: header_font.name
                font.pointSize: 11

                background: Rectangle {
                    implicitHeight: 35
                    color: Color.blend(parent.checked ? parent.palette.button : parent.palette.mid,
                                                         parent.palette.highlight, parent.down ? 0.5 : 0.0)
                }
            }
            TabButton {
                text: qsTr("Windows")
                font.family: header_font.name
                font.pointSize: 11

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

            // TODO: move each tab into individual qml files
            Item {
                id: settings_general

                ScrollView {
                    anchors.fill: parent
                    ScrollBar.vertical.policy: ScrollBar.AlwaysOn
                    clip: true

                    Column {
                        spacing: 10
                        topPadding: 15
                        bottomPadding: 15
                        leftPadding: 40
                        rightPadding: 40

                        Switch {
                            text: qsTr("Settings Option 1")
                            indicator.scale: parent.scale * 0.65
                            font.family: core_font.name
                            font.pointSize: 10
                        }

                        Switch {
                            text: qsTr("Settings Option 2")
                            indicator.scale: parent.scale * 0.65
                            font.family: core_font.name
                            font.pointSize: 10
                        }

                        Label {
                            text: qsTr("Settings Option 3")
                            font.family: core_font.name
                            font.pointSize: 10
                        }

                        Slider {
                            value: 0.65
                            scale: parent.scale * 0.65
                            Layout.minimumHeight: 10
                            Layout.preferredHeight: 40
                        }

                        ComboBox {
                            Layout.minimumHeight: 10
                            Layout.preferredHeight: 40
                            font.family: core_font.name
                            font.pointSize: 10

                            model: ListModel {
                                ListElement { text: "Banana" }
                                ListElement { text: "Apple" }
                                ListElement { text: "Coconut" }
                                ListElement { text: "Orange" }
                                ListElement { text: "Pineapple" }
                                ListElement { text: "Plum" }
                            }
                        }

                        CheckBox {
                            text: qsTr("Check Box")
                            font.family: core_font.name
                            font.pointSize: 10

                        }

                        RadioButton {
                            checked: true
                            text: qsTr("First")
                            font.family: core_font.name
                            font.pointSize: 10
                        }
                        RadioButton {
                            text: qsTr("Second")
                            font.family: core_font.name
                            font.pointSize: 10
                        }
                        RadioButton {
                            text: qsTr("Third")
                            font.family: core_font.name
                            font.pointSize: 10
                        }

                        SpinBox {
                            value: 3
                            font.family: core_font.name
                            font.pointSize: 10
                        }

                        Dial {
                            scale: 0.5
                            value: 30
                            font.family: core_font.name
                            font.pointSize: 10
                        }

                        ProgressBar {
                            value: 0.5
                            font.family: core_font.name
                            font.pointSize: 10
                        }

                        Button {
                            text: qsTr("Button")
                            font.family: core_font.name
                            font.pointSize: 10
                        }
                    }
                }
            }
            Item {
                id: settings_controls
                // TODO: settings for controls
                Label {
                    text: qsTr("Settings for Controls will go here...")
                    verticalAlignment: Text.AlignBottom
                    font.family: core_font.name
                    font.pointSize: 10
                    Layout.fillWidth: true
                    Layout.topMargin: 8
                }


            }
            Item {
                id: settings_keymapping
                // TODO: settings for keymappings
                Label {
                    text: qsTr("Settings for Keymaping will go here...")
                    verticalAlignment: Text.AlignBottom
                    font.family: core_font.name
                    font.pointSize: 10
                    Layout.fillWidth: true
                    Layout.topMargin: 8
                }
            }
            Item {
                id: settings_graphicsaudio
                // TODO: settings for graphics and audio
                Label {
                    text: qsTr("Settings for Graphics & Audio will go here...")
                    verticalAlignment: Text.AlignBottom
                    font.family: core_font.name
                    font.pointSize: 10
                    Layout.fillWidth: true
                    Layout.topMargin: 8
                }
            }
            Item {
                id: settings_windows
                // TODO: settings for windows/gui
                Label {
                    text: qsTr("Settings for Windows will go here...")
                    verticalAlignment: Text.AlignBottom
                    font.family: core_font.name
                    font.pointSize: 10
                    Layout.fillWidth: true
                    Layout.topMargin: 8
                }
            }
        }

        Row {
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
                font.family: header_font.name
                font.pointSize: 11
                anchors.left: parent.left
                padding: 8

                palette {
                    button: "#F24444"
                    buttonText: palette.buttonText
                }

                // override base style
                background: Rectangle {
                    implicitWidth: 40
                    implicitHeight: 35
                    color: cancel_button.down ? "#FF7DA7CA" : "SteelBlue"
                    border.color: cancel_button.palette.highlight
                    border.width: cancel_button.visualFocus ? 2 : 0
                    radius: 4
                }

                onClicked: {
                    //info_button_sfx.play() // this probably doesn't even fire
                }
            }

            Button {
                id: cancel_button
                text: qsTr("Cancel")
                font.family: header_font.name
                font.pointSize: 11
                anchors.right: save_button.left
                anchors.rightMargin: 24
                width: 120
                padding: 8

                palette {
                    button: "#F24444"
                    buttonText: palette.buttonText
                }

                // override base style
                background: Rectangle {
                    implicitWidth: 80
                    implicitHeight: 35
                    color: reset_button.down ? "#F78C8C" : "#F24444"
                    border.color: reset_button.palette.highlight
                    border.width: reset_button.visualFocus ? 2 : 0
                    radius: 4
                }

                onClicked: {
                    //bad_button_sfx.play()
                    settings_dialog.close()
                }
            }

            Button {
                id: save_button
                text: qsTr("Save")
                highlighted: true
                font.family: header_font.name
                font.pointSize: 11
                anchors.right: parent.right
                width: 120
                padding: 8
                icon.name: document-save

                palette {
                    button: "#6BA358"
                    dark: "#6BA358"
                    buttonText: palette.buttonText
                }

                // override base style
                background: Rectangle {
                    implicitWidth: 40
                    implicitHeight: 35
                    color: save_button.down ? "#92BF88" : "#6BA358"
                    border.color: save_button.palette.highlight
                    border.width: save_button.visualFocus ? 2 : 0
                    radius: 4
                }

                onClicked: {
                    //good_button_sfx.play()
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
