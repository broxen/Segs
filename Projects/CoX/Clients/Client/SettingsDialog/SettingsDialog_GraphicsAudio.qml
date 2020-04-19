import QtQuick 2.13
import QtQuick.Controls 2.13
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

        // TODO: settings for Graphics & Audio
        Label {
            text: qsTr("Settings for Graphics & Audio will go here...")
        }
    }
}
