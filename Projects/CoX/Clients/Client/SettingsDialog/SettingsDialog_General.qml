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
        }

        Label {
            text: qsTr("Slider Control")
        }

        Slider {
            value: 0.65
        }

        Label {
            text: qsTr("ComboBox Control")
        }

        ComboBox {
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
        }

        Label {
            text: qsTr("Radio Buttons")
        }

        RadioButton {
            checked: true
            text: qsTr("First")
        }
        RadioButton {
            text: qsTr("Second")
        }
        RadioButton {
            text: qsTr("Third")
        }

        Label {
            text: qsTr("Spin Box")
        }

        SpinBox {
            value: 3
        }

        Label {
            text: qsTr("Dial Control")
        }

        Dial {
            value: 0.65
        }

        Label {
            text: qsTr("Progress")
        }

        ProgressBar {
            value: 0.5
        }

        Button {
            text: qsTr("Button")
        }
    }
}
