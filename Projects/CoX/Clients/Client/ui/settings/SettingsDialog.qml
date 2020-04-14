import QtQuick 2.13
import QtQuick.Controls 2.13
import QtQuick.Window 2.13
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0

Item {
    id: dialogComponent
    anchors.fill: parent

    // Add a simple animation to fade in the popup
    // let the opacity go from 0 to 1 in 400ms
    PropertyAnimation { target: dialogComponent; property: "opacity";
                                  duration: 400; from: 0; to: 1;
                                  easing.type: Easing.InOutQuad ; running: true }

    // This rectange is the a overlay to partially show the parent through it
    // and clicking outside of the 'dialog' popup will do 'nothing'
    Rectangle {
        anchors.fill: parent
        id: overlay
        color: "#000000"
        opacity: 0.6
        // add a mouse area so that clicks outside
        // the dialog window will not do anything
        MouseArea {
            anchors.fill: parent
        }
    }

    Dialog {
        id: settings_dialog
        title: qsTr("SEGS Client Settings")
        modal: true
        focus: true
        visible: true
        z: 1000
        width: parent.width * 0.5
        height: parent.height * 0.8
        anchors.centerIn: overlay

        background: Rectangle {
            color: "#F1F1F1"
            border.width: 2
            border.color: palette.highlight
            opacity: 0.5
            radius: 4
        }

        DialogButtonBox {
            standardButtons: DialogButtonBox.RestoreDefaults | DialogButtonBox.Save | DialogButtonBox.Cancel

            onAccepted: {
                console.log("Ok clicked")
                settings_dialog.accept()
            }
            onRejected: {
                console.log("Cancel clicked")
                settings_dialog.close()
            }
        }
    }

    Component.onCompleted: visible = true
}
