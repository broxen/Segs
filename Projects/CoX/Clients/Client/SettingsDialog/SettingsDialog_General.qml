import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Controls.impl 2.12
import QtQuick.Window 2.13
import QtQuick.Layouts 1.3
import Theme 1.0

ScrollView {
    ScrollBar.vertical.policy: ScrollBar.AsNeeded
    clip: true

    Column {
        spacing: 10
        topPadding: 15
        bottomPadding: 15
        leftPadding: 40
        rightPadding: 40

        Switch {
            text: qsTr("Switch 01")
            indicator.scale: parent.scale * 0.65
            font.family: Theme.core_font.name
            font.pointSize: Theme.textSize
        }

        Label {
            text: qsTr("Slider Control")
            font.family: Theme.core_font.name
            font.pointSize: Theme.textSize
        }

        Slider {
            value: 0.65
        }

        Label {
            text: qsTr("ComboBox Control")
            font.family: Theme.core_font.name
            font.pointSize: Theme.textSize
        }

        ComboBox {
            font.family: Theme.core_font.name
            font.pointSize: Theme.textSize

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
            font.family: Theme.core_font.name
            font.pointSize: Theme.textSize

        }

        Label {
            text: qsTr("Radio Buttons")
            font.family: Theme.core_font.name
            font.pointSize: Theme.textSize
        }

        RadioButton {
            checked: true
            text: qsTr("First")
            font.family: Theme.core_font.name
            font.pointSize: Theme.textSize
        }
        RadioButton {
            text: qsTr("Second")
            font.family: Theme.core_font.name
            font.pointSize: Theme.textSize
        }
        RadioButton {
            text: qsTr("Third")
            font.family: Theme.core_font.name
            font.pointSize: Theme.textSize
        }

        Label {
            text: qsTr("Spin Box")
            font.family: Theme.core_font.name
            font.pointSize: Theme.textSize
        }

        SpinBox {
            value: 3
            font.family: Theme.core_font.name
            font.pointSize: Theme.textSize
        }

        Label {
            text: qsTr("Dial Control")
            font.family: Theme.core_font.name
            font.pointSize: Theme.textSize
        }

        Dial {
            value: 0.65
            font.family: Theme.core_font.name
            font.pointSize: Theme.textSize
        }

        Label {
            text: qsTr("Progress")
            font.family: Theme.core_font.name
            font.pointSize: Theme.textSize
        }

        ProgressBar {
            value: 0.5
            font.family: Theme.core_font.name
            font.pointSize: Theme.textSize
        }

        Button {
            text: qsTr("Button")
            font.family: Theme.core_font.name
            font.pointSize: Theme.textSize
        }
    }
}
